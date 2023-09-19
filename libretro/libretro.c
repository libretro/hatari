#include <stdarg.h>
#include <string/stdstring.h>
#include <sys/stat.h>
#include <dirent.h>
#include "libretro.h"
#include "libretro-hatari.h"
#include "libretro_core_options.h"
#include "hatari-mapper.h"

#include "STkeymap.h"
#include "memorySnapShot.h"
#include "main.h"
#include "screen.h"

#include "retro_strings.h"
#include "retro_files.h"
#include "retro_disk_control.h"

static dc_storage* dc;

// LOG
static void fallback_log(enum retro_log_level level, const char* fmt, ...);
retro_log_printf_t log_cb = fallback_log;

cothread_t mainThread;
cothread_t emuThread;

int CROP_WIDTH;
int CROP_HEIGHT;
int VIRTUAL_WIDTH ;
int retrow=1024; 
int retroh=1024;

extern unsigned short int bmp[1024*1024];
extern int STATUTON, SHOWKEY, SHIFTON, MOUSEMODE, PAS, SND;
extern int pauseg, snd_sampler;
extern short signed int SNDBUF[1024*2];
extern char RPATH[RETRO_PATH_MAX];
extern char RPATH2[RETRO_PATH_MAX];
extern char RETRO_HD[RETRO_PATH_MAX];
extern char RETRO_GD[RETRO_PATH_MAX];
extern char RETRO_DIR[RETRO_PATH_MAX];
extern char RETRO_TOS[RETRO_PATH_MAX];
extern char RETRO_IDE[RETRO_PATH_MAX];
extern char RETRO_FID[RETRO_PATH_MAX];

extern struct retro_midi_interface *MidiRetroInterface;

#define MAX_TOS_IMAGES  50
char TOS_Filenames[MAX_TOS_IMAGES][RETRO_PATH_MAX];
int num_TOS_files = 0;

#include "cmdline.c"

extern void update_input(void);
extern void texture_init(void);
extern void texture_uninit(void);
//extern void Screen_SetFullUpdate(void);
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
bool closedViaEmu = false;
bool libretro_runloop_active = false;
// core option vars
extern bool UseNonPolarizedLowPassFilter;
bool hatari_twojoy = true;
bool hatari_nomouse = false;
bool hatari_nokeys = false;
bool hatari_fastfdc = true;
bool hatari_borders = true;
bool hatari_autoloadb = true;
bool hatari_fastboot = false;
bool hatari_start_in_mouse_mode = true;
bool hatari_led_status_display = true;
int hatari_autoload_config = false;
int hatari_forcerefresh = 0;
int hatari_emulated_mouse_speed = 2;
int hatari_mouse_control_stick = 0;
int hatari_boot_hd = 1;
int hatari_joymousestatus_display = 1;
int hatari_reset_type = 1;
char hatari_machinetype[7];
char hatari_ramsize[3];
char hatari_frameskips[3];
char hatari_writeprotect_floppy[5];
char hatari_writeprotect_hd[5];

char savestate_fname[RETRO_PATH_MAX];
unsigned hatari_devices[4];

#define RETRO_DEVICE_HATARI_KEYBOARD RETRO_DEVICE_SUBCLASS(RETRO_DEVICE_KEYBOARD, 0)
#define RETRO_DEVICE_HATARI_JOYSTICK RETRO_DEVICE_SUBCLASS(RETRO_DEVICE_JOYPAD, 1)

#if 1
static struct retro_input_descriptor input_descriptors[] = {
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R2, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L3, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R3, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X, "Set in RetroPad Mapping" },
   { 0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y, "Set in RetroPad Mapping" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Joystick Up" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Joystick Down" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Joystick Left" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Joystick Right" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Turbo fire" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Fire" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "Status display" },
   { 1, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X, "Joystick X" },
   { 1, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y, "Joystick Y" },
   // Terminate
   { 0 }
};
#else // old settings before RETRO_MAPPER added
static struct retro_input_descriptor input_descriptors[] = {
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Joystick Up" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Joystick Down" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Joystick Left" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Joystick Right" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Turbo fire/Mouse button 2" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Fire/Mouse button 1" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "Virtual keyboard" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Shift keyboard toggle" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Joystick/Mouse toggle" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Hatari Settings" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Status display" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Virtual keyboard page" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "Mouse speed down" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R2, "Mouse speed up" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L3, "" },
   { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R3, "Keyboard space" },
   { 0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X, "Joystick/Mouse X" },
   { 0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y, "Joystick/Mouse Y" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Joystick Up" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Joystick Down" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Joystick Left" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Joystick Right" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Turbo fire" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Fire" },
   { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "Status display" },
   { 1, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X, "Joystick X" },
   { 1, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y, "Joystick Y" },
   // Terminate
   { 0 }
};
#endif

