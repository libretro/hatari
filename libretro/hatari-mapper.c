#include "libretro.h"
#include "libretro-hatari.h"
#include "hatari-mapper.h"
#include "retro_files.h"
#include "graph.h"
#include "vkbd.h"
#include "joy.h"
#include "screen.h"
#include "video.h"	/* FIXME: video.h is dependent on HBL_PALETTE_LINES from screen.h */
#include "ikbd.h"
#include "main.h"

//RETRO LIB
extern void retro_message(unsigned int frames, int level, const char* format, ...);
extern void retro_status(unsigned int frames, const char* format, ...);

//CORE VAR
extern const char *retro_save_directory;
extern const char *retro_system_directory;
extern const char *retro_content_directory;
char RETRO_DIR[RETRO_PATH_MAX];
char RETRO_TOS[RETRO_PATH_MAX];
char RETRO_HD[RETRO_PATH_MAX];
char RETRO_GD[RETRO_PATH_MAX];
char RETRO_IDE[RETRO_PATH_MAX];
char RETRO_FID[RETRO_PATH_MAX];
extern bool hatari_nomouse;
extern bool hatari_nokeys;
extern bool hatari_led_status_display;
extern int hatari_mouse_control_stick;
extern int hatari_joymousestatus_display;

/* HATARI PROTOTYPES */
#include "configuration.h"
#include "file.h"
extern bool Dialog_DoProperty(void);
extern void Screen_SetFullUpdate(void);
extern void Main_HandleMouseMotion(void);
extern void Main_UnInit(void);
extern int  hmain(int argc, char *argv[]);
extern int Reset_Cold(void);

#ifdef __PS3__
#ifndef __PSL1GHT__
#include <sys/sys_time.h>
#include <sys/timer.h>
#define usleep  sys_timer_usleep
#endif
#endif

#include <sys/types.h>
#include <sys/time.h>
#include <time.h>

/* VIDEO */
extern SDL_Surface *sdlscrn; 
unsigned short int bmp[1024*1024];
unsigned char savbkg[1024*1024* 2];

//SOUND
short signed int SNDBUF[1024*2];
int snd_sampler = 44100 / 50;

//PATH
char RPATH[RETRO_PATH_MAX];
char RPATH2[RETRO_PATH_MAX];

//EMU FLAGS
int NPAGE=-1, KCOL=1, BKGCOLOR=0, MAXPAS=6;
int SHIFTON=-1,MOUSEMODE=-1,SHOWKEY=-1,PAS=2,STATUTON=-1;
int SND=1; //SOUND ON/OFF
int pauseg=0; //enter_gui
int slowdown=0;
int exitgui=0; // exit gui (not serialized)

