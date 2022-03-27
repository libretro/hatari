#include <libco.h>
extern cothread_t mainThread;
extern cothread_t emuThread;
extern int pauseg;

extern int gmx,gmy;
extern int fmousex,fmousey;
extern int SND;

#ifndef sysconf
//#define sysconf(a) a
#endif

extern char RETRO_DIR[512];
extern char RETRO_TOS[512];
extern char RPATH[512];
extern long GetTicks(void);
extern void enter_gui();
extern int LoadTosFromRetroSystemDir();
extern void retro_shutdown_hatari(void);

#include <unistd.h>

#if defined(AND)
#define CONFDIR "/mnt/sdcard/st"
    //#warning "conf dir for android"
#elif defined(__PS3__)
#define CONFDIR "/dev_hdd0/game/RETROARCH/USRDIR/cores/system"
//#warning "conf dir for ps3"
int FAKEaccess(char* fpath, int unused)
{
	struct stat buffer;
	return stat(fpath, &buffer);
}

FILE* FAKEtmpfile()
{
	return fopen(tmpCfg, "w+");
}
#elif defined(WIIU)
#define CONFDIR "sd:/retroarch/cores/system"
#elif defined(GEKKO)
#define CONFDIR "sd:/HOMEBREW/ST"
#elif defined(VITA)
#define CONFDIR "ux0:/data/retroarch/system"
#else
#define CONFDIR "."
//#warning "conf dir for linux"
#endif

