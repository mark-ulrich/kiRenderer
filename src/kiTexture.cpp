#include <stb_image.h>

#include <SDL2/SDL.h>
#include <cstdio>
#include <format>
#include <string>

#include "PNGLib.h"
#include "kiError.h"
#include "kiTexture.h"
#include "types.h"

// TODO: Maybe use magic number instead of extension to determine filetype
kiTexture*
kiTexture::LoadFromFile(std::string const& path)
{
// #if !defined(KIR_USE_STB_IMAGE)
#if 0
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
#else
  int width, height;
  int numChannels;
  byte_t* imageData =
    stbi_load(path.c_str(), &width, &height, &numChannels, STBI_rgb);
  if (!imageData) {
    kiFatal(std::format("Failed to load image: {}", path));
    return nullptr; // unreachable; just to make the linter happy
  }

  auto* tex = new kiTexture(width, height);
  tex->numChannels = numChannels;
  tex->data = new u32[width * height];
  for (int i = 0; i < width * height; ++i) {
    tex->data[i] = 0xFF000000 | (imageData[i * 3] << 16) |
                   (imageData[i * 3 + 1] << 8) | imageData[i * 3 + 2];
  }
  stbi_image_free(imageData);
  return tex;
#endif
}
