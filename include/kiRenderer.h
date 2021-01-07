#ifndef __KIRENDERER_H__
#define __KIRENDERER_H__

#include <SDL2/SDL.h>

#include "kiColor.h"
#include "kiTexture.h"
#include "kiTypes.h"
#include "kiVector.h"

class kiRenderer
{
  int width, height;

  SDL_Window* sdlWindow;
  SDL_Renderer* sdlRenderer;

  // TODO: Perhaps implement page flipping? Look up whether SDL is already
  // handling it on the back end.
  SDL_Texture* frameBuffer;

  kiColor drawColor;

  int pitch;
  u32* pixels;
  bool isLocked;

public:
  kiRenderer(u32 width, u32 height);
  ~kiRenderer();

  void Lock();
  void Unlock();

  // Drawing Interface
  // TODO: Include methods to draw individual pixels, lines (vertical,
  void DrawPixel(kiVector2i const& position, kiColor const& color);

  void DrawLine(kiVector2i const& p1, kiVector2i const& p2)
  {
    DrawLine(p1, p2, drawColor);
  }
  void DrawLine(kiVector2i const& p1,
                kiVector2i const& p2,
                kiColor const& color);

  // TODO: Implement an "extended" version of Blit
  void Blit(kiTexture const& texture, kiVector2i const& position);

  void Clear() { Clear(drawColor); }
  void Clear(kiColor const& color);

  void Render() const;

private:
  void DrawLineHorizontal(int y, int x1, int x2, kiColor const& color);
  void DrawLineVertical(int x, int y1, int y2, kiColor const& color);
};

#endif // __KIRENDERER_H__