//JOY
int al[2];//left analog1
unsigned char MXjoy0; // joy 1
unsigned char MXjoy1; // joy 2
int mbt[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//MOUSE
int touch=-1; // gui mouse btn
int fmousex,fmousey; // emu mouse
extern int gmx,gmy; //gui mouse
int point_x_last = -1;
int point_y_last = -1;
int mbL=0,mbR=0;
int mmbL=0, mmbR=0;

//KEYBOARD
char Key_Sate[512];
char Key_Sate2[512];
int oldi=-1;
int vkx=0,vky=0;
int vkflag[5]={0,0,0,0,0};
int mapper_keys[RETRO_DEVICE_ID_JOYPAD_LAST] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

//STATS GUI
extern int LEDA,LEDB,LEDC;
int BOXDEC= 32+2;
int STAT_BASEY;

// savestate serialization

static bool serialize_forward;
static char* serialize_data;

#define SERIALIZE_STEP \
	if (serialize_forward) memcpy(serialize_data, x, sizeof(*x)); \
	else                   memcpy(x, serialize_data, sizeof(*x)); \
	serialize_data += sizeof(*x);

void serialize_char(char *x) { SERIALIZE_STEP }
void serialize_int(int *x) { SERIALIZE_STEP }

int hatari_mapper_serialize_size(void)
{
	return 1023; // +1 byte for version makes an even 1kb header
}

static bool hatari_mapper_serialize_bidi(char* data, char version)
{
   int i;
   int NUMjoy  = 0;
   int firstps = 0;
	/* ignoring version, there is only one version so far
	 * (Might be okay to append to this list without increasing version
	 * if 0 is an acceptable fallback for the new value,
	 * but do not reorder without increasing version number.)
    */
	serialize_data = data;
	serialize_int(&NPAGE);
	serialize_int(&KCOL);
	serialize_int(&BKGCOLOR);
	serialize_int(&MAXPAS);
	serialize_int(&SHIFTON);
	serialize_int(&MOUSEMODE);
	serialize_int(&SHOWKEY);
	serialize_int(&PAS);
	serialize_int(&STATUTON);
	serialize_int(&SND);
	serialize_int(&pauseg);
	serialize_int(&slowdown);
	serialize_int(&fmousex);
	serialize_int(&fmousey);
	serialize_int(&gmx);
	serialize_int(&gmy);
	serialize_int(&NUMjoy); // this variable was removed
	serialize_int(&firstps); // this variable was removed
	serialize_int(&mbL);
	serialize_int(&mbR);
	serialize_int(&mmbL);
	serialize_int(&mmbR);
	serialize_int(&oldi);
	serialize_int(&vkx);
	serialize_int(&vky);
	for (i=0; i<5;  ++i)
      serialize_int(&(vkflag[i]));
	for (i=0; i<16; ++i)
      serialize_int(&(mbt[i]));

	if ((int)(data - serialize_data) > hatari_mapper_serialize_size())
	{
		fprintf(stderr, "hatari_mapper_serialize_size()=%d insufficient! (Needs: %d)\n", hatari_mapper_serialize_size(), (int)(data - serialize_data));
		return false;
	}
	return true;
}

bool hatari_mapper_serialize(char* data, char version)
{
	serialize_forward = true;
	return hatari_mapper_serialize_bidi(data, version);
}

bool hatari_mapper_unserialize(const char* data, char version)
{
	serialize_forward = false;
	int pauseg_old    = pauseg;
	bool result       = hatari_mapper_serialize_bidi((char*)data, version);
	exitgui            = 0;
	if (pauseg_old && !pauseg)
	{
      /* want to exit GUI, turn pauseg back on 
       * and tell it to exit on its own */
		pauseg = pauseg_old;
		exitgui = 1;
	}
	return result;
}

int retro_keymap_id(const char* val)
{
    int i = 0;
    while (retro_keys[i].id < RETROK_LAST)
    {
        if (!strcmp(retro_keys[i].value, val))
            return retro_keys[i].id;
        i++;
    }
    return 0;
}

/* input state */
static retro_input_state_t input_state_cb;
static retro_input_poll_t input_poll_cb;

void retro_set_input_state(retro_input_state_t cb)
{
   input_state_cb = cb;
}

void retro_set_input_poll(retro_input_poll_t cb)
{
   input_poll_cb = cb;
}

#ifdef __PS3__
#ifndef __PSL1GHT__
#define sysGetCurrentTime sys_time_get_current_time
#endif
#endif

/* in milliseconds */
long GetTicks(void)
{
#ifdef _ANDROID_
   struct timespec now;
   clock_gettime(CLOCK_MONOTONIC, &now);
   return (now.tv_sec*1000000 + now.tv_nsec/1000)/1000;
#else
#ifdef __PS3__
   unsigned long        ticks_micro;
   uint64_t secs;
   uint64_t nsecs;

   sysGetCurrentTime(&secs, &nsecs);
   ticks_micro =  secs * 1000000UL + (nsecs / 1000);

   return ticks_micro/1000;
#else
   struct timeval tv;
   gettimeofday (&tv, NULL);
   return (tv.tv_sec*1000000 + tv.tv_usec)/1000;
#endif
#endif

} 

//NO SURE FIND BETTER WAY TO COME BACK IN MAIN THREAD IN HATARI GUI
bool gui_poll_events(void)
{
   slowdown=0;
   co_switch(mainThread);
   return (exitgui != 0);
}

//save bkg for screenshot
void save_bkg(void)
{
   int i, j, k; 
   unsigned char *ptr;

   k = 0;
   ptr = (unsigned char*)sdlscrn->pixels;

   for(j=0;j<retroh;j++)
   {
      for(i=0;i<retrow*2;i++)
      {
         savbkg[k]=*ptr;
         ptr++;
         k++;
      }
   }
}

void retro_fillrect(SDL_Surface * surf,SDL_Rect *rect,unsigned int col)
{
   DrawFBoxBmp(bmp,rect->x,rect->y,rect->w ,rect->h,col); 
}

int  GuiGetMouseState( int * x,int * y)
{
   *x=gmx;
   *y=gmy;
   return 0;
}

void texture_uninit(void)
{
   if(sdlscrn)
   {
      if(sdlscrn->format)
         free(sdlscrn->format);

      free(sdlscrn);
   }
}

SDL_Surface *prepare_texture(int w,int h,int b)
{
   SDL_Surface *bitmp;

   if(sdlscrn)
      texture_uninit();

   bitmp = (SDL_Surface *) calloc(1, sizeof(*bitmp));
   if (bitmp == NULL)
   {
      printf("tex surface failed");
      return NULL;
   }

   bitmp->format = calloc(1,sizeof(*bitmp->format));
   if (bitmp->format == NULL)
   {
      printf("tex format failed");
      return NULL;
   }

   bitmp->format->BitsPerPixel = 16;
   bitmp->format->BytesPerPixel = 2;
   bitmp->format->Rloss=3;
   bitmp->format->Gloss=3;
   bitmp->format->Bloss=3;
   bitmp->format->Aloss=0;
   bitmp->format->Rshift=11;
   bitmp->format->Gshift=6;
   bitmp->format->Bshift=0;
   bitmp->format->Ashift=0;
   bitmp->format->Rmask=0x0000F800;
   bitmp->format->Gmask=0x000007E0;
   bitmp->format->Bmask=0x0000001F;
   bitmp->format->Amask=0x00000000;
   bitmp->format->colorkey=0;
   bitmp->format->alpha=0;
   bitmp->format->palette = NULL;

   bitmp->flags=0;
   bitmp->w=w;
   bitmp->h=h;
   bitmp->pitch=retrow*2;
   bitmp->pixels=(unsigned char *)&bmp[0];
   bitmp->clip_rect.x=0;
   bitmp->clip_rect.y=0;
   bitmp->clip_rect.w=w;
   bitmp->clip_rect.h=h;

   return bitmp;
}      

void texture_init(void)
{
   memset(bmp, 0, sizeof(bmp));

   gmx=(retrow/2)-1;
   gmy=(retroh/2)-1;
}

void enter_gui(void)
{
   save_bkg();
   exitgui=0;
   pauseg=1; // should already be set
   Dialog_DoProperty();
   pauseg=0;
}

void Print_Statut(void)
{
   STAT_BASEY=CROP_HEIGHT+24;
   int NUMjoy = (ConfigureParams.Joysticks.Joy[0].nJoystickMode == JOYSTICK_REALSTICK) ? 2 : 1;

   DrawFBoxBmp(bmp,0,STAT_BASEY,CROP_WIDTH,STAT_YSZ,RGB565(0,0,0));

   Draw_text(bmp,STAT_DECX    ,STAT_BASEY,0xffff,0x8080,1,2,40,(MOUSEMODE<0)?" Joy ":"Mouse");
   if (MOUSEMODE>=0)
   Draw_text(bmp,STAT_DECX+40 ,STAT_BASEY,0xffff,0x8080,1,2,40,"Speed:%d",PAS);
   Draw_text(bmp,STAT_DECX+100,STAT_BASEY,0xffff,0x8080,1,2,40,(SHIFTON>0)?"SHIFT":"     ");
   Draw_text(bmp,STAT_DECX+150,STAT_BASEY,0xffff,0x8080,1,2,40,"Joysticks:%s",(NUMjoy > 1) ? " 2 " : " 1 ");

   if(LEDA)
   {
      DrawFBoxBmp(bmp,CROP_WIDTH-6*BOXDEC-6-16,STAT_BASEY,16,16,RGB565(0,7,0));//led A drive
      Draw_text(bmp,CROP_WIDTH-6*BOXDEC-6-16,STAT_BASEY,0xffff,0x0,1,2,40," A");
   }    

   if(LEDB)
   {
      DrawFBoxBmp(bmp,CROP_WIDTH-7*BOXDEC-6-16,STAT_BASEY,16,16,RGB565(0,7,0));//led B drive
      Draw_text(bmp,CROP_WIDTH-7*BOXDEC-6-16,STAT_BASEY,0xffff,0x0,1,2,40," B");
   }

   if(LEDC)
   {
      DrawFBoxBmp(bmp,CROP_WIDTH-8*BOXDEC-6-16,STAT_BASEY,16,16,RGB565(0,7,0));//led C drive
      Draw_text(bmp,CROP_WIDTH-8*BOXDEC-6-16,STAT_BASEY,0xffff,0x0,1,2,40," C");
      LEDC=0;
   }

}

void retro_key_down(unsigned char retrok)
{
   IKBD_PressSTKey(retrok,1); 
}

void retro_key_up(unsigned char retrok)
{
   IKBD_PressSTKey(retrok,0);
}

void Process_key(void)
{
   int i,j,d;
   int inp[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   const int threshold = 20000;
   // used to prevent duplicate RetroRemaps from conflicting
   inp[1] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X) > threshold;   //  RETRO_DEVICE_ID_JOYPAD_LR
   inp[2] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X) < -threshold;  //  RETRO_DEVICE_ID_JOYPAD_LL
   inp[3] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y) > threshold;   //  RETRO_DEVICE_ID_JOYPAD_LD
   inp[4] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y) < -threshold;  //  RETRO_DEVICE_ID_JOYPAD_LU
   inp[5] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X) > threshold;  // RETRO_DEVICE_ID_JOYPAD_RR
   inp[6] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X) < -threshold; // RETRO_DEVICE_ID_JOYPAD_RL
   inp[7] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y) > threshold;  // RETRO_DEVICE_ID_JOYPAD_RD
   inp[8] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y) < -threshold; // RETRO_DEVICE_ID_JOYPAD_RU

   for(i = 0; i < 320; i++)
   {
      int which = 0;
      Key_Sate[i] = (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0,i) && !hatari_nokeys) ? 0x80: 0;

      // RETROMAPPER... mapper... mapper.  Only check if VKBD not active.  :P
      if (SHOWKEY == -1)
      {
          for (j = 0; j < RETRO_DEVICE_ID_JOYPAD_LAST; ++j)
          {
              int what = j < 16 ? 0 : j - 15;

              inp[0] = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, j);
              which = inp[what];

              if (mapper_keys[j] == i)
              {
                  if (!what && (MOUSEMODE == -1 || j>8 || ( j>0 && j<4) ))
                  {
                      if (Key_Sate[i] == 0 && which)
                      {
                          Key_Sate[i] = 0x80;
                      }
                  }
                  // Only joystick mode.. or if mouse not left analog
                  else if (what < 5 && (hatari_mouse_control_stick || MOUSEMODE == -1))
                  {
                      if (Key_Sate[i] == 0 && which)
                      {
                          Key_Sate[i] = 0x80; 
                      }
                  }
                  // Only joystick mode.. or if mouse not right analog
                  else if (what > 4 && (!hatari_mouse_control_stick || MOUSEMODE == -1))
                  {
                      if (Key_Sate[i] == 0 && which)
                      {
                          Key_Sate[i] = 0x80;
                      }
                  }
              }
          }
      }

      if(SDLKeyToSTScanCode[i]==0x2a )
      {  //SHIFT CASE

         if( Key_Sate[i] && Key_Sate2[i]==0 )
         {
            if(SHIFTON == 1)
               retro_key_up(   SDLKeyToSTScanCode[i] );
            else if(SHIFTON == -1) 
               retro_key_down( SDLKeyToSTScanCode[i] );
            SHIFTON=-SHIFTON;
            Key_Sate2[i]=1;
         }
         else if ( !Key_Sate[i] && Key_Sate2[i]==1 )Key_Sate2[i]=0;
      }
      else
      {
         if(Key_Sate[i] && SDLKeyToSTScanCode[i]!=-1  && Key_Sate2[i]==0)
         {
            retro_key_down( SDLKeyToSTScanCode[i] );
            Key_Sate2[i]=1;
         }
         else if ( !Key_Sate[i] && SDLKeyToSTScanCode[i]!=-1 && Key_Sate2[i]==1 )
         {
            retro_key_up(   SDLKeyToSTScanCode[i] );
            Key_Sate2[i]=0;
         }
      }
   }
}

