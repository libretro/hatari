/*
  Hatari - vkbd.h

  This file is distributed under the GNU General Public License, version 2
  or at your option any later version. Read the file gpl.txt for details.
*/

#ifndef HATARI_RETRO_VKBD_H
#define HATARI_RETRO_VKBD_H

#include <stdbool.h>
#include <stdint.h>

/* RetroPad button that shows and hides the keyboard, or -1 for none */
void Vkbd_SetToggleButton(int retro_id);
void Vkbd_SetTheme(int theme);

/* Once per retro_run, before the emulation runs */
void Vkbd_Update(void);
bool Vkbd_IsActive(void);

/* Draw the keyboard into a copy of the frame */
void Vkbd_Draw(uint32_t *pixels, int width, int height, int pitch);

/* Let go of every key the keyboard holds down */
void Vkbd_Reset(void);

#endif /* ifndef HATARI_RETRO_VKBD_H */
