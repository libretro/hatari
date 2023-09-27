#ifndef LIBRETRO_CORE_OPTIONS_H__
#define LIBRETRO_CORE_OPTIONS_H__

#include <stdlib.h>
#include <string.h>

#include <libretro.h>
#include <retro_inline.h>

#ifndef HAVE_NO_LANGEXTRA
#include "libretro_core_options_intl.h"
#endif

/*
 ********************************
 * VERSION: 1.0
 ********************************
 *
 * - 1.0: First commit.  Support for core options v2 interfaec.
 *        - libretro_core_options_intl.h includes BOM and utf-8
 *          fix for MSVC 2010-2013
 *        - Contains HAVE_NO_LANGEXTRA flag to disable translations
 *          on platforms/compilers without BOM support
 *        - Uses core options v1 interface when
 *          RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION is >= 1
 *          (previously required RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION == 1)
 *        - Support for generation of core options v0 retro_core_option_value
 *          arrays containing options with a single value
 *  - 1.1: Implemented Retro_mapping.  Code from Vice64 by rsn887 and sonninnos.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 ********************************
 * Core Option Definitions
 ********************************
*/

/* RETRO_LANGUAGE_ENGLISH */

/* Default language:
 * - All other languages must include the same keys and values
 * - Will be used as a fallback in the event that frontend language
 *   is not available
 * - Will be used as a fallback for any missing entries in
 *   frontend language definition */

//struct retro_core_option_v2_category option_cats_us[] = {
//   { NULL, NULL, NULL },
//};

struct retro_core_option_v2_category option_cats_us[] = {
    {
        "system",
        "System",
        "Set Machine Type.  Ramsize.  TOS Used.  Enable Fast Boot."
    },
    {
        "input",
        "Input",
        "Enable/Disable second joystick, system mouse or system keyboard."
    },
    {
        "video",
        "Video",
        "Enable/Disable high resolution or overscan cropping.  Set Frameskip."
    },
    {
        "media",
        "Media",
        "Set Fast floppy access and Auto insert drive B."
    },
    {
        "hotkey",
        "Hotkey Mapping",
        "Configure keyboard hotkey mapping options."
    },
    {
        "retropad",
        "RetroPad Mapping",
        "Configure RetroPad mapping options."
    },
   { NULL, NULL, NULL },
};

