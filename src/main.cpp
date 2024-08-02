#define KIR_USE_STB_IMAGE

#if defined(KIR_USE_STB_IMAGE)
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

#include <SDL2/SDL.h>

#include <iostream>
#include <string>

#include "kiRenderer.h"

#define WIDTH 320
#define HEIGHT 200

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

  kiRenderer renderer(WIDTH, HEIGHT);
  kiTexture* tex = kiTexture::LoadFromFile("test.png");

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

    // TEST LINES
    kiColor color(0.2f, 1.0f, 0.2f);
    renderer.DrawLine(kiVector2i(20, 10), kiVector2i(20, 100), color);
    renderer.DrawLine(kiVector2i(45, 100), kiVector2i(90, 100), color);
    renderer.DrawLine(kiVector2i(20, 349), kiVector2i(20, 132), color);
    renderer.DrawLine(kiVector2i(430, 100), kiVector2i(210, 100), color);

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