void retro_message(unsigned int frames, int level, const char *format, ...)
{
    struct retro_message msg;
    struct retro_message_ext msg_ext;
    char msg_passed[512], msg_local[512];
    unsigned int message_interface_version;
    va_list ap;

    msg_local[0] = msg_passed[0] = 0;

    if (string_is_empty(format))
        return;

    va_start(ap, format);
    vsprintf(msg_passed, format, ap);
    va_end(ap);

    snprintf(msg_local, sizeof(msg_local), "Hatari: %s", msg_passed);

    msg.msg = msg_local;
    msg.frames = frames;

    msg_ext.msg = msg_local;
    msg_ext.duration = frames;
    msg_ext.priority = 3;
    msg_ext.level = level;
    msg_ext.target = RETRO_MESSAGE_TARGET_OSD;
    msg_ext.type = RETRO_MESSAGE_TYPE_NOTIFICATION;
    msg_ext.progress = -1;

    if (environ_cb(RETRO_ENVIRONMENT_GET_MESSAGE_INTERFACE_VERSION, &message_interface_version) && (message_interface_version >= 1))
    {
        environ_cb(RETRO_ENVIRONMENT_SET_MESSAGE_EXT, (void*)&msg_ext);
    }
    else
        environ_cb(RETRO_ENVIRONMENT_SET_MESSAGE, (void*)&msg);
}

void retro_status(unsigned int frames, const char *format, ...)
{
    struct retro_message msg;
    struct retro_message_ext msg_ext;
    char msg_passed[512], msg_local[512];
    unsigned int message_interface_version;
    va_list ap;

    msg_local[0] = msg_passed[0] = 0;

    if (string_is_empty(format))
        return;

    va_start(ap, format);
    vsprintf(msg_passed, format, ap);
    va_end(ap);

    snprintf(msg_local, sizeof(msg_local), "%s", msg_passed);

    msg.msg = msg_local;
    msg.frames = frames;

    msg_ext.msg = msg_local;
    msg_ext.duration = frames;
    msg_ext.priority = 3;
    msg_ext.level = RETRO_LOG_INFO;
    msg_ext.target = RETRO_MESSAGE_TARGET_OSD;
    msg_ext.type = RETRO_MESSAGE_TYPE_STATUS;
    msg_ext.progress = -1;

    if (environ_cb(RETRO_ENVIRONMENT_GET_MESSAGE_INTERFACE_VERSION, &message_interface_version) && (message_interface_version >= 1))
    {
        environ_cb(RETRO_ENVIRONMENT_SET_MESSAGE_EXT, (void*)&msg_ext);
    }
    else
        environ_cb(RETRO_ENVIRONMENT_SET_MESSAGE, (void*)&msg);
}

void libretro_set_dynamic_core_options()
{
    unsigned version = 0;
    struct retro_core_option_v2_definition *def;

    /* Fill out core option TOS images found in system\hatari\tos\ */
    if ((def = libretro_get_core_option_def("hatari_tosimage")))
    {
        int j = 0, i = 0;
        const char* TF = &TOS_Filenames[0][0];
        char msg[256];

        if (num_TOS_files > 0 && !strcmp(TF, "tos.img"))
        {
            // there it is!
            def->default_value = "<tos.img>";
            def->values[0].label = "system\\tos.img";
            ++i;
        }
        else
        {
            // nope RETRO_TOS.
            def->values[0].label = "system\\tos.img (not found)";
        }

        for (; (i < num_TOS_files) && (j < MAX_TOS_IMAGES); ++i)
        {
            TF = &TOS_Filenames[i][0];

            if (!strendswith(TF, "img"))
                continue;

            def->values[j + 1].value = TF;
            def->values[j + 1].label = TF;

            ++j;
        }
    }
    else
    {
        retro_message(6000, RETRO_LOG_ERROR, "hatarib_tos entry not found");
    }

    // Retro_mapping.  Code from Vice64 by rsn887 and sonninnos.
    /* Fill in the values for all the retro mappers */
    int i = 0;
    int j = 0;
    int hotkey = 0;
    int hotkeys_skipped = 0;
    /* Count special hotkeys */
    while (retro_keys[j].value[0] && j < RETRO_NUM_CORE_OPTION_VALUES_MAX - 1)
    {
        if (retro_keys[j].id < 0)
            hotkeys_skipped++;
        ++j;
    }
    while (option_defs_us[i].key)
    {
        if (strstr(option_defs_us[i].key, "hatari_mapper_"))
        {
            /* Show different key list for hotkeys (special negatives removed) */
            if (strstr(option_defs_us[i].key, "hatari_mapper_joymouse")
                || strstr(option_defs_us[i].key, "hatari_mapper_mouse_speed_down")
                || strstr(option_defs_us[i].key, "hatari_mapper_mouse_speed_up")
                || strstr(option_defs_us[i].key, "hatari_mapper_vkbd_toggle")
                || strstr(option_defs_us[i].key, "hatari_mapper_vkbd_page_toggle")
                || strstr(option_defs_us[i].key, "hatari_mapper_keyboard_shift_toggle")
                || strstr(option_defs_us[i].key, "hatari_mapper_hatari_settings")
                || strstr(option_defs_us[i].key, "hatari_mapper_statusbar"))

                hotkey = 1;
            else
                hotkey = 0;

            j = 0;
            if (hotkey)
            {
                while (retro_keys[j].value[0] && j < RETRO_NUM_CORE_OPTION_VALUES_MAX - 1)
                {
                    if (j == 0) /* "---" unmapped */
                    {
                        option_defs_us[i].values[j].value = retro_keys[j].value;
                        option_defs_us[i].values[j].label = retro_keys[j].label;
                    }
                    else
                    {
                        option_defs_us[i].values[j].value = retro_keys[j + hotkeys_skipped ].value;
                        option_defs_us[i].values[j].label = retro_keys[j + hotkeys_skipped ].label;
                    }
                    ++j;
                }
            }
            else
            {
                while (retro_keys[j].value[0] && j < RETRO_NUM_CORE_OPTION_VALUES_MAX - 1)
                {
                    option_defs_us[i].values[j].value = retro_keys[j].value;
                    option_defs_us[i].values[j].label = retro_keys[j].label;
                    ++j;
                }
            }
            option_defs_us[i].values[j].value = NULL;
            option_defs_us[i].values[j].label = NULL;
        }
        ++i;
    }
}

