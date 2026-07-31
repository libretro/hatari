/*
 * floppy_sound.c - Atari ST floppy drive sounds for Hatari libretro
 *
 * Plays a click/seek sound whenever a floppy LED turns on (rising edge).
 * Supports up to 2 simultaneous drives (A and B).
 *
 * External sample: place a raw PCM file at:
 *   <retroarch_system_dir>/floppy.raw
 *   Format: signed 16-bit little-endian stereo, 44100 Hz, no header
 *   Convert with: ffmpeg -i click.wav -f s16le -ar 44100 -ac 2 floppy.raw
 *
 * If no file is found, a built-in synthetic click is used automatically.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "floppy_sound.h"

/* ------------------------------------------------------------------ */
/* Built-in synthetic click                                             */
/* ~12ms of a decaying square wave at ~1kHz, 44100Hz stereo int16      */
/* ------------------------------------------------------------------ */
#define BUILTIN_SAMPLES 2425   /* ~55ms @ 44100Hz */
static int16_t builtin_pcm[BUILTIN_SAMPLES * 2];
static int     builtin_generated = 0;

static void generate_builtin(void)
{
    int i;
    /* Total ~55ms @ 44100Hz = 2425 samples
     * Layers:
     *   1. Initial mechanical THUD  - low thump ~120Hz, sharp attack, fast decay (~15ms)
     *   2. Stepper motor BUZZ       - mid freq ~800Hz, short burst (~20ms)
     *   3. Head seek CHIRP          - descending ~2400->800Hz sweep (~25ms)
     *   4. Light chassis RATTLE     - broadband noise burst (~10ms, offset 5ms)
     * All summed and normalised to int16 range.
     */
    for (i = 0; i < BUILTIN_SAMPLES; i++)
    {
        float t  = (float)i / 44100.0f;   /* time in seconds */
        float s  = 0.0f;

        /* --- 1. mechanical thud: 120 Hz, decays in ~12ms --- */
        {
            float env = expf(-t / 0.012f);
            s += sinf(2.0f * 3.14159265f * 120.0f * t) * env * 0.55f;
        }

        /* --- 2. stepper buzz: 800 Hz, onset 2ms, decays by 20ms --- */
        {
            float onset = (t > 0.002f) ? 1.0f : (t / 0.002f);
            float env   = onset * expf(-t / 0.008f);
            /* slight frequency wobble to sound mechanical */
            float freq  = 800.0f + 60.0f * sinf(2.0f * 3.14159265f * 180.0f * t);
            s += sinf(2.0f * 3.14159265f * freq * t) * env * 0.30f;
        }

        /* --- 3. head seek chirp: 2400->700 Hz sweep over 25ms --- */
        {
            float chirp_len = 0.025f;
            float env = (t < chirp_len)
                        ? expf(-t / 0.018f)
                        : 0.0f;
            float freq = 2400.0f - (2400.0f - 700.0f) * (t / chirp_len);
            if (t < chirp_len)
                s += sinf(2.0f * 3.14159265f * freq * t) * env * 0.20f;
        }

        /* --- 4. broadband rattle: pseudo-noise via fast square LFO, 5-15ms --- */
        {
            float t2 = t - 0.005f;
            if (t2 > 0.0f && t2 < 0.012f)
            {
                float env = expf(-t2 / 0.005f);
                /* cheap noise: XOR-ish pattern using incommensurable freqs */
                float n = sinf(2.0f * 3.14159265f * 3700.0f * t2)
                        * sinf(2.0f * 3.14159265f * 2300.0f * t2)
                        * sinf(2.0f * 3.14159265f *  970.0f * t2);
                s += n * env * 0.18f;
            }
        }

        /* clamp and write stereo */
        if (s >  1.0f) s =  1.0f;
        if (s < -1.0f) s = -1.0f;
        int16_t out = (int16_t)(s * 28000.0f);
        builtin_pcm[i * 2    ] = out;
        builtin_pcm[i * 2 + 1] = out;
    }
    builtin_generated = 1;
}