struct retro_core_option_v2_definition option_defs_us[] = {
    // [System]
    // Machine type
    {
        "hatari_machinetype",
        "System -> Atari Computer Machine Type",
        "Atari computer machine type",
        "Pick emulated machine.  ST, STE, TT or Falcon (Needs Restart)",
        NULL,
        "system",
        {
                {"st","ST (1.02, 2.06)"},
                {"ste","STE (1.62, 2.06)"},
                {"tt","TT (3.01, 3.05, 3.06)"},
                {"falcon","Falcon (4.00 and up)"},
            { NULL, NULL },
        },
        "st"
    },
    // Ramsize
    {
        "hatari_ramsize",
        "System -> Atari Computer Ramsize",
        "Atari Computer Ramsize",
        "Set amount of emulated ram.  (Needs Restart)",
        NULL,
        "system",
        {
            {"0","512 KB"},
            {"1","1 MB"},
            {"2","2 MB"},
            {"4","4 MB"},
            {"8","8 MB"},
            {"14","14 MB"},
            { NULL, NULL },
        },
        "1"
    },
    // Select TOS images used
    {
        "hatari_tosimage",
        "System -> TOS Image Used (Needs Restart)",
        "TOS Image Used (Needs Restart)",
        "Select from list.\n"
        "\nPlace TOS images in system\\hatari\\tos\\ folder.\n"
        "Defaults to tos.img in SYSTEM folder",                    /* For backwards compatibility with old location */
        NULL,
        "system",
        {
            {"default","system\\tos.img (default)" },
            {NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},
            {NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},
            {NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},
            {NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},
            {NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL},
        },
        "default"
    },
    // Fast boot
    {
        "hatari_fastboot",
        "System -> Enable Fastboot",
        "Enable Fastboot",
        "Enable/Disable fast boot TOS patch.",
        NULL,
        "system",
        {
            { "true", "Enabled" },
            { "false", "Disabled" },
            { NULL, NULL },
        },
        "false"
    },
    // Reset type
    {
        "hatari_reset_type",
        "System -> Reset Type",
        "Reset Type",
        "Whether to Cold Start or Warm Start on \"Restart\".",
        NULL,
        "system",
        {
            { "0", "Warm Start" },
            { "1", "Cold Start" },
            { NULL, NULL },
        },
        "1"
    },
    // [Input]
    // Mouse Mode
    {
        "hatari_start_in_mouse_mode",
        "Input -> Start In Mouse Mode",
        "Start In Mouse Mode",
        "Starts with emulated mouse active on port 1.  Otherwise joystick is active on port 1.",
        NULL,
        "input",
        {
            { "true", "Enabled" },
            { "false", "Disabled" },
            { NULL, NULL },
        },
        "true"
    },
    // Left/Right Analog Mouse
    {
        "hatari_mouse_control_stick",
        "Input -> Analog Stick Mouse",
        "Analog Stick Mouse",
        "Set whether emulated mouse is controlled by left or right analog stick.",
        NULL,
        "input",
        {
            { "0", "Left Analog" },
            { "1", "Right Analog" },
            { NULL, NULL },
        },
        "0"
    },
    // Starting mouse speed.
    {
        "hatari_emulated_mouse_speed",
        "Input -> Emulated Mouse Speed",
        "Emulated Mouse Speed",
        "Set the starting mouse speed from 1 to 6.  Default is 2.",
        NULL,
        "input",
        {
            { "1", NULL },
            { "2", "2 (default)" },
            { "3", NULL },
            { "4", NULL },
            { "5", NULL },
            { "6", NULL },
            { NULL, NULL },
        },
        "2"
    },
    // Enable 2nd joystick
    {
        "hatari_twojoy",
        "Input -> Enable Second Joystick",
        "Enable Second Joystick",
        "Enables a second joystick on port 2, may conflict with mouse.",
        NULL,
        "input",
        {
            { "true", "Enabled" },
            { "false", "Disabled" },
            { NULL, NULL },
        },
        "true"
    },
    // Enable/Disable Hardware Mouse
    {
        "hatari_nomouse",
        "Input -> Disable Connected Mouse",
        "Disable Connected Mouse",
        "Prevents input from your sytem mouse device. Gamepad mouse mode (select) is not disabled.",
        NULL,
        "input",
        {
            { "false", "disabled" },
            { "true", "enabled" },
            { NULL, NULL },
        },
        "false"
    },
    // Enable/Disable Hardware Keyboard
    {
        "hatari_nokeys",
        "Input -> Disable Connected Keyboard",
        "Disable Connected Keyboard",
        "Prevents input from your system keyboard. Virtual keyboard is not disabled.",
        NULL,
        "input",
        {
            { "false", "Disabled" },
            { "true", "Enabled" },
            { NULL, NULL },
        },
        "false"
    },
    //video
    // High res mode?
    // Say bye bye.  All this did was create confusion.
    //{
    //    "hatari_video_hires",
    //    "Video -> High Resolution. (Needs Restart)",
    //    "High Resolution. (Needs Restart)",
    //    "Enable Hi-Resolution.",
    //    NULL,
    //    "video",
    //    {
    //        { "true", "Enabled" },
    //        { "false",  "Disabled" },
    //        { NULL, NULL },
    //    },
    //    "true"
    //},
    // Crop Overscan?
    {
        "hatari_video_crop_overscan",
        "Video -> Crop Overscan.",
        "Crop Overscan.",
        "Enable for games.  Disable for low/med resolution overscan demos",
        NULL,
        "video",
        {
            { "true", "Enabled" },
            { "false",  "Disabled" },
            { NULL, NULL },
        },
        "true"
    },
    // Force refresh rate.
    {
        "hatari_forcerefresh",
        "Video -> Force Refresh Rate.",
        "Force Refresh Rate.",
        "Force refresh rate to Auto, NTSC 60hz or PAL 50hz.  Auto uses selected TOS rate.",
        NULL,
        "video",
        {
            { "auto", "Auto" },
            { "1",  "NTSC 60hz" },
            { "2",  "PAL 50hz" },
            { NULL, NULL },
        },
        "auto"
    },
    // Set frameskip
    {
        "hatari_frameskips",
        "Video -> Set Frameskip.  (Needs Restart)",
        "Set Frameskip.  (Needs Restart)",
        "Disabled, 1-4, Auto (Max 5), Auto (Max 10).",
        NULL,
        "video",
        {
            { "0", "Disabled" },
            { "1", NULL },
            { "2", NULL },
            { "3", NULL },
            { "4", NULL },
            { "5", "Auto (Max 5)" },
            { "10", "Auto (Max 10)" },
            { NULL, NULL },
        },
        "0"
    },
    // Status display Joy/Mouse toggle
    {
        "hatari_joymousestatus_display",
        "Video -> Joy/Mouse Toggle/Speed Msg Location",
        "Joy/Mouse Toggle/Speed Msg Location",
        "Where to display Joystick/Mouse toggle and speed change information",
        NULL,
        "video",
        {
            { "0", "Off" },
            { "1",  "Status" },
            { "2",  "OSD" },
            { NULL, NULL },
        },
        "1"
    },
    // Show drive activity in status info
    {
        "hatari_led_status_display",
        "Video -> Show Drive Activity In Status Info",
        "Show Drive Activity In Status Info",
        "Enable to show activity in Retroarch status display",
        NULL,
        "video",
        {
            { "true", "Enabled" },
            { "false",  "Disabled" },
            { NULL, NULL },
        },
        "true"
    },
    // Floppy speed
    {
        "hatari_fastfdc",
        "Media -> Fast Floppy Access",
        "Fast Floppy Access",
        "Decreases the time spent loading from disk.",
        NULL,
        "media",
        {
            { "true", "Enabled" },
            { "false", "Disabled" },
            { NULL, NULL },
        },
        "true"
    },
    // Autoload Drive B
    {
        "hatari_autoloadb",
        "Media -> Auto Insert Drive B",
        "Auto Insert Drive B",
        "Auto inserts disk in Drive B if detected.\n"
        "Use only for content that can use two drives.\n"     //eg.  Game b.st
        "M3U loads 2nd entry.  Otherwise looks for \"b\" as last letter before extension.",
        NULL,
        "media",
        {
            { "true", "Enabled" },
            { "false", "Disabled" },
            { NULL, NULL },
        },
        "false"
    },
    //// Boot from hard disk.  (not sticking?)
    //{
    //    "hatari_boot_hd",
    //    "Media -> Boot from hard disk.",
    //    "Boot from hard disk.",
    //    "Enable to execute the AUTO folder on the hard disk.",
    //    NULL,
    //    "media",
    //    {
    //        { "true", "enabled" },
    //        { "false", "disabled" },
    //        { NULL, NULL },
    //    },
    //    "true"
    //},
    // Write Protect Floopy
    {
        "hatari_writeprotect_floppy",
        "Media -> Write Protect Floppy Disks",
        "Write Protect Floppy Disks",
        "Enable/Disable write protection for floppy disks.",
        NULL,
        "media",
        {
            { "on", "On" },
            { "off", "Off" },
            { "auto", "Auto" },
            { NULL, NULL },
        },
        "off"
    },
    // Write Protect HD
    {
        "hatari_writeprotect_hd",
        "Media -> Write Protect Hard Drives",
        "Write Protect Hard Drives",
        "Enable/Disable write protection for hard drives.",
        NULL,
        "media",
        {
            { "on", "On" },
            { "off", "Off" },
            { "auto", "Auto" },
            { NULL, NULL },
        },
        "off"
    },
    // Audio
    {
        "hatari_polarized_filter",
        "Polarized Audio Filter",
        NULL,
        "Uses hatari's polarized lowpass filters on audio to simulate distortion.",
        NULL,
        NULL,
        {
            { "false", "Disabled" },
            { "true", "Enabled" },
            { NULL, NULL },
        },
        "false"
    },
    // Hatari
    {
        "hatari_autoload_config",
        "Autoload hatari.cfg.",
        NULL,
        "Loads SYSTEM\\hatari\\hatari.cfg on content start.  Warning.  Overrides everything except for selected TOS image.",
        NULL,
        NULL,
        {
            { "false", "Disabled" },
            { "true", "Enabled" },
            { NULL, NULL },
        },
        "false"
    },
    ///* Hotkeys */
    //{
    //    "hatari_mapper_joymouse",
    //    "Hotkey > Toggle Joystick/Mouse",
    //    "Toggle Joystick/Mouse",
    //    "Press the mapped key to toggle between Joystick/Mouse.",
    //    NULL,
    //    "hotkey",
    //    {{ NULL, NULL }},
    //    "---"
    //},
    //{
    //    "hatari_mapper_mouse_speed_down",
    //    "Hotkey > Decrease Mouse Speed",
    //    "Decrease Mouse Speed",
    //    "Press the mapped key to decrease mouse speed.",
    //    NULL,
    //    "hotkey",
    //    {{ NULL, NULL }},
    //    "---"
    //},
    //{
    //    "hatari_mapper_mouse_speed_up",
    //    "Hotkey > Increase Mouse Speed",
    //    "Increase Mouse Speed",
    //    "Press the mapped key to increase mouse speed.",
    //    NULL,
    //    "hotkey",
    //    {{ NULL, NULL }},
    //    "---"
    //},
    //{
    //    "hatari_mapper_vkbd_toggle",
    //    "Hotkey > Toggle Virtual Keyboard",
    //    "Toggle Virtual Keyboard",
    //    "Press the mapped key to toggle virtual keyboard.",
    //    NULL,
    //    "hotkey",
    //    {{ NULL, NULL }},
    //    "---"
    //},
    //{
    //    "hatari_mapper_vkbd_page_toggle",
    //    "Hotkey > Toggle Virtual Keyboard Page",
    //    "Toggle Virtual Keyboard Page",
    //    "Press the mapped key to switch virtual keyboard page.",
    //    NULL,
    //    "hotkey",
    //    {{ NULL, NULL }},
    //    "---"
    //},
    //{
    //    "hatari_mapper_keyboard_shift_toggle",
    //    "Hotkey > Toggle VKBD Shift Key",
    //    "Toggle VKBD Shift Key",
    //    "Press the mapped key to toggle the VKBD shift key.",
    //    NULL,
    //    "hotkey",
    //    {{ NULL, NULL }},
    //    "---"
    //},
    //{
    //    "hatari_mapper_hatari_settings",
    //    "Hotkey > Enter/Exit Hatari Settings",
    //    "Enter/Exit Hatari Settings",
    //    "Press the mapped key to Enter/Exit the Hatari Settings.",
    //    NULL,
    //    "hotkey",
    //    {{ NULL, NULL }},
    //    "---"
    //},
    //{
    //    "hatari_mapper_statusbar",
    //    "Hotkey > Toggle Status display",
    //    "Toggle Status display",
    //    "Press the mapped key to toggle the Status display.",
    //    NULL,
    //    "hotkey",
    //    {{ NULL, NULL }},
    //    "---"
    //},
    /* Button mappings */
    {
        "hatari_mapper_up",
        "RetroPad > Joystick Up",
        "Joystick Up",
        "Unmapped defaults to joystick up.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "JOYSTICK_UP"
    },
    {
        "hatari_mapper_down",
        "RetroPad > Joystick Down",
        "Joystick Down",
        "Unmapped defaults to joystick down.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "JOYSTICK_DOWN"
    },
    {
        "hatari_mapper_left",
        "RetroPad > Joystick Left",
        "Joystick Left",
        "Unmapped defaults to joystick left.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "JOYSTICK_LEFT"
    },
    {
        "hatari_mapper_right",
        "RetroPad > Joystick Right",
        "Joystick Right",
        "Unmapped defaults to joystick right.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "JOYSTICK_RIGHT"
    },
    {
        "hatari_mapper_a",
        "RetroPad > A",
        "A",
        "Unmapped defaults to turbo fire/Mouse button 2.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "JOYSTICK_TURBOFIRE"
    },
    {
        "hatari_mapper_b",
        "RetroPad > B",
        "B",
        "Unmapped defaults to fire/mouse button 1.\nVKBD: Press selected key.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "JOYSTICK_FIRE"
    },
    {
        "hatari_mapper_x",
        "RetroPad > X",
        "X",
        "VKBD: Toggle.  Remapping overrides VKBD toggle.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "TOGGLE_VKBD"
    },
    {
        "hatari_mapper_y",
        "RetroPad > Y",
        "Y",
        "VKBD: Toggle 'ShiftLock'. Remapping overrides VKBD function!",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "TOGGLE_VKBS"
    },
    {
        "hatari_mapper_select",
        "RetroPad > Select",
        "Select",
        "Unmapped defaults to Joystick/Mouse mode toggle.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "TOGGLE_JOYMOUSE"
    },
    {
        "hatari_mapper_start",
        "RetroPad > Start",
        "Start",
        "Unmapped defaults to Enter/Exit the Hatari Settings.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "TOGGLE_SETTINGS"
    },
    {
        "hatari_mapper_l",
        "RetroPad > L",
        "L",
        "Unmapped defaults to toggle the Status display.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "TOGGLE_STATUSBAR"
    },
    {
        "hatari_mapper_r",
        "RetroPad > R",
        "R",
        "Unmapped defaults to switch virtual keyboard page.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "TOGGLE_VKBP"
    },
    {
        "hatari_mapper_l2",
        "RetroPad > L2",
        "L2",
        "Unmapped defaults to decrease mouse speed.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "MOUSE_SLOWER"
    },
    {
        "hatari_mapper_r2",
        "RetroPad > R2",
        "R2",
        "Unmapped defaults to increase mouse speed.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "MOUSE_FASTER"
    },
    {
        "hatari_mapper_l3",
        "RetroPad > L3",
        "L3",
        "",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "---"
    },
    {
        "hatari_mapper_r3",
        "RetroPad > R3",
        "R3",
        "Unmapped defaults to space.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "RETROK_SPACE"
    },
    /* Left Stick */
    {
        "hatari_mapper_lu",
        "RetroPad > Left Analog > Up",
        "Left Analog > Up",
        "Mouse mode must be off or on right analog.\n"
        "Ignored if assigned to VKBD.\n",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "---"
    },
    {
        "hatari_mapper_ld",
        "RetroPad > Left Analog > Down",
        "Left Analog > Down",
        "Mouse mode must be off or on right analog.\n"
        "Ignored if assigned to VKBD.\n",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "---"
    },
    {
        "hatari_mapper_ll",
        "RetroPad > Left Analog > Left",
        "Left Analog > Left",
        "Mouse mode must be off or on right analog.\n"
        "Ignored if assigned to VKBD.\n",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "---"
    },
    {
        "hatari_mapper_lr",
        "RetroPad > Left Analog > Right",
        "Left Analog > Right",
        "Mouse mode must be off or on right analog.\n"
        "Ignored if assigned to VKBD.\n",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "---"
    },
    /* Right Stick */
    {
        "hatari_mapper_ru",
        "RetroPad > Right Analog > Up",
        "Right Analog > Up",
        "Mouse mode must be off or on left analog.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "---"
    },
    {
        "hatari_mapper_rd",
        "RetroPad > Right Analog > Down",
        "Right Analog > Down",
        "Mouse mode must be off or on left analog.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "---"
    },
    {
        "hatari_mapper_rl",
        "RetroPad > Right Analog > Left",
        "Right Analog > Left",
        "Mouse mode must be off or on left analog.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "---"
    },
    {
        "hatari_mapper_rr",
        "RetroPad > Right Analog > Right",
        "Right Analog > Right",
        "Mouse mode must be off or on left analog.",
        NULL,
        "retropad",
        {{ NULL, NULL }},
        "---"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};

struct retro_core_options_v2 options_us = {
   option_cats_us,
   option_defs_us
};

/*
 ********************************
 * Language Mapping
 ********************************
*/

#ifndef HAVE_NO_LANGEXTRA
struct retro_core_options_v2 *options_intl[RETRO_LANGUAGE_LAST] = {
   &options_us, /* RETRO_LANGUAGE_ENGLISH */
   NULL,        /* RETRO_LANGUAGE_JAPANESE */
   NULL,        /* RETRO_LANGUAGE_FRENCH */
   NULL,        /* RETRO_LANGUAGE_SPANISH */
   NULL,        /* RETRO_LANGUAGE_GERMAN */
   NULL,        /* RETRO_LANGUAGE_ITALIAN */
   NULL,        /* RETRO_LANGUAGE_DUTCH */
   NULL,        /* RETRO_LANGUAGE_PORTUGUESE_BRAZIL */
   NULL,        /* RETRO_LANGUAGE_PORTUGUESE_PORTUGAL */
   NULL,        /* RETRO_LANGUAGE_RUSSIAN */
   NULL,        /* RETRO_LANGUAGE_KOREAN */
   NULL,        /* RETRO_LANGUAGE_CHINESE_TRADITIONAL */
   NULL,        /* RETRO_LANGUAGE_CHINESE_SIMPLIFIED */
   NULL,        /* RETRO_LANGUAGE_ESPERANTO */
   NULL,        /* RETRO_LANGUAGE_POLISH */
   NULL,        /* RETRO_LANGUAGE_VIETNAMESE */
   NULL,        /* RETRO_LANGUAGE_ARABIC */
   NULL,        /* RETRO_LANGUAGE_GREEK */
   NULL,        /* RETRO_LANGUAGE_TURKISH */
   NULL,        /* RETRO_LANGUAGE_SLOVAK */
   NULL,        /* RETRO_LANGUAGE_PERSIAN */
   NULL,        /* RETRO_LANGUAGE_HEBREW */
   NULL,        /* RETRO_LANGUAGE_ASTURIAN */
   NULL,        /* RETRO_LANGUAGE_FINNISH */
};
#endif

/*
 ********************************
 * Functions
 ********************************
*/

/* Handle Dynamically created core options*/

static struct retro_core_option_v2_definition *libretro_get_core_option_def(const char *key)
{
    for (struct retro_core_option_v2_definition *d = option_defs_us; d->key != NULL; ++d)
    {
        if (!strcmp(d->key, key)) return d;
    }
    return NULL;
}

/* Handles configuration/setting of core options.
 * Should be called as early as possible - ideally inside
 * retro_set_environment(), and no later than retro_load_game()
 * > We place the function body in the header to avoid the
 *   necessity of adding more .c files (i.e. want this to
 *   be as painless as possible for core devs)
 */

static INLINE void libretro_set_core_options(retro_environment_t environ_cb,
      bool *categories_supported)
{
   unsigned version  = 0;
#ifndef HAVE_NO_LANGEXTRA
   unsigned language = 0;
#endif

   if (!environ_cb || !categories_supported)
      return;

   *categories_supported = false;

   if (!environ_cb(RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION, &version))
      version = 0;

   if (version >= 2)
   {
#ifndef HAVE_NO_LANGEXTRA
      struct retro_core_options_v2_intl core_options_intl;

      core_options_intl.us    = &options_us;
      core_options_intl.local = NULL;

      if (environ_cb(RETRO_ENVIRONMENT_GET_LANGUAGE, &language) &&
          (language < RETRO_LANGUAGE_LAST) && (language != RETRO_LANGUAGE_ENGLISH))
         core_options_intl.local = options_intl[language];

      *categories_supported = environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_V2_INTL,
            &core_options_intl);
#else
      *categories_supported = environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_V2,
            &options_us);
#endif
   }
   else
   {
      size_t i, j;
      size_t option_index              = 0;
      size_t num_options               = 0;
      struct retro_core_option_definition
            *option_v1_defs_us         = NULL;
#ifndef HAVE_NO_LANGEXTRA
      size_t num_options_intl          = 0;
      struct retro_core_option_v2_definition
            *option_defs_intl          = NULL;
      struct retro_core_option_definition
            *option_v1_defs_intl       = NULL;
      struct retro_core_options_intl
            core_options_v1_intl;
#endif
      struct retro_variable *variables = NULL;
      char **values_buf                = NULL;

      /* Determine total number of options */
      while (true)
      {
         if (option_defs_us[num_options].key)
            num_options++;
         else
            break;
      }

      if (version >= 1)
      {
         /* Allocate US array */
         option_v1_defs_us = (struct retro_core_option_definition *)
               calloc(num_options + 1, sizeof(struct retro_core_option_definition));

         /* Copy parameters from option_defs_us array */
         for (i = 0; i < num_options; i++)
         {
            struct retro_core_option_v2_definition *option_def_us = &option_defs_us[i];
            struct retro_core_option_value *option_values         = option_def_us->values;
            struct retro_core_option_definition *option_v1_def_us = &option_v1_defs_us[i];
            struct retro_core_option_value *option_v1_values      = option_v1_def_us->values;

            option_v1_def_us->key           = option_def_us->key;
            option_v1_def_us->desc          = option_def_us->desc;
            option_v1_def_us->info          = option_def_us->info;
            option_v1_def_us->default_value = option_def_us->default_value;

            /* Values must be copied individually... */
            while (option_values->value)
            {
               option_v1_values->value = option_values->value;
               option_v1_values->label = option_values->label;

               option_values++;
               option_v1_values++;
            }
         }

#ifndef HAVE_NO_LANGEXTRA
         if (environ_cb(RETRO_ENVIRONMENT_GET_LANGUAGE, &language) &&
             (language < RETRO_LANGUAGE_LAST) && (language != RETRO_LANGUAGE_ENGLISH) &&
             options_intl[language])
            option_defs_intl = options_intl[language]->definitions;

         if (option_defs_intl)
         {
            /* Determine number of intl options */
            while (true)
            {
               if (option_defs_intl[num_options_intl].key)
                  num_options_intl++;
               else
                  break;
            }

            /* Allocate intl array */
            option_v1_defs_intl = (struct retro_core_option_definition *)
                  calloc(num_options_intl + 1, sizeof(struct retro_core_option_definition));

            /* Copy parameters from option_defs_intl array */
            for (i = 0; i < num_options_intl; i++)
            {
               struct retro_core_option_v2_definition *option_def_intl = &option_defs_intl[i];
               struct retro_core_option_value *option_values           = option_def_intl->values;
               struct retro_core_option_definition *option_v1_def_intl = &option_v1_defs_intl[i];
               struct retro_core_option_value *option_v1_values        = option_v1_def_intl->values;

               option_v1_def_intl->key           = option_def_intl->key;
               option_v1_def_intl->desc          = option_def_intl->desc;
               option_v1_def_intl->info          = option_def_intl->info;
               option_v1_def_intl->default_value = option_def_intl->default_value;

               /* Values must be copied individually... */
               while (option_values->value)
               {
                  option_v1_values->value = option_values->value;
                  option_v1_values->label = option_values->label;

                  option_values++;
                  option_v1_values++;
               }
            }
         }

         core_options_v1_intl.us    = option_v1_defs_us;
         core_options_v1_intl.local = option_v1_defs_intl;

         environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_INTL, &core_options_v1_intl);
#else
         environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS, option_v1_defs_us);
