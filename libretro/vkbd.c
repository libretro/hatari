/*
 * Hatari libretro - Virtual Keyboard
 * Ported and adapted from PUAE libretro (libretro-vkbd.c)
 * Original: Copyright 2020-2023 PUAE libretro contributors
 * ST layout and adaptation for Hatari
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "libretro.h"
#include "libretro-hatari.h"
#include "libretro-graph.h"
#include "vkbd.h"
#include "vkbd_def.h"

/* Externals from hatari-mapper / libretro.c */
extern unsigned short int bmp[];
extern int retrow, retroh;
extern int CROP_WIDTH;
extern int STATUTON, SHOWKEY, MOUSEMODE;
extern retro_input_state_t input_state_cb;
extern void Screen_SetFullUpdate(void);
extern void texture_init(void);

/* Public state */
bool          vkbd_active    = false;
bool          retro_capslock = false;
signed char   vkbd_ready     = 0;
int           vkflag[10]     = {0};

/* Options */
unsigned int  opt_vkbd_theme = 1;   /* 1=classic beige, 2=dark, 3=light */
unsigned int  opt_vkbd_alpha = 255; /* opacity 0-255 */

/* Internal state */
static bool   vkbd_page      = false;
static int    vkey_pos_x     = 0;
static int    vkey_pos_y     = 0;

static int    vkey_pressed      = -1;
static int    last_vkey_pressed  = -1;
static int    vkey_pressed_hold  = 0;
#define VKEY_PRESS_FRAMES  4   /* hold key for 4 frames ~80ms */
static bool   vkey_sticky    = false;
static int    vkey_sticky1   = -1;
static int    vkey_sticky2   = -1;
static bool   vkey_sticky1_release = false;
static bool   vkey_sticky2_release = false;

static long   vkey_pressed_time  = 0;
static bool   vkey_press_hold    = false;
#define VKEY_HOLD_DELAY  600   /* ms before sticky activates */

/* Pointer/touch state */
static int    last_pointer_x  = 0;
static int    last_pointer_y  = 0;
static int    last_pointer_p  = 0;
static bool   pointer_active  = false;
static int    vkbd_x_min = 0, vkbd_x_max = 0;
static int    vkbd_y_min = 0, vkbd_y_max = 0;

/* Forward declarations */
static void st_key_down(int scancode);
static void st_key_up(int scancode);

/* Drawing via libretro-graph.c */

/* ------------------------------------------------------------------
 * Theme colors (RGB565)
 * ------------------------------------------------------------------ */
#define C_BEIGE      RGBc(208, 208, 202)
#define C_BEIGE_DRK  RGBc(154, 154, 150)
#define C_DARK       RGBc( 32,  32,  32)
#define C_DARK_ALT   RGBc( 64,  64,  64)
#define C_LIGHT      RGBc(220, 220, 220)
#define C_LIGHT_ALT  RGBc(160, 160, 160)
#define C_SEL_DARK   RGBc(180, 180, 180)
#define C_SEL_LIGHT  RGBc( 40,  40,  40)
#define C_EXTRA      RGBc(100, 100, 100)
#define C_WHITE      RGBc(255, 255, 255)
#define C_BLACK      RGBc(  5,   5,   5)
#define C_ACTIVE     RGBc(250, 250, 250)

/* ------------------------------------------------------------------
 * print_vkbd - draws the keyboard onto bmp[]
 * ------------------------------------------------------------------ */
