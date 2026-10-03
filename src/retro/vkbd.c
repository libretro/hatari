/*
  Hatari - vkbd.c

  This file is distributed under the GNU General Public License, version 2
  or at your option any later version. Read the file gpl.txt for details.

  On-screen virtual keyboard for the libretro core, from the hatari2014 core
  (libretro/vkbd.c there, itself adapted from PUAE's): an ST keyboard in two
  pages of 11x8 keys, drawn over the frame and driven from the first RetroPad
  or a touchscreen.

  RetroPad, while it is shown: D-pad or left stick to move, B to press the
  key, Y for Shift, R to switch pages, and the toggle button (X by default)
  to hide it again. Shift, Control, Alternate and Caps Lock stay down until
  pressed again; Shift, Control and Alternate also let go after the next key.
  The first RetroPad does not drive the ST joystick meanwhile.
*/
const char Vkbd_fileid[] = "Hatari vkbd.c";

#include <string.h>
#include <libretro.h>

#include "main.h"
#include "main_retro.h"
#include "ikbd.h"
#include "keymap.h"
#include "vkbd.h"

/* The GUI's 5x8 font, an XBM bitmap of 16x16 characters */
typedef uint8_t Uint8;
#include "../gui-sdl/font5x8.h"
#define FONT_W 5
#define FONT_H 8

#define VKBDX 11
#define VKBDY 8

/* Values of keys that are not ST keys */
#define VK_NONE   -1
#define VK_PAGE   -2
#define VK_HIDE   -3
#define VK_THEME  -4

/* ST scancodes */
#define SK_ESC     0x01
#define SK_MINUS   0x0C
#define SK_EQUAL   0x0D
#define SK_BACKSP  0x0E
#define SK_TAB     0x0F
#define SK_LBRACK  0x1A
#define SK_RBRACK  0x1B
#define SK_RETURN  0x1C
#define SK_CTRL    0x1D
#define SK_SEMICOL 0x27
#define SK_QUOTE   0x28
#define SK_GRAVE   0x29
#define SK_LSHIFT  0x2A
#define SK_BACKSL  0x2B
#define SK_COMMA   0x33
#define SK_PERIOD  0x34
#define SK_SLASH   0x35
#define SK_RSHIFT  0x36
#define SK_ALT     0x38
#define SK_SPACE   0x39
#define SK_CAPS    0x3A
#define SK_CLRHOME 0x47
#define SK_UP      0x48
#define SK_NPSUB   0x4A
#define SK_LEFT    0x4B
#define SK_RIGHT   0x4D
#define SK_NPADD   0x4E
#define SK_DOWN    0x50
#define SK_INSERT  0x52
#define SK_DELETE  0x53
#define SK_UNDO    0x61
#define SK_HELP    0x62
#define SK_NPLPAR  0x63
#define SK_NPRPAR  0x64
#define SK_NPDIV   0x65
#define SK_NPMUL   0x66
#define SK_NP7     0x67
#define SK_NP8     0x68
#define SK_NP9     0x69
#define SK_NP4     0x6A
#define SK_NP5     0x6B
#define SK_NP6     0x6C
#define SK_NP1     0x6D
#define SK_NP2     0x6E
#define SK_NP3     0x6F
#define SK_NP0     0x70
#define SK_NPDOT   0x71
#define SK_NPENTER 0x72

typedef struct
{
	const char *normal;
	const char *shifted;
	int val;
} vkey_t;

#define K(n, s, v) { n, s, v }
#define NOKEY { "", "", VK_NONE }

