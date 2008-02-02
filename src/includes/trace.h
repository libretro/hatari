#ifndef HATARI_TRACE_H
#define HATARI_TRACE_H


#include <SDL_types.h>


/* Comment next line to turn off dynamic trace */
#define HATARI_TRACE_ACTIVATED


/* Up to 32 levels when using Uint32 for HatariTraceLevel */
#define	HATARI_TRACE_VIDEO_SYNC		(1<<0)
#define	HATARI_TRACE_VIDEO_RES		(1<<1)
#define	HATARI_TRACE_VIDEO_COLOR	(1<<2)
#define	HATARI_TRACE_VIDEO_BORDER_V	(1<<3)
#define	HATARI_TRACE_VIDEO_BORDER_H	(1<<4)
#define	HATARI_TRACE_VIDEO_ADDR		(1<<5)
#define	HATARI_TRACE_VIDEO_VBL		(1<<6)
#define	HATARI_TRACE_VIDEO_HBL		(1<<7)
#define	HATARI_TRACE_VIDEO_STE		(1<<8)

#define	HATARI_TRACE_MFP_EXCEPTION	(1<<9)
#define	HATARI_TRACE_MFP_START		(1<<10)
#define	HATARI_TRACE_MFP_READ		(1<<11)

#define	HATARI_TRACE_PSG_WRITE_REG	(1<<12)
#define	HATARI_TRACE_PSG_WRITE_DATA	(1<<13)

#define	HATARI_TRACE_CPU_PAIRING	(1<<14)
#define	HATARI_TRACE_CPU_DISASM		(1<<15)
#define	HATARI_TRACE_CPU_EXCEPTION	(1<<16)

#define	HATARI_TRACE_INT		(1<<17)

#define	HATARI_TRACE_FDC		(1<<18)

#define	HATARI_TRACE_IKBD		(1<<19)

#define	HATARI_TRACE_NONE		(0)
#define	HATARI_TRACE_ALL		(~0)

#define	HATARI_TRACE_VIDEO_ALL		( HATARI_TRACE_VIDEO_SYNC | HATARI_TRACE_VIDEO_RES | HATARI_TRACE_VIDEO_COLOR \
		| HATARI_TRACE_VIDEO_BORDER_V | HATARI_TRACE_VIDEO_BORDER_H | HATARI_TRACE_VIDEO_ADDR \
		| HATARI_TRACE_VIDEO_VBL | HATARI_TRACE_VIDEO_HBL | HATARI_TRACE_VIDEO_STE )

#define HATARI_TRACE_MFP_ALL		( HATARI_TRACE_MFP_EXCEPTION | HATARI_TRACE_MFP_START | HATARI_TRACE_MFP_READ )

#define	HATARI_TRACE_PSG_ALL		( HATARI_TRACE_PSG_WRITE_REG | HATARI_TRACE_PSG_WRITE_DATA )

#define	HATARI_TRACE_CPU_ALL		( HATARI_TRACE_CPU_PAIRING | HATARI_TRACE_CPU_DISASM | HATARI_TRACE_CPU_EXCEPTION )




#ifndef HATARI_TRACE_ACTIVATED

#define HATARI_TRACE( level, args... )	{}
#define HATARI_TRACE_LEVEL( level )	(0)

#else

#define	HATARI_TRACE( level, args... ) \
	if ( HatariTraceLevel & level ) fprintf ( stderr , args )
#define HATARI_TRACE_LEVEL( level )	(HatariTraceLevel & level)

#endif


#define HATARI_TRACE_PRINT( args... )	fprintf ( stderr , args )



extern Uint32 HatariTraceLevel;


int	ParseTraceOptions ( char *OptionsStr );


#endif		/* HATARI_TRACE_H */

