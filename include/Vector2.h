//
// Created by mark on 6/4/2023.
//

#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#include "core/types.h"
#include "fe/core/macros.h"
#include "kiMath.h"
#include <string>
#include <valarray>

namespace fe::Math {

template<typename T>
struct Vector2
{
  static_assert(std::is_arithmetic_v<T>, "Vector2 must be of arithmetic type");

  static Vector2<T> const Zero;
  static Vector2<T> const Right;
  static Vector2<T> const Left;
  static Vector2<T> const Up;
  static Vector2<T> const Down;

  union
  {
    struct
    {
      union
      {
        T X, x, Width, W, w;
      };
      union
      {
        T Y, y, Height, H, h;
      };
    };

    union
    {
      T XY[2]{};
      T WH[2];
    };
  };

  /* ------------------------------------------------------------------------
   *                              CONSTRUCTORS
   * ------------------------------------------------------------------------ */

  FE_FORCEINLINE Vector2<T>() = default;

  FE_FORCEINLINE Vector2<T>(T const& x, T const& y)
    : x(x)
    , y(y)
  {
  }

  FE_FORCEINLINE Vector2<T>(T const& a)
    : Vector2<T>(a, a)
  {
  }

  /**
   * Constructor to convert a Vector2 of type U to type T
   * @tparam U Type of other Vector2
   * @param a Other Vector2 (of type U)
   */
  template<typename U>
  FE_FORCEINLINE Vector2<T>(Vector2<U> const& a)
    : Vector2<T>(static_cast<T>(a.x), static_cast<T>(a.y))
  {
  }

  FE_FORCEINLINE void Normalize();

  FE_FORCEINLINE Vector2<T> Normalized() const;

  FE_FORCEINLINE bool IsNormalized() const;

  FE_FORCEINLINE real_t Length() const;

  /**
   * @brief Return the angle in degrees
   * @return Angle in degrees
   */
  FE_FORCEINLINE real_t Angle() const;

  FE_FORCEINLINE real_t Aspect() const;

  FE_FORCEINLINE real_t DistanceTo(Vector2<T> const& v2) const;

  FE_FORCEINLINE real_t AngleTo(Vector2<T> const& v2) const;

  /**
   * @brief Rotate the vector in place by angle degrees
   * @param angle Angle in degrees
   */
  FE_FORCEINLINE void Rotate(real_t angle);

  /**
   * @brief Rotate the vector by angle degrees
   * @param angle Angle in degrees
   * @return A new Vector2<T> rotated by angle degrees
   */
  FE_FORCEINLINE Vector2<T> Rotated(real_t angle);

  FE_FORCEINLINE void Reflect(Vector2<T> const& normal);

  FE_FORCEINLINE Vector2<T> Reflected(Vector2<T> const& normal) const;

  FE_FORCEINLINE Vector2<T> Project(Vector2<T> const& v2) const;

  FE_FORCEINLINE Vector2<T> MoveToward(Vector2<T> const& v2,
                                       real_t delta) const;

  FE_FORCEINLINE Vector2<T> Lerp(Vector2<T> const& v2, real_t weight) const;

  // TODO: Add more interpolation methods
  //  Vector2<T> Slerp(Vector2<T> const& v, real_t weight) const;

  FE_FORCEINLINE T Dot(Vector2<T> const& other) const;

  FE_FORCEINLINE T Cross(Vector2<T> const& other) const;

  FE_FORCEINLINE static real_t DistanceBetween(Vector2<T> const& v1,
                                               Vector2<T> const& v2);

  FE_FORCEINLINE static real_t AngleBetween(Vector2<T> const& v1,
                                            Vector2<T> const& v2);

  FE_FORCEINLINE static T DotProduct(Vector2<T> const& v1,
                                     Vector2<T> const& v2);

  FE_FORCEINLINE static T CrossProduct(Vector2<T> const& v1,
                                       Vector2<T> const& v2);

  FE_FORCEINLINE static Vector2<T> FromAngle(real_t angle);

  /* ------------------------------------------------------------------------
   *                              OPERATORS
   * ------------------------------------------------------------------------ */

  //
  // Vector arithmetic
  // -----------------

  FE_FORCEINLINE Vector2<T> operator+(Vector2<T> const& v2) const;

  FE_FORCEINLINE void operator+=(Vector2<T> const& v2);

  FE_FORCEINLINE Vector2<T> operator-(Vector2<T> const& v2) const;

  FE_FORCEINLINE void operator-=(Vector2<T> const& v2);

  FE_FORCEINLINE Vector2<T> operator*(Vector2<T> const& v2) const;

