/*
  Hatari - floppy_sound.c

  This file is distributed under the GNU General Public License, version 2
  or at your option any later version. Read the file gpl.txt for details.

  Floppy drive sounds for the libretro core, from the hatari2014 core
  (libretro/floppy_sound.c there): a click and seek sound when the led of
  drive A or B comes on, repeated for as long as the floppy controller keeps
  working on the drive, for both at the same time.

  A sample of one's own can be put in the frontend's system directory as
  floppy.raw: signed 16-bit little-endian stereo at 44100 Hz, no header
  (ffmpeg -i click.wav -f s16le -ar 44100 -ac 2 floppy.raw). Without it a
  synthetic one is used. Both are made to fit the core's audio rate, which
  can change at run time.
*/
const char FloppySound_fileid[] = "Hatari floppy_sound.c";

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "main_retro.h"
#include "floppy_sound.h"
#include "vfs.h"

#define RAW_RATE 44100

static int16_t *raw_pcm;          /* floppy.raw as loaded, at RAW_RATE */
static int      raw_frames;

static int16_t *sample;           /* what is mixed, at sample_rate */
static int      sample_frames;
static int      sample_rate;

static int  play_pos[2] = { -1, -1 };
static bool enabled = true;
static int  volume = 192;         /* 0-256 */


/**
 * The built-in sound, ~55 ms: a low mechanical thud, the stepper motor's
 * buzz, a descending head seek chirp and a short chassis rattle.
 */
static int16_t *FloppySound_Synthesize(int rate, int *frames)
{
	const float pi = 3.14159265f;
	int n = rate * 55 / 1000;
	int16_t *pcm = malloc(n * 2 * sizeof(*pcm));
	int i;

	if (!pcm)
		return NULL;

	for (i = 0; i < n; i++)
	{
		float t = (float)i / (float)rate;
		float s = 0.0f;

		/* thud: 120 Hz, decays in ~12 ms */
		s += sinf(2.0f * pi * 120.0f * t) * expf(-t / 0.012f) * 0.55f;

		/* stepper buzz: ~800 Hz with a wobble, 2 ms onset */
		{
			float onset = t > 0.002f ? 1.0f : t / 0.002f;
			float freq = 800.0f + 60.0f * sinf(2.0f * pi * 180.0f * t);
			s += sinf(2.0f * pi * freq * t) * onset * expf(-t / 0.008f) * 0.30f;
		}

		/* head seek chirp: 2400 -> 700 Hz over 25 ms */
		if (t < 0.025f)
		{
			float freq = 2400.0f - 1700.0f * (t / 0.025f);
			s += sinf(2.0f * pi * freq * t) * expf(-t / 0.018f) * 0.20f;
		}

		/* rattle: products of unrelated frequencies, 5-17 ms */
		{
			float t2 = t - 0.005f;
			if (t2 > 0.0f && t2 < 0.012f)
			{
				float noise = sinf(2.0f * pi * 3700.0f * t2)
				            * sinf(2.0f * pi * 2300.0f * t2)
				            * sinf(2.0f * pi * 970.0f * t2);
				s += noise * expf(-t2 / 0.005f) * 0.18f;
			}
		}

		if (s > 1.0f)
			s = 1.0f;
		if (s < -1.0f)
			s = -1.0f;
		pcm[i * 2] = pcm[i * 2 + 1] = (int16_t)(s * 28000.0f);
	}

	*frames = n;
	return pcm;
}

/**
 * floppy.raw at another rate, linearly interpolated
 */
static int16_t *FloppySound_Resample(int rate, int *frames)
{
	int n = (int)((int64_t)raw_frames * rate / RAW_RATE);
	int16_t *pcm;
	int i, c;

	if (n <= 0 || !(pcm = malloc(n * 2 * sizeof(*pcm))))
		return NULL;

	for (i = 0; i < n; i++)
	{
		int64_t pos = (int64_t)i * RAW_RATE * 256 / rate;
		int idx = (int)(pos >> 8), frac = (int)(pos & 255);
		int next = idx + 1 < raw_frames ? idx + 1 : idx;

		for (c = 0; c < 2; c++)
			pcm[i * 2 + c] = (int16_t)((raw_pcm[idx * 2 + c] * (256 - frac) +
			                            raw_pcm[next * 2 + c] * frac) >> 8);
	}

	*frames = n;
	return pcm;
}