/* ------------------------------------------------------------------ */
/* Sample storage                                                       */
/* ------------------------------------------------------------------ */
static int16_t *sample_data   = NULL;
static int      sample_frames = 0;    /* stereo frames */
static int      sample_is_external = 0;

/* playback cursors per drive, -1 = not playing */
static int play_pos[2] = { -1, -1 };

/* previous LED states for rising-edge detection */
static int prev_led[2] = { 0, 0 };

/* settings */
static int floppy_enabled = 1;
static int floppy_volume  = 200;   /* 0-256 */

/* ------------------------------------------------------------------ */
/* Public API                                                           */
/* ------------------------------------------------------------------ */

void floppy_sound_init(const char *system_dir)
{
    char path[512];
    FILE *f;
    long  size;

    if (!builtin_generated)
        generate_builtin();

    /* try to load external raw PCM */
    if (system_dir)
    {
        snprintf(path, sizeof(path), "%s/floppy.raw", system_dir);
        f = fopen(path, "rb");
        if (f)
        {
            fseek(f, 0, SEEK_END);
            size = ftell(f);
            rewind(f);
            if (size > 0)
            {
                sample_data = (int16_t *)malloc((size_t)size);
                if (sample_data)
                {
                    size_t nread = fread(sample_data, 1, (size_t)size, f);
                    if ((long)nread == size)
                    {
                        sample_frames      = (int)(size / (2 * sizeof(int16_t)));
                        sample_is_external = 1;
                    }
                    else
                    {
                        free(sample_data);
                        sample_data = NULL;
                    }
                }
            }
            fclose(f);
        }
    }

    /* fall back to built-in */
    if (!sample_data)
    {
        sample_data        = builtin_pcm;
        sample_frames      = BUILTIN_SAMPLES;
        sample_is_external = 0;
    }

    /* reset state */
    play_pos[0] = play_pos[1] = -1;
    prev_led[0] = prev_led[1] = 0;
}

void floppy_sound_set_enabled(int enabled)
{
    floppy_enabled = enabled;
}

void floppy_sound_set_volume(int vol)
{
    floppy_volume = vol;  /* 0-256 */
}

void floppy_sound_update_leds(int leda, int ledb)
{
    /* rising edge: drive A */
    if (leda && !prev_led[0])
        play_pos[0] = 0;
    /* rising edge: drive B */
    if (ledb && !prev_led[1])
        play_pos[1] = 0;

    prev_led[0] = leda;
    prev_led[1] = ledb;
}

void floppy_sound_mix(int16_t *buf, int frames)
{
    int d, i;

    if (!floppy_enabled || !sample_data)
        return;

    for (d = 0; d < 2; d++)
    {
        if (play_pos[d] < 0)
            continue;

        for (i = 0; i < frames && play_pos[d] < sample_frames; i++, play_pos[d]++)
        {
            int l = (int)buf[i * 2    ] + ((int)sample_data[play_pos[d] * 2    ] * floppy_volume >> 8);
            int r = (int)buf[i * 2 + 1] + ((int)sample_data[play_pos[d] * 2 + 1] * floppy_volume >> 8);
            /* clamp to int16 range */
            buf[i * 2    ] = (l >  32767) ?  32767 : (l < -32768) ? (int16_t)-32768 : (int16_t)l;
            buf[i * 2 + 1] = (r >  32767) ?  32767 : (r < -32768) ? (int16_t)-32768 : (int16_t)r;
        }

        if (play_pos[d] >= sample_frames)
            play_pos[d] = -1;
    }
}

void floppy_sound_free(void)
{
    if (sample_is_external && sample_data)
        free(sample_data);
    sample_data        = NULL;
    sample_frames      = 0;
    sample_is_external = 0;
}
