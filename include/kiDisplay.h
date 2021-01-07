#ifndef __KIDISPLAY_H_
#define __KIDISPLAY_H_

#include <SDL2/SDL.h>


class kiDisplay
{
  SDL_Window* sdlWindow;
  SDL_Renderer* sdlRenderer;

public:
  kiDisplay();
  ~kiDisplay();

  SDL_Renderer* GetRenderer() { return sdlRenderer; }
  SDL_Window* GetWindow() { return sdlWindow; }
};


#endif // __KIDISPLAY_H_
