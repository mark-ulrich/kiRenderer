//
// Created by mark on 6/1/2023.
//

#include "kiTimer.h"

Timer::Timer()
{
  m_perfFreq = SDL_GetPerformanceFrequency();
  Reset();
}

Uint64
Timer::GetSystemTicks()
{
  return SDL_GetPerformanceCounter();
}

void
Timer::Reset()
{
  m_startTicks = GetSystemTicks();
}

float
Timer::GetElapsed() const
{
  auto currentTicks = GetSystemTicks();
  auto elapsedTicks = currentTicks - m_startTicks;
  float seconds = elapsedTicks / static_cast<float>(m_perfFreq);
  return seconds;
}

float
Timer::GetElapsedAndReset()
{
  auto elapsed = GetElapsed();
  Reset();
  return elapsed;
}

u64
Timer::GetElapsedMillis() const
{
  auto currentTicks = GetSystemTicks();
  auto elapsedTicks = currentTicks - m_startTicks;
  u64 millis = (u64)(elapsedTicks / static_cast<float>(m_perfFreq) * 1000);
  return millis;
}
