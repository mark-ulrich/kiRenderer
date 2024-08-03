#define KIR_USE_STB_IMAGE

#if defined(KIR_USE_STB_IMAGE)
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

#include <SDL2/SDL.h>

#include <iostream>
#include <string>

#include "kiRenderer.h"

static int const Width = 320;
static int const Height = 200;
static float const RenderScale = 4.0f;

void
LogConsole(std::string const& msg);

using std::cout;
using std::endl;

int
main(int argc, char* argv[])
{
  FE_UNUSED_PARM(argc);
  FE_UNUSED_PARM(argv);

  LogConsole("Initializing...");
  SDL_Init(SDL_INIT_EVERYTHING);

  kiRenderer renderer(Width, Height, RenderScale);
  kiTexture* tex = kiTexture::LoadFromFile("test_rgb.png");

  bool isRunning = true;
  while (isRunning) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        isRunning = false;
      }

      if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
          case SDLK_q:
            isRunning = false;
            break;
        }
      }
    }

    renderer.Lock();

    u8 const* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_J]) {
      renderer.Clear(kiColor(0.4, 0.4, 0.4));
    } else {
      renderer.Clear();
    }

    renderer.Blit(*tex, Vector2i(0, 0));

    // TEST LINES
    kiColor color(0.2f, 1.0f, 0.2f);
    renderer.DrawLine(Vector2i(20, 10), Vector2i(20, 100), color);
    renderer.DrawLine(Vector2i(45, 100), Vector2i(90, 100), color);
    renderer.DrawLine(Vector2i(20, 199), Vector2i(20, 132), color);
    renderer.DrawLine(Vector2i(310, 100), Vector2i(210, 100), color);

    renderer.Unlock();

    renderer.Render();
  }

  LogConsole("Shutting down...");
  SDL_Quit();

  return 0;
}

void
LogConsole(std::string const& msg)
{
  std::clog << "[-] " << msg << std::endl;
}
