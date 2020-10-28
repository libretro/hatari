#include "libretro.h"

#include "libretro-hatari.h"

#include "STkeymap.h"
#include "memorySnapShot.h"

#include "retro_strings.h"
#include "retro_files.h"
#include "retro_disk_control.h"
static dc_storage* dc;

// LOG
retro_log_printf_t log_cb;

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
extern char RETRO_TOS[512];
extern struct retro_midi_interface *MidiRetroInterface;

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
static char buf[64][4096] = { 0 };

unsigned int video_config = 0;
#define HATARI_VIDEO_HIRES 	0x04
#define HATARI_VIDEO_CROP 	0x08

#define HATARI_VIDEO_OV_LO 	0x00
#define HATARI_VIDEO_CR_LO 	HATARI_VIDEO_CROP
#define HATARI_VIDEO_OV_HI 	HATARI_VIDEO_HIRES
#define HATARI_VIDEO_CR_HI 	HATARI_VIDEO_HIRES|HATARI_VIDEO_CROP

int CHANGE_RATE = 0, CHANGEAV_TIMING = 0;
float FRAMERATE = 50.0, SAMPLERATE = 44100.0;

extern bool UseNonPolarizedLowPassFilter;
bool hatari_twojoy = true;
bool hatari_fastfdc = true;
bool hatari_borders = true;
char hatari_frameskips[2];
char savestate_fname[RETRO_PATH_MAX];

static struct retro_input_descriptor input_descriptors[] = {
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Up" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Down" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Left" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Right" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Turbo Fire" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Fire" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "Virtual keyboard" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Shift keyboard toggle" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Joystick/Mouse toggle" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Hatari Settings" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Mouse speed down" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Mouse speed up" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "Status display" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R2, "Virtual keyboard page" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R3, "Keyboard space" },
   { 0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X, "Joystick/Mouse X" },
   { 0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y, "Joystick/Mouse Y" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Up" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Down" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Left" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Right" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Turbo Fire" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Fire" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "Status display" },
   { 1, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X, "Joystick X" },
   { 1, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y, "Joystick Y" },
   // Terminate
   { 0 }
};

void retro_set_environment(retro_environment_t cb)
{
   environ_cb = cb;

   static struct retro_core_option_definition core_options[] =
   {
       // Second joystick
       {
         "hatari_twojoy",
         "Enable second joystick",
         "Enables a second joystick on port 2, may conflict with mouse.",
         {
           { "true", "enabled" },
           { "false", "disabled" },
           { NULL, NULL },
         },
         "true"
       },
       // Floppy speed
       {
         "hatari_fastfdc",
         "Fast floppy access",
         "Decreases the time spent loading from disk",
         {
           { "true", "enabled" },
           { "false", "disabled" },
           { NULL, NULL },
         },
         "true"
       },
       // Audio
       {
         "hatari_polarized_filter",
         "Polarized audio filter",
         "Uses hatari's polarized lowpass filters on audio to simulate distortion",
         {
           { "false", "disabled" },
           { "true", "enabled" },
           { NULL, NULL },
         },
         "false"
       },
       // Video
       {
         "hatari_video_hires",
         "High resolution",
         "Needs restart",
         {
            { "true", "enabled" },
            { "false", "disabled" },
            { NULL, NULL },
         },
         "true"
      },
      {
         "hatari_video_crop_overscan",
         "Crop overscan",
         "Needs restart",
         {
            { "false", "disabled" },
            { "true", "enabled" },
            { NULL, NULL },
         },
         "false"
      },  
      {
         "hatari_frameskips",
         "Frameskip",
         "Needs restart",
         {
            { "0", "disabled" },
            { "1", NULL },
            { "2", NULL },
            { "3", NULL },
            { "4", NULL },
            { "5", "auto (max 5)" },
            { "10", "auto (max 10)" },
            { NULL, NULL },
         },
         "0"
      },
	  
      { NULL, NULL, NULL, {{0}}, NULL },
	};

   // Set options or variables
   int i = 0;
   int j = 0;
   unsigned version = 0;
   if (cb(RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION, &version) && (version == 1))
      cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS, core_options);
   else
   {
      // Fallback for older API
      static struct retro_variable variables[64] = { 0 };
      i = 0;
      while(core_options[i].key)
      {
         buf[i][0] = 0;
         variables[i].key = core_options[i].key;
         strcpy(buf[i], core_options[i].desc);
         strcat(buf[i], "; ");
         strcat(buf[i], core_options[i].default_value);
         j = 0;
         while(core_options[i].values[j].value && j < RETRO_NUM_CORE_OPTION_VALUES_MAX)
         {
            strcat(buf[i], "|");
            strcat(buf[i], core_options[i].values[j].value);
            ++j;
         };
         variables[i].value = buf[i];
         ++i;
      };
      variables[i].key = NULL;
      variables[i].value = NULL;
      cb( RETRO_ENVIRONMENT_SET_VARIABLES, variables);
   }
}

