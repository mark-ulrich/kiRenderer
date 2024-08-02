#include "kiColor.h"

u32
kiColor::PackARGB() const
{
  u32 packed = 0;
  packed |= (int)(a * 0xff) << 24;
  packed |= (int)(r * 0xff) << 16;
  packed |= (int)(g * 0xff) << 8;
  packed |= (int)(b * 0xff);
  return packed;
}

kiColor
kiColor::FromARGB(u32 packed)
{
  u8 a = (packed >> 24) & 0xff;
  u8 r = (packed >> 16) & 0xff;
  u8 g = (packed >> 8) & 0xff;
  u8 b = packed & 0xff;
  kiColor color(static_cast<float>(r) / 255.0f,
                static_cast<float>(g) / 255.0f,
                static_cast<float>(b) / 255.0f,
                static_cast<float>(a) / 255.0f);
  return color;
}

kiColor
kiColor::FromRGBA(u32 packed)
{
  u8 r = (packed >> 24) & 0xff;
  u8 g = (packed >> 16) & 0xff;
  u8 b = (packed >> 8) & 0xff;
  u8 a = packed & 0xff;
  kiColor color(static_cast<float>(r) / 255.0f,
                static_cast<float>(g) / 255.0f,
                static_cast<float>(b) / 255.0f,
                static_cast<float>(a) / 255.0f);
  return color;
}

kiColor
kiColor::FromRGB(u32 packed)
{
  u8 r = (packed >> 16) & 0xff;
  u8 g = (packed >> 8) & 0xff;
  u8 b = packed & 0xff;
  kiColor color(static_cast<float>(r) / 255.0f,
                static_cast<float>(g) / 255.0f,
                static_cast<float>(b) / 255.0f);
  return color;
}