#endif
      }
      else
      {
         /* Allocate arrays */
         variables  = (struct retro_variable *)calloc(num_options + 1,
               sizeof(struct retro_variable));
         values_buf = (char **)calloc(num_options, sizeof(char *));

         if (!variables || !values_buf)
            goto error;

         /* Copy parameters from option_defs_us array */
         for (i = 0; i < num_options; i++)
         {
            const char *key                        = option_defs_us[i].key;
            const char *desc                       = option_defs_us[i].desc;
            const char *default_value              = option_defs_us[i].default_value;
            struct retro_core_option_value *values = option_defs_us[i].values;
            size_t buf_len                         = 3;
            size_t default_index                   = 0;

            values_buf[i] = NULL;

            if (desc)
            {
               size_t num_values = 0;

               /* Determine number of values */
               while (true)
               {
                  if (values[num_values].value)
                  {
                     /* Check if this is the default value */
                     if (default_value)
                        if (strcmp(values[num_values].value, default_value) == 0)
                           default_index = num_values;

                     buf_len += strlen(values[num_values].value);
                     num_values++;
                  }
                  else
                     break;
               }

               /* Build values string */
               if (num_values > 0)
               {
                  buf_len += num_values - 1;
                  buf_len += strlen(desc);

                  values_buf[i] = (char *)calloc(buf_len, sizeof(char));
                  if (!values_buf[i])
                     goto error;

                  strcpy(values_buf[i], desc);
                  strcat(values_buf[i], "; ");

                  /* Default value goes first */
                  strcat(values_buf[i], values[default_index].value);

                  /* Add remaining values */
                  for (j = 0; j < num_values; j++)
                  {
                     if (j != default_index)
                     {
                        strcat(values_buf[i], "|");
                        strcat(values_buf[i], values[j].value);
                     }
                  }
               }
            }

            variables[option_index].key   = key;
            variables[option_index].value = values_buf[i];
            option_index++;
         }

         /* Set variables */
         environ_cb(RETRO_ENVIRONMENT_SET_VARIABLES, variables);
      }

error:
      /* Clean up */

      if (option_v1_defs_us)
      {
         free(option_v1_defs_us);
         option_v1_defs_us = NULL;
      }

#ifndef HAVE_NO_LANGEXTRA
      if (option_v1_defs_intl)
      {
         free(option_v1_defs_intl);
         option_v1_defs_intl = NULL;
      }
#endif

      if (values_buf)
      {
         for (i = 0; i < num_options; i++)
         {
            if (values_buf[i])
            {
               free(values_buf[i]);
               values_buf[i] = NULL;
            }
         }

         free(values_buf);
         values_buf = NULL;
      }

      if (variables)
      {
         free(variables);
         variables = NULL;
      }
   }
}

#ifdef __cplusplus
}
#endif

#endif