static void update_variables(void)
{
   struct retro_variable var = {0};

   // Joystick
   var.key = "hatari_twojoy";
   var.value = NULL;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      hatari_twojoy = true;
      if(strcmp(var.value, "false") == 0)
         hatari_twojoy = false;
      ConfigureParams.Joysticks.Joy[0].nJoystickMode = hatari_twojoy ? JOYSTICK_REALSTICK : JOYSTICK_DISABLED;
   }

   // Floppy
   var.key = "hatari_fastfdc";
   var.value = NULL;
   bool new_hatari_fastfdc = false;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if(strcmp(var.value, "true") == 0)
         new_hatari_fastfdc = true;
   }
   if (new_hatari_fastfdc != hatari_fastfdc) // switch immediately
   {
      hatari_fastfdc = new_hatari_fastfdc;
      ConfigureParams.DiskImage.FastFloppy = hatari_fastfdc;
   }

   // Audio
   var.key = "hatari_polarized_filter";
   var.value = NULL;
   UseNonPolarizedLowPassFilter = true;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if(strcmp(var.value, "true") == 0)
         UseNonPolarizedLowPassFilter = false;
   }

   // Video
   var.key = "hatari_video_hires";
   var.value = NULL;
   int new_video_config = 0;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if(strcmp(var.value, "true") == 0)
         new_video_config |= HATARI_VIDEO_HIRES;
   }

   var.key = "hatari_video_crop_overscan";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if(strcmp(var.value, "true") == 0)
         new_video_config |= HATARI_VIDEO_CROP;
   }

   var.key = "hatari_frameskips";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      strncpy((char*)hatari_frameskips, var.value, 2);
   }

   if (new_video_config != video_config)
   {
      video_config = new_video_config;
      switch(video_config)
      {
         case HATARI_VIDEO_OV_LO:
            retrow = 416;
            retroh = 260;
            hatari_borders = true;
            break;
         case HATARI_VIDEO_CR_LO:
            retrow = 320;
            retroh = 200;
            // Strange, do not work if set to false...
            hatari_borders = true;
            break;
         case HATARI_VIDEO_OV_HI:
            retrow = 832;
            retroh = 520;
            hatari_borders = true;
            break;
         case HATARI_VIDEO_CR_HI:
            retrow = 832;
            retroh = 520;
            hatari_borders = false;
            break;
      }

      log_cb(RETRO_LOG_INFO, "Resolution %u x %u.\n", retrow, retroh);

      CROP_WIDTH =retrow;
      CROP_HEIGHT= (retroh-80);
      VIRTUAL_WIDTH = retrow;
      texture_init();
   }
}

static void retro_wrap_emulator()
{
log_cb(RETRO_LOG_INFO, "WRAP EMU THD\n");
   pre_main(RPATH);
log_cb(RETRO_LOG_INFO, "EXIT EMU THD\n");
   pauseg=-1;

   environ_cb(RETRO_ENVIRONMENT_SHUTDOWN, 0); 

   // Were done here
   co_switch(mainThread);

   // Dead emulator, but libco says not to return
   while(true)
   {
      log_cb(RETRO_LOG_INFO, "Running a dead emulator.");
      co_switch(mainThread);
   }
}

void Emu_init()
{
#ifdef RETRO_AND
   //you can change this after in core option if device support to setup a 832x576 res 
   retrow=640; 
   retroh=480;
   MOUSEMODE=1;
#endif
   memset(Key_Sate,0,512);
   memset(Key_Sate2,0,512);

   if(!emuThread && !mainThread)
   {
      mainThread = co_active();
      emuThread = co_create(65536*sizeof(void*), retro_wrap_emulator);
   }

   update_variables();
}

void Emu_uninit()
{
   texture_uninit();
}

void retro_shutdown_hatari(void)
{
   log_cb(RETRO_LOG_INFO, "SHUTDOWN\n");
   texture_uninit();
   environ_cb(RETRO_ENVIRONMENT_SHUTDOWN, NULL);
}

void retro_reset(void){
   update_variables();
   Reset_Warm();
}

//*****************************************************************************
//*****************************************************************************
// Disk control
extern bool Floppy_EjectDiskFromDrive(int Drive);
extern const char* Floppy_SetDiskFileName(int Drive, const char *pszFileName, const char *pszZipPath);
extern bool Floppy_InsertDiskIntoDrive(int Drive);

static bool disk_set_eject_state(bool ejected)
{
	if (dc)
	{
		dc->eject_state = ejected;
		
		if(dc->eject_state)
			return Floppy_EjectDiskFromDrive(0);
		else
			return Floppy_InsertDiskIntoDrive(0);			
	}
	
	return true;
}

