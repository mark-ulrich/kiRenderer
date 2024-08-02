//
// Created by mark on 6/4/2023.
//

#pragma once

#include <cstdint>
#include <string>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef float f32;
typedef double f64;

// typedef std::u8string string_t;
typedef std::string string_t;

/* Picked this up from Godot */
#if defined(REAL_T_DOUBLE_PRECISION)
typedef f64 real_t;
#else
typedef f32 real_t;
#endif

#define INTERNAL static