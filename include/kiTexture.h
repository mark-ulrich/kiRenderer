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

public:
  kiTexture(int width, int height)
    : width(width)
    , height(height)
  {}

  static kiTexture* LoadFromFile(std::string const& path);
};

#endif // __KITEXTURE_H__