void retro_set_environment(retro_environment_t cb)
{
    bool option_cats_supported;

    DIR *dir;
    struct dirent *de;
    struct stat s;
    const char* system_dir = NULL;
    char filepath[RETRO_PATH_MAX], msg[1024];

    num_TOS_files = 0;
    environ_cb = cb;

    if (environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &system_dir) && system_dir)
    {
        // if defined, use the system directory			
        retro_system_directory = system_dir;
    }

    // compile list of available TOS images
    sprintf(filepath, "%s%stos.img", retro_system_directory, RETRO_PATH_SEPARATOR );

    if (!stat(filepath, &s) && !(s.st_mode & S_IFDIR))
        strcpy(&TOS_Filenames[num_TOS_files++][0], "tos.img");

    sprintf(filepath, "%s%shatari%stos%s", retro_system_directory, RETRO_PATH_SEPARATOR, RETRO_PATH_SEPARATOR, RETRO_PATH_SEPARATOR);

    dir = opendir(filepath);

    if (dir)
    {
        while ((de = readdir(dir)))
        {
            sprintf(filepath, "%s%shatari%stos%s%s", retro_system_directory, RETRO_PATH_SEPARATOR, RETRO_PATH_SEPARATOR, RETRO_PATH_SEPARATOR, de->d_name);

            if (!stat(filepath, &s))
            {
                if (!(s.st_mode & S_IFDIR))
                    strcpy(&TOS_Filenames[num_TOS_files++][0], de->d_name);
                else
                    strcpy(&TOS_Filenames[num_TOS_files++][0], de->d_name);
            }
        }
        closedir(dir);
    }

    //sprintf(msg, "%i TOS files found in %s.", num_TOS_files, filepath);
    //retro_message(msg, 6000, 0);

    static const struct retro_controller_description p1_controllers[] = {
      { "ATARI Joystick", RETRO_DEVICE_HATARI_JOYSTICK },
      { "ATARI Keyboard", RETRO_DEVICE_HATARI_KEYBOARD },
    };
    static const struct retro_controller_description p2_controllers[] = {
      { "ATARI Joystick", RETRO_DEVICE_HATARI_JOYSTICK },
      { "ATARI Keyboard", RETRO_DEVICE_HATARI_KEYBOARD },
    };

    static const struct retro_controller_info ports[] = {
      { p1_controllers, 2  }, // port 1
      { p2_controllers, 2  }, // port 2
      { NULL, 0 }
    };

    // Disable.  Have user use RETROPAD_MAPPINGS to reduce confusion.
    //cb(RETRO_ENVIRONMENT_SET_CONTROLLER_INFO, (void*)ports);

    /* Set core dynamic options*/
    libretro_set_dynamic_core_options();

    /* Initialise core options */
    libretro_set_core_options(environ_cb, &option_cats_supported);
}

static void update_retropad_variables(void)
{
    struct retro_variable var = { 0 };

    /* RetroPad */
    var.key = "hatari_mapper_up";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_UP] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_down";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_DOWN] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_left";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_LEFT] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_right";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_RIGHT] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_select";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_SELECT] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_start";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_START] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_b";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_B] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_a";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_A] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_y";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_Y] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_x";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_X] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_l";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_L] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_r";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_R] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_l2";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_L2] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_r2";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_R2] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_l3";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_L3] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_r3";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_R3] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_lr";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_LR] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_ll";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_LL] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_ld";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_LD] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_lu";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_LU] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_rr";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_RR] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_rl";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_RL] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_rd";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_RD] = retro_keymap_id(var.value);
    }

    var.key = "hatari_mapper_ru";
    var.value = NULL;
    if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
    {
        mapper_keys[RETRO_DEVICE_ID_JOYPAD_RU] = retro_keymap_id(var.value);
    }
}

