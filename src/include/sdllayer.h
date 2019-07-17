#ifndef SDLLAYER_H
#define SDLLAYER_H

#include "SDL.h"

class SDLLayer {
 public:
  static void draw_v_line ( SDL_Surface* Surface, SDL_Color RGBcolor, Uint16 x, Uint16 y, Uint16 length, Uint16 pt );
  static void draw_h_line ( SDL_Surface* Surface, SDL_Color RGBcolor, Uint16 x, Uint16 y, Uint16 length, Uint16 pt );
  static void draw_solidrectangle ( SDL_Surface* Surface, SDL_Color RGBcolor, Uint16 x, Uint16 y, Uint16 width, Uint16 height );
  static void draw_solidrectangle ( SDL_Surface* Surface, Uint32 color, Uint16 x, Uint16 y, Uint16 width, Uint16 height );
  static void draw_rectangle ( SDL_Surface* Surface, SDL_Color RGBcolor, Uint16 x, Uint16 y, Uint16 width, Uint16 height, Uint8 lnpx = 1);
  static void draw_rectangle ( SDL_Surface* Surface, Uint32 color, Uint16 x, Uint16 y, Uint16 width, Uint16 height, Uint8 lnpx = 1);
  static void set_pixel ( SDL_Surface * Surface, SDL_Color RGBcolor, Sint32 x, Sint32 y );
  static void set_pixel ( SDL_Surface * Surface, Uint32 color, Sint32 x, Sint32 y );
  static void get_pixel ( SDL_Surface * Surface, SDL_Color & RGBcolor, Sint32 x, Sint32 y );
  static void get_pixel ( SDL_Surface * Surface, Uint32 & color, Sint32 x, Sint32 y );
};

#endif //SDLLAYER_H
