#ifndef __KICOLOR_H__
#define __KICOLOR_H__

#include "macros.h"
#include "types.h"

struct kiColor
{
  float r, g, b, a;

  kiColor()
    : r(0.0f)
    , g(0.0f)
    , b(0.0f)
    , a(0.0f)
  {
  }

  kiColor(float r, float g, float b, float a = 0.0f)
    : r(r)
    , g(g)
    , b(b)
    , a(a)
  {
  }

  FE_NODISCARD u32 PackARGB() const;

  static kiColor FromARGB(u32 packed);
  static kiColor FromRGBA(u32 packed);
  static kiColor FromRGB(u32 packed);
};

#endif //  __KICOLOR_H__