  FE_FORCEINLINE Vector2<T> operator*(real_t scalar) const;

  FE_FORCEINLINE void operator*=(real_t scalar);

  FE_FORCEINLINE void operator*=(Vector2<T> const& v2);

  FE_FORCEINLINE Vector2<T> operator/(Vector2<T> const& v2) const;

  FE_FORCEINLINE Vector2<T> operator/(real_t scalar) const;

  FE_FORCEINLINE void operator/=(real_t scalar);

  FE_FORCEINLINE void operator/=(Vector2<T> const& v2);

  FE_FORCEINLINE Vector2<T> operator-() const;

  //
  // Vector comparison
  // -----------------

  // Comparator operators

  FE_FORCEINLINE bool operator==(Vector2<T> const& v2) const;
  FE_FORCEINLINE bool operator!=(Vector2<T> const& v2) const;
  FE_FORCEINLINE bool operator<(Vector2<T> const& v2) const;
  FE_FORCEINLINE bool operator<=(Vector2<T> const& v2) const;
  FE_FORCEINLINE bool operator>(Vector2<T> const& v2) const;
  FE_FORCEINLINE bool operator>=(Vector2<T> const& v2) const;

  //
  // Misc operators
  // --------------

  FE_FORCEINLINE operator std::string() const;
};

template<typename T>
void
Vector2<T>::Rotate(real_t angle)
{
  real_t radians = Math::DegToRad(angle);
  real_t cos = Math::Cos(radians);
  real_t sin = Math::Sin(radians);
  x *= cos - y * sin;
  y *= sin + y * cos;
}

template<typename T>
Vector2<T>
Vector2<T>::Rotated(real_t angle)
{
  Vector2<T> v{ *this };
  real_t radians = Math::DegToRad(angle);
  real_t cos = Math::Cos(radians);
  real_t sin = Math::Sin(radians);
  v.x *= cos - v.y * sin;
  v.y *= sin + v.y * cos;
  return v;
}

// TODO: Sort these

template<typename T>
FE_FORCEINLINE real_t
Vector2<T>::Aspect() const
{
  return x / y;
}

template<typename T>
FE_FORCEINLINE Vector2<T>
Vector2<T>::MoveToward(Vector2<T> const& v2, real_t delta) const
{
  Vector2<T> v = *this;
  Vector2<T> vd = v2 - v;
  real_t deltaLength = vd.Length();
  return (deltaLength <= delta || deltaLength < Math::Epsilon)
           ? v2
           : v + (vd / deltaLength) * delta;
}

template<typename T>
FE_FORCEINLINE Vector2<T>
Vector2<T>::Project(Vector2<T> const& v2) const
{
  return v2 * (Dot(v2) / (v2.Length() * v2.Length()));
}

template<typename T>
FE_FORCEINLINE Vector2<T>
Vector2<T>::FromAngle(real_t angle)
{
  return Vector2<T>(Math::Cos(angle), Math::Sin(angle));
}

template<typename T>
FE_FORCEINLINE Vector2<T>
Vector2<T>::Lerp(Vector2<T> const& v2, real_t weight) const
{
  Vector2<T> res = *this;
  res.x = Math::Lerp(res.x, v2.x, weight);
  res.y = Math::Lerp(res.y, v2.y, weight);
  return res;
}

template<typename T>
FE_FORCEINLINE real_t
Vector2<T>::Angle() const
{
  return Math::RadToDeg(Math::Atan2(y, x));
}

template<typename T>
FE_FORCEINLINE Vector2<T>
Vector2<T>::operator+(Vector2<T> const& v2) const
{
  return Vector2<T>(x + v2.x, y + v2.y);
}

template<typename T>
FE_FORCEINLINE void
Vector2<T>::operator+=(Vector2<T> const& v2)
{
  *this = *this + v2;
}

template<typename T>
FE_FORCEINLINE Vector2<T>
Vector2<T>::operator-(Vector2<T> const& v2) const
{
  return Vector2<T>(x - v2.x, y - v2.y);
}

template<typename T>
FE_FORCEINLINE void
Vector2<T>::operator-=(Vector2<T> const& v2)
{
  *this = *this - v2;
}

template<typename T>
FE_FORCEINLINE Vector2<T>
Vector2<T>::operator*(Vector2<T> const& v2) const
{
  return Vector2<T>(x * v2.x, y * v2.y);
}

template<typename T>
FE_FORCEINLINE Vector2<T>
Vector2<T>::operator*(real_t scalar) const
{
  return Vector2<T>(x * scalar, y * scalar);
}

template<typename T>
FE_FORCEINLINE void
Vector2<T>::operator*=(real_t scalar)
{
  *this = *this * scalar;
}

template<typename T>
FE_FORCEINLINE void
Vector2<T>::operator*=(Vector2<T> const& v2)
{
  *this = *this * v2;
}

template<typename T>
FE_FORCEINLINE Vector2<T>
Vector2<T>::operator/(Vector2<T> const& v2) const
{
  return Vector2<T>(x / v2.x, y / v2.y);
}

template<typename T>
FE_FORCEINLINE Vector2<T>
Vector2<T>::operator/(real_t scalar) const
{
  return Vector2<T>(x / scalar, y / scalar);
}

template<typename T>
FE_FORCEINLINE void
Vector2<T>::operator/=(real_t scalar)
{
  *this = *this / scalar;
}

template<typename T>
FE_FORCEINLINE void
Vector2<T>::operator/=(Vector2<T> const& v2)
{
  *this = *this / v2;
}

template<typename T>
FE_FORCEINLINE Vector2<T>
Vector2<T>::operator-() const
{
  return Vector2<T>(-x, -y);
}

template<typename T>
Vector2<T>::operator std::string() const
{
  return std::string("(" + std::to_string(x) + ", " + std::to_string(y) + ")");
}

template<typename T>
FE_FORCEINLINE void
Vector2<T>::Reflect(Vector2<T> const& normal)
{
  *this = Reflected(normal);
}

template<typename T>
FE_FORCEINLINE Vector2<T>
Vector2<T>::Reflected(Vector2<T> const& normal) const
{
  return *this - (2 * DotProduct(*this, normal) * normal);
}

template<typename T>
FE_FORCEINLINE real_t
Vector2<T>::AngleBetween(Vector2<T> const& v1, Vector2<T> const& v2)
{
  // TODO: Test this
  return Math::Atan2(v1.Cross(v2), v1.Dot(v2));
}

template<typename T>
FE_FORCEINLINE real_t
Vector2<T>::AngleTo(Vector2<T> const& v2) const
{
  return Math::Atan2(Cross(v2), Dot(v2));
}

/* --------------------------------------------------------------------------
 *                         TEMPLATE METHODS
 * -------------------------------------------------------------------------- */

template<typename T>
FE_FORCEINLINE void
Vector2<T>::Normalize()
{
  *this /= Length();
}

template<typename T>
FE_FORCEINLINE Vector2<T>
Vector2<T>::Normalized() const
{
  return *this / Length();
}

template<typename T>
FE_FORCEINLINE bool
Vector2<T>::IsNormalized() const
{
  real_t length = Length();

  if (Math::Abs(length) == 1.0f) {
    return true;
  }

  if (Math::Abs(length) - 1.0f < Math::Epsilon) {
    return true;
  }

  return false;
}

template<typename T>
FE_FORCEINLINE real_t
Vector2<T>::Length() const
{
  return Math::Sqrt(x * x + y * y);
}

template<typename T>
FE_FORCEINLINE real_t
Vector2<T>::DistanceTo(Vector2<T> const& v2) const
{
  return Math::Sqrt((v2.x - x) * (v2.x - x) + (v2.y - y) * (v2.y - y));
}

template<typename T>
FE_FORCEINLINE T
Vector2<T>::Dot(Vector2<T> const& other) const
{
  return x * other.x + y * other.y;
}

template<typename T>
FE_FORCEINLINE T
Vector2<T>::Cross(Vector2<T> const& other) const
{
  return x * other.y - y * other.x;
}

/* --------------------------------------------------------------------------
 *                        STATIC TEMPLATE METHODS
 * -------------------------------------------------------------------------- */

template<typename T>
FE_FORCEINLINE real_t
Vector2<T>::DistanceBetween(Vector2<T> const& v1, Vector2<T> const& v2)
{
  return Math::Sqrt((v2.x - v1.x) * (v2.x - v1.x) +
                    (v2.y - v1.y) * (v2.y - v1.y));
}

template<typename T>
FE_FORCEINLINE T
Vector2<T>::DotProduct(Vector2<T> const& v1, Vector2<T> const& v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}

template<typename T>
FE_FORCEINLINE T
Vector2<T>::CrossProduct(Vector2<T> const& v1, Vector2<T> const& v2)
{
  return v1.x * v2.y - v1.y * v2.x;
}

// Comparators
template<typename T>
FE_FORCEINLINE bool
Vector2<T>::operator==(Vector2<T> const& v2) const
{
  return (x == v2.x) && (y == v2.y);
}

template<typename T>
FE_FORCEINLINE bool
Vector2<T>::operator!=(Vector2<T> const& v2) const
{
  return (x != v2.x) || (y != v2.y);
}

template<typename T>
FE_FORCEINLINE bool
Vector2<T>::operator<(Vector2<T> const& v2) const
{
  return (x < v2.x) && (y < v2.y);
}

template<typename T>
FE_FORCEINLINE bool
Vector2<T>::operator<=(Vector2<T> const& v2) const
{
  return (x <= v2.x) && (y <= v2.y);
}

template<typename T>
FE_FORCEINLINE bool
Vector2<T>::operator>(Vector2<T> const& v2) const
{
  return (x > v2.x) && (y > v2.y);
}

template<typename T>
bool
Vector2<T>::operator>=(Vector2<T> const& v2) const
{
  return x >= v2.x && y >= v2.y;
}

/* --------------------------------------------------------------------------
 *                        NON-MEMBER OPERATORS
 * -------------------------------------------------------------------------- */

// ======================================
//            Arithmetic
// ======================================
template<typename T>
FE_FORCEINLINE Vector2<T>
operator+(Vector2<T> const& v1, Vector2<T> const& v2)
{
  return v1 + v2;
}

template<typename T>
FE_FORCEINLINE Vector2<T>
operator-(Vector2<T> const& v1, Vector2<T> const& v2)
{
  return v1 - v2;
}

template<typename T>
FE_FORCEINLINE Vector2<T>
operator*(Vector2<T> const& v1, Vector2<T> const& v2)
{
  return v1 * v2;
}

template<typename T>
FE_FORCEINLINE Vector2<T>
operator*(real_t scalar, Vector2<T> const& v2)
{
  return v2 * scalar;
}

template<typename T>
FE_FORCEINLINE Vector2<T>
operator*(Vector2<T> const& v2, real_t scalar)
{
  return v2 * scalar;
}

template<typename T>
FE_FORCEINLINE Vector2<T>
operator/(Vector2<T> const& v1, Vector2<T> const& v2)
{
  return v1 / v2;
}

template<typename T>
FE_FORCEINLINE Vector2<T>
operator/(Vector2<T> const& v2, real_t scalar)
{
  return v2 / scalar;
}

// ======================================
//        Comparators
// ======================================

template<typename T>
FE_FORCEINLINE bool
operator==(Vector2<T> const& v1, Vector2<T> const& v2)
{
  return (v1.x == v2.x) && (v1.y == v2.y);
}

template<typename T>
FE_FORCEINLINE bool
operator!=(Vector2<T> const& v1, Vector2<T> const& v2)
{
  return (v1.x != v2.x) || (v1.y != v2.y);
}

template<typename T>
FE_FORCEINLINE bool
operator<(Vector2<T> const& v1, Vector2<T> const& v2)
{
  return (v1.x < v2.x) && (v1.y < v2.y);
}

template<typename T>
FE_FORCEINLINE bool
operator<=(Vector2<T> const& v1, Vector2<T> const& v2)
{
  return (v1.x <= v2.x) && (v1.y <= v2.y);
}

template<typename T>
FE_FORCEINLINE bool
operator>(Vector2<T> const& v1, Vector2<T> const& v2)
{
  return (v1.x > v2.x) && (v1.y > v2.y);
}

template<typename T>
FE_FORCEINLINE bool
operator>=(Vector2<T> const& v1, Vector2<T> const& v2)
{
  return (v1.x >= v2.x) && (v1.y >= v2.y);
}

/* --------------------------------------------------------------------------
 *                        STATIC CONSTANTS
 * -------------------------------------------------------------------------- */

template<typename T>
Vector2<T> const Vector2<T>::Zero = { 0, 0 };

template<typename T>
Vector2<T> const Vector2<T>::Right = { 1, 0 };

template<typename T>
Vector2<T> const Vector2<T>::Left = { -1, 0 };

template<typename T>
Vector2<T> const Vector2<T>::Up = { 0, 1 };

template<typename T>
Vector2<T> const Vector2<T>::Down = { 0, -1 };

} // namespace fe::Math

/* --------------------------------------------------------------------------
 *                         TYPE DEFINITIONS
 * -------------------------------------------------------------------------- */

// TODO: Should we even worry about int vectors? These are useful for dealing
//  with finite screen coordinates, but we could always just round or floor
//  client-side when necessary...

typedef fe::Math::Vector2<int> Vector2i;
typedef fe::Math::Vector2<real_t> Vector2f;

typedef Vector2i Vec2i;
typedef Vector2f Vec2f;

typedef Vector2i Point2i;
typedef Vector2f Point2f;

typedef Vector2i Size2i;
typedef Vector2f Size2f;

#pragma clang diagnostic pop