const int DEADZONE = 0x8000 / 12;
void Deadzone(int* a)
{
    return; // let retroarch control the deadzone for now

   if (al[0] <= -DEADZONE) al[0] += DEADZONE;
   if (al[1] <= -DEADZONE) al[1] += DEADZONE;
   if (al[0] >=  DEADZONE) al[0] -= DEADZONE;
   if (al[1] >=  DEADZONE) al[1] -= DEADZONE;
}

//preliminary mouse via Wii-U touch tablet will need time checks to distinguish double clicks plus relative mouse handling since Hatari ignores ABS values.
bool input_mouse_via_pointer(void)
{
    int i;
    int mouse_l;
    int mouse_r;
    int16_t mouse_x = 0;
    int16_t mouse_y = 0;
    //  might not need thesetwo
    int ratio_x = retrow / KeyboardProcessor.Abs.MaxX;
    int ratio_y = retroh / KeyboardProcessor.Abs.MaxY;

    input_poll_cb();

    //if (slowdown > 0)
    //    return;

    // pointer mouse control.  x,y return 0 if point_b is 0.
    int point_x = input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_X);
    int point_y = input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_Y);
    int point_b = input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_PRESSED);

    if (point_x != point_x_last || point_y != point_y_last)
    {
        const int PMIN = -0x7FFF;
        const int PMAX = 0x7FFF;
        point_x_last = point_x;
        point_y_last = point_y;
        mouse_x = ((point_x - PMIN) * retrow) / (PMAX - PMIN);
        mouse_y = ((point_y - PMIN) * retroh) / (PMAX - PMIN);
    }

    if (mouse_x < 0)
        mouse_x = 0;
    if (mouse_x > retrow - 1)
        mouse_x = retrow - 1;
    if (mouse_y < 0)
        mouse_y = 0;
    if (mouse_y > retroh - 1)
        mouse_y = retroh - 1;

    //may not need cause ABS is unusable.
    mouse_x /= ratio_x;
    mouse_y /= ratio_y;

    //this guy will need time stamps in order to work properly.
    if (mbL == 0 && point_b)
    {
        mbL = 1;
        Keyboard.bLButtonDown |= BUTTON_MOUSE;
    }
    else if (mbL == 1 && !point_b)
    {
        mbL = 0;
        Keyboard.bLButtonDown &= ~BUTTON_MOUSE;
    }

    /* Wii-U doesn't do multi-touch?  A shame.. :P
    if (mbR == 0 && mouse_r)
    {
        mbR = 1;
        Keyboard.bRButtonDown |= BUTTON_MOUSE;
        Keyboard.bRButtonDown |= BUTTON_MOUSE;
    }
    else if (mbR == 1 && !mouse_r)
    {
        mbR = 0;
        Keyboard.bRButtonDown &= ~BUTTON_MOUSE;
    }
*/

    if (point_b)
    {
        // do something clever here...
    }

    //status display so we know what numbers are being fed.
    char msg[256];
    // mouse_x, mouse_y, point_b,
    sprintf(msg, "touchX=%i, touchY=%i.\n", mouse_x, mouse_y);
        //KeyboardProcessor.Mouse.DeltaX, KeyboardProcessor.Mouse.DeltaY, KeyboardProcessor.Mouse.dx, KeyboardProcessor.Mouse.dy) ;
    retro_message(60, RETRO_LOG_INFO, msg);

    // might not need to return this.. but we will figure out later
    if (!point_b)
        return false;
    else
        return true;
}

