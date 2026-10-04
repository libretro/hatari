/*
  Hatari - floppy_sound.h

  This file is distributed under the GNU General Public License, version 2
  or at your option any later version. Read the file gpl.txt for details.
*/

#ifndef HATARI_RETRO_FLOPPY_SOUND_H
#define HATARI_RETRO_FLOPPY_SOUND_H

#include <stdbool.h>
#include <stdint.h>

/* Load floppy.raw from the system directory, if there is one */
void FloppySound_Init(const char *system_dir);
void FloppySound_UnInit(void);

void FloppySound_SetEnabled(bool enabled);
void FloppySound_SetVolume(int percent);

/* Start the drive sound for drive 0 (A) or 1 (B) */
void FloppySound_Trigger(int drive);

/* Whether the sound for drive 0 (A) or 1 (B) is still playing */
bool FloppySound_Playing(int drive);

/* Mix the playing drive sounds into 'frames' stereo frames at 'rate' Hz */
void FloppySound_Mix(int16_t *buf, int frames, int rate);

#endif /* ifndef HATARI_RETRO_FLOPPY_SOUND_H */
