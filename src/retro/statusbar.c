/*
  Hatari - statusbar.c

  This file is distributed under the GNU General Public License, version 2
  or at your option any later version. Read the file gpl.txt for details.

  Code to draw statusbar area, floppy leds etc.

  The libretro core has no statusbar area: the drive LEDs are drawn over the
  top right corner of the frame instead, a small amber bar per floppy drive
  like the one on an STFM, and a green one for the hard disk (from the
  hatari2014 core). A floppy LED going on also starts the drive sound.
*/
const char Statusbar_fileid[] = "Hatari statusbar.c";

#include <assert.h>
#include "main.h"
#include "configuration.h"
#include "screenSnapShot.h"
#include "statusbar.h"
#include "tos.h"
#include "video.h"
#include "sound.h"
#include "avi_record.h"
#include "vdi.h"
#include "fdc.h"
#include "stMemory.h"
#include "blitter.h"
#include "str.h"
#include "lilo.h"
#include "floppy_sound.h"
#include "main_retro.h"


#define HD_LED_FRAMES	10		/* frames the HD led stays on */

static bool leds_shown = true;
static drive_led_t floppy_led[2];
static bool floppy_busy[2];	/* the controller has worked on the drive this frame */
static int hd_led_frames;

/**
 * Return statusbar height for given width and height
 */
int Statusbar_GetHeightForSize(int width, int height)
{
	return 0;
}

/**
 * Set screen height used for statusbar height calculation.
 *
 * Return height of statusbar that should be added to the screen
 * height when screen is (re-)created, or zero if statusbar will
 * not be shown
 */
int Statusbar_SetHeight(int width, int height)
{
	return Statusbar_GetHeightForSize(width, height);
}

/**
 * Return height of statusbar set with Statusbar_SetHeight()
 */
int Statusbar_GetHeight(void)
{
	return 0;
}


/**
 * Enable HD drive led, it will be automatically disabled after a while.
 */
void Statusbar_EnableHDLed(drive_led_t state)
{
	if (state != LED_STATE_OFF)
		hd_led_frames = HD_LED_FRAMES;
}

/**
 * Set given floppy drive led state, anything enabling led with this
 * needs also to take care of disabling it.
 */
void Statusbar_SetFloppyLed(drive_index_t drive, drive_led_t state)
{
	assert(drive == DRIVE_LED_A || drive == DRIVE_LED_B);

	if (state == LED_STATE_ON_BUSY)
		floppy_busy[drive] = true;
	floppy_led[drive] = state;
}

/**
 * Show or hide the drive leds drawn over the frame
 */
void Statusbar_ShowLeds(bool show)
{
	leds_shown = show;
}

/**
 * Whether any drive led is to be drawn over this frame
 */
bool Statusbar_LedsVisible(void)
{
	return leds_shown && (floppy_led[0] != LED_STATE_OFF ||
	                      floppy_led[1] != LED_STATE_OFF || hd_led_frames > 0);
}

/**
 * Once per retro_run: what times the HD led out, and what starts the floppy
 * sound. Drive leds are looked at once a frame, as the hatari2014 core did:
 * the sound starts when a led has come on since the last frame, and plays
 * again each time it has finished for as long as the controller has worked
 * on the drive during the frame - so a load sounds for as long as it lasts,
 * and the sample is never cut off to start it over. TOS selecting drive A
 * and B in turn every eight VBLs to check for a disk change is over within
 * the frame and carries out no command, so it is not heard.
 */
void Statusbar_FrameDone(void)
{
	static bool was_on[2];
	int d;

	for (d = 0; d < 2; d++)
	{
		bool on = floppy_led[d] != LED_STATE_OFF;
		bool busy = floppy_busy[d] || floppy_led[d] == LED_STATE_ON_BUSY;
		if ((on && !was_on[d]) || (busy && !FloppySound_Playing(d)))
			FloppySound_Trigger(d);
		was_on[d] = on;
		floppy_busy[d] = false;
	}

	if (hd_led_frames > 0)
		hd_led_frames--;
}

/**
 * Draw the drive leds into a copy of the frame about to be handed to the
 * frontend
 */
void Statusbar_DrawLeds(uint32_t *pixels, int width, int height, int pitch)
{
	static const uint32_t floppy_color = 0xF8D800;	/* STFM amber */
	static const uint32_t hd_color = 0x30E030;
	bool on[3];
	int led_w, led_h, gap, right, top, i, x, y;
	int stride = pitch / 4;

	if (!Statusbar_LedsVisible() || !pixels)
		return;

	on[0] = floppy_led[0] != LED_STATE_OFF;
	on[1] = floppy_led[1] != LED_STATE_OFF;
	on[2] = hd_led_frames > 0;

	/* The hatari2014 core's 13x5 bar in a 384 pixel wide frame, scaled */
	led_w = width * 13 / 384;
	led_h = height * 5 / 276;
	if (led_w < 7)
		led_w = 7;
	if (led_w > 64)
		led_w = 64;
	if (led_h < 3)
		led_h = 3;
	if (led_h > 16)
		led_h = 16;
	gap = led_w / 2;
	right = width - led_w / 2;
	top = led_h;
	if (right - 3 * led_w - 2 * gap < 0 || top + led_h > height)
		return;

	/* A rightmost, then B, then the hard disk */
	for (i = 0; i < 3; i++)
	{
		int left = right - (i + 1) * led_w - i * gap;
		if (!on[i])
			continue;
		for (y = top; y < top + led_h; y++)
			for (x = left; x < left + led_w; x++)
				pixels[y * stride + x] = i < 2 ? floppy_color : hd_color;
	}
}

/**
 * Set TOS etc information and initial help message
 */
void Statusbar_InitialSetup(void)
{
}


/**
 * Queue new statusbar message 'msg' to be shown for 'msecs' milliseconds
 */
void Statusbar_AddMessage(const char *msg, uint32_t msecs)
{
}

/**
 * Retrieve/update default statusbar information
 */
void Statusbar_UpdateInfo(void)
{
}