/*
   L   show/hide Status
   R   swap kbd pages
   L2  MOUSE SPEED DOWN (gui/emu)
   R2  MOUSE SPEED UP(gui/emu)
   SEL toggle mouse/joy mode
   STR Hatari Gui / Exit Gui
   B   fire/mouse-left/valid key in vkbd
   A   mouse-right
   Y   switch Shift ON/OFF
   X   show/hide vkbd
   R3  keyboard space
   */

void update_input(void)
{
   int i,d;
   int mouse_l, mouse_r;
   int16_t mouse_x, mouse_y;
   const int threshold = 20000;
   static int status_update_joymouse = 0;
   static int status_update_mousespeed = 0;
   static int selected[16] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };  // used to prevent duplicate RetroRemaps from conflicting
   int inp[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
   char msg[50];

   msg[0] = 0;
   MXjoy0 = MXjoy1 = 0;

   if(oldi!=-1)
   {
      IKBD_PressSTKey(oldi,0);
      oldi=-1;
   }

   input_poll_cb();

   Process_key();

#if 1
   // interface functions
   // only need to check once
   inp[1] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X) > threshold;   //  RETRO_DEVICE_ID_JOYPAD_LR
   inp[2] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X) < -threshold;  //  RETRO_DEVICE_ID_JOYPAD_LL
   inp[3] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y) > threshold;   //  RETRO_DEVICE_ID_JOYPAD_LD
   inp[4] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y) < -threshold;  //  RETRO_DEVICE_ID_JOYPAD_LU
   inp[5] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X) > threshold;  // RETRO_DEVICE_ID_JOYPAD_RR
   inp[6] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X) < -threshold; // RETRO_DEVICE_ID_JOYPAD_RL
   inp[7] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y) > threshold;  // RETRO_DEVICE_ID_JOYPAD_RD
   inp[8] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y) < -threshold; // RETRO_DEVICE_ID_JOYPAD_RU

   for (i = 0; i < RETRO_DEVICE_ID_JOYPAD_LAST; ++i)
   {
       int which = 0;

       inp[0] = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i);
       which = inp[i < 16 ? 0 : i - 15];

       // only  do these if VKBD not active
       if (SHOWKEY == -1)
       {
            d = RETRO_DEVICE_ID_JOYPAD_START;// Hatari GUI
            if (mapper_keys[i] == TOGGLE_SETTINGS)
            {
                if (which && mbt[d] == 0)
                {
                    mbt[d] = 1;
                    selected[d] = i;
                }
                else if (mbt[d] == 1 && !which && selected[d] == i)
                {
                    mbt[d] = 0;
                    pauseg = 1;
                    selected[d] = -1;
                }
            }
            d = RETRO_DEVICE_ID_JOYPAD_SELECT;//mouse/joy toggle
            if (mapper_keys[i] == TOGGLE_JOYMOUSE)
            {
                if (which && mbt[d] == 0)
                {
                    mbt[d] = 1;
                    selected[d] = i;
                }
                else if (mbt[d] == 1 && !which && selected[d] == i)
                {
                    mbt[d] = 0;
                    selected[d] = -1;
                    MOUSEMODE = -MOUSEMODE;
                    status_update_joymouse = 60;
                }
            }
            d = RETRO_DEVICE_ID_JOYPAD_L2;//mouse gui speed down
            if (mapper_keys[i] == MOUSE_SLOWER)
            {
                if (which && mbt[d] == 0)
                {
                    mbt[d] = 1;
                    selected[d] = i;
                }
                else if (mbt[d] == 1 && !which && selected[d] == i)
                {
                    mbt[d] = 0;
                    selected[d] = -1;
                    PAS--; if (PAS < 1)PAS = MAXPAS;
                    status_update_mousespeed = 60;
                }
            }
            d = RETRO_DEVICE_ID_JOYPAD_R2;//mouse gui speed up
            if (mapper_keys[i] == MOUSE_FASTER)
            {
                if (which && mbt[d] == 0)
                {
                    mbt[d] = 1;
                    selected[d] = i;
                }
                else if (mbt[d] == 1 && !which && selected[d] == i)
                {
                    mbt[d] = 0;
                    selected[d] = -1;
                    PAS++; if (PAS > MAXPAS)PAS = 1;
                    status_update_mousespeed = 60;
                }
            }
            d = RETRO_DEVICE_ID_JOYPAD_L;//show/hide status (either joystick)
            if (mapper_keys[i] == TOGGLE_STATUSBAR)
            {
                if (which && mbt[d] == 0)
                {
                    mbt[d] = 1;
                    selected[d] = i;
                }
                else if (mbt[d] == 1 && !which && selected[d] == i)
                {
                    mbt[d] = 0;
                    selected[d] = -1;
                    STATUTON = -STATUTON;
                    Screen_SetFullUpdate();
                }
            }
       }
       // do these only when VKBD is active.
       else
       {
           // do this for analog sticks later
           //if (i < 16)
           {
               d = RETRO_DEVICE_ID_JOYPAD_Y;//switch shift On/Off 
               if (mapper_keys[i] == TOGGLE_VKBS)
               {
                   if (which && mbt[d] == 0)
                   {
                       mbt[d] = 1;
                       selected[d] = i;
                   }
                   else if (mbt[d] == 1 && !input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, d) && selected[d] == i)
                   {
                       mbt[d] = 0;
                       selected[d] = -1;
                       SHIFTON = -SHIFTON;
                       Screen_SetFullUpdate();
                   }
               }
               d = RETRO_DEVICE_ID_JOYPAD_R;//swap kbd pages
               if (mapper_keys[i] == TOGGLE_VKBP)
               {
                   if (which && mbt[d] == 0)
                   {
                       mbt[d] = 1;
                       selected[d] = i;
                   }
                   else if (mbt[d] == 1 && !input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, d) && selected[d] == i)
                   {
                       mbt[d] = 0;
                       selected[d] = -1;
                       if (SHOWKEY == 1)
                       {
                           NPAGE = -NPAGE;
                           Screen_SetFullUpdate();
                       }
                   }
               }
           }
       }

       // check always but not left analog since that is used to naviage VKBD
       if (i < RETRO_DEVICE_ID_JOYPAD_LR || i > RETRO_DEVICE_ID_JOYPAD_LU)
       {
           d = RETRO_DEVICE_ID_JOYPAD_X;//show vkey toggle
           if (mapper_keys[i] == TOGGLE_VKBD)
           {
               if (which && mbt[d] == 0)
               {
                   mbt[d] = 1;
                   selected[d] = i;
               }
               else if (mbt[d] == 1 && !which && selected[d] == i)
               {
                   mbt[d] = 0;
                   selected[d] = -1;
                   SHOWKEY = -SHOWKEY;
                   texture_init();           //clear kbd bmp so complete keyboard is cleared
                   Screen_SetFullUpdate();
               }
           }
       }
   }
