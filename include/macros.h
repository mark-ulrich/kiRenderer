//
// Created by mark on 6/4/2023.
//

#pragma once

#define FE_UNUSED_PARM(x) (void)(x)

#if defined(_MSC_VER)
#define FE_FORCEINLINE __forceinline
#elif defined(__GNUC__)
#define FE_FORCEINLINE __attribute__((always_inline)) inline
#else
#define FE_FORCEINLINE inline
#endif

#undef MIN
template<typename T1, typename T2>
constexpr auto
MIN(const T1 a, const T2 b) -> decltype(a < b ? a : b)
{
  return a < b ? a : b;
}

#undef MAX
template<typename T1, typename T2>
constexpr auto
MAX(const T1 a, const T2 b) -> decltype(a > b ? a : b)
{
  return a > b ? a : b;
}

#define FE_NODISCARD [[nodiscard]]