static const vkey_t vkeys[2][VKBDY][VKBDX] =
{
	{	/* Page 1: the main keyboard */
		{ K("Esc","Esc",SK_ESC), K("F1","F1",0x3B), K("F2","F2",0x3C), K("F3","F3",0x3D),
		  K("F4","F4",0x3E), K("F5","F5",0x3F), K("F6","F6",0x40), K("F7","F7",0x41),
		  K("F8","F8",0x42), K("F9","F9",0x43), K("F10","F10",0x44) },
		{ K("`","~",SK_GRAVE), K("1","!",0x02), K("2","@",0x03), K("3","#",0x04),
		  K("4","$",0x05), K("5","%",0x06), K("6","^",0x07), K("7","&",0x08),
		  K("8","*",0x09), K("9","(",0x0A), K("0",")",0x0B) },
		{ K("Tab","Tab",SK_TAB), K("q","Q",0x10), K("w","W",0x11), K("e","E",0x12),
		  K("r","R",0x13), K("t","T",0x14), K("y","Y",0x15), K("u","U",0x16),
		  K("i","I",0x17), K("o","O",0x18), K("p","P",0x19) },
		{ K("Ctrl","Ctrl",SK_CTRL), K("a","A",0x1E), K("s","S",0x1F), K("d","D",0x20),
		  K("f","F",0x21), K("g","G",0x22), K("h","H",0x23), K("j","J",0x24),
		  K("k","K",0x25), K("l","L",0x26), K(";",":",SK_SEMICOL) },
		{ K("Caps","Caps",SK_CAPS), K("z","Z",0x2C), K("x","X",0x2D), K("c","C",0x2E),
		  K("v","V",0x2F), K("b","B",0x30), K("n","N",0x31), K("m","M",0x32),
		  K(",","<",SK_COMMA), K(".",">",SK_PERIOD), K("/","?",SK_SLASH) },
		{ K("Shft","Shft",SK_LSHIFT), K("-","_",SK_MINUS), K("=","+",SK_EQUAL),
		  K("\\","|",SK_BACKSL), K("[","{",SK_LBRACK), K("]","}",SK_RBRACK),
		  K("'","\"",SK_QUOTE), K("RSft","RSft",SK_RSHIFT), K("Bksp","Bksp",SK_BACKSP),
		  K("Up","Up",SK_UP), K("Help","Help",SK_HELP) },
		{ K("Pg2","Pg2",VK_PAGE), K("Alt","Alt",SK_ALT), K("Spc","Spc",SK_SPACE),
		  K("Ret","Ret",SK_RETURN), K("Del","Del",SK_DELETE), K("Ins","Ins",SK_INSERT),
		  K("Clr","Clr",SK_CLRHOME), K("Undo","Undo",SK_UNDO), K("Left","Left",SK_LEFT),
		  K("Down","Down",SK_DOWN), K("Rght","Rght",SK_RIGHT) },
		{ NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,
		  K("Col","Col",VK_THEME), NOKEY, K("Hide","Hide",VK_HIDE) },
	},
	{	/* Page 2: the keypad, and the letters again */
		{ K("Esc","Esc",SK_ESC), K("F1","F1",0x3B), K("F2","F2",0x3C), K("F3","F3",0x3D),
		  K("F4","F4",0x3E), K("F5","F5",0x3F), K("F6","F6",0x40), K("F7","F7",0x41),
		  K("F8","F8",0x42), K("F9","F9",0x43), K("F10","F10",0x44) },
		{ K("(","(",SK_NPLPAR), K(")",")",SK_NPRPAR), K("/","/",SK_NPDIV),
		  K("*","*",SK_NPMUL), K("7","7",SK_NP7), K("8","8",SK_NP8), K("9","9",SK_NP9),
		  K("-","-",SK_NPSUB), NOKEY, NOKEY, NOKEY },
		{ NOKEY, NOKEY, NOKEY, NOKEY, K("4","4",SK_NP4), K("5","5",SK_NP5),
		  K("6","6",SK_NP6), K("+","+",SK_NPADD), NOKEY, NOKEY, NOKEY },
		{ NOKEY, NOKEY, NOKEY, NOKEY, K("1","1",SK_NP1), K("2","2",SK_NP2),
		  K("3","3",SK_NP3), K("Ent","Ent",SK_NPENTER), NOKEY, NOKEY, NOKEY },
		{ NOKEY, NOKEY, NOKEY, NOKEY, K("0","0",SK_NP0), K(".",".",SK_NPDOT),
		  NOKEY, NOKEY, NOKEY, NOKEY, NOKEY },
		{ K("Shft","Shft",SK_LSHIFT), K("Ctrl","Ctrl",SK_CTRL), K("Alt","Alt",SK_ALT),
		  NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, K("Bksp","Bksp",SK_BACKSP),
		  K("Up","Up",SK_UP), K("Help","Help",SK_HELP) },
		{ K("Pg1","Pg1",VK_PAGE), NOKEY, K("Spc","Spc",SK_SPACE),
		  K("Ret","Ret",SK_RETURN), K("Del","Del",SK_DELETE), K("Ins","Ins",SK_INSERT),
		  K("Clr","Clr",SK_CLRHOME), K("Undo","Undo",SK_UNDO), K("Left","Left",SK_LEFT),
		  K("Down","Down",SK_DOWN), K("Rght","Rght",SK_RIGHT) },
		{ NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY, NOKEY,
		  K("Col","Col",VK_THEME), NOKEY, K("Hide","Hide",VK_HIDE) },
	},
};

/* Themes: key, darker key, selected key, special key, modifier down, text */
typedef struct
{
	uint32_t key, key_alt, selected, special, active, text, text_selected;
} vkbd_theme_t;

