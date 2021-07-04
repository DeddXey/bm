#ifndef SYSTICK_H
#define SYSTICK_H

#include "rcc.h"
#include <stdint.h>
#include "nvic.h"


struct SysTickTimer {

    struct CTRL_t {
        uint32_t    ENABLE:1;
        uint32_t    TICKINT:1;
        uint32_t    CLKSOURCE:1;
        uint32_t    RESERVED:13;
        uint32_t    COUNTFLAG:1;
    };

    struct LOAD_t {
        uint32_t    RELOAD:24;
    };

    struct VAL_t {
        uint32_t    RELOAD:24;
    };

    struct CALIB_t {
        uint32_t    TENMS:24;
        uint32_t    RESERVED:6;
        uint32_t    SKEW:1;
        uint32_t    NOREF:1;
    };

    struct Regs {
        CTRL_t      CTRL;
        LOAD_t      LOAD;
        VAL_t       VAL;
        CALIB_t     CALIB;
    };

    constexpr static uint32_t BASE = 0xE000E010;

#ifdef DEBUG
    volatile Regs* const debug = reinterpret_cast<Regs*>(BASE);
#endif
//    constexpr static volatile Regs* const rcc = /*reinterpret_cast<Regs*>*/(Regs*)(BASE);

    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    static volatile Regs* rg()
    {
        return reinterpret_cast<Regs * >(BASE);
    }


    static void set(uint32_t ticks)
    {
        rg()->LOAD.RELOAD = ticks - 1;
        Nvic::setPriority(Nvic::itSysTick, (1 << 4) - 1);
        rg()->VAL.RELOAD = 0;
        rg()->CTRL.CLKSOURCE = 1;
        rg()->CTRL.TICKINT = 1;
        rg()->CTRL.ENABLE = 1;
    }

};


#endif // SYSTICK_H
