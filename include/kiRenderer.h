#ifndef __KIRENDERER_H__
#define __KIRENDERER_H__

#include <SDL2/SDL.h>

#include "kiColor.h"
#include "kiTexture.h"
#include "types.h"
#include "Vector2.h"

class kiRenderer
{
  int width, height;
  float scale;

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
  kiRenderer(int width, int height, float scale = 1.0f);
  ~kiRenderer();

  void Lock();
  void Unlock();

  // Drawing Interface
  // TODO: Include methods to draw individual pixels, lines (vertical,
  void DrawPixel(Vector2i const& position, kiColor const& color);

  void DrawLine(Vector2i const& p1, Vector2i const& p2)
  {
    DrawLine(p1, p2, drawColor);
  }
  void DrawLine(Vector2i const& p1,
                Vector2i const& p2,
                kiColor const& color);

  // TODO: Implement an "extended" version of Blit
  void Blit(kiTexture const& texture, Vector2i const& position);

  void Clear() { Clear(drawColor); }
  void Clear(kiColor const& color);

  void Render() const;

private:
  void DrawLineHorizontal(int y, int x1, int x2, kiColor const& color);
  void DrawLineVertical(int x, int y1, int y2, kiColor const& color);
};

#endif // __KIRENDERER_H__
