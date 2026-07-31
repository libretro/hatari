#ifndef FLOPPY_SOUND_H
#define FLOPPY_SOUND_H

#include <stdint.h>

/* Call once after retro_system_directory is known */
void floppy_sound_init(const char *system_dir);

/* Call from update_variables() */
void floppy_sound_set_enabled(int enabled);
void floppy_sound_set_volume(int vol);   /* 0-256, default 200 */

/* Call each frame with current LED states, BEFORE audio_cb loop */
void floppy_sound_update_leds(int leda, int ledb);

/* Mix floppy click into stereo int16 buffer of `frames` stereo frames */
void floppy_sound_mix(int16_t *buf, int frames);

/* Call from retro_deinit() */
void floppy_sound_free(void);

#endif /* FLOPPY_SOUND_H */