static const vkbd_theme_t themes[] =
{
	{ 0xD0D0CA, 0x9A9A96, 0x282828, 0x646464, 0xFAFAFA, 0x050505, 0xFFFFFF },	/* beige, as the ST */
	{ 0x202020, 0x404040, 0xB4B4B4, 0x646464, 0x0A0A0A, 0xFFFFFF, 0x050505 },	/* dark */
	{ 0xDCDCDC, 0xA0A0A0, 0x282828, 0x646464, 0xFAFAFA, 0x050505, 0xFFFFFF },	/* light */
};
#define NUM_THEMES ((int)(sizeof(themes) / sizeof(themes[0])))

#define PRESS_FRAMES 4		/* a key press lasts this many frames */
#define REPEAT_DELAY 15		/* frames before a held direction repeats */
#define REPEAT_RATE  4

static bool active;
static int toggle_button = RETRO_DEVICE_ID_JOYPAD_X;
static int theme;
static int page;
static int pos_x, pos_y;

static int pressed_key = -1;	/* normal key held for PRESS_FRAMES */
static int pressed_frames;
static bool mod_down[3];	/* Shift, Control, Alternate */
static bool caps_down;		/* as far as the keyboard knows */

static bool prev_toggle;
static bool prev_buttons[16];
static int dir_frames[4];

/* Where the keys were last drawn, for the touchscreen */
static int kbd_x, kbd_y, key_w, key_h, frame_w, frame_h;
static bool touch_down;
static int touch_key_x = -1, touch_key_y = -1;


static void Vkbd_Key(int scancode, bool down)
{
	if (scancode <= 0 || scancode > 0x7f)
		return;
	if (Keyboard.KeyStates[scancode] == down)
		return;
	Keyboard.KeyStates[scancode] = down;
	IKBD_PressSTKey(scancode, down);
}

static int Vkbd_ModIndex(int val)
{
	switch (val)
	{
	 case SK_LSHIFT: case SK_RSHIFT: return 0;
	 case SK_CTRL: return 1;
	 case SK_ALT: return 2;
	 default: return -1;
	}
}

static const int mod_scancodes[3] = { SK_LSHIFT, SK_CTRL, SK_ALT };

static void Vkbd_ReleaseMods(void)
{
	int i;
	for (i = 0; i < 3; i++)
	{
		if (mod_down[i])
		{
			Vkbd_Key(mod_scancodes[i], false);
			mod_down[i] = false;
		}
	}
}

void Vkbd_Reset(void)
{
	if (pressed_key > 0)
		Vkbd_Key(pressed_key, false);
	pressed_key = -1;
	Vkbd_ReleaseMods();
}

void Vkbd_SetToggleButton(int retro_id)
{
	toggle_button = retro_id;
	if (retro_id < 0 && active)
	{
		active = false;
		Vkbd_Reset();
	}
}

void Vkbd_SetTheme(int t)
{
	theme = (t >= 0 && t < NUM_THEMES) ? t : 0;
}

bool Vkbd_IsActive(void)
{
	return active;
}

/**
 * Act on the key at (x, y) of the current page
 */
static void Vkbd_Activate(int x, int y)
{
	int val = vkeys[page][y][x].val;
	int mod = Vkbd_ModIndex(val);

	if (val == VK_PAGE)
		page ^= 1;
	else if (val == VK_HIDE)
	{
		active = false;
		Vkbd_Reset();
	}
	else if (val == VK_THEME)
		theme = (theme + 1) % NUM_THEMES;
	else if (val == SK_CAPS)
	{
		/* Caps Lock locks on the ST itself, so it is a plain press */
		caps_down = !caps_down;
		if (pressed_key > 0)
			Vkbd_Key(pressed_key, false);
		Vkbd_Key(SK_CAPS, true);
		pressed_key = SK_CAPS;
		pressed_frames = PRESS_FRAMES;
	}
	else if (mod >= 0)
	{
		mod_down[mod] = !mod_down[mod];
		Vkbd_Key(mod_scancodes[mod], mod_down[mod]);
	}
	else if (val > 0)
	{
		if (pressed_key > 0)
			Vkbd_Key(pressed_key, false);
		Vkbd_Key(val, true);
		pressed_key = val;
		pressed_frames = PRESS_FRAMES;
	}
}

static bool Vkbd_Button(int id)
{
	return input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, id) != 0;
}

/* A press, on the frame the button goes down */
static bool Vkbd_Pressed(int id)
{
	bool now = Vkbd_Button(id);
	bool was = prev_buttons[id];
	prev_buttons[id] = now;
	return now && !was;
}

