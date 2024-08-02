#ifndef __KITEXTURE_H__
#define __KITEXTURE_H__

#include <string>

#include "kiTypes.h"

// TODO: Write a PNG loader for starters
// TODO: Develop a simple custom texture format and tools to convert from
// popular formats

class kiTexture
{
  // TODO: Making this/these friends seems a little... hacky
  friend kiTexture* LoadTexturePNG(std::string const& path);

  u32* data = nullptr;
  int width, height;
  int numChannels;

public:
  kiTexture(int width, int height, int numChannels = 4)
    : width(width)
    , height(height)
    , numChannels(numChannels)
  {
    data = new u32[width * height * numChannels];
  }

  static kiTexture* LoadFromFile(std::string const& path);
  FE_NODISCARD kiColor GetPixel(int x, int y) const;

  FE_NODISCARD int GetWidth() const { return width; }
  FE_NODISCARD int GetHeight() const { return height; }
};

#endif // __KITEXTURE_H__