#else   // old code before RETRO_MAPPING was added.
   i=RETRO_DEVICE_ID_JOYPAD_START;// Hatari GUI
   if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i]==0 )
      mbt[i]=1;
   else if ( mbt[i]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) )
   {
      mbt[i]=0;
      pauseg=1;
   }

   i=RETRO_DEVICE_ID_JOYPAD_X;//show vkey toggle
   if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i]==0 )
      mbt[i]=1;
   else if ( mbt[i]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) )
   {
      mbt[i]=0;
      SHOWKEY=-SHOWKEY;
      texture_init();           //clear kbd bmp so complete keyboard is cleared
      Screen_SetFullUpdate();
   }

   i=RETRO_DEVICE_ID_JOYPAD_SELECT;//mouse/joy toggle
   if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i]==0 )
      mbt[i]=1;
   else if ( mbt[i]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) )
   {
      mbt[i]=0;
      MOUSEMODE=-MOUSEMODE;
      status_update_joymouse = 60;
   }

   i=RETRO_DEVICE_ID_JOYPAD_L2;//mouse gui speed down
   if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i]==0 )
      mbt[i]=1;
   else if ( mbt[i]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) )
   {
      mbt[i]=0;
      PAS--;if(PAS<1)PAS=MAXPAS;
      status_update_mousespeed = 60;
   }

   i=RETRO_DEVICE_ID_JOYPAD_R2;//mouse gui speed up
   if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i]==0 )
      mbt[i]=1;
   else if ( mbt[i]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) )
   {
      mbt[i]=0;
      PAS++;if(PAS>MAXPAS)PAS=1;
      status_update_mousespeed = 60;
   }

   i=RETRO_DEVICE_ID_JOYPAD_Y;//switch shift On/Off 
   if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i]==0 )
      mbt[i]=1;
   else if ( mbt[i]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) )
   {
      mbt[i]=0;
      SHIFTON=-SHIFTON;
      Screen_SetFullUpdate();
   }

   i=RETRO_DEVICE_ID_JOYPAD_L;//show/hide status (either joystick)
   if ( (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) || input_state_cb(1, RETRO_DEVICE_JOYPAD, 0, i)) && mbt[i]==0 )
      mbt[i]=1;
   else if ( mbt[i]==1 && ! (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) || input_state_cb(1, RETRO_DEVICE_JOYPAD, 0, i)) )
   {
      mbt[i]=0;
      STATUTON=-STATUTON;
      Screen_SetFullUpdate();
   }

   i=RETRO_DEVICE_ID_JOYPAD_R;//swap kbd pages
   if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i]==0 )
      mbt[i]=1;
   else if ( mbt[i]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) )
   {
      mbt[i]=0;
      if(SHOWKEY==1)
      {
         NPAGE=-NPAGE;
         Screen_SetFullUpdate();
      }
   }
