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
   { NULL, NULL, NULL },
};

struct retro_core_option_v2_definition option_defs_us[] = {
    // [System]
    // Machine type
    {
        "hatari_machinetype",
        "Atari computer machine Type",
        NULL,
        "Pick emulated machine.  ST, STE, TT or Falcon (Needs Restart)",
        NULL,
        "system",
        {
                {"st","ST"},
                {"ste","STE"},
                {"tt","TT"},
                {"falcon","Falcon"},
            { NULL, NULL },
        },
        "st"
    },
    // Ramsize
    {
        "hatari_ramsize",
        "Atari computer ramsize",
        NULL,
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
        "TOS image used (Needs Restart)",
        NULL,
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
        "Enable fastboot",
        NULL,
        "Enable/Disable fast boot TOS patch.",
        NULL,
        "system",
        {
            { "true", "enabled" },
            { "false", "disabled" },
            { NULL, NULL },
        },
        "false"
    },
    // [Input]
    // Mouse Mode
    {
        "hatari_start_in_mouse_mode",
        "Start in mouse mode",
        NULL,
        "Starts with emulated mouse active on port 1.  Otherwise joystick is active on port 1.",
        NULL,
        "input",
        {
            { "true", "enabled" },
            { "false", "disabled" },
            { NULL, NULL },
        },
        "true"
    },
    // Left/Right Analog Mouse
    {
        "hatari_mouse_control_stick",
        "Analog stick mouse",
        NULL,
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
        "Emulated mouse speed",
        NULL,
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
        "Enable second joystick",
        NULL,
        "Enables a second joystick on port 2, may conflict with mouse.",
        NULL,
        "input",
        {
            { "true", "enabled" },
            { "false", "disabled" },
            { NULL, NULL },
        },
        "true"
    },
    // Enable/Disable Hardware Mouse
    {
        "hatari_nomouse",
        "Disable connected mouse",
        NULL,
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
        "Disable connectedkeyboard",
        NULL,
        "Prevents input from your system keyboard. Virtual keyboard is not disabled.",
        NULL,
        "input",
        {
            { "false", "disabled" },
            { "true", "enabled" },
            { NULL, NULL },
        },
        "false"
    },
    //video
    // High res mode?
    {
        "hatari_video_hires",
        "High resolution. (Needs Restart)",
        NULL,
        "Enable Hi-Resolution.",
        NULL,
        "video",
        {
            { "true", "enabled" },
            { "false",  "disabled" },
            { NULL, NULL },
        },
        "true"
    },
    // Crop Overscan?
    {
        "hatari_video_crop_overscan",
        "Crop overscan. (Needs Restart)",
        NULL,
        "Enable for games.  Disable for low/med resolution overscan demos",
        NULL,
        "video",
        {
            { "true", "enabled" },
            { "false",  "disabled" },
            { NULL, NULL },
        },
        "true"
    },
    // Force refresh rate.
    {
        "hatari_forcerefresh",
        "Force refresh rate.",
        NULL,
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
        "Set frameskip.  (Needs Restart)",
        NULL,
        "Set emulated systems internal resolution.\n"
        "Disabled, 1-4, Auto (Max 5), Auto (Max 10).",
        NULL,
        "video",
        {
            { "0", "disabled" },
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
    // Floppy speed
    {
        "hatari_fastfdc",
        "Fast floppy access",
        NULL,
        "Decreases the time spent loading from disk.",
        NULL,
        "media",
        {
            { "true", "enabled" },
            { "false", "disabled" },
            { NULL, NULL },
        },
        "true"
    },
    // Autoload Drive B
    {
        "hatari_autoloadb",
        "Auto insert drive B",
        NULL,
        "Auto inserts disk in Drive B if detected.\n"
        "Use only for content that can use two drives.\n"     //eg.  Game b.st
        "M3U loads 2nd entry.  Otherwise looks for \"b\" as last letter before extension.",
        NULL,
        "media",
        {
            { "true", "enabled" },
            { "false", "disabled" },
            { NULL, NULL },
        },
        "false"
    },
    // Audio
    {
        "hatari_polarized_filter",
        "Polarized audio filter",
        NULL,
        "Uses hatari's polarized lowpass filters on audio to simulate distortion.",
        NULL,
        NULL,
        {
            { "false", "disabled" },
            { "true", "enabled" },
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
            { "false", "disabled" },
            { "true", "enabled" },
            { NULL, NULL },
        },
        "false"
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
