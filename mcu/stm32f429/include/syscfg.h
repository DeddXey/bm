#ifndef SYSCFG_H
#define SYSCFG_H

#include "utility.h"
#include "rcc.h"
#include <cstdint>


struct Syscfg {

    constexpr static uint32_t BASE = 0x40013800;

    constexpr static uint32_t base = 0x40013800;

    struct Regs {
         uint32_t MEMRM; 	//< 0x0 memory remap register
         uint32_t PMC; 	//< 0x4 peripheral mode configuration register
         uint32_t EXTICR[4]; 	//< 0x8 external interrupt configuration register 1
         uint32_t reserved0[2]; 	//< reserved
         uint32_t CMPCR; 	//< 0x20 Compensation cell control register
    };

    struct MEMRM {
        constexpr static uint8_t MEM_MODE[]{ 0, 3 }; 	//< Memory mapping selection
        constexpr static uint8_t FB_MODE[]{ 8, 1 }; 	//< Flash bank mode selection
        constexpr static uint8_t SWP_FMC[]{ 10, 2 }; 	//< FMC memory mapping swap
    };

    struct PMC {
        constexpr static uint8_t MII_RMII_SEL[]{ 23, 1 }; 	//< Ethernet PHY interface selection
        constexpr static uint8_t ADC1DC2[]{ 16, 1 }; 	//< ADC1DC2
        constexpr static uint8_t ADC2DC2[]{ 17, 1 }; 	//< ADC2DC2
        constexpr static uint8_t ADC3DC2[]{ 18, 1 }; 	//< ADC3DC2
    };

    struct CMPCR {
        constexpr static uint8_t READY[]{ 8, 1 }; 	//< READY
        constexpr static uint8_t CMP_PD[]{ 0, 1 }; 	//< Compensation cell power-down
    };

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
//        return reinterpret_cast<Regs * volatile>(BASE);
        return reinterpret_cast<Regs *>(BASE);
    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Включение тактирования
    ///
    static void clockEnable(const bool en)
    {
        Rcc::clockSyscfg(en);
    }

    static void assignExtiLine(const uint8_t port, const uint8_t pin)
    {
        uint8_t value = port - 'A';
        uint8_t index = (pin >> 2) & 0x3;
        uint8_t pos = (pin & 0x3) * 4;

        Syscfg::rg()->EXTICR[index] &= ~ (0xf << pos);
        Syscfg::rg()->EXTICR[index] |= (value << pos);

    }

};


#endif // SYSCFG_H