void print_vkbd(void)
{
   int x, y;
   int page = vkbd_page ? VKBDX * VKBDY : 0;

   /* Theme */
   unsigned short BKG_NORMAL, BKG_ALT, BKG_SEL, BKG_EXTRA, BKG_ACTIVE;
   unsigned short FNT_NORMAL, FNT_SEL;

   switch (opt_vkbd_theme)
   {
      default:
      case 1: /* Classic beige */
         BKG_NORMAL = C_BEIGE;     BKG_ALT  = C_BEIGE_DRK;
         BKG_SEL    = C_SEL_LIGHT; BKG_EXTRA = C_EXTRA;
         BKG_ACTIVE = C_ACTIVE;
         FNT_NORMAL = C_BLACK;     FNT_SEL  = C_WHITE;
         break;
      case 2: /* Dark */
         BKG_NORMAL = C_DARK;      BKG_ALT  = C_DARK_ALT;
         BKG_SEL    = C_SEL_DARK;  BKG_EXTRA = C_EXTRA;
         BKG_ACTIVE = RGBc( 10,  10,  10);
         FNT_NORMAL = C_WHITE;     FNT_SEL  = C_BLACK;
         break;
      case 3: /* Light */
         BKG_NORMAL = C_LIGHT;     BKG_ALT  = C_LIGHT_ALT;
         BKG_SEL    = C_SEL_LIGHT; BKG_EXTRA = C_EXTRA;
         BKG_ACTIVE = C_ACTIVE;
         FNT_NORMAL = C_BLACK;     FNT_SEL  = C_WHITE;
         break;
   }

   /* Scale font to resolution */
   int FONT_W = (CROP_WIDTH >= 640) ? 2 : 1;
   int FONT_H = FONT_W;

   int VK_XSIDE = (320 * FONT_W) / VKBDX;
   int VK_YSIDE = (170 * FONT_H) / VKBDY;

   int XPAD = retrow  - (VK_XSIDE * VKBDX);
   int YPAD = retroh  - (VK_YSIDE * VKBDY);

   int VK_XBASE = (XPAD > 0) ? XPAD / 2 : 0;
   int VK_YBASE = (YPAD > 0) ? YPAD / 2 : 0;

   int VK_XTEXT = VK_XBASE + (2 * FONT_W);
   int VK_YTEXT = VK_YBASE + (2 * FONT_H);

   int SPACING = 1;

   /* Store bounds for pointer hit testing */
   vkbd_x_min = VK_XBASE;
   vkbd_x_max = VK_XBASE + VK_XSIDE * VKBDX;
   vkbd_y_min = VK_YBASE;
   vkbd_y_max = VK_YBASE + VK_YSIDE * VKBDY;

   /* Draw keys */
   for (x = 0; x < VKBDX; x++)
   {
      for (y = 0; y < VKBDY; y++)
      {
         int idx = y * VKBDX + x + page;
         int val = st_vkeys[idx].val;

         /* Skip empty keys */
         if (val == -1 && st_vkeys[idx].normal[0] == '\0')
            continue;

         /* Pick key color */
         unsigned short key_color;
         bool is_selected = (x == vkey_pos_x && y == vkey_pos_y);

         if (is_selected)
            key_color = BKG_SEL;
         else if (val < 0)
            key_color = BKG_EXTRA;
         else if (val == SK_LSHIFT || val == SK_RSHIFT || val == SK_CTRL ||
                  val == SK_ALT    || val == SK_CAPS)
         {
            /* Highlight active modifiers */
            bool active = false;
            if (val == SK_LSHIFT && vkey_sticky1 == SK_LSHIFT) active = true;
            if (val == SK_RSHIFT && vkey_sticky1 == SK_RSHIFT) active = true;
            if (val == SK_CTRL   && vkey_sticky1 == SK_CTRL)   active = true;
            if (val == SK_ALT    && vkey_sticky1 == SK_ALT)    active = true;
            if (val == SK_LSHIFT && vkey_sticky2 == SK_LSHIFT) active = true;
            if (val == SK_CAPS   && retro_capslock)             active = true;
            key_color = active ? BKG_ACTIVE : BKG_ALT;
         }
         else
            key_color = (y % 2) ? BKG_NORMAL : BKG_ALT;

         int kx = VK_XBASE + x * VK_XSIDE;
         int ky = VK_YBASE + y * VK_YSIDE;

         /* Fill + border using libretro-graph */
         draw_fbox(kx + SPACING, ky + SPACING,
                   VK_XSIDE - SPACING*2, VK_YSIDE - SPACING*2,
                   key_color, GRAPH_ALPHA_75);
         draw_box(kx + SPACING, ky + SPACING,
                  VK_XSIDE - SPACING*2, VK_YSIDE - SPACING*2,
                  retrow, retroh,
                  is_selected ? C_WHITE : C_BLACK, GRAPH_ALPHA_100);

         /* Label */
         bool shifted = (vkey_sticky1 == SK_LSHIFT || vkey_sticky1 == SK_RSHIFT ||
                         vkey_sticky2 == SK_LSHIFT || vkey_sticky2 == SK_RSHIFT);
         const char *label = shifted ? st_vkeys[idx].shift : st_vkeys[idx].normal;

         draw_text(VK_XTEXT + x * VK_XSIDE, VK_YTEXT + y * VK_YSIDE,
                   is_selected ? FNT_SEL : FNT_NORMAL,
                   key_color,
                   GRAPH_ALPHA_100, GRAPH_BG_NONE,
                   FONT_W, FONT_H, 4,
                   (const unsigned char *)label);
      }
   }
}

