#include "libretro.h"

#include "libretro-hatari.h"

#include "STkeymap.h"

cothread_t mainThread;
cothread_t emuThread;

int CROP_WIDTH;
int CROP_HEIGHT;
int VIRTUAL_WIDTH ;
int retrow=1024; 
int retroh=1024;

extern unsigned short int bmp[1024*1024];
extern int STATUTON,SHOWKEY,SHIFTON,pauseg,SND ,snd_sampler;
extern short signed int SNDBUF[1024*2];
extern char RPATH[512];
extern char RETRO_DIR[512];

#include "cmdline.c"

extern void update_input(void);
extern void texture_init(void);
extern void texture_uninit(void);
extern void Emu_init();
extern void Emu_uninit();

const char *retro_save_directory;
const char *retro_system_directory;
const char *retro_content_directory;

static retro_video_refresh_t video_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_environment_t environ_cb;

void retro_set_environment(retro_environment_t cb)
{
   environ_cb = cb;

   struct retro_variable variables[] = {
      {
         "Hatari_resolution",
         "Internal resolution; 640x480|832x576|832x588|800x600|960x720|1024x768|1024x1024",

      },
      { NULL, NULL },
   };

   cb(RETRO_ENVIRONMENT_SET_VARIABLES, variables);
}


static void update_variables(void)
{
   struct retro_variable var = {
      .key = "Hatari_resolution",
   };

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      char *pch;
      char str[100];
	  snprintf(str, sizeof(str), "%s", var.value);

      pch = strtok(str, "x");
      if (pch)
         retrow = strtoul(pch, NULL, 0);
      pch = strtok(NULL, "x");
      if (pch)
         retroh = strtoul(pch, NULL, 0);

      fprintf(stderr, "[libretro-test]: Got size: %u x %u.\n", retrow, retroh);

      CROP_WIDTH =retrow;
      CROP_HEIGHT= (retroh-80);
      VIRTUAL_WIDTH = retrow;
      texture_init();
      //reset_screen();
   }

}

static void retro_wrap_emulator()
{    

   pre_main(RPATH);

   pauseg=-1;

   environ_cb(RETRO_ENVIRONMENT_SHUTDOWN, 0); 

   // Were done here
   co_switch(mainThread);

   // Dead emulator, but libco says not to return
   while(true)
   {
      LOGI("Running a dead emulator.");
      co_switch(mainThread);
   }
}

void Emu_init(){

#ifdef RETRO_AND
   //you can change this after in core option if device support to setup a 832x576 res 
   retrow=640; 
   retroh=480;
   MOUSEMODE=1;
#endif

   update_variables();

   memset(Key_Sate,0,512);
   memset(Key_Sate2,0,512);

   if(!emuThread && !mainThread)
   {
      mainThread = co_active();
      emuThread = co_create(65536*sizeof(void*), retro_wrap_emulator);
   }

}

void Emu_uninit(){
   texture_uninit();
}

void retro_shutdown_hatari(void)
{
   printf("SHUTDOWN\n");
   texture_uninit();
   environ_cb(RETRO_ENVIRONMENT_SHUTDOWN, NULL);
}

void retro_reset(void){

}

void retro_init(void)
{    	
   const char *system_dir = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &system_dir) && system_dir)
   {
      // if defined, use the system directory			
      retro_system_directory=system_dir;		
   }		   

   const char *content_dir = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_CONTENT_DIRECTORY, &content_dir) && content_dir)
   {
      // if defined, use the system directory			
      retro_content_directory=content_dir;		
   }			

   const char *save_dir = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, &save_dir) && save_dir)
   {
      // If save directory is defined use it, otherwise use system directory
      retro_save_directory = *save_dir ? save_dir : retro_system_directory;      
   }
   else
   {
      // make retro_save_directory the same in case RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY is not implemented by the frontend
      retro_save_directory=retro_system_directory;
   }

   if(retro_system_directory==NULL)sprintf(RETRO_DIR, "%s\0",".");
   else sprintf(RETRO_DIR, "%s\0", retro_system_directory);

   printf("Retro SYSTEM_DIRECTORY %s\n",retro_system_directory);
   printf("Retro SAVE_DIRECTORY %s\n",retro_save_directory);
   printf("Retro CONTENT_DIRECTORY %s\n",retro_content_directory);

   enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_RGB565;
   if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt))
   {
      fprintf(stderr, "RGB565 is not supported.\n");
      exit(0);
   }

   Emu_init();
   texture_init();
}

void retro_deinit(void)
{	 
   Emu_uninit(); 

   if(emuThread)
   {	 
      co_delete(emuThread);
      emuThread = 0;
   }

   LOGI("Retro DeInit\n");
}

unsigned retro_api_version(void)
{
   return RETRO_API_VERSION;
}

void retro_set_controller_port_device(unsigned port, unsigned device)
{
   (void)port;
   (void)device;
}

void retro_get_system_info(struct retro_system_info *info)
{
   memset(info, 0, sizeof(*info));
   info->library_name     = "Hatari";
   info->library_version  = "1.8";
   info->valid_extensions = "ST|MSA|ZIP|STX|DIM|IPF";
   info->need_fullpath    = true;
   info->block_extract = false;

}

void retro_get_system_av_info(struct retro_system_av_info *info)
{
   struct retro_game_geometry geom = { retrow, retroh, 1024, 1024,4.0 / 3.0 };
   struct retro_system_timing timing = { 50.0, 44100.0 };

   info->geometry = geom;
   info->timing   = timing;
}

void retro_set_audio_sample(retro_audio_sample_t cb)
{
   audio_cb = cb;
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb)
{
   audio_batch_cb = cb;
}

void retro_set_video_refresh(retro_video_refresh_t cb)
{
   video_cb = cb;
}

void retro_run(void)
{
   int x;

   bool updated = false;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated)
      update_variables();

   if(pauseg==0){

      update_input();

      if(SND==1){
         signed short int *p=(signed short int *)SNDBUF;
         for(x=0;x<snd_sampler;x++)audio_cb(*p++,*p++);			
      }	
   }   

   if(ConfigureParams.Screen.bAllowOverscan || SHOWKEY==1 || STATUTON==1 || pauseg==1 )video_cb(bmp,retrow,retroh, retrow<< 1);
   // EMU ST FULLSCREEN NO BORDER
   else video_cb(bmp,640/*retrow*/,400/*retrow-80*/,retrow << 1);

   co_switch(emuThread);

}

bool retro_load_game(const struct retro_game_info *info)
{
   const char *full_path;

   (void)info;

   full_path = info->path;

   strcpy(RPATH,full_path);

   co_switch(emuThread);

   return true;
}

void retro_unload_game(void){

   pauseg=0;
}

unsigned retro_get_region(void)
{
   return RETRO_REGION_NTSC;
}

bool retro_load_game_special(unsigned type, const struct retro_game_info *info, size_t num)
{
   (void)type;
   (void)info;
   (void)num;
   return false;
}

size_t retro_serialize_size(void)
{
   return 0;
}

bool retro_serialize(void *data_, size_t size)
{
   return false;
}

bool retro_unserialize(const void *data_, size_t size)
{
   return false;
}

void *retro_get_memory_data(unsigned id)
{
   (void)id;
   return NULL;
}

size_t retro_get_memory_size(unsigned id)
{
   (void)id;
   return 0;
}

void retro_cheat_reset(void) {}

void retro_cheat_set(unsigned index, bool enabled, const char *code)
{
   (void)index;
   (void)enabled;
   (void)code;
}

