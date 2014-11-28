//RETRO HACK TO REDO
//SDL SAVEBMP (used in screenSnapShot.c)

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "main.h"
#include "screen.h"

extern unsigned char savbkg[1024*1024*2];

typedef struct                       /**** BMP file header structure ****/
{
   unsigned short bfType;           /* Magic number for file */
   unsigned int   bfSize;           /* Size of file */
   unsigned short bfReserved1;      /* Reserved */
   unsigned short bfReserved2;      /* ... */
   unsigned int   bfOffBits;        /* Offset to bitmap data */
} BITMAPFILEHEADER;

#  define BF_TYPE 0x4D42             /* "MB" */

typedef struct                       /**** BMP file info structure ****/
{
   unsigned int   biSize;           /* Size of info header */
   int            biWidth;          /* Width of image */
   int            biHeight;         /* Height of image */
   unsigned short biPlanes;         /* Number of color planes */
   unsigned short biBitCount;       /* Number of bits per pixel */
   unsigned int   biCompression;    /* Type of compression to use */
   unsigned int   biSizeImage;      /* Size of image data */
   int            biXPelsPerMeter;  /* X pixels per meter */
   int            biYPelsPerMeter;  /* Y pixels per meter */
   unsigned int   biClrUsed;        /* Number of colors used */
   unsigned int   biClrImportant;   /* Number of important colors */
} BITMAPINFOHEADER;

/*
 * Constants for the biCompression field...
 */

#  define BI_RGB       0             /* No compression - straight BGR data */
#  define BI_RLE8      1             /* 8-bit run-length compression */
#  define BI_RLE4      2             /* 4-bit run-length compression */
#  define BI_BITFIELDS 3             /* RGB bitmap with RGB masks */

typedef struct                       /**** Colormap entry structure ****/
{
   unsigned char  rgbBlue;          /* Blue value */
   unsigned char  rgbGreen;         /* Green value */
   unsigned char  rgbRed;           /* Red value */
   unsigned char  rgbReserved;      /* Reserved */
} RGBQUAD;

typedef struct                       /**** Bitmap information structure ****/
{
   BITMAPINFOHEADER bmiHeader;      /* Image header */
   RGBQUAD          bmiColors[256]; /* Image colormap */
} BITMAPINFO;

/*
 * 'read_word()' - Read a 16-bit unsigned integer.
 */

   static unsigned short     /* O - 16-bit unsigned integer */
read_word(FILE *fp)       /* I - File to read from */
{
   unsigned char b0, b1; /* Bytes from file */

   b0 = getc(fp);
   b1 = getc(fp);

   return ((b1 << 8) | b0);
}

/*
 * 'read_dword()' - Read a 32-bit unsigned integer.
 */

   static unsigned int               /* O - 32-bit unsigned integer */
read_dword(FILE *fp)              /* I - File to read from */
{
   unsigned char b0, b1, b2, b3; /* Bytes from file */

   b0 = getc(fp);
   b1 = getc(fp);
   b2 = getc(fp);
   b3 = getc(fp);

   return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}


/*
 * 'read_long()' - Read a 32-bit signed integer.
 */

   static int                        /* O - 32-bit signed integer */
read_long(FILE *fp)               /* I - File to read from */
{
   unsigned char b0, b1, b2, b3; /* Bytes from file */

   b0 = getc(fp);
   b1 = getc(fp);
   b2 = getc(fp);
   b3 = getc(fp);

   return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}


/*
 * 'write_word()' - Write a 16-bit unsigned integer.
 */

   static int                     /* O - 0 on success, -1 on error */
write_word(FILE           *fp, /* I - File to write to */
      unsigned short w)   /* I - Integer to write */
{
   putc(w, fp);
   return (putc(w >> 8, fp));
}


/*
 * 'write_dword()' - Write a 32-bit unsigned integer.
 */

   static int                    /* O - 0 on success, -1 on error */
write_dword(FILE         *fp, /* I - File to write to */
      unsigned int dw)  /* I - Integer to write */
{
   putc(dw, fp);
   putc(dw >> 8, fp);
   putc(dw >> 16, fp);
   return (putc(dw >> 24, fp));
}


