#include "libretro-hatari.h"

#include "vkbd_def.h"
#include "graph.h"

extern int NPAGE;
extern int KCOL;
extern int BKGCOLOR;
extern int SHIFTON;
 
void virtual_kdb(unsigned short int *pixels,int vx,int vy)
{
   int x, y, page;
   short unsigned *pix, coul;

   page = (NPAGE == -1) ? 0 : 50;
   pix= (short unsigned *)&pixels[0];
   coul = RGB565(1, 1, 1);   // text color
   BKGCOLOR = (KCOL>0?0x9cb3:0);  //text background color

   for(x=0;x<NPLGN;x++)  // 10 letters horiz.
   {
      for(y=0;y<NLIGN;y++)  // 5 letters vert.
      {
         DrawBoxBmp(pix,XBASE3+x*XSIDE,YBASE3+y*YSIDE, XSIDE,YSIDE, RGB565(3, 7, 3)); // unselected
         Draw_text(pix,XBASE0-2+x*XSIDE ,YBASE0+YSIDE*y,coul, BKGCOLOR ,2, 2,20,
               SHIFTON==-1?MVk[(y*NPLGN)+x+page].norml:MVk[(y*NPLGN)+x+page].shift);	
      }
   }

   DrawBoxBmp(pix,XBASE3+vx*XSIDE,YBASE3+vy*YSIDE, XSIDE,YSIDE, RGB565(31, 0, 31)); //selected
   Draw_text(pix,XBASE0-2+vx*XSIDE ,YBASE0+YSIDE*vy,RGB565(30,57,0), BKGCOLOR ,2, 2,20,
         SHIFTON==-1?MVk[(vy*NPLGN)+vx+page].norml:MVk[(vy*NPLGN)+vx+page].shift);	
}

int check_vkey2(int x,int y)
{
   int page;
   //check which key is press
   page= (NPAGE==-1) ? 0 : 50;
   return MVk[y*NPLGN+x+page].val;
}

