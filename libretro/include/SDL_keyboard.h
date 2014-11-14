//JUST WRAPPER

#ifndef _SDL_keyboard_h
#define _SDL_keyboard_h

#include "SDL_keysym.h"

typedef struct{
  Uint8 scancode;
  SDLKey sym;
  SDLMod mod;
  Uint16 unicode;
} SDL_keysym;

#endif
