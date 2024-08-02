//
// Created by mark on 6/1/2023.
//

#pragma once

#include <SDL2/SDL.h>

#include "macros.h"
#include "types.h"
#include "cstdint"

class Timer
{
public:
  FE_NODISCARD static Uint64 GetSystemTicks();

  Timer();

  void Reset();
  float GetElapsed() const;
  float GetElapsedAndReset();
  u64 GetElapsedMillis() const;

private:
  u64 m_startTicks = 0;
  u64 m_perfFreq;
};
