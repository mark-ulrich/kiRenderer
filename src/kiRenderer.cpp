#include <SDL2/SDL.h>
#include <algorithm>
#include <cassert>

#include "kiError.h"
#include "kiRenderer.h"

kiRenderer::kiRenderer(int width, int height, float scale)
  : width(width)
  , height(height)
  , scale(scale)
  , isLocked(false)
{
  this->pitch = width * 4;
  this->pixels = nullptr;

  // Init SDL window & renderer
  sdlWindow =
    SDL_CreateWindow("kiRenderer",
                     SDL_WINDOWPOS_CENTERED,
                     SDL_WINDOWPOS_CENTERED,
                     static_cast<int>(static_cast<float>(width) * scale),
                     static_cast<int>(static_cast<float>(height) * scale),
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
kiRenderer::DrawPixel(Vector2i const& position, kiColor const& color)
{
  assert(isLocked);
  if (position.x < 0 || position.x >= width || position.y < 0 ||
      position.y >= height) {
    return;
  }
  int index = position.y * (pitch / 4) + position.x;
  u32 pixel = color.PackARGB();
  pixels[index] = pixel;
}

// Render a colored line between points p1 and p2.
void
kiRenderer::DrawLine(Vector2i const& p1,
                     Vector2i const& p2,
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
      DrawPixel(Vector2i(x, y), color);
    }
  }
}

void
kiRenderer::Render() const
{
  SDL_RenderClear(sdlRenderer);
  SDL_RenderCopy(sdlRenderer, frameBuffer, nullptr, nullptr);
  SDL_RenderPresent(sdlRenderer);
}

void
kiRenderer::DrawLineVertical(int x, int y1, int y2, kiColor const& color)
{
  int begin = std::min(y1, y2);
  int end = std::max(y1, y2);

  for (int y = begin; y < end; ++y) {
    DrawPixel(Vector2i(x, y), color);
  }
}

void
kiRenderer::DrawLineHorizontal(int y, int x1, int x2, kiColor const& color)
{
  int begin = std::min(x1, x2);
  int end = std::max(x1, x2);

  for (int x = begin; x < end; ++x) {
    DrawPixel(Vector2i(x, y), color);
  }
}

void
kiRenderer::Lock()
{
  if (SDL_LockTexture(frameBuffer, nullptr, (void**)&pixels, (int*)&pitch) <
      0) {
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
kiRenderer::Blit(kiTexture const& texture, Vector2i const& position)
{
  // TODO: Optimize this
  for (int y = 0; y < texture.Height(); ++y) {
    for (int x = 0; x < texture.Width(); ++x) {
      kiColor const& color = texture.GetPixel(x, y);
      if (texture.UsesColorKey() && color == texture.ColorKey())
        continue;
      DrawPixel(Vector2i(x + position.x, y + position.y),
                texture.GetPixel(x, y));
    }
  }
}