static void update_variables(void)
{
   struct retro_variable var = {0};

   // System -> Atari Computer Machine Type 
   var.key = "hatari_machinetype";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value) 
   {
       strcpy((char*)hatari_machinetype, var.value);
   }

   // System -> amount of emulated RAM
   var.key = "hatari_ramsize";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       strcpy((char*)hatari_ramsize, var.value);
   }

   // System -> selected TOS image
   var.key = "hatari_tosimage";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       if (strcmp(var.value, "default") == 0)
           sprintf(RETRO_TOS, "%s%stos.img", retro_system_directory, RETRO_PATH_SEPARATOR);
       else
           sprintf(RETRO_TOS, "%s%shatari%stos%s%s", retro_system_directory, RETRO_PATH_SEPARATOR, RETRO_PATH_SEPARATOR, RETRO_PATH_SEPARATOR, var.value);
   }

   // System -> Fast boot
   var.key = "hatari_fastboot";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       if (strcmp(var.value, "true") == 0)
           hatari_fastboot = true;
       else
           hatari_fastboot = false;
   }

   // System -> Reset Type
   var.key = "hatari_reset_type";
   var.value = NULL;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       hatari_reset_type = string_to_unsigned(var.value);
   }

   // Input -> Start with emulated mouse active
   // only set when first starting
   if (!libretro_runloop_active)
   {
       var.key = "hatari_start_in_mouse_mode";
       var.value = NULL;
       if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
       {
           MOUSEMODE = 1;
           if (strcmp(var.value, "false") == 0)
               MOUSEMODE = -1;
       }
   }

   // Input -> Which stick controls the mouse
   var.key = "hatari_mouse_control_stick";
   var.value = NULL;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       hatari_mouse_control_stick = string_to_unsigned(var.value);
   }

   // Input -> Emulated mouse speed
   // only set when first starting
   if (!libretro_runloop_active)
   {
       var.key = "hatari_emulated_mouse_speed";
       var.value = NULL;
       if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
       {
           PAS = string_to_unsigned(var.value);
       }
   }

   // Input -> Two joysticks connected?
   var.key = "hatari_twojoy";
   var.value = NULL;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      hatari_twojoy = true;
      if(strcmp(var.value, "false") == 0)
         hatari_twojoy = false;
      ConfigureParams.Joysticks.Joy[0].nJoystickMode = hatari_twojoy ? JOYSTICK_REALSTICK : JOYSTICK_DISABLED;
   }

   // Enable/Disable Hardware Mouse
   var.key = "hatari_nomouse";
   var.value = NULL;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      hatari_nomouse = false;
      if(strcmp(var.value, "true") == 0)
         hatari_nomouse = true;
      // This doesn't correspond to any Hatari configuration setting, as far as I could find,
      // but instead just disables input from the RetroArch mouse device for the user (outside the Hatari GUI),
      // to prevent conflicts if needed, because Hatari seems to automatically merge/combine mouse and joystick in a weird way.
   }

   // Enable/Disable Hardware Keyboard
   var.key = "hatari_nokeys";
   var.value = NULL;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      hatari_nokeys = false;
      if(strcmp(var.value, "true") == 0)
         hatari_nokeys = true;
   }

   // Video High resolution
   // Say bye bye.  All this did was create confusion.
   //var.key = "hatari_video_hires";
   //var.value = NULL;
   //int new_video_config = 0;

   //if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   //{
   //    if (strcmp(var.value, "true") == 0)
   //        new_video_config |= HATARI_VIDEO_HIRES;
   //}

   // Video Crop Overscan
   var.key = "hatari_video_crop_overscan";
   var.value = NULL;
   bool old_hatari_borders = hatari_borders;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       if (strcmp(var.value, "true") == 0)
           hatari_borders = false;
       //new_video_config |= HATARI_VIDEO_CROP;
       else
           hatari_borders = true;
           
   }

   //leave here for archival purposes.  Or just in case I retract my changes.  :P
   //if (new_video_config != video_config)
   //{
   //    video_config = new_video_config;
   //    switch (video_config)
   //    {
   //    case HATARI_VIDEO_OV_LO:
   //        retrow = 416;
   //        retroh = 274;
   //        hatari_borders = true;
   //        break;
   //    case HATARI_VIDEO_CR_LO:
   //        retrow = 366;
   //        retroh = 243;
   //        // Strange, do not work if set to false...  double image
   //        hatari_borders = false;
   //        break;
   //    case HATARI_VIDEO_OV_HI:
   //        retrow = 832;
   //        retroh = 548;
   //        hatari_borders = true;
   //        break;
   //    case HATARI_VIDEO_CR_HI:
   //        retrow = 732;
   //        retroh = 486;
   //        hatari_borders = false;
   //        break;
   //    }

   //    retrow = 832;
   //    retroh = 552;
   //    log_cb(RETRO_LOG_INFO, "Resolution %u x %u.\n", retrow, retroh);

   //     moved to retro_run()
   //    CROP_WIDTH = retrow;
   //    CROP_HEIGHT = (retroh - 80);
   //    VIRTUAL_WIDTH = retrow;

   //    texture_init();

   //     It's alive! It's alive!
   //    if (libretro_runloop_active)
   //    {
   //        ConfigureParams.Screen.bAllowOverscan = hatari_borders;
   //        //why do all the work when the Hatari core can do the work for us?
   //        Screen_ModeChanged();
   //        Screen_SetFullUpdate();
   //    }
   //}

   if (hatari_borders != old_hatari_borders && libretro_runloop_active)
   {
       retrow = 832;
       retroh = 552;
       log_cb(RETRO_LOG_INFO, "Resolution %u x %u.\n", retrow, retroh);
       texture_init();

       ConfigureParams.Screen.bAllowOverscan = hatari_borders;
       //why do all the work when the Hatari core can do the work for us?
       Screen_ModeChanged();
       Screen_SetFullUpdate();
   }

   // Video Force Refresh
   var.key = "hatari_forcerefresh";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       hatari_forcerefresh = atoi(var.value);       //  Auto = 0, NTSC = 1, PAL = 2
   }

   // Set location of joystick/mouse toggle message
   var.key = "hatari_joymousestatus_display";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       hatari_joymousestatus_display = atoi(var.value);  // Off = 0, Status = 1, OSD = 2;
   }

   // Show drive activity in status info
   var.key = "hatari_led_status_display";
   var.value = NULL;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       hatari_led_status_display = false;
       if (strcmp(var.value, "true") == 0)
           hatari_led_status_display = true;
   }

   // Set frameskip
   var.key = "hatari_frameskips";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       strcpy((char*)hatari_frameskips, var.value);
   }

   // Fast Floppy
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
   
   // Auto Insert Disk B
   var.key = "hatari_autoloadb";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       if (strcmp(var.value, "true") == 0)
           hatari_autoloadb = true;
       else
           hatari_autoloadb = false;
   }

   // Boot from hard disk.  Currently disabled.. does not seem to be working.
   var.key = "hatari_boot_hd";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       if (strcmp(var.value, "true") == 0)
           hatari_boot_hd = true;
       else
           hatari_boot_hd = false;
   }

   // Write protect floppy disks.
   var.key = "hatari_writeprotect_floppy";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       strcpy((char*)hatari_writeprotect_floppy, var.value);
   }

   // Write protect hard drives.
   var.key = "hatari_writeprotect_hd";
   var.value = NULL;

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       strcpy((char*)hatari_writeprotect_hd, var.value);
   }

   // Audio
   var.key = "hatari_polarized_filter";
   var.value = NULL;
   UseNonPolarizedLowPassFilter = true;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       if (strcmp(var.value, "false") == 0)
           UseNonPolarizedLowPassFilter = false;
   }

   // Autoload hatari.cfg
   var.key = "hatari_autoload_config";
   var.value = NULL;
   hatari_autoload_config = false;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
       if (strcmp(var.value, "true") == 0)
           hatari_autoload_config = true;
   }

   // Retropad
   update_retropad_variables();
}

