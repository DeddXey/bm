#ifndef __DAC_H
#define __DAC_H

#include "utility.h"
#include <cstdint>
#include "rcc.h"

enum class DacTrigger : uint8_t{
    tim6 = 0b000,
    tim8 = 0b001,
    tim7 = 0b010,
    tim5 = 0b011,
    tim2 = 0b100,
    tim4 = 0b101,
    exti9 = 0b110,
    sw = 0b111,
};


enum class DacWaweGeneration : uint8_t {
    disabled = 0b00,
    noise = 0b01,
    triangle = 0b10
};

enum class DacMaskAmplitude : uint8_t {
    triangle1 =     0b0000,
    triangle3 =     0b0001,
    triangle7 =     0b0010,
    triangle15 =    0b0011,
    triangle31 =    0b0100,
    triangle63 =    0b0101,
    triangle127 =   0b0110,
    triangle255 =   0b0111,
    triangle511 =   0b1000,
    triangle1023 =  0b1001,
    triangle2047 =  0b1010,
    triangle4095 =  0b1011,
};

// TODO: сделать выбор регистров от канала
// TODO: сделать выбор триггера от таймера

struct Dac {
    constexpr static uint32_t base = 0x40007400;
    constexpr static uint32_t interrupt = 54;

    struct Regs {
         uint32_t CR; 	//< 0x0 control register
         uint32_t SWTRIGR; 	//< 0x4 software trigger register
         uint32_t DHR12R1; 	//< 0x8 channel1 12-bit right-aligned data holding register
         uint32_t DHR12L1; 	//< 0xC channel1 12-bit left aligned data holding register
         uint32_t DHR8R1; 	//< 0x10 channel1 8-bit right aligned data holding register
         uint32_t DHR12R2; 	//< 0x14 channel2 12-bit right aligned data holding register
         uint32_t DHR12L2; 	//< 0x18 channel2 12-bit left aligned data holding register
         uint32_t DHR8R2; 	//< 0x1C channel2 8-bit right-aligned data holding register
         uint32_t DHR12RD; 	//< 0x20 Dual DAC 12-bit right-aligned data holding register
         uint32_t DHR12LD; 	//< 0x24 DUAL DAC 12-bit left aligned data holding register
         uint32_t DHR8RD; 	//< 0x28 DUAL DAC 8-bit right aligned data holding register
         uint32_t DOR1; 	//< 0x2C channel1 data output register
         uint32_t DOR2; 	//< 0x30 channel2 data output register
         uint32_t SR; 	//< 0x34 status register
    };

    struct CR {
        constexpr static uint8_t DMAUDRIE2[]{ 29, 1 }; 	//< DAC channel2 DMA underrun interrupt enable
        constexpr static uint8_t DMAEN2[]{ 28, 1 }; 	//< DAC channel2 DMA enable
        constexpr static uint8_t MAMP2[]{ 24, 4 }; 	//< DAC channel2 mask/amplitude selector
        constexpr static uint8_t WAVE2[]{ 22, 2 }; 	//< DAC channel2 noise/triangle wave generation enable
        constexpr static uint8_t TSEL2[]{ 19, 3 }; 	//< DAC channel2 trigger selection
        constexpr static uint8_t TEN2[]{ 18, 1 }; 	//< DAC channel2 trigger enable
        constexpr static uint8_t BOFF2[]{ 17, 1 }; 	//< DAC channel2 output buffer disable
        constexpr static uint8_t EN2[]{ 16, 1 }; 	//< DAC channel2 enable
        constexpr static uint8_t DMAUDRIE1[]{ 13, 1 }; 	//< DAC channel1 DMA Underrun Interrupt enable
        constexpr static uint8_t DMAEN1[]{ 12, 1 }; 	//< DAC channel1 DMA enable
        constexpr static uint8_t MAMP1[]{ 8, 4 }; 	//< DAC channel1 mask/amplitude selector
        constexpr static uint8_t WAVE1[]{ 6, 2 }; 	//< DAC channel1 noise/triangle wave generation enable
        constexpr static uint8_t TSEL1[]{ 3, 3 }; 	//< DAC channel1 trigger selection
        constexpr static uint8_t TEN1[]{ 2, 1 }; 	//< DAC channel1 trigger enable
        constexpr static uint8_t BOFF1[]{ 1, 1 }; 	//< DAC channel1 output buffer disable
        constexpr static uint8_t EN1[]{ 0, 1 }; 	//< DAC channel1 enable
    };

