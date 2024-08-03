#include <stb_image.h>

#include <SDL2/SDL.h>
#include <cstdio>
#include <format>
#include <string>

#include "PNGLib.h"
#include "kiError.h"
#include "kiTexture.h"
#include "types.h"

// ----------------------------------------------------------------------------
//                        Static Methods
// ----------------------------------------------------------------------------
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
  int desiredChannels = STBI_rgb;
  //  int desiredChannels = STBI_rgb_alpha;
  byte_t* imageData =
    stbi_load(path.c_str(), &width, &height, &numChannels, desiredChannels);
  if (!imageData) {
    kiFatal(std::format("Failed to load image: {}", path));
    return nullptr; // unreachable; just to make the linter happy
  }
  if (numChannels != desiredChannels) {
    kiWarning(std::format(
      "Desired {} channels, but got {}", desiredChannels, numChannels));
  }

  kiDebug(std::format(
    "Loaded image: {} ({}x{}); {} channels", path, width, height, numChannels));

  auto* tex = new kiTexture(width, height);
  tex->_numChannels = numChannels;
  tex->_data = new u32[width * height];
  for (int i = 0; i < width * height; ++i) {
    tex->_data[i] = 0xFF000000 | (imageData[i * 3] << 16) |
                    (imageData[i * 3 + 1] << 8) | imageData[i * 3 + 2];
  }
  stbi_image_free(imageData);
  return tex;
#endif
}

// ----------------------------------------------------------------------------
//                        Constructors/Destructor
// ----------------------------------------------------------------------------
kiTexture::kiTexture(int width, int height, int numChannels)
  : _width(width)
  , _height(height)
  , _numChannels(numChannels)
  , _pixelFormat(PixelFormat::ARGB)
  , _colorKey(0, 0, 0)
{
  _data = new u32[width * height];
}

// ----------------------------------------------------------------------------
//                        Public Methods
// ----------------------------------------------------------------------------
kiColor
kiTexture::PixelAt(int x, int y) const
{
  int index = y * _width + x;
  u32 pixel = _data[index];
  switch (_pixelFormat) {
    case PixelFormat::ARGB:
      return kiColor::FromARGB(pixel);
    case PixelFormat::RGBA:
      return kiColor::FromRGBA(pixel);
    case PixelFormat::RGB:
      return kiColor::FromRGB(pixel);
    default:
      kiFatal("Invalid pixel format");
      return kiColor(); // unreachable; just to make the compiler happy
  }
}

void
kiTexture::SetPixelFormat(kiTexture::PixelFormat format)
{
  this->_pixelFormat = format;
}

int
kiTexture::Width() const
{
  return _width;
}

int
kiTexture::Height() const
{
  return _height;
}

kiTexture::PixelFormat
kiTexture::Format() const
{
  return _pixelFormat;
}

void
kiTexture::SetColorKey(const kiColor& colorKey)
{
  _colorKey = colorKey;
  _usesColorKey = true;
}

kiColor
kiTexture::ColorKey() const
{
  return _colorKey;
}

bool
kiTexture::UsesColorKey() const
{
  return _usesColorKey;
}
