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
    stbi_load(path.c_str(), &width, &height, &numChannels, STBI_rgb_alpha);
  if (!imageData) {
    kiFatal(std::format("Failed to load image: {}", path));
    return nullptr; // unreachable; just to make the linter happy
  }

  kiDebug(std::format(
    "Loaded image: {} ({}x{}x{})", path, width, height, numChannels));
  int y = height / 2;
  for (int x = width / 2; x < width / 2 + 10; ++x) {
    int index = y * width + x;
    u32 pixel = (imageData[index * 4 + 0] << 24) |
                (imageData[index * 4 + 1] << 16) |
                (imageData[index * 4 + 2] << 8) | imageData[index * 4 + 3];
    kiDebug(std::format("Pixel at ({}, {}): {:#x}", x, y, pixel));
  }

  auto* tex = new kiTexture(width, height, numChannels);
  const int numPixels = width * height;
  tex->data = new u32[numPixels];
  for (int i = 0; i < numPixels; ++i) {
    u32 pixel = *(u32*)(imageData + i);
    tex->data[i] = pixel;
  }
  stbi_image_free(imageData);
  return tex;
#endif
}

kiColor
kiTexture::GetPixel(int x, int y) const
{
  int index = y * width + x;
  u32 pixel = data[index];
  return kiColor::FromARGB(pixel);
}

int
kiTexture::Width() const
{
  return width;
}

int
kiTexture::Height() const
{
  return height;
}

kiColor
kiTexture::ColorKey() const
{
  return colorKey;
}

bool
kiTexture::UsesColorKey() const
{
  return useColorKey;
}

void
kiTexture::SetColorKey(kiColor const& color)
{
  useColorKey = true;
  colorKey = color;
}