#endif /* 1 */

   // joystick 2.  Retromappings not done for joystick 2 yet. (if at all)
   if (ConfigureParams.Joysticks.Joy[0].nJoystickMode == JOYSTICK_REALSTICK) // 2 joysticks
   {
      al[0] =(input_state_cb(1, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X));
      al[1] =(input_state_cb(1, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y));

      /* Directions */
      if (al[1] <= JOYRANGE_UP_VALUE)
         MXjoy1 |= ATARIJOY_BITMASK_UP;
      else if (al[1] >= JOYRANGE_DOWN_VALUE)
         MXjoy1 |= ATARIJOY_BITMASK_DOWN;

      if (al[0] <= JOYRANGE_LEFT_VALUE)
         MXjoy1 |= ATARIJOY_BITMASK_LEFT;
      else if (al[0] >= JOYRANGE_RIGHT_VALUE)
         MXjoy1 |= ATARIJOY_BITMASK_RIGHT;

      if( input_state_cb(1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP   ) ) MXjoy1 |= ATARIJOY_BITMASK_UP;
      if( input_state_cb(1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN ) ) MXjoy1 |= ATARIJOY_BITMASK_DOWN;
      if( input_state_cb(1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT ) ) MXjoy1 |= ATARIJOY_BITMASK_LEFT;
      if( input_state_cb(1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT) ) MXjoy1 |= ATARIJOY_BITMASK_RIGHT;
      if( input_state_cb(1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B)     ) MXjoy1 |= ATARIJOY_BITMASK_FIRE;

      // Joy autofire
      if( input_state_cb(1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A) )
      {
         MXjoy1 |= ATARIJOY_BITMASK_FIRE;
         if ((nVBLs&0x7)<4)
            MXjoy1 &= ~ATARIJOY_BITMASK_FIRE;
      }
   }

   // ignore joystick 1 and mouse input when VKBD active.
   // Guess what!?  With RETROMAPPING active.. we can actually read these JOYPAD buttons directly!  No weird remapping to confuse the user!
   if(SHOWKEY==1)
   {
      // analog stick can work the keyboard
      al[0] =(input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X));
      al[1] =(input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y));
      bool al_up = al[1] <= JOYRANGE_UP_VALUE;
      bool al_dn = al[1] >= JOYRANGE_DOWN_VALUE;
      bool al_lf = al[0] <= JOYRANGE_LEFT_VALUE;
      bool al_rt = al[0] >= JOYRANGE_RIGHT_VALUE;

      if ( (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP) || al_up) && vkflag[0]==0 )
         vkflag[0]=1;
      else if (vkflag[0]==1 && ! (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP) || al_up) )
      {
         vkflag[0]=0;
         vky -= 1; 
      }

      if ( (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN) || al_dn) && vkflag[1]==0 )
         vkflag[1]=1;
      else if (vkflag[1]==1 && ! (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN) || al_dn) )
      {
         vkflag[1]=0;
         vky += 1; 
      }

      if ( (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT) || al_lf) && vkflag[2]==0 )
         vkflag[2]=1;
      else if (vkflag[2]==1 && ! (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT) || al_lf) )
      {
         vkflag[2]=0;
         vkx -= 1;
      }

      if ( (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT) || al_rt) && vkflag[3]==0 )
         vkflag[3]=1;
      else if (vkflag[3]==1 && ! (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT) || al_rt) )
      {
         vkflag[3]=0;
         vkx += 1;
      }

      if(vkx<0)vkx=9;
      if(vkx>9)vkx=0;
      if(vky<0)vky=4;
      if(vky>4)vky=0;

      virtual_kdb(bmp,vkx,vky);

      if(input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B)  && vkflag[4]==0)
         vkflag[4]=1;
      else if( !input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B)  && vkflag[4]==1)
      {
         vkflag[4]=0;
         i=check_vkey2(vkx,vky);

         if(i==-2)
         {
            NPAGE=-NPAGE;oldi=-1;
            //Clear interface zone
            texture_init();           //clear kbd bmp so complete keyboard is cleared
            Screen_SetFullUpdate();
         }
         else if(i==-1)
            oldi=-1;
         else if(i==-3)
         {
            //KDB bgcolor
            Screen_SetFullUpdate();
            KCOL=-KCOL;
            oldi=-1;
         }
         else if(i==-4)
         {
            //VKbd show/hide
            oldi=-1;
            texture_init();           //clear kbd bmp so complete keyboard is cleared
            Screen_SetFullUpdate();
            SHOWKEY=-SHOWKEY;
         }
         else if(i==-5)
         {
            //Toggle stats
            STATUTON=-STATUTON;
            Screen_SetFullUpdate();
         }
         else
         {
            if(i==0x2a)
            {

               IKBD_PressSTKey(i,(SHIFTON == 1)?0:1);

               SHIFTON=-SHIFTON;

               Screen_SetFullUpdate();

               oldi=-1;
            }
            else
            {
               oldi=i;
               IKBD_PressSTKey(i,1);
            }
         }
      }

      if(STATUTON==1)
         Print_Statut();

      return;
   }

   // joystick 1 / mouse
   if (MOUSEMODE < 0)
   {
       //Joy mode (joystick controls joystick, mouse controls mouse)

       //emulate Joy0 with joy analog left.  User should really set this in the Retro_Mapper section if they want this
       //al[0] =(input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X));
       //al[1] =(input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y));

       /* Directions */
       //if (al[1] <= JOYRANGE_UP_VALUE)
       //   MXjoy0 |= ATARIJOY_BITMASK_UP;
       //else if (al[1] >= JOYRANGE_DOWN_VALUE)
       //   MXjoy0 |= ATARIJOY_BITMASK_DOWN;

       //if (al[0] <= JOYRANGE_LEFT_VALUE)
       //   MXjoy0 |= ATARIJOY_BITMASK_LEFT;
       //else if (al[0] >= JOYRANGE_RIGHT_VALUE)
       //   MXjoy0 |= ATARIJOY_BITMASK_RIGHT;

 // new RETROMAPPER code
#if 1 

       //Only if VKBD not active.
       if (SHOWKEY == -1)
       {
           for (i = 0; i < RETRO_DEVICE_ID_JOYPAD_LAST; ++i)
           {
               int which = 0;

               inp[0] = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i);
               which = inp[i < 16 ? 0 : i - 15];

               // do for analog sticks later
               //if (i < 16)
               {
                   // RETRO_DEVICE_ID_JOYPAD_UP;
                   if (mapper_keys[i] == JOYSTICK_UP)
                   {
                       if (which)
                           MXjoy0 |= ATARIJOY_BITMASK_UP;
                   }
                   // RETRO_DEVICE_ID_JOYPAD_DOWN;
                   if (mapper_keys[i] == JOYSTICK_DOWN)
                   {
                       if (which)
                           MXjoy0 |= ATARIJOY_BITMASK_DOWN;
                   }
                   // RETRO_DEVICE_ID_JOYPAD_LEFT;
                   if (mapper_keys[i] == JOYSTICK_LEFT)
                   {
                       if (which)
                           MXjoy0 |= ATARIJOY_BITMASK_LEFT;
                   }
                   // RETRO_DEVICE_ID_JOYPAD_RIGHT;
                   if (mapper_keys[i] == JOYSTICK_RIGHT)
                   {
                       if (which)
                           MXjoy0 |= ATARIJOY_BITMASK_RIGHT;
                   }
                   // RETRO_DEVICE_ID_JOYPAD_B;
                   if (mapper_keys[i] == JOYSTICK_FIRE)
                   {
                       if (which)
                           MXjoy0 |= ATARIJOY_BITMASK_FIRE;
                   }
                   // RETRO_DEVICE_ID_JOYPAD_A;
                   if (mapper_keys[i] == JOYSTICK_TURBOFIRE)
                   {
                       if (which)
                       {
                           MXjoy0 |= ATARIJOY_BITMASK_FIRE;

                           if ((nVBLs & 0x7) < 4)
                               MXjoy0 &= ~ATARIJOY_BITMASK_FIRE;
                       }
                   }
               }
           }
           //old code
#else   
           if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN)) MXjoy0 |= ATARIJOY_BITMASK_DOWN;
           if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT)) MXjoy0 |= ATARIJOY_BITMASK_LEFT;
           if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT)) MXjoy0 |= ATARIJOY_BITMASK_RIGHT;
           if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B)) MXjoy0 |= ATARIJOY_BITMASK_FIRE;

           // Joy autofire
           if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A))
           {
               MXjoy0 |= ATARIJOY_BITMASK_FIRE;
               if ((nVBLs & 0x7) < 4)
                   MXjoy0 &= ~ATARIJOY_BITMASK_FIRE;
           }
