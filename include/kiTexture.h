#ifndef __KITEXTURE_H__
#define __KITEXTURE_H__

#include <string>

#include "kiColor.h"
#include "macros.h"
#include "types.h"

// TODO: Write a PNG loader for starters
// TODO: Develop a simple custom texture format and tools to convert from
// popular formats

class kiTexture
{
public:
  enum class PixelFormat
  {
    None,
    ARGB,
    RGBA,
    RGB
  };

public:
  kiTexture(int width, int height, int numChannels = 4);

  static kiTexture* LoadFromFile(std::string const& path);

  FE_NODISCARD kiColor PixelAt(int x, int y) const;

  FE_NODISCARD int Width() const;
  FE_NODISCARD int Height() const;

  void SetColorKey(kiColor const& colorKey);
  FE_NODISCARD kiColor ColorKey() const;
  bool UsesColorKey() const;

  void SetPixelFormat(PixelFormat format);
  FE_NODISCARD PixelFormat Format() const;

private:
  static PixelFormat const DefaultPixelFormat = PixelFormat::ARGB;

  u32* _data = nullptr;
  int _width, _height;
  int _numChannels;
  PixelFormat _pixelFormat = PixelFormat::None;
  kiColor _colorKey;
  bool _usesColorKey = false;
};

#endif // __KITEXTURE_H__
