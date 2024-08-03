#ifndef __KITEXTURE_H__
#define __KITEXTURE_H__

#include <string>

#include "kiColor.h"
#include "macros.h"
#include "types.h"

// TODO: Write a PNG loader for starters
// TODO: Develop a simple custom texture format and tools to convert from
//  popular formats

class kiTexture
{
  // TODO: Making this/these friends seems a little... hacky
  friend kiTexture* LoadTexturePNG(std::string const& path);

  u32* data = nullptr;
  int width, height;
  int numChannels;
  bool useColorKey = false;
  kiColor colorKey; // Used for transparency

public:
  kiTexture(int width, int height, int numChannels = 4)
    : width(width)
    , height(height)
    , numChannels(numChannels)
  {
  }

  static kiTexture* LoadFromFile(std::string const& path);
  FE_NODISCARD kiColor GetPixel(int x, int y) const;

  FE_NODISCARD int Width() const;
  FE_NODISCARD int Height() const;
  FE_NODISCARD kiColor ColorKey() const;
  FE_NODISCARD bool UsesColorKey() const;
  void SetColorKey(kiColor const& color);
};

#endif // __KITEXTURE_H__