static void retro_wrap_emulator()
{
    // This crashes retro arch on xbox one if logging enabled.  Moved into retro_load_game()
    //log_cb(RETRO_LOG_INFO, "WRAP EMU THD\n");
    pre_main(RPATH);
    // This one does too..  moved into retro_run()
    //log_cb(RETRO_LOG_INFO, "EXIT EMU THD\n");

    closedViaEmu = true;
    pauseg=-1;

    // moved into retro_run() to preven crashing on xbox when logging is enabled.  Relies on closedViaEmu being set to tru.
    //environ_cb(RETRO_ENVIRONMENT_SHUTDOWN, 0); 

    // Were done here
    co_switch(mainThread);

    // Dead emulator, but libco says not to return
    while(true)
    {
        // This crashes retro arch on xbox one if logging enabled.  Moved into retro_load_game()
        //log_cb(RETRO_LOG_INFO, "Running a dead emulator.");
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
   //  Allow Hatari to "properly" close and exit
   if ( !closedViaEmu )
       Main_UnInit();
}

void retro_shutdown_hatari(void)
{
   log_cb(RETRO_LOG_INFO, "SHUTDOWN\n");
   texture_uninit();
   environ_cb(RETRO_ENVIRONMENT_SHUTDOWN, NULL);
}

//*****************************************************************************
//*****************************************************************************
// Disk control
extern bool Floppy_EjectDiskFromDrive(int Drive);
extern const char* Floppy_SetDiskFileNameNone(int Drive);
extern const char* Floppy_SetDiskFileName(int Drive, const char *pszFileName, const char *pszZipPath);
extern bool Floppy_InsertDiskIntoDrive(int Drive);

// might not need this if floppy image is the only type we are going to worry about.
static int get_image_unit()
{
    int unit = dc->unit;
    if (dc->index < dc->count)
    {
        if (dc_get_image_type(dc->files[dc->index]) == DC_IMAGE_TYPE_FLOPPY)
            dc->unit = DC_IMAGE_TYPE_FLOPPY;
        else
            dc->unit = DC_IMAGE_TYPE_FLOPPY;
    }
    else
        unit = DC_IMAGE_TYPE_FLOPPY;

    return unit;
}

static void disk_insert_image()
{
    if (dc->unit == DC_IMAGE_TYPE_FLOPPY)
    {
        // check if in Drive B ( mount to A will fail if so ).  If it is.. eject from drive B first
        if (strcmp(dc->files[dc->index], ConfigureParams.DiskImage.szDiskFileName[1]) == 0)
        {
            Floppy_EjectDiskFromDrive(1);
            Floppy_SetDiskFileNameNone(1);
        }

        if (Floppy_SetDiskFileName(0, dc->files[dc->index], NULL) == NULL)
        {
            retro_message(3000, RETRO_LOG_ERROR, "[disk_insert_image] mount in Drive A failed.\n", dc->files[dc->index]);
            log_cb(RETRO_LOG_INFO, "[disk_insert_image] Disk (%d) Error : %s\n", dc->index + 1, dc->files[dc->index]);
            return;
        }

#ifndef HAVE_CAPSIMAGE
        //display warning if IPF image selected when CAPS image support is not compiled.
        if (strendswith(dc->files[dc->index], "ipf"))
        {
            retro_message(6000, RETRO_LOG_WARN, "Warning: CAPS support for IPF files not in this build");
            log_cb(RETRO_LOG_WARN, "Warning: CAPS support for IPS files not in this build\n");
        }
#endif

        log_cb(RETRO_LOG_INFO, "[disk_insert_image] Disk (%d) inserted into drive A : %s\n", dc->index + 1, dc->files[dc->index]);
    }
    else
    {
        log_cb(RETRO_LOG_INFO, "[disk_insert_image] unsupported image-type : %u\n", dc->unit);
    }
}

static bool disk_set_eject_state(bool ejected)
{
    if (dc)
    {
        int unit = get_image_unit();

        if (dc->eject_state == ejected)
            return true;

        if (ejected && dc->index <= dc->count && dc->files[dc->index] != NULL)
            Floppy_EjectDiskFromDrive(0);
        else if (!ejected && dc->index < dc->count && dc->files[dc->index] != NULL)
        {
            disk_insert_image();
            Floppy_InsertDiskIntoDrive(0);
        }

        dc->eject_state = ejected;

        return true;
    }

    return false;
}

/* Gets current eject state. The initial state is 'not ejected'. */
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

/* Sets image index. Can only be called when disk is ejected.
 * The implementation supports setting "no disk" by using an
 * index >= get_num_images().
 */
static bool disk_set_image_index(unsigned index)
{
    // Insert image
    if (dc)
    {
        if (index == dc->index)
            return true;

        if (dc->replace)
        {
            dc->replace = false;
            index = 0;
        }

        if (index < dc->count && dc->files[index])
        {
            dc->index = index;
            int unit = get_image_unit();
            log_cb(RETRO_LOG_INFO, "[retro_set_image_index] Unit (%d) image (%d/%d) inserted: %s\n", dc->index + 1, unit, dc->count, dc->files[dc->index]);
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

/* Adds a new valid index (get_num_images()) to the internal disk list.
 * This will increment subsequent return values from get_num_images() by 1.
 * This image index cannot be used until a disk image has been set
 * with replace_image_index.
 */
static bool disk_add_image_index(void)
{
    if (dc)
    {
        if (dc->count <= DC_MAX_SIZE)
        {
            dc->files[dc->count] = NULL;
            dc->names[dc->count] = NULL;
            dc->types[dc->count] = DC_IMAGE_TYPE_NONE;
            dc->count++;
            return true;
        }
    }

    return false;
}

static bool disk_replace_image_index(unsigned index, const struct retro_game_info* info)
{
    if (dc)
    {
        if (info != NULL)
        {
            int error = dc_replace_file(dc, index, info->path);

            if (error == 2)
                retro_message(8000, RETRO_LOG_ERROR, "Duplicate Disk selected.  Use Index");
        }
        else
        {
            dc_remove_file(dc, index);
        }

        return true;
    }

    return false;
}

static bool disk_get_image_path(unsigned index, char* path, size_t len)
{
    if (len < 1)
        return false;

    if (dc)
    {
        if (index < dc->count)
        {
            if (!string_is_empty(dc->files[index]))
            {
                strncpy(path, dc->files[index], len);
                return true;
            }
        }
    }

    return false;
}

static bool disk_get_image_label(unsigned index, char* label, size_t len)
{
    if (len < 1)
        return false;

    if (dc)
    {
        if (index < dc->count)
        {
            if (!string_is_empty(dc->names[index]))
            {
                strncpy(label, dc->names[index], len);
                return true;
            }
        }
    }

    return false;
}

void disk_rotate_images()
{
    char *p = 0;

    //nothing to see here..move along!
    if (dc->count < 2)
        return;

    // eject current disk
    disk_set_eject_state(true);

    // rotate
    dc->index++;
    if (dc->index >= dc->count)
        dc->index = 0;

    // insert next disk in line
    disk_set_eject_state(false);

    //let the user know
    p = strrchr(dc->files[dc->index], RETRO_PATH_SEPARATOR[0]);

    if (p)
        retro_message(3000, RETRO_LOG_INFO, "Rotate to disk %s in drive A.", p+1 );
    else
        retro_message(3000, RETRO_LOG_INFO, "Rotate to disk %s in drive A.", dc->files[dc->index]);
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

static struct retro_disk_control_ext_callback disk_interface_ext = {
   disk_set_eject_state,
   disk_get_eject_state,
   disk_get_image_index,
   disk_set_image_index,
   disk_get_num_images,
   disk_replace_image_index,
   disk_add_image_index,
   NULL, /* disk_set_initial_image, not even sure if I want to use this */
   disk_get_image_path,
   disk_get_image_label,
};

void retro_reset(void)
{
    update_variables();

    if (hatari_reset_type)
    {
        /* Reset DC index to first entry */
        if (dc)
        {
            dc->index = 0;
            disk_set_eject_state(true);
            disk_set_eject_state(false);
        }

        Reset_Cold();
    }
    else
        Reset_Warm();
}

//*****************************************************************************
//*****************************************************************************
// Init
static void fallback_log(enum retro_log_level level, const char* fmt, ...)
{
    va_list va;

    (void)level;

    va_start(va, fmt);
    vfprintf(stderr, fmt, va);
    va_end(va);
}

void retro_init(void)
{    	
	struct retro_log_callback log;	
	const char *system_dir = NULL;
    unsigned dci_version = 0;

    libretro_runloop_active = false;
	dc = dc_create();

	// Init log
    if (environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log))
        log_cb = log.log;
    else
        retro_message(6000, RETRO_LOG_ERROR, "Unable to init Retroarch Log");

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

    if(retro_system_directory==NULL)
        sprintf(RETRO_DIR, "%s\0",".");
    else 
        sprintf(RETRO_DIR, "%s\0", retro_system_directory);

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
    if (environ_cb(RETRO_ENVIRONMENT_GET_DISK_CONTROL_INTERFACE_VERSION, &dci_version) && (dci_version >= 1))
        environ_cb(RETRO_ENVIRONMENT_SET_DISK_CONTROL_EXT_INTERFACE, &disk_interface_ext);
    else
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
    //(void)port;
    //(void)device;

    if (port < 2)
    {
        //if (device == RETRO_DEVICE_HATARI_JOYSTICK)
        //{
        //    struct retro_input_descriptor *d = input_descriptors;

        //    for (d; d->port != port; ++d)
        //    {
        //    }

        //    d += 4;
        //    d->description = "Hello There";

        //    environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, input_descriptors);
        //}

        hatari_devices[port] = device; 
    }
}

void retro_get_system_info(struct retro_system_info *info)
{
   memset(info, 0, sizeof(*info));
   info->library_name     = "Hatari";
#ifndef GIT_VERSION
#define GIT_VERSION ""
#endif
   info->library_version  = "1.8" GIT_VERSION;
   info->valid_extensions = "ST|MSA|ZIP|STX|DIM|IPF|VHD|GEM|IDE|M3U";
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
   unsigned width = retrow;
   unsigned height = retroh;

   bool updated = false;
   libretro_runloop_active = true;

   CROP_WIDTH = retrow;
   CROP_HEIGHT = (retroh - 80);
   VIRTUAL_WIDTH = retrow;

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

   //if(ConfigureParams.Screen.bAllowOverscan || SHOWKEY==1 || STATUTON==1 || pauseg==1 )
   //{
   //     width  = ???;
   //     height = ???;
   //}

   //for debug purposes
   //retro_status(100, "W=%i, H=%i", width, height);
   video_cb(bmp, width, height, retrow<< 1);

   co_switch(emuThread);

   if (MidiRetroInterface && MidiRetroInterface->output_enabled())
      MidiRetroInterface->flush();

   // this prevents retroarch from crashing on xbox when logs are enabled
   if (closedViaEmu)
   {
       log_cb(RETRO_LOG_INFO, "EXIT EMU THD\n");
       environ_cb(RETRO_ENVIRONMENT_SHUTDOWN, 0);
   }
}

#define M3U_FILE_EXT "m3u"

bool retro_load_game(const struct retro_game_info *info)
{
    char msg[256];
    bool LoadDriveA = false;
    char* ptr;

    closedViaEmu = false;

    // Clear all paths
    RPATH[0] = RPATH2[0] = RETRO_GD[0] = RETRO_HD[0] = RETRO_IDE[0] = 0;

    // Init
    environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, input_descriptors);

    //path_join(RETRO_TOS, RETRO_DIR, "tos.img");

    // Verify if tos.img is present
    if (!file_exists(RETRO_TOS))
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
		//log_cb(RETRO_LOG_INFO, "m3u file parsed, %d file(s) found\n", dc->count);
		for(unsigned i = 0; i < dc->count; i++)
		{
			log_cb(RETRO_LOG_INFO, "file %d: %s\n", i+1, dc->files[i]);
		}	

        LoadDriveA = true;
	}
	else if (strendswith(full_path, "st") ||
        strendswith(full_path, "msa") ||
        strendswith(full_path, "stx") ||
        strendswith(full_path, "dim") ||
        strendswith(full_path, "ipf"))
	{
		// Add the file to disk control context
		// Maybe, in a later version of retroarch, we could add disk on the fly (didn't find how to do this)
		dc_add_file(dc, full_path);
        LoadDriveA = true;
	}

#ifndef HAVE_CAPSIMAGE
    //display warning if IPF image selected when CAPS image support is not compiled.
    if (strendswith(full_path, "ipf"))
    {
        retro_message(6000, RETRO_LOG_WARN, "Warning: CAPS support for IPF files not in this build");
        log_cb(RETRO_LOG_WARN, "Warning: CAPS support for IPS files not in this build\n");
    }
#endif

    if (strendswith(full_path, "ide"))
    {
        strcpy(RETRO_IDE, full_path);
        log_cb(RETRO_LOG_INFO, "HardDisk (%s) inserted into IDE Master Slot\n", RETRO_IDE);
    }
    else if (strendswith(full_path, "vhd"))
    {
        strcpy(RETRO_HD, full_path);
        log_cb(RETRO_LOG_INFO, "HardDisk (%s) inserted into ASCI Slot\n", RETRO_HD);
    }
    else if (strendswith(full_path, "gem"))
    {
        char bootfilepath[RETRO_PATH_MAX];

        strncpy(RETRO_GD, full_path, strlen(full_path)-4);
        log_cb(RETRO_LOG_INFO, "GEMDOS HDD emulation set to \"(%s)\".\n", RETRO_GD);
        sprintf(bootfilepath, "%s%shatari%sBOOT.ST", retro_system_directory, RETRO_PATH_SEPARATOR, RETRO_PATH_SEPARATOR );
        dc_add_file(dc, bootfilepath);
        LoadDriveA = true;
    }

    if (LoadDriveA)
    {
        // Init first disk
        dc->index = 0;
        dc->eject_state = false;
        strcpy(RPATH, dc->files[0]);
        log_cb(RETRO_LOG_INFO, "Disk (%d) inserted into drive A : %s\n", dc->index + 1, dc->files[dc->index]);

        // Auto Insert Drive B
        if (hatari_autoloadb)
        {
            if (dc->count > 1)
            {
                strcpy(RPATH2, dc->files[1]);
                log_cb(RETRO_LOG_INFO, "Disk 2 inserted into drive B: %s\n", dc->files[1]);
            }
            else
            {
                strcpy(RPATH2, RPATH);
                ptr = strrchr(RPATH2, '.');

                if (ptr)
                {
                    ptr--;

                    // change last letter before extension to a 'b'
                    if (*ptr == 'A' || *ptr == 'a')
                    {
                        *ptr += 1;
                        if (file_exists(RPATH2))
                        {
                            dc_add_file(dc, RPATH2);
                            log_cb(RETRO_LOG_INFO, "Disk 2 inserted into drive B: %s\n", dc->files[1]);
                        }
                    }
                    else
                        RPATH2[0] = 0;
                }
                else
                    RPATH2[0] = 0;
            }
        }
    }

    // Point the DiskImageDirectory to the retro_content_directory
    strcpy(RETRO_FID, full_path);
    ptr = strrchr(RETRO_FID, RETRO_PATH_SEPARATOR[0]);

    if (ptr)
        *ptr = 0;

    //clear sound buffer
	memset(SNDBUF,0,1024*2*2);

    log_cb(RETRO_LOG_INFO, "WRAP EMU THD\n");
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

