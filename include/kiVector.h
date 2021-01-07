#ifndef __KIVECTOR_H__
#define __KIVECTOR_H__


struct kiVector2i
{
  int x, y;

  kiVector2i() :
    x(0), y(0) {}

  kiVector2i(int x, int y) :
    x(x), y(y) {}
};


#endif // __KIVECTOR_H__
