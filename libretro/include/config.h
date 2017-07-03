/* CMake config.h for Hatari */
//RETRO HACK

/* Define if you have a PNG compatible library */
//#define HAVE_LIBPNG 1

/* Define if you have a readline compatible library */
//#define HAVE_LIBREADLINE 1

/* Define if you have the PortAudio library */
//#define HAVE_PORTAUDIO 1

/* Define if you have the capsimage library */
//#define HAVE_CAPSIMAGE 1

/* Define if you have a X11 environment */
//#define HAVE_X11 1

/* Define to 1 if you have the `z' library (-lz). */
#define HAVE_LIBZ 1

/* Define to 1 if you have the <zlib.h> header file. */
#define HAVE_ZLIB_H 1

/* Define to 1 if you have the <termios.h> header file. */
//#define HAVE_TERMIOS_H 1

/* Define to 1 if you have the <glob.h> header file. */
//#define HAVE_GLOB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <SDL/SDL_config.h> header file. */
//#define HAVE_SDL_SDL_CONFIG_H 1

/* Define to 1 if you have the <sys/times.h> header file. */
#define HAVE_SYS_TIMES_H 1

/* Define to 1 if you have the `cfmakeraw' function. */
//#define HAVE_CFMAKERAW 1

/* Define to 1 if you have the 'setenv' function. */
//#define HAVE_SETENV 1

/* Define to 1 if you have the `select' function. */
//#define HAVE_SELECT 1

/* Define to 1 if you have unix domain sockets */
//#define HAVE_UNIX_DOMAIN_SOCKETS 1

#ifdef __LIBRETRO__
#if defined(AND) || defined(__CELLOS_LV2__)
#undef HAVE_POSIX_MEMALIGN
#else
#define HAVE_POSIX_MEMALIGN 1
#endif
#else
/* Define to 1 if you have the 'posix_memalign' function. */
#define HAVE_POSIX_MEMALIGN 1
#endif

/* Define to 1 if you have the 'posix_memalign' function. */
//#define HAVE_POSIX_MEMALIGN 1

/* Define to 1 if you have the 'memalign' function. */
#define HAVE_MEMALIGN 1

/* Define to 1 if you have the 'gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define to 1 if you have the 'nanosleep' function. */
//#define HAVE_NANOSLEEP 1

/* Define to 1 if you have the 'alphasort' function. */
#ifndef WIN32PORT
#define HAVE_ALPHASORT 1
#endif
/* Define to 1 if you have the 'scandir' function. */
#define HAVE_SCANDIR 1

#ifdef __LIBRETRO__
#if defined(AND) || defined(__CELLOS_LV2__) || defined(WIN32PORT)
#undef HAVE_STATVFS
#else
#define HAVE_STATVFS 1
#endif
#else
/* Define to 1 if you have the 'statvfs' function. */
#define HAVE_STATVFS 1
#endif
/* Define to 1 if you have the 'statvfs' function. */
//#define HAVE_STATVFS 1

/* Define to 1 if you have the 'fseeko' function. */
//#define HAVE_FSEEKO 1

/* Define to 1 if you have the 'ftello' function. */
//#define HAVE_FTELLO 1


/* Relative path from bindir to datadir */
#define BIN2DATADIR "."

/* Define to 1 to enable DSP 56k emulation for Falcon mode */
#define ENABLE_DSP_EMU 1

/* Define to 1 to enable WINUAE cpu  */

#ifdef NEW_WCPU 
#define ENABLE_WINUAE_CPU 1
#endif

/* Define to 1 to use less memory - at the expense of emulation speed */
//#define ENABLE_SMALL_MEM 1

/* Define to 1 to enable trace logs - undefine to slightly increase speed */
//#define ENABLE_TRACING 1