static void FloppySound_Prepare(int rate)
{
	free(sample);
	sample = NULL;
	sample_frames = 0;
	sample_rate = rate;

	if (raw_pcm)
		sample = FloppySound_Resample(rate, &sample_frames);
	if (!sample)
		sample = FloppySound_Synthesize(rate, &sample_frames);

	play_pos[0] = play_pos[1] = -1;
}


void FloppySound_Init(const char *system_dir)
{
	char path[FILENAME_MAX];
	VFS_FILE f;
	int64_t size;

	FloppySound_UnInit();

	if (!system_dir || !system_dir[0])
		return;

	snprintf(path, sizeof(path), "%s%sfloppy.raw", system_dir, RETRO_PATH_SEPARATOR);
	f = VFS_fopen(path, "rb");
	if (!f)
		return;

	size = VFS_fsize(f);
	if (size >= 4 && size <= 16 * 1024 * 1024 && (raw_pcm = malloc(size)) != NULL)
	{
		if (VFS_fread(raw_pcm, 1, size, f) == (size_t)size)
		{
			raw_frames = (int)(size / 4);
#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
			{
				int i;
				for (i = 0; i < raw_frames * 2; i++)
				{
					uint16_t v = (uint16_t)raw_pcm[i];
					raw_pcm[i] = (int16_t)((v >> 8) | (v << 8));
				}
			}
#endif
		}
		else
		{
			free(raw_pcm);
			raw_pcm = NULL;
		}
	}
	VFS_fclose(f);
}

void FloppySound_UnInit(void)
{
	free(raw_pcm);
	raw_pcm = NULL;
	raw_frames = 0;
	free(sample);
	sample = NULL;
	sample_frames = 0;
	sample_rate = 0;
	play_pos[0] = play_pos[1] = -1;
}

void FloppySound_SetEnabled(bool on)
{
	enabled = on;
	if (!on)
		play_pos[0] = play_pos[1] = -1;
}

void FloppySound_SetVolume(int percent)
{
	volume = percent * 256 / 100;
}

void FloppySound_Trigger(int drive)
{
	if (enabled && (drive == 0 || drive == 1))
		play_pos[drive] = 0;
}

bool FloppySound_Playing(int drive)
{
	return (drive == 0 || drive == 1) && play_pos[drive] >= 0;
}

void FloppySound_Mix(int16_t *buf, int frames, int rate)
{
	int d, i;

	if (!enabled || rate <= 0 || (play_pos[0] < 0 && play_pos[1] < 0))
		return;

	if (rate != sample_rate)
	{
		int pos[2] = { play_pos[0], play_pos[1] };
		FloppySound_Prepare(rate);
		play_pos[0] = pos[0] >= 0 ? 0 : -1;
		play_pos[1] = pos[1] >= 0 ? 0 : -1;
	}
	if (!sample)
		return;

	for (d = 0; d < 2; d++)
	{
		if (play_pos[d] < 0)
			continue;

		for (i = 0; i < frames && play_pos[d] < sample_frames; i++, play_pos[d]++)
		{
			int l = buf[i * 2] + ((sample[play_pos[d] * 2] * volume) >> 8);
			int r = buf[i * 2 + 1] + ((sample[play_pos[d] * 2 + 1] * volume) >> 8);
			buf[i * 2] = l > 32767 ? 32767 : l < -32768 ? -32768 : l;
			buf[i * 2 + 1] = r > 32767 ? 32767 : r < -32768 ? -32768 : r;
		}

		if (play_pos[d] >= sample_frames)
			play_pos[d] = -1;
	}
}