static bool disk_get_eject_state(void)
{
	if (dc)
		return dc->eject_state;
	
	return true;
}

static unsigned disk_get_image_index(void)
{
	if (dc)
		return dc->index;
	
	return 0;
}

static bool disk_set_image_index(unsigned index)
{
	// Insert disk
	if (dc)
	{
		// Same disk...
		// This can mess things in the emu
		if(index == dc->index)
			return true;
		
		if ((index < dc->count) && (dc->files[index]))
		{
			dc->index = index;
			Floppy_SetDiskFileName(0, dc->files[index], NULL);
			log_cb(RETRO_LOG_INFO, "Disk (%d) inserted into drive A : %s\n", dc->index+1, dc->files[dc->index]);
			return true;
		}
	}
	
	return false;
}

static unsigned disk_get_num_images(void)
{
	if (dc)
		return dc->count;

	return 0;
}

static bool disk_replace_image_index(unsigned index, const struct retro_game_info *info)
{
	if (dc)
	{
		if (index >= dc->count)
			return false;

		if(dc->files[index])
		{
			free(dc->files[index]);
			dc->files[index] = NULL;
		}

		// TODO : Handling removing of a disk image when info = NULL

		if(info != NULL)
			dc->files[index] = strdup(info->path);
	}

    return false;
}

static bool disk_add_image_index(void)
{
	if (dc)
	{
		if(dc->count <= DC_MAX_SIZE)
		{
			dc->files[dc->count] = NULL;
			dc->count++;
			return true;
		}
	}

    return false;
}

static struct retro_disk_control_callback disk_interface = {
   disk_set_eject_state,
   disk_get_eject_state,
   disk_get_image_index,
   disk_set_image_index,
   disk_get_num_images,
   disk_replace_image_index,
   disk_add_image_index,
};

//*****************************************************************************
//*****************************************************************************
// Init
static void fallback_log(enum retro_log_level level, const char *fmt, ...)
{
}

void retro_init(void)
{    	
	struct retro_log_callback log;	
	const char *system_dir = NULL;
	dc = dc_create();

	// Init log
	if (environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log))
		log_cb = log.log;
	else
		log_cb = fallback_log;

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

   log_cb(RETRO_LOG_INFO, "Retro SYSTEM_DIRECTORY %s\n",retro_system_directory);
   log_cb(RETRO_LOG_INFO, "Retro SAVE_DIRECTORY %s\n",retro_save_directory);
   log_cb(RETRO_LOG_INFO, "Retro CONTENT_DIRECTORY %s\n",retro_content_directory);

   enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_RGB565;
   if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt))
   {
      log_cb(RETRO_LOG_ERROR, "RGB565 is not supported.\n");
      exit(0);
   }

	environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, input_descriptors);

   static struct retro_midi_interface midi_interface;

   if(environ_cb(RETRO_ENVIRONMENT_GET_MIDI_INTERFACE, &midi_interface))
      MidiRetroInterface = &midi_interface;
   else
      MidiRetroInterface = NULL;

 	// Disk control interface
	environ_cb(RETRO_ENVIRONMENT_SET_DISK_CONTROL_INTERFACE, &disk_interface);

   // Savestates
   static uint32_t quirks = RETRO_SERIALIZATION_QUIRK_INCOMPLETE | RETRO_SERIALIZATION_QUIRK_MUST_INITIALIZE | RETRO_SERIALIZATION_QUIRK_CORE_VARIABLE_SIZE;
   environ_cb(RETRO_ENVIRONMENT_SET_SERIALIZATION_QUIRKS, &quirks);

   // Init
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

	// Clean the m3u storage
	if(dc)
	{
		dc_free(dc);
		dc = 0;
	}

   log_cb(RETRO_LOG_INFO, "Retro DeInit\n");
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
#ifndef GIT_VERSION
#define GIT_VERSION ""
#endif
   info->library_version  = "1.8" GIT_VERSION;
   info->valid_extensions = "ST|MSA|ZIP|STX|DIM|IPF|M3U";
   info->need_fullpath    = true;
   info->block_extract = false;

}

