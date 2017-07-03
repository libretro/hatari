#ifndef SDL_ENDIAN_H
#define SDL_ENDIAN_H
//RETRO HACK
#include "SDL.h"

static __inline__ unsigned short SDL_Swap16(unsigned short x){
	unsigned short result= ((x<<8)|(x>>8)); 
return result;
}
static __inline__ unsigned SDL_Swap32(unsigned x){
	unsigned result= ((x<<24)|((x<<8)&0x00FF0000)|((x>>8)&0x0000FF00)|(x>>24));
 return result;
}

//#define SDL_SwapLE16(X) SDL_Swap16(X)
//#define SDL_SwapLE32(X) SDL_Swap32(X)

#ifdef LSB_FIRST

#define SDL_SwapLE16(X)	(X)
#define SDL_SwapLE32(X) (X)

#define SDL_SwapBE16(X) SDL_Swap16(X)
#define SDL_SwapBE32(X) SDL_Swap32(X)

#else

#define SDL_SwapLE16(X)	SDL_Swap16(X)
#define SDL_SwapLE32(X) SDL_Swap32(X)

#define SDL_SwapBE16(X) (X)
#define SDL_SwapBE32(X) (X)

#endif

#define SDL_LIL_ENDIAN	1234
#define SDL_BIG_ENDIAN	4321

#ifdef LSB_FIRST
#define SDL_BYTEORDER SDL_LIL_ENDIAN         
#else    
#define SDL_BYTEORDER SDL_BIG_ENDIAN
#endif


#endif /* UAE_MACCESS_H */
