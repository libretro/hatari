#ifdef HAVE_LIBCO
#include <libco.h>
extern cothread_t mainThread;
extern cothread_t emuThread;
#else
extern int CPULOOP;
#endif

extern int pauseg;
#ifdef __CELLOS_LV2__
#undef HAVE_GETTIMEOFDAY
#undef HAVE_NANOSLEEP
#endif
extern int gmx,gmy;
extern int fmousex,fmousey;
extern int SND;

#ifndef sysconf
//#define sysconf(a) a
#endif

extern char RETRO_DIR[512];
extern char RPATH[512];
extern long GetTicks(void);
extern void pause_select();
extern int LoadTosFromRetroSystemDir();
extern void retro_shutdown_hatari(void);

#include <unistd.h>

#if defined(AND)
#define CONFDIR "/mnt/sdcard/st"
    //#warning "conf dir for android"
#elif defined(__CELLOS_LV2__)
#define CONFDIR "/dev_hdd0/HOMEBREW/ST"
//#warning "conf dir for ps3"
#elif defined(GEKKO)
#define CONFDIR "sd:/HOMEBREW/ST"
#else
#define CONFDIR "."
//#warning "conf dir for linux"
#endif

#define  Main_WarpMouse(a,b)  Main_WarpMouse((a),(b), false)