void retro_get_system_av_info(struct retro_system_av_info *info)
{
   struct retro_game_geometry geom = { retrow, retroh, 1024, 1024, 4.0 / 3.0 };
   struct retro_system_timing timing = { FRAMERATE, SAMPLERATE };

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

void update_timing(void)
{
   struct retro_system_av_info system_av_info;
   retro_get_system_av_info(&system_av_info);
   system_av_info.timing.fps = FRAMERATE;
   system_av_info.timing.sample_rate = SAMPLERATE;
   environ_cb(RETRO_ENVIRONMENT_SET_SYSTEM_AV_INFO, &system_av_info);
   snd_sampler = (int)SAMPLERATE / (int)FRAMERATE;
}

void retro_run(void)
{
   int x;
   unsigned width = 640;
   unsigned height = 400;

   bool updated = false;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated)
      update_variables();

   if (CHANGE_RATE || CHANGEAV_TIMING)
   {
      if (CHANGEAV_TIMING)
      {
         update_timing();
         CHANGEAV_TIMING = 0;
         CHANGE_RATE = 0;
      }
	  
      if (CHANGE_RATE)
      {
         update_timing();
         CHANGEAV_TIMING = 0;
         CHANGE_RATE = 0;
      }	  
   }

   if(pauseg==0)
   {
      update_input();

      if(SND==1)
      {
         int16_t *p=(int16_t*)SNDBUF;

         for(x = 0; x < snd_sampler; x++)
            audio_cb(*p++,*p++);
      }
   }

   if(ConfigureParams.Screen.bAllowOverscan || SHOWKEY==1 || STATUTON==1 || pauseg==1 )
   {
      width  = retrow;
      height = retroh;
   }
   video_cb(bmp, width, height, retrow<< 1);

   co_switch(emuThread);

   if (MidiRetroInterface && MidiRetroInterface->output_enabled())
      MidiRetroInterface->flush();
}

#define M3U_FILE_EXT "m3u"

bool retro_load_game(const struct retro_game_info *info)
{
   // Init
   environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, input_descriptors);
   path_join(RETRO_TOS, RETRO_DIR, "tos.img");
   
   // Verify if tos.img is present
   if(!file_exists(RETRO_TOS))
   {
	   log_cb(RETRO_LOG_ERROR, "TOS image '%s' not found. Content cannot be loaded\n", RETRO_TOS);
	   return false;
   }

   const char *full_path;

   (void)info;

   full_path = info->path;
	
	update_variables();

	// If it's a m3u file
	if(strendswith(full_path, M3U_FILE_EXT))
	{
		// Parse the m3u file
		dc_parse_m3u(dc, full_path);

		// Some debugging
		log_cb(RETRO_LOG_INFO, "m3u file parsed, %d file(s) found\n", dc->count);
		for(unsigned i = 0; i < dc->count; i++)
		{
			log_cb(RETRO_LOG_INFO, "file %d: %s\n", i+1, dc->files[i]);
		}	
	}
	else
	{
		// Add the file to disk control context
		// Maybe, in a later version of retroarch, we could add disk on the fly (didn't find how to do this)
		dc_add_file(dc, full_path);
	}

	// Init first disk
	dc->index = 0;
	dc->eject_state = false;
	log_cb(RETRO_LOG_INFO, "Disk (%d) inserted into drive A : %s\n", dc->index+1, dc->files[dc->index]);
	strcpy(RPATH,dc->files[0]);

	memset(SNDBUF,0,1024*2*2);

	co_switch(emuThread);

   return true;
}

void retro_unload_game(void)
{
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

const char RETRO_SAVE_VERSION = 1;
char* retro_save_buffer = NULL;
int retro_save_pos = 0;
int retro_save_size = 0;
int retro_save_head = 1; // bytes reserved for libretro header/state
int retro_save_max = 0;
int retro_save_error = 0;

extern int hatari_mapper_serialize_size();
extern bool hatari_mapper_serialize(char* data, char version);
extern bool hatari_mapper_unserialize(const char* data, char version);

size_t retro_serialize_size(void)
{
	return 10 * 1024 * 1024; // Hatari uncompressed savestates seem to be about 6MB
}

bool retro_serialize(void *data_, size_t size)
{
	retro_save_max = size;
	retro_save_head = hatari_mapper_serialize_size() + 1;
	if (size < retro_save_head) return false;
	retro_save_buffer = data_;
	memset(retro_save_buffer, 0, size);
	retro_save_buffer[0] = RETRO_SAVE_VERSION;
	retro_save_error = hatari_mapper_serialize(data_+1, retro_save_buffer[0]) ? 0 : 1;
	retro_save_size = retro_save_head;
	MemorySnapShot_Capture("", false);
	return retro_save_error == 0;
}

bool retro_unserialize(const void *data_, size_t size)
{
	retro_save_max = size;
	retro_save_head = hatari_mapper_serialize_size() + 1;
	if (size < retro_save_head) return false;
	retro_save_buffer = (void*)data_; // discarding const
	if (retro_save_buffer[0] != RETRO_SAVE_VERSION) return false; // unknown version
	retro_save_error = hatari_mapper_unserialize(data_+1, retro_save_buffer[0]) ? 0 : 1;
	retro_save_size = size;
	MemorySnapShot_Restore("", false);
	return retro_save_error == 0;
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

