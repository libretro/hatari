#include "libretro.h"
#include "libretro-hatari.h"
#include "graph.h"
#include "vkbd.h"
#include "joy.h"
#include "screen.h"
#include "video.h"	/* FIXME: video.h is dependent on HBL_PALETTE_LINES from screen.h */
#include "ikbd.h"

//CORE VAR
extern const char *retro_save_directory;
extern const char *retro_system_directory;
extern const char *retro_content_directory;
char RETRO_DIR[512];
char RETRO_TOS[512];
extern bool hatari_nomouse;

//HATARI PROTOTYPES
#include "configuration.h"
#include "file.h"
extern bool Dialog_DoProperty(void);
extern void Screen_SetFullUpdate(void);
extern void Main_HandleMouseMotion(void);
extern void Main_UnInit(void);
extern int  hmain(int argc, char *argv[]);
extern int Reset_Cold(void);

//TIME
#ifdef __CELLOS_LV2__
#include "sys/sys_time.h"
#include "sys/timer.h"
#define usleep  sys_timer_usleep
#else
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#endif

//VIDEO
extern SDL_Surface *sdlscrn; 
unsigned short int bmp[1024*1024];
unsigned char savbkg[1024*1024* 2];

//SOUND
short signed int SNDBUF[1024*2];
int snd_sampler = 44100 / 50;

//PATH
char RPATH[512];

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

int hatari_mapper_serialize_size()
{
	return 1023; // +1 byte for version makes an even 1kb header
}

static bool hatari_mapper_serialize_bidi(char* data, char version)
{
	// ignoring version, there is only one version so far
	// (Might be okay to append to this list without increasing version
	// if 0 is an acceptable fallback for the new value,
	// but do not reorder without increasing version number.)
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
	int NUMjoy=0; serialize_int(&NUMjoy); // this variable was removed
	int firstps=0; serialize_int(&firstps); // this variable was removed
	serialize_int(&mbL);
	serialize_int(&mbR);
	serialize_int(&mmbL);
	serialize_int(&mmbR);
	serialize_int(&oldi);
	serialize_int(&vkx);
	serialize_int(&vky);
	for (int i=0; i<5;  ++i) serialize_int(&(vkflag[i]));
	for (int i=0; i<16; ++i) serialize_int(&(mbt[i]));

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
	int pauseg_old = pauseg;
	bool result = hatari_mapper_serialize_bidi((char*)data, version);
	exitgui = 0;
	if (pauseg_old && !pauseg) // want to exit GUI, turn pauseg back on and tell it to exit on its own
	{
		pauseg = pauseg_old;
		exitgui = 1;
	}
	return result;
}

// input state

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

