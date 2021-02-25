#ifndef PWR_H
#define PWR_H

#include "rcc.h"

struct Pwr{

    struct CR_t {
        uint32_t    LPDS:1;
        uint32_t    PDDS:1;
        uint32_t    CWUF:1;
        uint32_t    CSBF:1;
        uint32_t    PWDE:1;
        uint32_t    PLS:3;
        uint32_t    DBP:1;
        uint32_t    FPDS:1;
        uint32_t    LPUDS:1;
        uint32_t    MRUDS:1;
        uint32_t    RESERVED1:1;
        uint32_t    ADCDC1:1;
        uint32_t    VOS:2;
        uint32_t    ODEN:1;
        uint32_t    ODSWEN:1;
        uint32_t    UDEN:2;
    };

    struct CSR_t {
        uint32_t    WUF:1;
        uint32_t    SBF:1;
        uint32_t    PVDO:1;
        uint32_t    BRR:1;
        uint32_t    RESERVED1:4;
        uint32_t    EWUP:1;
        uint32_t    BRE:1;
        uint32_t    RESERVED2:4;
        uint32_t    VOSRDY:1;
        uint32_t    RESERVED3:1;
        uint32_t    ODRDY:1;
        uint32_t    ODSWRDY:1;
        uint32_t    UDRDY:2;
    };

    struct Regs {
        CR_t    CR;
        CSR_t   CSR;
    };


    constexpr static uint32_t BASE = 0x40007000;
    constexpr static uint32_t backupSramBase = 0x40024000U;
    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    INLINE static volatile Regs* rg()
    {
        return reinterpret_cast<volatile Regs * volatile>(BASE);
    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Включение тактирования
    ///
    INLINE static void clockEnable(const bool en)
    {
        Rcc::clockPwr(en);
    }

    INLINE static bool backupAccessEnable(bool en)
    {

        Rcc::clockBkpsram(en);
        rg()->CR.DBP = en;
        rg()->CSR.BRE = en;

        if (en) {
            uint32_t counter = 0xffff;
            while (--counter) {
                if (rg()->CSR.BRR) {

                    return true;
                }
            }
            return false;
        }
        return true;
    }

};



#endif // PWR_H