/* A direction: on the frame it goes down, then repeating while held */
static bool Vkbd_Direction(int dir, bool held)
{
	if (!held)
	{
		dir_frames[dir] = 0;
		return false;
	}
	dir_frames[dir]++;
	return dir_frames[dir] == 1 ||
	       (dir_frames[dir] > REPEAT_DELAY && (dir_frames[dir] - REPEAT_DELAY) % REPEAT_RATE == 0);
}

static void Vkbd_Touch(void)
{
	int px, py, x, y;
	bool down = input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_PRESSED) != 0;

	if (down && key_w > 0 && key_h > 0)
	{
		px = (input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_X) + 0x7fff) * frame_w / 0xfffe;
		py = (input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_Y) + 0x7fff) * frame_h / 0xfffe;
		x = (px - kbd_x) / key_w;
		y = (py - kbd_y) / key_h;
		if (px >= kbd_x && py >= kbd_y && x < VKBDX && y < VKBDY &&
		    vkeys[page][y][x].normal[0])
		{
			pos_x = x;
			pos_y = y;
			touch_key_x = x;
			touch_key_y = y;
		}
		else
			touch_key_x = touch_key_y = -1;
	}
	else if (!down && touch_down && touch_key_x >= 0)
	{
		/* The key goes off when the finger lifts, where it last was */
		Vkbd_Activate(touch_key_x, touch_key_y);
		touch_key_x = touch_key_y = -1;
	}
	touch_down = down;
}

void Vkbd_Update(void)
{
	bool toggle, left, right, up, down;
	int ax, ay, tries;
	const int threshold = 20000;

	toggle = toggle_button >= 0 && Vkbd_Button(toggle_button);
	if (toggle && !prev_toggle)
	{
		active = !active;
		if (!active)
			Vkbd_Reset();
		else
		{
			/* What is down when it opens is not a key press */
			int i;
			for (i = 0; i < 16; i++)
				prev_buttons[i] = Vkbd_Button(i);
		}
	}
	prev_toggle = toggle;

	/* A normal key goes up after a few frames, and takes the modifiers
	 * that were down for it along */
	if (pressed_key > 0 && --pressed_frames <= 0)
	{
		bool was_mod_key = pressed_key == SK_CAPS;
		Vkbd_Key(pressed_key, false);
		pressed_key = -1;
		if (!was_mod_key)
			Vkbd_ReleaseMods();
	}

	if (!active)
		return;

	ax = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X);
	ay = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y);
	left = Vkbd_Button(RETRO_DEVICE_ID_JOYPAD_LEFT) || ax < -threshold;
	right = Vkbd_Button(RETRO_DEVICE_ID_JOYPAD_RIGHT) || ax > threshold;
	up = Vkbd_Button(RETRO_DEVICE_ID_JOYPAD_UP) || ay < -threshold;
	down = Vkbd_Button(RETRO_DEVICE_ID_JOYPAD_DOWN) || ay > threshold;

	/* Move, skipping the gaps in the layout */
	if (Vkbd_Direction(0, left))
		for (tries = 0; tries < VKBDX && (pos_x = (pos_x + VKBDX - 1) % VKBDX, !vkeys[page][pos_y][pos_x].normal[0]); tries++);
	if (Vkbd_Direction(1, right))
		for (tries = 0; tries < VKBDX && (pos_x = (pos_x + 1) % VKBDX, !vkeys[page][pos_y][pos_x].normal[0]); tries++);
	if (Vkbd_Direction(2, up))
		for (tries = 0; tries < VKBDY && (pos_y = (pos_y + VKBDY - 1) % VKBDY, !vkeys[page][pos_y][pos_x].normal[0]); tries++);
	if (Vkbd_Direction(3, down))
		for (tries = 0; tries < VKBDY && (pos_y = (pos_y + 1) % VKBDY, !vkeys[page][pos_y][pos_x].normal[0]); tries++);

	if (Vkbd_Pressed(RETRO_DEVICE_ID_JOYPAD_B) && vkeys[page][pos_y][pos_x].normal[0])
		Vkbd_Activate(pos_x, pos_y);
	if (Vkbd_Pressed(RETRO_DEVICE_ID_JOYPAD_Y))
	{
		mod_down[0] = !mod_down[0];
		Vkbd_Key(SK_LSHIFT, mod_down[0]);
	}
	if (Vkbd_Pressed(RETRO_DEVICE_ID_JOYPAD_R))
	{
		page ^= 1;
		if (!vkeys[page][pos_y][pos_x].normal[0])
			pos_x = pos_y = 0;
	}

	Vkbd_Touch();
}


