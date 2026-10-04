/*
  Hatari - main_retro.h

  This file is distributed under the GNU General Public License, version 2
  or at your option any later version. Read the file gpl.txt for details.
*/

#pragma once
#include <libretro.h>

extern bool has_cpu_config_changed;
extern const char *retro_system_directory;
extern const char *retro_save_directory;
extern retro_environment_t environment_cb;
extern retro_video_refresh_t video_refresh_cb;
extern retro_input_state_t input_state_cb;

/* screen.c: cache the drive LED option when runtime options are applied */
void Screen_ShowDriveLeds(bool show);

/* statusbar.c: the drive leds, drawn over the frame */
void Statusbar_ShowLeds(bool show);
bool Statusbar_LedsVisible(void);
void Statusbar_DrawLeds(uint32_t *pixels, int width, int height, int pitch);
void Statusbar_FrameDone(void);