long GetTicks(void)
{ // in MSec
#ifndef _ANDROID_

#ifdef __CELLOS_LV2__

   //#warning "GetTick PS3\n"

   unsigned long        ticks_micro;
   uint64_t secs;
   uint64_t nsecs;

   sys_time_get_current_time(&secs, &nsecs);
   ticks_micro =  secs * 1000000UL + (nsecs / 1000);

   return ticks_micro/1000;
#else
   struct timeval tv;
   gettimeofday (&tv, NULL);
   return (tv.tv_sec*1000000 + tv.tv_usec)/1000;
#endif

#else

   struct timespec now;
   clock_gettime(CLOCK_MONOTONIC, &now);
   return (now.tv_sec*1000000 + now.tv_nsec/1000)/1000;
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

   //printf("fin prepare tex:%dx%dx%d\n",bitmp->w,bitmp->h,bitmp->format->BytesPerPixel);
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
   int i;
   for(i=0;i<320;i++)
   {
      Key_Sate[i]=input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0,i) ? 0x80: 0;

      if (i == RETROK_SPACE) // can map R3 to space bar
      {
         char joyspace = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R3) ? 0x80 : 0;
         Key_Sate[i] |= joyspace;
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
   if (al[0] <= -DEADZONE) al[0] += DEADZONE;
   if (al[1] <= -DEADZONE) al[1] += DEADZONE;
   if (al[0] >=  DEADZONE) al[0] -= DEADZONE;
   if (al[1] >=  DEADZONE) al[1] -= DEADZONE;
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
   int i;

   int mouse_l;
   int mouse_r;
   int16_t mouse_x;
   int16_t mouse_y;

   MXjoy0=0;
   MXjoy1=0;

   if(oldi!=-1)
   {
      IKBD_PressSTKey(oldi,0);
      oldi=-1;
   }

   input_poll_cb();

   Process_key();

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
      Screen_SetFullUpdate();
   }

   i=RETRO_DEVICE_ID_JOYPAD_SELECT;//mouse/joy toggle
   if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i]==0 )
      mbt[i]=1;
   else if ( mbt[i]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) )
   {
      mbt[i]=0;
      MOUSEMODE=-MOUSEMODE;
   }

   i=RETRO_DEVICE_ID_JOYPAD_L2;//mouse gui speed down
   if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i]==0 )
      mbt[i]=1;
   else if ( mbt[i]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) )
   {
      mbt[i]=0;
      PAS--;if(PAS<1)PAS=MAXPAS;
   }

   i=RETRO_DEVICE_ID_JOYPAD_R2;//mouse gui speed up
   if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i]==0 )
      mbt[i]=1;
   else if ( mbt[i]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) )
   {
      mbt[i]=0;
      PAS++;if(PAS>MAXPAS)PAS=1;
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

   // joystick 2

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

   // virtual keyboard (prevents other joystick 1 input and mouse)

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

      i=RETRO_DEVICE_ID_JOYPAD_B;
      if(input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i)  && vkflag[4]==0)
         vkflag[4]=1;
      else if( !input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i)  && vkflag[4]==1)
      {
         vkflag[4]=0;
         i=check_vkey2(vkx,vky);

         if(i==-2)
         {
            NPAGE=-NPAGE;oldi=-1;
            //Clear interface zone
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

   if(MOUSEMODE < 0)
   {
      //Joy mode (joystick controls joystick, mouse controls mouse)

      //emulate Joy0 with joy analog left 
      al[0] =(input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X));
      al[1] =(input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y));

      /* Directions */
      if (al[1] <= JOYRANGE_UP_VALUE)
         MXjoy0 |= ATARIJOY_BITMASK_UP;
      else if (al[1] >= JOYRANGE_DOWN_VALUE)
         MXjoy0 |= ATARIJOY_BITMASK_DOWN;

      if (al[0] <= JOYRANGE_LEFT_VALUE)
         MXjoy0 |= ATARIJOY_BITMASK_LEFT;
      else if (al[0] >= JOYRANGE_RIGHT_VALUE)
         MXjoy0 |= ATARIJOY_BITMASK_RIGHT;

      if( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP   ) ) MXjoy0 |= ATARIJOY_BITMASK_UP;
      if( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN ) ) MXjoy0 |= ATARIJOY_BITMASK_DOWN;
      if( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT ) ) MXjoy0 |= ATARIJOY_BITMASK_LEFT;
      if( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT) ) MXjoy0 |= ATARIJOY_BITMASK_RIGHT;
      if( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B)     ) MXjoy0 |= ATARIJOY_BITMASK_FIRE;

      // Joy autofire
      if( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A) )
      {
         MXjoy0 |= ATARIJOY_BITMASK_FIRE;
         if ((nVBLs&0x7)<4)
            MXjoy0 &= ~ATARIJOY_BITMASK_FIRE;
      }

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
   else // MOUSEMODE >= 0
   {
      //Mouse mode (joystick controls mouse)
      fmousex=fmousey=0;

      //emulate mouse with joy analog left
      al[0] = (input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X));
      al[1] = (input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y));
      Deadzone(al);
      al[0] = (al[0] * PAS) / MAXPAS;
      al[1] = (al[1] * PAS) / MAXPAS;
      fmousex += al[0]/1024;
      fmousey += al[1]/1024;

      //emulate mouse with dpad
      if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT))
         fmousex += PAS;
      if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT))
         fmousex -= PAS;
      if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN))
         fmousey += PAS;
      if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP))
         fmousey -= PAS;

      mouse_l=input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B);
      mouse_r=input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A);
   }

   if(mbL==0 && mouse_l)
   {
      mbL=1;
      Keyboard.bLButtonDown |= BUTTON_MOUSE;
   }
   else if(mbL==1 && !mouse_l)
   {
      Keyboard.bLButtonDown &= ~BUTTON_MOUSE;
      mbL=0;
   }

   if(mbR==0 && mouse_r)
   {
      mbR=1;
      Keyboard.bRButtonDown |= BUTTON_MOUSE;
   }
   else if(mbR==1 && !mouse_r)
   {
      Keyboard.bRButtonDown &= ~BUTTON_MOUSE;
      mbR=0;
   }

   Main_HandleMouseMotion();

   if(STATUTON==1)
      Print_Statut();
}

void input_gui(void)
{
   input_poll_cb();

   int i;
   int mouse_l;
   int mouse_r;
   int16_t mouse_x,mouse_y;
   mouse_x=mouse_y=0;

   if(slowdown>0)return;

   // ability to adjust mouse speed in hatari GUI

   i=RETRO_DEVICE_ID_JOYPAD_L2;
   if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i]==0 )
      mbt[i]=1;
   else if ( mbt[i]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) )
   {
      mbt[i]=0;
      PAS--;if(PAS<0)PAS=MAXPAS;
   }

   i=RETRO_DEVICE_ID_JOYPAD_R2;
   if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i]==0 )
      mbt[i]=1;
   else if ( mbt[i]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) )
   {
      mbt[i]=0;
      PAS++;if(PAS>MAXPAS)PAS=1;
   }

   // START to exit GUI

   i=RETRO_DEVICE_ID_JOYPAD_START;
   if ( input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) && mbt[i]==0 )
      mbt[i]=1;
   else if ( mbt[i]==1 && ! input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i) )
   {
      mbt[i]=0;
      exitgui=1;
   }

   //emulate mouse with joy analog left
   al[0] = (input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X));
   al[1] = (input_state_cb(0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y));
   Deadzone(al);
   al[0] = (al[0] * PAS) / MAXPAS;
   al[1] = (al[1] * PAS) / MAXPAS;
   mouse_x += al[0]/1024;
   mouse_y += al[1]/1024;

   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT))
      mouse_x += PAS;
   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT))
      mouse_x -= PAS;
   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN))
      mouse_y += PAS;
   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP))
      mouse_y -= PAS;
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
      point_x_last = point_x;
      point_y_last = point_y;
      const int PMIN = -0x7FFF;
      const int PMAX = 0x7FFF;
      gmx = ((point_x - PMIN) * retrow) / (PMAX - PMIN);
      gmy = ((point_y - PMIN) * retroh) / (PMAX - PMIN);
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
   if(mmbR==0 && mouse_r)
      mmbR=1;
   else if(mmbR==1 && !mouse_r)
      mmbR=0;

   if (gmx<0)
      gmx=0;
   if (gmx>retrow-1)
      gmx=retrow-1;
   if (gmy<0)
      gmy=0;
   if (gmy>retroh-1)
      gmy=retroh-1;
}