#endif /*  1 */
   
            if (hatari_nomouse)
            {
                mouse_l = 0;
                mouse_r = 0;
            }
            else
            {
                mouse_x = input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_X);
                mouse_y = input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_Y);
                mouse_l = input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_LEFT);
                mouse_r = input_state_cb(0, RETRO_DEVICE_MOUSE, 0, RETRO_DEVICE_ID_MOUSE_RIGHT);
                fmousex=mouse_x;
                fmousey=mouse_y;
            }
       }
   }
   else // MOUSEMODE >= 0
   {
       //Mouse mode (joystick controls mouse)
       // We won't tie this to RETROMAPPER.  Hopefully it won't confuse the user.

       // Only if VKDB not active.
       if (SHOWKEY == -1)
       {
           fmousex = fmousey = 0;

           //emulate mouse with joy analog left
           al[0] = (input_state_cb(0, RETRO_DEVICE_ANALOG, hatari_mouse_control_stick, RETRO_DEVICE_ID_ANALOG_X));
           al[1] = (input_state_cb(0, RETRO_DEVICE_ANALOG, hatari_mouse_control_stick, RETRO_DEVICE_ID_ANALOG_Y));
           Deadzone(al);
           al[0] = (al[0] * PAS) / MAXPAS;
           al[1] = (al[1] * PAS) / MAXPAS;
           fmousex += al[0] / 1024;
           fmousey += al[1] / 1024;

           //emulate mouse with dpad.  May change this in future to be more userdefinable
           if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT))
               fmousex += PAS * 3;
           if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT))
               fmousex -= PAS * 3;
           if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN))
               fmousey += PAS * 3;
           if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP))
               fmousey -= PAS * 3;

           mouse_l = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B);
           mouse_r = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A);
       }
   }

   if (mbL == 0 && mouse_l)
   {
       mbL = 1;
       Keyboard.bLButtonDown |= BUTTON_MOUSE;
   }
   else if (mbL == 1 && !mouse_l)
   {
       Keyboard.bLButtonDown &= ~BUTTON_MOUSE;
       mbL = 0;
   }

   if (mbR == 0 && mouse_r)
   {
       mbR = 1;
       Keyboard.bRButtonDown |= BUTTON_MOUSE;
   }
   else if (mbR == 1 && !mouse_r)
   {
       Keyboard.bRButtonDown &= ~BUTTON_MOUSE;
       mbR = 0;
   }

   // maybe some day..
   //input_mouse_via_pointer();
   Main_HandleMouseMotion();

   // display status if enabled
   if (status_update_joymouse || status_update_mousespeed)
   {
       if (hatari_joymousestatus_display == 0)
           status_update_joymouse = status_update_mousespeed = 0;
       else if (hatari_joymousestatus_display == 2)
       {
           if (status_update_joymouse)
               retro_message(1000, RETRO_LOG_INFO, (MOUSEMODE < 0) ? "Joystick Mode" : "Mouse Mode");
           else
               retro_message(1000, RETRO_LOG_INFO, "Mouse Speed:%d", PAS);

           status_update_joymouse = status_update_mousespeed = 0;
       }
       else
       {
           char msp[8];

           if (status_update_mousespeed)
               sprintf(msp, "Speed:%d", PAS);
           else
               msp[0] = 0;

           sprintf(msg, "%s%s%s", status_update_joymouse ? (MOUSEMODE < 0) ? "Joystick Mode" : "Mouse Mode" : "",
                        (status_update_mousespeed && status_update_joymouse) ? " || " : "", msp );

           if (status_update_joymouse > 0)
               status_update_joymouse--;
           if (status_update_mousespeed > 0)
               status_update_mousespeed--;
       }
   }

   if (hatari_led_status_display)
   {
       if (LEDA)
       {
           if (status_update_joymouse || status_update_mousespeed)
               strcat(msg, " || A");
           else
               retro_status(60, "A");
       }
       if (LEDB)
       {
           if (status_update_joymouse || status_update_mousespeed)
               strcat(msg, " || B");
           else
               retro_status(60, "B");
       }
       if (LEDC)
       {
           if (status_update_joymouse || status_update_mousespeed)
               strcat(msg, " || C");
           else
               retro_status(60, "C");

           if (STATUTON == -1)
               LEDC = 0;
       }
   }

   if ( msg[0] )
       retro_status(60, msg);

   if(STATUTON==1)
      Print_Statut();
}

