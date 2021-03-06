#include <SDL2/SDL.h>
#include <algorithm>
#include <cassert>

#include "kiError.h"
#include "kiRenderer.h"

kiRenderer::kiRenderer(u32 width, u32 height)
{
  this->width = width;
  this->height = height;

  // Init SDL window & renderer
  sdlWindow = SDL_CreateWindow("kiRenderer",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               width,
                               height,
                               0);
  if (!sdlWindow) {
    kiFatal();
  }
  sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
  if (!sdlRenderer) {
    kiFatal();
  }

  // Init framebuffer
  SDL_RendererInfo rendererInfo;
  SDL_GetRendererInfo(sdlRenderer, &rendererInfo);
  frameBuffer = SDL_CreateTexture(sdlRenderer,
                                  rendererInfo.texture_formats[0],
                                  SDL_TEXTUREACCESS_STREAMING,
                                  width,
                                  height);
  if (!frameBuffer) {
    kiFatal();
  }
}

kiRenderer::~kiRenderer()
{
  SDL_DestroyTexture(frameBuffer);
  SDL_DestroyRenderer(sdlRenderer);
  SDL_DestroyWindow(sdlWindow);
}

inline void
kiRenderer::DrawPixel(kiVector2i const& position, kiColor const& color)
{
  assert(isLocked);
  int index = position.y * (pitch / 4) + position.x;
  u32 pixel = color.PackARGB();
  pixels[index] = pixel;
}

// Render a colored line between points p1 and p2.
void
kiRenderer::DrawLine(kiVector2i const& p1,
                     kiVector2i const& p2,
                     kiColor const& color)
{
  using std::max;
  using std::min;

  // TODO: Implement clipping (Higher level?)

  if (p1.x == p2.x) {
    return DrawLineVertical(p1.x, p1.y, p2.y, color);
  } else if (p1.y == p2.y) {
    return DrawLineHorizontal(p1.y, p1.x, p2.x, color);
  }

  // TODO: Oblique
}

void
kiRenderer::Clear(kiColor const& color)
{
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      DrawPixel(kiVector2i(x, y), color);
    }
  }
}

void
kiRenderer::Render() const
{
  SDL_RenderClear(sdlRenderer);
  SDL_RenderCopy(sdlRenderer, frameBuffer, NULL, NULL);
  SDL_RenderPresent(sdlRenderer);
}

void
kiRenderer::DrawLineVertical(int x, int y1, int y2, kiColor const& color)
{
  using std::max;
  using std::min;

  int begin = min(y1, y2);
  int end = max(y1, y2);

  for (int y = begin; y < end; ++y) {
    DrawPixel(kiVector2i(x, y), color);
  }
}

void
kiRenderer::DrawLineHorizontal(int y, int x1, int x2, kiColor const& color)
{
  using std::max;
  using std::min;

  int begin = min(x1, x2);
  int end = max(x1, x2);

  for (int x = begin; x < end; ++x) {
    DrawPixel(kiVector2i(x, y), color);
  }
}

void
kiRenderer::Lock()
{
  if (SDL_LockTexture(frameBuffer, NULL, (void**)&pixels, &pitch) < 0) {
    kiFatal();
  }
  isLocked = true;
}

void
kiRenderer::Unlock()
{
  SDL_UnlockTexture(frameBuffer);
  isLocked = false;
}

void
kiRenderer::Blit(kiTexture const& texture, kiVector2i const& position)
{
  // NOT IMPLEMENTED
}
