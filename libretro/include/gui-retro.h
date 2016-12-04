#undef SGRADIOBUTTON_NORMAL 
#undef SGRADIOBUTTON_SELECTED 
#undef SGCHECKBOX_NORMAL 
#undef SGCHECKBOX_SELECTED 
#undef SGARROWUP 
#undef SGARROWDOWN 
#undef SGFOLDER

#define SGRADIOBUTTON_NORMAL 46//12
#define SGRADIOBUTTON_SELECTED 219//13
#define SGCHECKBOX_NORMAL 196//14
#define SGCHECKBOX_SELECTED 197//15
#define SGARROWUP "\xCB"// 1
#define SGARROWDOWN "\xCA"// 2
#define SGARROWLEFT "<"// 4
#define SGARROWRIGHT ">"// 3
#define SGFOLDER     '~'

#include "graph.h"

extern void gui_poll_events();
extern int  GuiGetMouseState( int * x,int * y);
extern int pauseg;

#define SDLGui_DoDialog(a,b) SDLGui_DoDialog((a),(b), false)
#define  Main_WarpMouse(a,b)  Main_WarpMouse((a),(b), false)
