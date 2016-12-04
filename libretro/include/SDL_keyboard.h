//JUST WRAPPER

#ifndef _SDL_keyboard_h
#define _SDL_keyboard_h

#include "SDL_keysym.h"

typedef struct{

  unsigned char scancode;
  SDLKey sym;
  SDLMod mod;
  unsigned short unicode;

} SDL_keysym;

#endif