/* ------------------------------------------------------------------
 * Key send helpers
 * ------------------------------------------------------------------ */
static void st_key_down(int scancode)
{
   if (scancode <= 0) return;
   IKBD_PressSTKey((unsigned char)scancode, true);
}

static void st_key_up(int scancode)
{
   if (scancode <= 0) return;
   IKBD_PressSTKey((unsigned char)scancode, false);
}

/* ------------------------------------------------------------------
 * toggle_vkbd
 * ------------------------------------------------------------------ */
void toggle_vkbd(void)
{
   vkbd_active = !vkbd_active;
   SHOWKEY = vkbd_active ? 1 : -1;
   texture_init();
   Screen_SetFullUpdate();
}

/* ------------------------------------------------------------------
 * input_vkbd - called every frame when vkbd is visible
 * ------------------------------------------------------------------ */
void input_vkbd(void)
{
   static long frame_count = 0;
   frame_count++;

   /* --- Navigation --- */
   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP) && vkflag[0] == 0)
      vkflag[0] = 1;
   else if (!input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP) && vkflag[0] == 1)
   {
      vkflag[0] = 0;
      vkey_pos_y = (vkey_pos_y - 1 + VKBDY) % VKBDY;
   }

   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN) && vkflag[1] == 0)
      vkflag[1] = 1;
   else if (!input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN) && vkflag[1] == 1)
   {
      vkflag[1] = 0;
      vkey_pos_y = (vkey_pos_y + 1) % VKBDY;
   }

   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT) && vkflag[2] == 0)
      vkflag[2] = 1;
   else if (!input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT) && vkflag[2] == 1)
   {
      vkflag[2] = 0;
      vkey_pos_x = (vkey_pos_x - 1 + VKBDX) % VKBDX;
   }

   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT) && vkflag[3] == 0)
      vkflag[3] = 1;
   else if (!input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT) && vkflag[3] == 1)
   {
      vkflag[3] = 0;
      vkey_pos_x = (vkey_pos_x + 1) % VKBDX;
   }

   /* Analog stick navigation */
   int ax = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X);
   int ay = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y);
   const int THRESH = 20000;

   if (ay < -THRESH && vkflag[5] == 0) { vkflag[5] = 1; }
   else if (ay >= -THRESH && vkflag[5] == 1) { vkflag[5] = 0; vkey_pos_y = (vkey_pos_y - 1 + VKBDY) % VKBDY; }

   if (ay >  THRESH && vkflag[6] == 0) { vkflag[6] = 1; }
   else if (ay <=  THRESH && vkflag[6] == 1) { vkflag[6] = 0; vkey_pos_y = (vkey_pos_y + 1) % VKBDY; }

   if (ax < -THRESH && vkflag[7] == 0) { vkflag[7] = 1; }
   else if (ax >= -THRESH && vkflag[7] == 1) { vkflag[7] = 0; vkey_pos_x = (vkey_pos_x - 1 + VKBDX) % VKBDX; }

   if (ax >  THRESH && vkflag[8] == 0) { vkflag[8] = 1; }
   else if (ax <=  THRESH && vkflag[8] == 1) { vkflag[8] = 0; vkey_pos_x = (vkey_pos_x + 1) % VKBDX; }

   /* --- Key press (B button) --- */
   bool b_pressed = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B);

   if (b_pressed && vkflag[4] == 0)
   {
      vkflag[4] = 1;
      vkey_pressed_time = frame_count;
      vkey_press_hold   = false;
   }
   else if (b_pressed && vkflag[4] == 1)
   {
      /* Check for long press -> sticky */
      if (!vkey_press_hold && (frame_count - vkey_pressed_time) > 30)
      {
         vkey_press_hold = true;
         vkey_sticky = true;
      }
   }
   else if (!b_pressed && vkflag[4] == 1)
   {
      vkflag[4] = 0;

      int page = vkbd_page ? VKBDX * VKBDY : 0;
      int idx  = vkey_pos_y * VKBDX + vkey_pos_x + page;
      int val  = st_vkeys[idx].val;

      if (val == VKBD_PAGE2)
      {
         vkbd_page = !vkbd_page;
         texture_init();
      }
      else if (val == VKBD_HIDE)
      {
         toggle_vkbd();
      }
      else if (val == VKBD_STAT)
      {
         STATUTON = -STATUTON;
      }
      else if (val == VKBD_COLOR)
      {
         /* cycle theme */
         opt_vkbd_theme = (opt_vkbd_theme % 3) + 1;
      }
      else if (val > 0)
      {
         /* Modifier keys are always sticky (toggle on/off) */
         if (val == SK_LSHIFT || val == SK_RSHIFT ||
             val == SK_CTRL   || val == SK_ALT    || val == SK_CAPS)
         {
            if (vkey_sticky1 == val)
            {
               st_key_up(val);
               vkey_sticky1 = -1;
            }
            else if (vkey_sticky2 == val)
            {
               st_key_up(val);
               vkey_sticky2 = -1;
            }
            else
            {
               if (vkey_sticky1 == -1)
                  vkey_sticky1 = val;
               else
                  vkey_sticky2 = val;
               st_key_down(val);
            }
         }
         else
         {
            /* Normal key: press down now, release after VKEY_PRESS_FRAMES */
            st_key_down(val);
            last_vkey_pressed  = val;
            vkey_pressed       = val;
            vkey_pressed_hold  = VKEY_PRESS_FRAMES;
         }
      }

      vkey_sticky = false;
   }

   /* Release normal key after hold frames */
   if (vkey_pressed != -1 && !vkflag[4])
   {
      if (vkey_pressed_hold > 0)
      {
         vkey_pressed_hold--;
      }
      else
      {
         st_key_up(vkey_pressed);

         /* Release sticky modifiers */
         if (vkey_sticky1 > 0) { st_key_up(vkey_sticky1); vkey_sticky1_release = true; }
         if (vkey_sticky2 > 0) { st_key_up(vkey_sticky2); vkey_sticky2_release = true; }

         vkey_pressed = -1;
      }
   }

   if (vkey_sticky1_release) { vkey_sticky1 = -1; vkey_sticky1_release = false; }
   if (vkey_sticky2_release) { vkey_sticky2 = -1; vkey_sticky2_release = false; }

   /* Pointer / touchscreen */
   {
      int p_x = input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_X);
      int p_y = input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_Y);
      int p_p = input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_PRESSED);

      /* Activate pointer on first press, deactivate on joypad use */
      if (!last_pointer_p && p_p)
         pointer_active = true;

      if (pointer_active && p_x != 0 && p_y != 0 &&
          (p_x != last_pointer_x || p_y != last_pointer_y || p_p != last_pointer_p))
      {
         /* Convert -0x7fff..0x7fff pointer range to screen coords */
         int px = (int)((p_x + 0x7fff) * retrow / 0xffff);
         int py = (int)((p_y + 0x7fff) * retroh / 0xffff);

         if (px >= vkbd_x_min && px <= vkbd_x_max &&
             py >= vkbd_y_min && py <= vkbd_y_max)
         {
            float kw = (float)(vkbd_x_max - vkbd_x_min) / VKBDX;
            float kh = (float)(vkbd_y_max - vkbd_y_min) / VKBDY;
            int nx = (int)((px - vkbd_x_min) / kw);
            int ny = (int)((py - vkbd_y_min) / kh);
            nx = (nx < 0) ? 0 : (nx > VKBDX-1) ? VKBDX-1 : nx;
            ny = (ny < 0) ? 0 : (ny > VKBDY-1) ? VKBDY-1 : ny;
            vkey_pos_x = nx;
            vkey_pos_y = ny;

            /* Touch press = key press */
            if (!last_pointer_p && p_p)
            {
               vkflag[4] = 1;
               vkey_pressed_time = frame_count;
            }
            else if (last_pointer_p && !p_p)
            {
               /* Simulate button release */
               if (vkflag[4] == 1)
               {
                  vkflag[4] = 0;
                  int page = vkbd_page ? VKBDX * VKBDY : 0;
                  int idx  = vkey_pos_y * VKBDX + vkey_pos_x + page;
                  int val  = st_vkeys[idx].val;
                  if (val > 0) { st_key_down(val); vkey_pressed = val; }
                  else if (val == VKBD_PAGE2) { vkbd_page = !vkbd_page; texture_init(); }
                  else if (val == VKBD_HIDE)  { toggle_vkbd(); }
                  else if (val == VKBD_STAT)  { STATUTON = -STATUTON; }
                  else if (val == VKBD_COLOR) { opt_vkbd_theme = (opt_vkbd_theme % 3) + 1; }
               }
            }
         }

         last_pointer_x = p_x;
         last_pointer_y = p_y;
         last_pointer_p = p_p;
      }
   }

   /* Draw */
   print_vkbd();
}