void input_gui(void)
{
   int i,d;
   int mouse_l, mouse_r;
   static int status_update_mousespeed = 0;
   int16_t mouse_x = 0, mouse_y = 0;
   const int threshold = 20000;
   static int selected[16]= {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};  // used to prevent duplicate RetroRemaps from conflicting
   int inp[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

   input_poll_cb();

   if(slowdown>0)
      return;

#if 1

   inp[1] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X) > threshold;   //  RETRO_DEVICE_ID_JOYPAD_LR
   inp[2] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X) < -threshold;  //  RETRO_DEVICE_ID_JOYPAD_LL
   inp[3] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y) > threshold;   //  RETRO_DEVICE_ID_JOYPAD_LD
   inp[4] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y) < -threshold;  //  RETRO_DEVICE_ID_JOYPAD_LU
   inp[5] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X) > threshold;  // RETRO_DEVICE_ID_JOYPAD_RR
   inp[6] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X) < -threshold; // RETRO_DEVICE_ID_JOYPAD_RL
   inp[7] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y) > threshold;  // RETRO_DEVICE_ID_JOYPAD_RD
   inp[8] = input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y) < -threshold; // RETRO_DEVICE_ID_JOYPAD_RU

   /* ability to adjust mouse speed in hatari GUI */
   // sorry stick to pad remappings.. don't use analog since it and dpad is used for mouse control
   for (i = 0; i < RETRO_DEVICE_ID_JOYPAD_LAST; ++i)
   {
       int which = 0;

       inp[0] = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i);
       which = inp[i < 16 ? 0 : i - 15];

       if (i < RETRO_DEVICE_ID_JOYPAD_LR || i > RETRO_DEVICE_ID_JOYPAD_LU)
       {
           d = RETRO_DEVICE_ID_JOYPAD_L2;//mouse gui speed down
           if (mapper_keys[i] == MOUSE_SLOWER)
           {
               if (which && mbt[d] == 0)
               {
                   mbt[d] = 1;
                   selected[d] = i;
               }
               else if (mbt[d] == 1 && !which)
               {
                   mbt[d] = 0;
                   selected[d] = -1;
                   PAS--; if (PAS < 1)PAS = MAXPAS;
                   status_update_mousespeed = 60;
               }
           }
           d = RETRO_DEVICE_ID_JOYPAD_R2;//mouse gui speed up
           if (mapper_keys[i] == MOUSE_FASTER)
           {
               if (which && mbt[d] == 0)
               {
                   mbt[d] = 1;
                   selected[d] = i;
               }
               else if (mbt[d] == 1 && !which)
               {
                   mbt[d] = 0;
                   selected[d] = -1;
                   PAS++; if (PAS > MAXPAS)PAS = 1;
                   status_update_mousespeed = 60;
               }
           }
           d = RETRO_DEVICE_ID_JOYPAD_START;// Hatari GUI
           if (mapper_keys[i] == TOGGLE_SETTINGS)
           {
               if (which && mbt[d] == 0)
               {
                   mbt[d] = 1;
                   selected[d] = i;
               }
               else if (mbt[d] == 1 && !which && selected[d] == i)
               {
                   mbt[d] = 0;
                   selected[d] = -1;
                   exitgui = 1;
                   status_update_mousespeed = 0;
               }
           }
           d = RETRO_DEVICE_ID_JOYPAD_L;//show/hide status (either joystick)
           if (mapper_keys[i] == TOGGLE_STATUSBAR)
           {
               if (which && mbt[d] == 0)
               {
                   mbt[d] = 1;
                   selected[d] = i;
               }
               else if (mbt[d] == 1 && !which && selected[d] == i)
               {
                   mbt[d] = 0;
                   selected[d] = -1;
                   STATUTON = -STATUTON;
                   Screen_SetFullUpdate();
               }
           }
       }
   }
#else
   /* ability to adjust mouse speed in hatari GUI */
   i = RETRO_DEVICE_ID_JOYPAD_L2;
   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i] == 0)
       mbt[i] = 1;
   else if (mbt[i] == 1 && !input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i))
   {
       mbt[i] = 0;
       PAS--; if (PAS < 0)PAS = MAXPAS;
       status_update_mousespeed = 60;
   }

   i = RETRO_DEVICE_ID_JOYPAD_R2;
   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i] == 0)
       mbt[i] = 1;
   else if (mbt[i] == 1 && !input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i))
   {
       mbt[i] = 0;
       PAS++; if (PAS > MAXPAS)PAS = 1;
       status_update_mousespeed = 60;
   }

   // START to exit GUI
   i = RETRO_DEVICE_ID_JOYPAD_START;
   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i] == 0)
       mbt[i] = 1;
   else if (mbt[i] == 1 && !input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i))
   {
       mbt[i] = 0;
       exitgui = 1;
       status_update_mousespeed = 0;
   }
#endif /* 1 */

   //emulate mouse with joy analog left
   al[0] = (input_state_cb(0, RETRO_DEVICE_ANALOG, hatari_mouse_control_stick, RETRO_DEVICE_ID_ANALOG_X));
   al[1] = (input_state_cb(0, RETRO_DEVICE_ANALOG, hatari_mouse_control_stick, RETRO_DEVICE_ID_ANALOG_Y));

   Deadzone(al);

   al[0] = (al[0] * PAS) / MAXPAS;
   al[1] = (al[1] * PAS) / MAXPAS;

   mouse_x += al[0]/1024;
   mouse_y += al[1]/1024;

   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT))
      mouse_x += PAS*3;
   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT))
      mouse_x -= PAS*3;
   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN))
      mouse_y += PAS*3;
   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP))
      mouse_y -= PAS*3;

   mouse_l=input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B);
   mouse_r=input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A);

   // joystick mouse control is relative
   gmx+=mouse_x;
   gmy+=mouse_y;

   // pointer mouse control is absolute, and overrides joystick when you move it
   int point_x = input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_X);
   int point_y = input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_Y);
   int point_b = input_state_cb(0, RETRO_DEVICE_POINTER, 0, RETRO_DEVICE_ID_POINTER_PRESSED);

   if (point_x != point_x_last || point_y != point_y_last)
   {
      const int PMIN = -0x7FFF;
      const int PMAX = 0x7FFF;
      point_x_last   = point_x;
      point_y_last   = point_y;
      gmx            = ((point_x - PMIN) * retrow) / (PMAX - PMIN);
      gmy            = ((point_y - PMIN) * retroh) / (PMAX - PMIN);
   }

   slowdown=1;

   if(mmbL==0 && (mouse_l || point_b))
   {
      mmbL=1;
      touch=1;
   }
   else if(mmbL==1 && (!mouse_l && !point_b))
   {
      mmbL=0;
      touch=-1;
   }

   // POINTER doesn't have a right button, but Hatari GUI doesn't need it
   if (mmbR==0 && mouse_r)
      mmbR=1;
   else if (mmbR==1 && !mouse_r)
      mmbR=0;

   if (gmx<0)
      gmx=0;
   if (gmx>retrow-1)
      gmx=retrow-1;
   if (gmy<0)
      gmy=0;
   if (gmy>retroh-1)
      gmy=retroh-1;

   if (status_update_mousespeed)
   {
       if (hatari_joymousestatus_display == 0)
           status_update_mousespeed = 0;
       // bummer.. can't do here because xbox one crashes due to libco
       //else
       //    retro_status(60, "Speed:%d", PAS);

       if (status_update_mousespeed > 0)
           status_update_mousespeed--;
   }

   if (STATUTON == 1)
       Print_Statut();
}
