#include <ctype.h>

//Args for experimental_cmdline
static char ARGUV[64][1024];
static unsigned char ARGUC=0;

// Args for Core
static char XARGV[64][1024];
static const char* xargv_cmd[64];
int PARAMCOUNT=0;

extern int  hmain(int argc, char *argv[]);
void parse_cmdline( const char *argv );

// Global variables
extern bool hatari_twojoy;
extern bool hatari_fastfdc;
extern bool hatari_autoloadb;
extern bool hatari_fastboot;
extern bool hatari_borders;
extern char hatari_frameskips[3];
extern char hatari_ramsize[3];
extern char hatari_machinetype[7];
extern char hatari_writeprotect_floppy[5];
extern char hatari_writeprotect_hd[5];

void Add_Option(const char* option)
{
   printf("Option : %s\n", option);
   static int first=0;

   if(first==0)
   {
      PARAMCOUNT=0;	
      first++;
   }

   sprintf(XARGV[PARAMCOUNT++],"%s\0",option);
}

int pre_main(const char *argv)
{
   int i;
   bool Only1Arg;

   parse_cmdline(argv); 

   Only1Arg = (strcmp(ARGUV[0],"hatari") == 0) ? 0 : 1;

   for (i = 0; i<64; i++)
      xargv_cmd[i] = NULL;

   //	Add_Option("hatari");

   if(Only1Arg)
   {
      Add_Option("hatari");
      //logfile use when debugging
      //Add_Option("--log-file");
      //Add_Option("E:\\Hatari.log");
      Add_Option("--statusbar");
      Add_Option("0");
      Add_Option("--joy0");
      Add_Option(hatari_twojoy==true ? "real":"none");
      Add_Option("--fastfdc");
      Add_Option(hatari_fastfdc==true ? "1":"0");
      Add_Option("--fast-boot");
      Add_Option(hatari_fastboot ==true ? "1":"0");
      Add_Option("--borders");
      Add_Option(hatari_borders==true ? "1":"0");
      Add_Option("--frameskips");
      Add_Option(hatari_frameskips);
      Add_Option("--machine");
      Add_Option(hatari_machinetype);
      Add_Option("--memsize");
      Add_Option(hatari_ramsize);
      Add_Option("--disk-a");
      Add_Option(RPATH[0]==0 ? "":RPATH/*ARGUV[0]*/);
      Add_Option("--disk-b");
      Add_Option(hatari_autoloadb==true ? RPATH2[0]==0 ? "" : RPATH2 : "");
      Add_Option("--protect-floppy");
      Add_Option(hatari_writeprotect_floppy);
      Add_Option("--protect-hd");
      Add_Option(hatari_writeprotect_hd);
      if (RETRO_GD[0] == 0 && RETRO_IDE[0]==0)
      {
          Add_Option("--acsi");
          Add_Option(RETRO_HD[0] == 0 ? "" : RETRO_HD);
      }
      else if (RETRO_IDE[0] == 0)
      {
          Add_Option("--harddrive");
          //Add_Option("E:\\Games_RetroArch\\Atari\\Atari - ST\\GEM\\Chaos Engine Gamex\\");
          Add_Option(RETRO_GD[0] == 0 ? "" : RETRO_GD);
      }
      else
      {
          Add_Option("--ide-master");
          Add_Option(RETRO_IDE[0] == 0 ? "" : RETRO_IDE);
      }
   }
   else
   { // Pass all cmdline args
      for(i = 0; i < ARGUC; i++)
         Add_Option(ARGUV[i]);
   }

   for (i = 0; i < PARAMCOUNT; i++)
   {
      xargv_cmd[i] = (char*)(XARGV[i]);
      printf("%2d  %s\n",i,XARGV[i]);
   }

   hmain(PARAMCOUNT,( char **)xargv_cmd); 

   xargv_cmd[PARAMCOUNT - 2] = NULL;
}

void parse_cmdline(const char *argv)
{
	char *p,*p2,*start_of_word;
	int c,c2;
	static char buffer[512*4];
	enum states { DULL, IN_WORD, IN_STRING } state = DULL;
	
	strcpy(buffer,argv);
	strcat(buffer," \0");

	for (p = buffer; *p != '\0'; p++)
   {
      c = (unsigned char) *p; /* convert to unsigned char for is* functions */
      switch (state)
      {
         case DULL: /* not in a word, not in a double quoted string */
            if (isspace(c)) /* still not in a word, so ignore this char */
               continue;
            /* not a space -- if it's a double quote we go to IN_STRING, else to IN_WORD */
            if (c == '"')
            {
               state = IN_STRING;
               start_of_word = p + 1; /* word starts at *next* char, not this one */
               continue;
            }
            state = IN_WORD;
            start_of_word = p; /* word starts here */
            continue;
         case IN_STRING:
            /* we're in a double quoted string, so keep going until we hit a close " */
            if (c == '"')
            {
               /* word goes from start_of_word to p-1 */
               //... do something with the word ...
               for (c2 = 0,p2 = start_of_word; p2 < p; p2++, c2++)
                  ARGUV[ARGUC][c2] = (unsigned char) *p2;
               ARGUC++; 

               state = DULL; /* back to "not in word, not in string" state */
            }
            continue; /* either still IN_STRING or we handled the end above */
         case IN_WORD:
            /* we're in a word, so keep going until we get to a space */
            if (isspace(c))
            {
               /* word goes from start_of_word to p-1 */
               //... do something with the word ...
               for (c2 = 0,p2 = start_of_word; p2 <p; p2++,c2++)
                  ARGUV[ARGUC][c2] = (unsigned char) *p2;
               ARGUC++; 

               state = DULL; /* back to "not in word, not in string" state */
            }
            continue; /* either still IN_WORD or we handled the end above */
      }	
   }
}

