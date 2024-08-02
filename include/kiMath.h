//
// Created by mark on 6/4/2023.
//

#pragma once

#include <fe/core/macros.h>

#include "macros.h"
#include "types.h"

namespace fe::Math {

constexpr real_t PI = 3.14159265358979323846f;
constexpr real_t Epsilon = 0.0001f;

FE_FORCEINLINE real_t
Sqrt(real_t value)
{
  return SDL_sqrtf(value);
}

FE_FORCEINLINE real_t
Sin(real_t value)
{
  return SDL_sinf(value);
}

FE_FORCEINLINE real_t
Cos(real_t value)
{
  return SDL_cosf(value);
}

FE_FORCEINLINE real_t
Tan(real_t value)
{
  return SDL_tanf(value);
}

FE_FORCEINLINE real_t
Atan(real_t value)
{
  return SDL_atanf(value);
}

FE_FORCEINLINE real_t
Atan2(real_t y, real_t x)
{
  return SDL_atan2f(y, x);
}

FE_FORCEINLINE real_t
Abs(real_t value)
{
  return SDL_fabsf(value);
}

FE_FORCEINLINE real_t
Floor(real_t value)
{
  return SDL_floorf(value);
}

FE_FORCEINLINE real_t
Ceil(real_t value)
{
  return SDL_ceilf(value);
}

FE_FORCEINLINE real_t
Round(real_t value)
{
  return SDL_roundf(value);
}

template<typename T>
FE_FORCEINLINE constexpr T
Sign(const T val)
{
  return val == 0 ? 0.0f : (val > 0 ? 1.0f : -1.0f);
}

template<typename T1, typename T2, typename T3>
FE_FORCEINLINE constexpr auto
Clamp(const T1 val, const T2 min, const T3 max)
{
  return val < min ? min : (val > max ? max : val);
}

template<typename T>
FE_FORCEINLINE const T
Clamp01(const T val)
{
  // TODO: we need to make sure real_ting point math doesn't screw us here. E.g.
  //  overflows of single-byte values (e.g. color channels)
  return val < 0 ? 0 : (val > 1 ? 1 : val);
}

template<typename T>
FE_FORCEINLINE bool
InRange(T val, T min, T max)
{
  return val >= min && val <= max;
}

template<typename T>
FE_FORCEINLINE T
Lerp(real_t from, real_t to, real_t weight)
{
  return from + (to - from) * weight;
}

FE_FORCEINLINE real_t
DegToRad(real_t angle)
{
  return angle * PI / 180.0f;
}

FE_FORCEINLINE real_t
RadToDeg(real_t angle)
{
  return angle * 180.0f / PI;
}

FE_FORCEINLINE bool
ApproximatelyZero(real_t value)
{
  return value > -Epsilon && value < Epsilon;
}

}; // namespace fe::Math
