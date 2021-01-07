#ifndef  __KICOLOR_H__
#define  __KICOLOR_H__

#include "kiTypes.h"


struct kiColor
{
  float r, g, b, a;

  kiColor() :
    r(0), g(0), b(0), a(0) {}

  kiColor(float r, float g, float b, float a = 0.0f) :
    r(r), g(g), b(b), a(a) {}

  u32 PackARGB() const;
};


#endif //  __KICOLOR_H__