/* ---------------------------------------------------------------------- */
/* Drawing                                                                */
/* ---------------------------------------------------------------------- */

static void Vkbd_Blend(uint32_t *p, uint32_t color, int alpha)
{
	uint32_t c = *p;
	uint32_t rb = ((color & 0xFF00FF) * alpha + (c & 0xFF00FF) * (256 - alpha)) >> 8;
	uint32_t g = ((color & 0x00FF00) * alpha + (c & 0x00FF00) * (256 - alpha)) >> 8;
	*p = (rb & 0xFF00FF) | (g & 0x00FF00);
}

static void Vkbd_FillBox(uint32_t *pixels, int stride, int x0, int y0, int w, int h,
                         uint32_t color, int alpha)
{
	int x, y;
	for (y = y0; y < y0 + h; y++)
		for (x = x0; x < x0 + w; x++)
			Vkbd_Blend(&pixels[y * stride + x], color, alpha);
}

static void Vkbd_Frame(uint32_t *pixels, int stride, int x0, int y0, int w, int h, uint32_t color)
{
	int x, y;
	for (x = x0; x < x0 + w; x++)
	{
		pixels[y0 * stride + x] = color;
		pixels[(y0 + h - 1) * stride + x] = color;
	}
	for (y = y0; y < y0 + h; y++)
	{
		pixels[y * stride + x0] = color;
		pixels[y * stride + x0 + w - 1] = color;
	}
}

static void Vkbd_Text(uint32_t *pixels, int stride, int x0, int y0, int scale,
                      const char *text, uint32_t color)
{
	int i, x, y, sx, sy;

	for (i = 0; text[i]; i++)
	{
		unsigned char ch = (unsigned char)text[i];
		int col = ch % 16, row = ch / 16;

		for (y = 0; y < FONT_H; y++)
		{
			for (x = 0; x < FONT_W; x++)
			{
				int bit = col * FONT_W + x;
				int byte = (row * FONT_H + y) * (font5x8_width / 8) + bit / 8;
				if (!(font5x8_bits[byte] & (1 << (bit % 8))))
					continue;
				for (sy = 0; sy < scale; sy++)
					for (sx = 0; sx < scale; sx++)
						pixels[(y0 + y * scale + sy) * stride +
						       x0 + (i * FONT_W + x) * scale + sx] = color;
			}
		}
	}
}

void Vkbd_Draw(uint32_t *pixels, int width, int height, int pitch)
{
	const vkbd_theme_t *t = &themes[theme];
	int stride = pitch / 4;
	int scale = (width >= 640 && height >= 400) ? 2 : 1;
	int x, y;
	bool shifted = mod_down[0];

	if (!active || !pixels)
		return;

	/* Each key fits four characters and a margin */
	key_w = (4 * FONT_W + 6) * scale;
	key_h = (FONT_H + 10) * scale;
	if (key_w * VKBDX > width || key_h * VKBDY > height)
		return;
	kbd_x = (width - key_w * VKBDX) / 2;
	kbd_y = height - key_h * VKBDY - (height - key_h * VKBDY) / 8;
	frame_w = width;
	frame_h = height;

	for (y = 0; y < VKBDY; y++)
	{
		for (x = 0; x < VKBDX; x++)
		{
			const vkey_t *k = &vkeys[page][y][x];
			bool selected = x == pos_x && y == pos_y;
			int mod = Vkbd_ModIndex(k->val);
			int kx = kbd_x + x * key_w, ky = kbd_y + y * key_h;
			const char *label;
			uint32_t color;
			int len;

			if (!k->normal[0])
				continue;

			if (selected)
				color = t->selected;
			else if (k->val < 0)
				color = t->special;
			else if ((mod >= 0 && mod_down[mod]) || (k->val == SK_CAPS && caps_down))
				color = t->active;
			else if (mod >= 0 || k->val == SK_CAPS)
				color = t->key_alt;
			else
				color = (y & 1) ? t->key : t->key_alt;

			Vkbd_FillBox(pixels, stride, kx + 1, ky + 1, key_w - 2, key_h - 2, color, 192);
			Vkbd_Frame(pixels, stride, kx + 1, ky + 1, key_w - 2, key_h - 2,
			           selected ? 0xFFFFFF : 0x050505);

			label = shifted ? k->shifted : k->normal;
			len = (int)strlen(label);
			if (len > 4)
				len = 4;
			Vkbd_Text(pixels, stride,
			          kx + (key_w - len * FONT_W * scale) / 2,
			          ky + (key_h - FONT_H * scale) / 2,
			          scale, label, selected ? t->text_selected : t->text);
		}
	}
}