    struct SWTRIGR {
        constexpr static uint8_t SWTRIG2[]{ 1, 1 }; 	//< DAC channel2 software trigger
        constexpr static uint8_t SWTRIG1[]{ 0, 1 }; 	//< DAC channel1 software trigger
    };

    struct DHR12R1 {
        constexpr static uint8_t DACC1DHR[]{ 0, 12 }; 	//< DAC channel1 12-bit right-aligned data
    };

    struct DHR12L1 {
        constexpr static uint8_t DACC1DHR[]{ 4, 12 }; 	//< DAC channel1 12-bit left-aligned data
    };

    struct DHR8R1 {
        constexpr static uint8_t DACC1DHR[]{ 0, 8 }; 	//< DAC channel1 8-bit right-aligned data
    };

    struct DHR12R2 {
        constexpr static uint8_t DACC2DHR[]{ 0, 12 }; 	//< DAC channel2 12-bit right-aligned data
    };

    struct DHR12L2 {
        constexpr static uint8_t DACC2DHR[]{ 4, 12 }; 	//< DAC channel2 12-bit left-aligned data
    };

    struct DHR8R2 {
        constexpr static uint8_t DACC2DHR[]{ 0, 8 }; 	//< DAC channel2 8-bit right-aligned data
    };

    struct DHR12RD {
        constexpr static uint8_t DACC2DHR[]{ 16, 12 }; 	//< DAC channel2 12-bit right-aligned data
        constexpr static uint8_t DACC1DHR[]{ 0, 12 }; 	//< DAC channel1 12-bit right-aligned data
    };

    struct DHR12LD {
        constexpr static uint8_t DACC2DHR[]{ 20, 12 }; 	//< DAC channel2 12-bit left-aligned data
        constexpr static uint8_t DACC1DHR[]{ 4, 12 }; 	//< DAC channel1 12-bit left-aligned data
    };

    struct DHR8RD {
        constexpr static uint8_t DACC2DHR[]{ 8, 8 }; 	//< DAC channel2 8-bit right-aligned data
        constexpr static uint8_t DACC1DHR[]{ 0, 8 }; 	//< DAC channel1 8-bit right-aligned data
    };

    struct DOR1 {
        constexpr static uint8_t DACC1DOR[]{ 0, 12 }; 	//< DAC channel1 data output
    };

    struct DOR2 {
        constexpr static uint8_t DACC2DOR[]{ 0, 12 }; 	//< DAC channel2 data output
    };

    struct SR {
        constexpr static uint8_t DMAUDR2[]{ 29, 1 }; 	//< DAC channel2 DMA underrun flag
        constexpr static uint8_t DMAUDR1[]{ 13, 1 }; 	//< DAC channel1 DMA underrun flag
    };

    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    static volatile Regs* rg()
    {
        return reinterpret_cast<volatile Regs*>(base);
    }

    static void INLINE clockEnable(const bool en) { Rcc::clockDac(en); }


    static void ch1Enable(const bool en)
    {
        tl::setRegister(rg()->CR,
                             CR::EN1, en);
    }

    static void ch2Enable(const bool en)
    {
      tl::setRegister(rg()->CR,
                             CR::EN2, en);
    }

    static void buff1Enable(const bool en)
    {
      tl::setRegister(rg()->CR,
                             CR::BOFF1, !en);
    }

    static void buff2Enable(const bool en)
    {
      tl::setRegister(rg()->CR,
                             CR::BOFF2, !en);
    }

    static void trigger1Enable(const bool en)
    {
      tl::setRegister(rg()->CR,
                             CR::TEN1, en);
    }

    static void trigger2Enable(const bool en)
    {
      tl::setRegister(rg()->CR,
                             CR::TEN2, en);
    }

    static void trigger1Select(const DacTrigger trigger)
    {
      tl::setRegister(rg()->CR,
                             CR::TSEL1, static_cast<uint8_t>(trigger));
    }

    static void trigger2Select(const DacTrigger trigger)
    {
      tl::setRegister(rg()->CR,
                             CR::TSEL2, static_cast<uint8_t>(trigger));
    }

    static void dma1Enable(const bool en)
    {
      tl::setRegister(rg()->CR,
                             CR::DMAEN1, en);
    }

    static void dma2Enable(const bool en)
    {
      tl::setRegister(rg()->CR,
                             CR::DMAEN2, en);
    }


};
#endif // __DAC_H
