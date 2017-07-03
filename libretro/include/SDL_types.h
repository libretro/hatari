/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997, 1998, 1999, 2000, 2001, 2002  Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Sam Lantinga
    slouken@libsdl.org
*/

#ifdef SAVE_RCSID
static char rcsid =
 "@(#) $Id: SDL_types.h,v 1.6 2002/03/06 11:23:01 slouken Exp $";
#endif

/* General data types used by the SDL library */

#ifndef _SDL_types_h
#define _SDL_types_h

//RETRO HACK

#ifdef LSB_FIRST
#define SDL_BYTEORDER SDL_LIL_ENDIAN         
#else    
#define SDL_BYTEORDER SDL_BIG_ENDIAN
#endif


/* The number of elements in a table */
#define SDL_TABLESIZE(table)	(sizeof(table)/sizeof(table[0]))

typedef unsigned char	Uint8;
typedef signed char	Sint8;
typedef unsigned short	Uint16;
typedef signed short	Sint16;
typedef unsigned int	Uint32;
typedef signed int	Sint32;

typedef signed char     int8;
typedef signed short    int16;
typedef signed int   int32;
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned int  uint32;



/* Figure out how to support 64-bit datatypes */
#if !defined(__STRICT_ANSI__)
#if defined(__GNUC__) || defined(__MWERKS__) || defined(__SUNPRO_C)
#define SDL_HAS_64BIT_TYPE	 long
#elif defined(_MSC_VER) /* VC++ */
#define SDL_HAS_64BIT_TYPE	__int64
#endif
#endif /* !__STRICT_ANSI__ */


#define Uint64 unsigned long long 
#define Sint64 signed long long 

#undef SDL_HAS_64BIT_TYPE

/* General keyboard/mouse state definitions */
enum { SDL_PRESSED = 0x01, SDL_RELEASED = 0x00 };

#endif
