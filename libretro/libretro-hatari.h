#ifndef LIBRETRO_HATARI_H
#define LIBRETRO_HATARI_H 1

#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "SDL.h"

#include <stdbool.h>
#include "ikbd.h"
#include "configuration.h"

extern const char SDLKeyToSTScanCode[512] ;

#ifdef HAVE_LIBCO
#include <libco.h>
extern cothread_t mainThread;
extern cothread_t emuThread;
#endif

extern char Key_Sate[512];
extern char Key_Sate2[512];

extern int pauseg; 

#include "SDL_video.h"

#define LOGI printf

#define NPLGN 10
#define NLIGN 5
#define NLETT 5

#define XSIDE  (CROP_WIDTH/NPLGN -1)
#define YSIDE  (CROP_HEIGHT/8 -1)

#define YBASE0 (CROP_HEIGHT - NLIGN*YSIDE -8)
#define XBASE0 0+4+2
#define XBASE3 0
#define YBASE3 YBASE0 -4

#define STAT_DECX 120
#define STAT_YSZ  20

#define RGB565(r, g, b)  (((r) << (5+6)) | ((g) << 6) | (b))

#endif
