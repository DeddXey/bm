#ifndef SYSTICK_H
#define SYSTICK_H

#include "utility.h"
#include <cstdint>

struct SysTick
{
  struct CTRL
  {
    constexpr static uint8_t ENABLE[]{ 0, 1 };
    constexpr static uint8_t TICKINT[]{ 1, 1 };
    constexpr static uint8_t CLKSOURCE[]{ 2, 1 };
    constexpr static uint8_t COUNTFLAG[]{ 16, 1 };
  };

  struct CALIB
  {
    constexpr static uint8_t TENMS[]{ 0, 24 };
    constexpr static uint8_t SKEW[]{ 30, 1 };
    constexpr static uint8_t NOREF[]{ 31, 1 };
  };

  struct Regs
  {
    uint32_t CTRL;
    uint32_t LOAD;
    uint32_t VAL;
    uint32_t CALIB;
  };

  static volatile Regs *rg()
  {
    return reinterpret_cast<volatile Regs *>(0xE000E010);
  }

  static void
  init_and_run(uint32_t divider, bool interrupt = false, bool ahb_div_8 = false)
  {

    rg()->LOAD = divider - 1;
    tl::setRegister(rg()->CTRL,
                    CTRL::CLKSOURCE,
                    !ahb_div_8,
                    CTRL::TICKINT,
                    interrupt,
                    CTRL::ENABLE,
                    1U);
  }

  static uint32_t get_ticks()
  {
    return rg()->VAL;
  }
};

#endif // SYSTICK_H
