//
// Created by mark on 6/10/2023.
//

#pragma once

#include "Vector2.h"
#include <fe/core/macros.h>
#include <fe/core/math/Vector2.h>

template<typename T>
struct Rect2
{
  union
  {
    struct
    {
      union
      {
        T X, x;
      };
      union
      {
        T Y, y;
      };
      union
      {
        T Width, w;
      };
      union
      {
        T Height, h;
      };
    };
  };

  bool Intersects(Rect2<T> const& otherBox);

  FE_NODISCARD fe::Math::Vector2<T> GetCenter() const;
};

template<typename T>
fe::Math::Vector2<T>
Rect2<T>::GetCenter() const
{
  return { x + w / 2, y + h / 2 };
}

template<typename T>
bool
Rect2<T>::Intersects(Rect2<T> const& otherBox)
{
  return (x < otherBox.x + otherBox.w && x + w > otherBox.x &&
          y < otherBox.y + otherBox.h && y + h > otherBox.y);
}

typedef Rect2<int> Rect2i;
typedef Rect2<float> Rect2f;
