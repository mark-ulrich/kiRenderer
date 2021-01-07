#include <SDL2/SDL.h>
#include <cstdio>
#include <string>

#include "PNGLib.h"
#include "kiError.h"
#include "kiTexture.h"
#include "kiTypes.h"

// TODO: Maybe use magic number instead of extension to determine filetype
kiTexture*
kiTexture::LoadFromFile(std::string const& path)
{
  // Grab the extension
  size_t extStart = path.rfind('.');
  if (extStart == std::string::npos) {
    kiFatal("no extension");
  }
  std::string ext = path.substr(extStart + 1, path.length() - extStart + 1);
  // TODO: Case insensitivity
  if (ext == "png") {
    return LoadTexturePNG(path);
  }

  kiFatal("Invalid extension or file not found");
  return NULL;
}