/*
 * 'write_long()' - Write a 32-bit signed integer.
 */

   static int           /* O - 0 on success, -1 on error */
write_long(FILE *fp, /* I - File to write to */
      int  l)   /* I - Integer to write */
{
   putc(l, fp);
   putc(l >> 8, fp);
   putc(l >> 16, fp);
   return (putc(l >> 24, fp));
}



int SDL_SaveBMP(SDL_Surface *surface,const char *file){

   FILE *fp;                      /* Open file pointer */
   int  i,size,                     /* Size of file */
        infosize,                 /* Size of bitmap info */
        bitsize;                  /* Size of bitmap pixels */

   unsigned char *pixels,*pixflip;
   unsigned short int temp;


   /* Try opening the file; use "wb" mode to write this *binary* file. */
   if ((fp = fopen(file, "wb")) == NULL){
      printf("openfile faided %s\n",file);
      return (-1);
   }

   pixels = malloc(sizeof(unsigned char)*3*retrow*retroh);

   bitsize = 3*retrow*retroh;

   /* Figure out the header size */
   infosize = sizeof(BITMAPINFOHEADER);

   size = sizeof(BITMAPFILEHEADER) + infosize + bitsize;

   /* Write the file header, bitmap information, and bitmap pixel data... */

   write_word(fp, BF_TYPE);        /* bfType */
   write_dword(fp, size);          /* bfSize */
   write_word(fp, 0);              /* bfReserved1 */
   write_word(fp, 0);              /* bfReserved2 */
   write_dword(fp, 18 + infosize); /* bfOffBits */

   write_dword(fp, 40/*info->bmiHeader.biSize*/);
   write_long(fp, retrow/*info->bmiHeader.biWidth*/);
   write_long(fp, retroh/*info->bmiHeader.biHeight*/);
   write_word(fp,   1/* info->bmiHeader.biPlanes*/);
   write_word(fp,  24/*info->bmiHeader.biBitCount*/);
   write_dword(fp,  0/*info->bmiHeader.biCompression*/);
   write_dword(fp,  3*retrow*retroh/*info->bmiHeader.biSizeImage*/);
   write_long(fp,   0/*info->bmiHeader.biXPelsPerMeter*/);
   write_long(fp,   0/*info->bmiHeader.biYPelsPerMeter*/);
   write_dword(fp,  0/*info->bmiHeader.biClrUsed*/);
   write_dword(fp,  0/*info->bmiHeader.biClrImportant*/);


   // RGB565 to bgr

   unsigned short int *ptr=(unsigned short int*)&savbkg[0];

   short R8, G8 , B8 ;

   for (i = 0; i < retrow * retroh; i++)
   {
      temp = (unsigned short  int) (*ptr)&0xffff;

#define R5 ((temp>>11)&0x1F)
#define G6 ((temp>>5 )&0x3F)
#define B5 ((temp    )&0x1F)

      R8 = ( R5 * 527 + 23 ) >> 6;
      G8 = ( G6 * 259 + 33 ) >> 6;
      B8 = ( B5 * 527 + 23 ) >> 6;

      ptr++; 

      //rbg?
      pixels[(i*3)+0]= R8;
      pixels[(i*3)+1]= B8;
      pixels[(i*3)+2]= G8;
   }  

   const int bw = retrow*3;
   int pad;

   // Write the bitmap image upside down 
   pixflip = (Uint8 *) pixels + (retroh *bw);
   pad = ((bw % 4) ? (4 - (bw % 4)) : 0);
   while (pixflip > (Uint8 *) pixels)
   {
      pixflip -= bw;
      if (fwrite(pixflip, 1, bw, fp) != bw)
      {
         printf("write erreur %d\n",bw);
         free(pixels);
         fclose(fp);
         return -1;                
      }
      if (pad)
      {
         const Uint8 padbyte = 0;
         for (i = 0; i < pad; ++i)
            fwrite( &padbyte, 1, 1, fp);
      }
   }

   fclose(fp);
   free(pixels);

   return (0);    

}

