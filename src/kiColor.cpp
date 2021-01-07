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
