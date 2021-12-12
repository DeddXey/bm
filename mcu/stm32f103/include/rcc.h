#ifndef __RCC_H
#define __RCC_H

#include "flash.h"
#include "utility.h"
#include <cstdint>

struct Rcc
{
  constexpr static uint32_t base         = 0x40021000;
  constexpr static uint32_t interrupt    = 5;
  constexpr static uint16_t timeoutValue = 0xffff;

  enum class McoSrc : uint8_t
  {
    no     = 0b0,
    sysclk = 0b100,
    hsi    = 0b101,
    hse    = 0b110,
    pll2   = 0b111,
  };

  enum class UsbPsc : uint8_t
  {
    pllDiv2  = 0,
    pllNoDiv = 1
  };

  enum class AdcPsc : uint8_t
  {
    pclk2Div2 = 0b00,
    pclk2Div4 = 0b01,
    pclk2Div6 = 0b10,
    pclk2Div8 = 0b11,
  };

  enum class Ppre : uint8_t
  {
    hclk      = 0b0,
    hclkDiv2  = 0b100,
    hclkDiv4  = 0b101,
    hclkDiv8  = 0b110,
    hclkDiv16 = 0b111,
  };

  enum class Hpre : uint8_t
  {
    hclk       = 0b0,
    hclkDiv2   = 0b1000,
    hclkDiv4   = 0b1001,
    hclkDiv8   = 0b1010,
    hclkDiv16  = 0b1011,
    hclkDiv64  = 0b1100,
    hclkDiv128 = 0b1101,
    hclkDiv256 = 0b1110,
    hclkDiv512 = 0b1111,
  };

  enum class Sw : uint8_t
  {
    hsi = 0b00,
    hse = 0b01,
    pll = 0b10
  };

  struct Regs
  {
    uint32_t CR;       //< 0x0 Clock control register
    uint32_t CFGR;     //< 0x4 Clock configuration register (RCC_CFGR)
    uint32_t CIR;      //< 0x8 Clock interrupt register (RCC_CIR)
    uint32_t APB2RSTR; //< 0xC APB2 peripheral reset register (RCC_APB2RSTR)
    uint32_t APB1RSTR; //< 0x10 APB1 peripheral reset register (RCC_APB1RSTR)
    uint32_t AHBENR; //< 0x14 AHB Peripheral Clock enable register (RCC_AHBENR)
    uint32_t
      APB2ENR; //< 0x18 APB2 peripheral clock enable register (RCC_APB2ENR)
    uint32_t
      APB1ENR;     //< 0x1C APB1 peripheral clock enable register (RCC_APB1ENR)
    uint32_t BDCR; //< 0x20 Backup domain control register (RCC_BDCR)
    uint32_t CSR;  //< 0x24 Control/status register (RCC_CSR)
  };

  struct CR
  {
    constexpr static uint8_t HSION[]{ 0,
                                      1 }; //< Internal High Speed clock enable
    constexpr static uint8_t HSIRDY[]{
      1,
      1
    }; //< Internal High Speed clock ready flag
    constexpr static uint8_t HSITRIM[]{
      3,
      5
    }; //< Internal High Speed clock trimming
    constexpr static uint8_t HSICAL[]{
      8,
      8
    }; //< Internal High Speed clock Calibration
    constexpr static uint8_t HSEON[]{ 16,
                                      1 }; //< External High Speed clock enable
    constexpr static uint8_t HSERDY[]{
      17,
      1
    }; //< External High Speed clock ready flag
    constexpr static uint8_t HSEBYP[]{ 18,
                                       1 }; //< External High Speed clock Bypass
    constexpr static uint8_t CSSON[]{ 19, 1 };  //< Clock Security System enable
    constexpr static uint8_t PLLON[]{ 24, 1 };  //< PLL enable
    constexpr static uint8_t PLLRDY[]{ 25, 1 }; //< PLL clock ready flag
  };

  struct CFGR
  {
    constexpr static uint8_t SW[]{ 0, 2 };    //< System clock Switch
    constexpr static uint8_t SWS[]{ 2, 2 };   //< System Clock Switch Status
    constexpr static uint8_t HPRE[]{ 4, 4 };  //< AHB prescaler
    constexpr static uint8_t PPRE1[]{ 8, 3 }; //< APB Low speed prescaler (APB1)
    constexpr static uint8_t PPRE2[]{ 11,
                                      3 }; //< APB High speed prescaler (APB2)
    constexpr static uint8_t ADCPRE[]{ 14, 2 };   //< ADC prescaler
    constexpr static uint8_t PLLSRC[]{ 16, 1 };   //< PLL entry clock source
    constexpr static uint8_t PLLXTPRE[]{ 17, 1 }; //< HSE divider for PLL entry
    constexpr static uint8_t PLLMUL[]{ 18, 4 };   //< PLL Multiplication Factor
    constexpr static uint8_t OTGFSPRE[]{ 22, 1 }; //< USB OTG FS prescaler
    constexpr static uint8_t MCO[]{ 24, 3 }; //< Microcontroller clock output
  };

  struct CIR
  {
    constexpr static uint8_t LSIRDYF[]{ 0, 1 }; //< LSI Ready Interrupt flag
    constexpr static uint8_t LSERDYF[]{ 1, 1 }; //< LSE Ready Interrupt flag
    constexpr static uint8_t HSIRDYF[]{ 2, 1 }; //< HSI Ready Interrupt flag
    constexpr static uint8_t HSERDYF[]{ 3, 1 }; //< HSE Ready Interrupt flag
    constexpr static uint8_t PLLRDYF[]{ 4, 1 }; //< PLL Ready Interrupt flag
    constexpr static uint8_t CSSF[]{
      7,
      1
    }; //< Clock Security System Interrupt flag
    constexpr static uint8_t LSIRDYIE[]{ 8, 1 };  //< LSI Ready Interrupt Enable
    constexpr static uint8_t LSERDYIE[]{ 9, 1 };  //< LSE Ready Interrupt Enable
    constexpr static uint8_t HSIRDYIE[]{ 10, 1 }; //< HSI Ready Interrupt Enable
    constexpr static uint8_t HSERDYIE[]{ 11, 1 }; //< HSE Ready Interrupt Enable
    constexpr static uint8_t PLLRDYIE[]{ 12, 1 }; //< PLL Ready Interrupt Enable
    constexpr static uint8_t LSIRDYC[]{ 16, 1 };  //< LSI Ready Interrupt Clear
    constexpr static uint8_t LSERDYC[]{ 17, 1 };  //< LSE Ready Interrupt Clear
    constexpr static uint8_t HSIRDYC[]{ 18, 1 };  //< HSI Ready Interrupt Clear
    constexpr static uint8_t HSERDYC[]{ 19, 1 };  //< HSE Ready Interrupt Clear
    constexpr static uint8_t PLLRDYC[]{ 20, 1 };  //< PLL Ready Interrupt Clear
    constexpr static uint8_t CSSC[]{
      23,
      1
    }; //< Clock security system interrupt clear
  };

  struct APB2RSTR
  {
    constexpr static uint8_t AFIORST[]{ 0, 1 }; //< Alternate function I/O reset
    constexpr static uint8_t IOPARST[]{ 2, 1 }; //< IO port A reset
    constexpr static uint8_t IOPBRST[]{ 3, 1 }; //< IO port B reset
    constexpr static uint8_t IOPCRST[]{ 4, 1 }; //< IO port C reset
    constexpr static uint8_t IOPDRST[]{ 5, 1 }; //< IO port D reset
    constexpr static uint8_t IOPERST[]{ 6, 1 }; //< IO port E reset
    constexpr static uint8_t IOPFRST[]{ 7, 1 }; //< IO port F reset
    constexpr static uint8_t IOPGRST[]{ 8, 1 }; //< IO port G reset
    constexpr static uint8_t ADC1RST[]{ 9, 1 }; //< ADC 1 interface reset
    constexpr static uint8_t ADC2RST[]{ 10, 1 };   //< ADC 2 interface reset
    constexpr static uint8_t TIM1RST[]{ 11, 1 };   //< TIM1 timer reset
    constexpr static uint8_t SPI1RST[]{ 12, 1 };   //< SPI 1 reset
    constexpr static uint8_t TIM8RST[]{ 13, 1 };   //< TIM8 timer reset
    constexpr static uint8_t USART1RST[]{ 14, 1 }; //< USART1 reset
    constexpr static uint8_t ADC3RST[]{ 15, 1 };   //< ADC 3 interface reset
    constexpr static uint8_t TIM9RST[]{ 19, 1 };   //< TIM9 timer reset
    constexpr static uint8_t TIM10RST[]{ 20, 1 };  //< TIM10 timer reset
    constexpr static uint8_t TIM11RST[]{ 21, 1 };  //< TIM11 timer reset
  };

  struct APB1RSTR
  {
    constexpr static uint8_t TIM2RST[]{ 0, 1 };    //< Timer 2 reset
    constexpr static uint8_t TIM3RST[]{ 1, 1 };    //< Timer 3 reset
    constexpr static uint8_t TIM4RST[]{ 2, 1 };    //< Timer 4 reset
    constexpr static uint8_t TIM5RST[]{ 3, 1 };    //< Timer 5 reset
    constexpr static uint8_t TIM6RST[]{ 4, 1 };    //< Timer 6 reset
    constexpr static uint8_t TIM7RST[]{ 5, 1 };    //< Timer 7 reset
    constexpr static uint8_t TIM12RST[]{ 6, 1 };   //< Timer 12 reset
    constexpr static uint8_t TIM13RST[]{ 7, 1 };   //< Timer 13 reset
    constexpr static uint8_t TIM14RST[]{ 8, 1 };   //< Timer 14 reset
    constexpr static uint8_t WWDGRST[]{ 11, 1 };   //< Window watchdog reset
    constexpr static uint8_t SPI2RST[]{ 14, 1 };   //< SPI2 reset
    constexpr static uint8_t SPI3RST[]{ 15, 1 };   //< SPI3 reset
    constexpr static uint8_t USART2RST[]{ 17, 1 }; //< USART 2 reset
    constexpr static uint8_t USART3RST[]{ 18, 1 }; //< USART 3 reset
    constexpr static uint8_t UART4RST[]{ 19, 1 };  //< UART 4 reset
    constexpr static uint8_t UART5RST[]{ 20, 1 };  //< UART 5 reset
    constexpr static uint8_t I2C1RST[]{ 21, 1 };   //< I2C1 reset
    constexpr static uint8_t I2C2RST[]{ 22, 1 };   //< I2C2 reset
    constexpr static uint8_t USBRST[]{ 23, 1 };    //< USB reset
    constexpr static uint8_t CANRST[]{ 25, 1 };    //< CAN reset
    constexpr static uint8_t BKPRST[]{ 27, 1 };    //< Backup interface reset
    constexpr static uint8_t PWRRST[]{ 28, 1 };    //< Power interface reset
    constexpr static uint8_t DACRST[]{ 29, 1 };    //< DAC interface reset
  };

  struct AHBENR
  {
    constexpr static uint8_t DMA1EN[]{ 0, 1 };  //< DMA1 clock enable
    constexpr static uint8_t DMA2EN[]{ 1, 1 };  //< DMA2 clock enable
    constexpr static uint8_t SRAMEN[]{ 2, 1 };  //< SRAM interface clock enable
    constexpr static uint8_t FLITFEN[]{ 4, 1 }; //< FLITF clock enable
    constexpr static uint8_t CRCEN[]{ 6, 1 };   //< CRC clock enable
    constexpr static uint8_t FSMCEN[]{ 8, 1 };  //< FSMC clock enable
    constexpr static uint8_t SDIOEN[]{ 10, 1 }; //< SDIO clock enable
  };

  struct APB2ENR
  {
    constexpr static uint8_t AFIOEN[]{
      0,
      1
    }; //< Alternate function I/O clock enable
    constexpr static uint8_t IOPAEN[]{ 2, 1 };  //< I/O port A clock enable
    constexpr static uint8_t IOPBEN[]{ 3, 1 };  //< I/O port B clock enable
    constexpr static uint8_t IOPCEN[]{ 4, 1 };  //< I/O port C clock enable
    constexpr static uint8_t IOPDEN[]{ 5, 1 };  //< I/O port D clock enable
    constexpr static uint8_t IOPEEN[]{ 6, 1 };  //< I/O port E clock enable
    constexpr static uint8_t IOPFEN[]{ 7, 1 };  //< I/O port F clock enable
    constexpr static uint8_t IOPGEN[]{ 8, 1 };  //< I/O port G clock enable
    constexpr static uint8_t ADC1EN[]{ 9, 1 };  //< ADC 1 interface clock enable
    constexpr static uint8_t ADC2EN[]{ 10, 1 }; //< ADC 2 interface clock enable
    constexpr static uint8_t TIM1EN[]{ 11, 1 }; //< TIM1 Timer clock enable
    constexpr static uint8_t SPI1EN[]{ 12, 1 }; //< SPI 1 clock enable
    constexpr static uint8_t TIM8EN[]{ 13, 1 }; //< TIM8 Timer clock enable
    constexpr static uint8_t USART1EN[]{ 14, 1 }; //< USART1 clock enable
    constexpr static uint8_t ADC3EN[]{ 15, 1 };  //< ADC3 interface clock enable
    constexpr static uint8_t TIM9EN[]{ 19, 1 };  //< TIM9 Timer clock enable
    constexpr static uint8_t TIM10EN[]{ 20, 1 }; //< TIM10 Timer clock enable
    constexpr static uint8_t TIM11EN[]{ 21, 1 }; //< TIM11 Timer clock enable
  };

  struct APB1ENR
  {
    constexpr static uint8_t TIM2EN[]{ 0, 1 };  //< Timer 2 clock enable
    constexpr static uint8_t TIM3EN[]{ 1, 1 };  //< Timer 3 clock enable
    constexpr static uint8_t TIM4EN[]{ 2, 1 };  //< Timer 4 clock enable
    constexpr static uint8_t TIM5EN[]{ 3, 1 };  //< Timer 5 clock enable
    constexpr static uint8_t TIM6EN[]{ 4, 1 };  //< Timer 6 clock enable
    constexpr static uint8_t TIM7EN[]{ 5, 1 };  //< Timer 7 clock enable
    constexpr static uint8_t TIM12EN[]{ 6, 1 }; //< Timer 12 clock enable
    constexpr static uint8_t TIM13EN[]{ 7, 1 }; //< Timer 13 clock enable
    constexpr static uint8_t TIM14EN[]{ 8, 1 }; //< Timer 14 clock enable
    constexpr static uint8_t WWDGEN[]{ 11, 1 }; //< Window watchdog clock enable
    constexpr static uint8_t SPI2EN[]{ 14, 1 }; //< SPI 2 clock enable
    constexpr static uint8_t SPI3EN[]{ 15, 1 }; //< SPI 3 clock enable
    constexpr static uint8_t USART2EN[]{ 17, 1 }; //< USART 2 clock enable
    constexpr static uint8_t USART3EN[]{ 18, 1 }; //< USART 3 clock enable
    constexpr static uint8_t UART4EN[]{ 19, 1 };  //< UART 4 clock enable
    constexpr static uint8_t UART5EN[]{ 20, 1 };  //< UART 5 clock enable
    constexpr static uint8_t I2C1EN[]{ 21, 1 };   //< I2C 1 clock enable
    constexpr static uint8_t I2C2EN[]{ 22, 1 };   //< I2C 2 clock enable
    constexpr static uint8_t USBEN[]{ 23, 1 };    //< USB clock enable
    constexpr static uint8_t CANEN[]{ 25, 1 };    //< CAN clock enable
    constexpr static uint8_t BKPEN[]{ 27, 1 }; //< Backup interface clock enable
    constexpr static uint8_t PWREN[]{ 28, 1 }; //< Power interface clock enable
    constexpr static uint8_t DACEN[]{ 29, 1 }; //< DAC interface clock enable
  };

  struct BDCR
  {
    constexpr static uint8_t LSEON[]{
      0,
      1
    }; //< External Low Speed oscillator enable
    constexpr static uint8_t LSERDY[]{
      1,
      1
    }; //< External Low Speed oscillator ready
    constexpr static uint8_t LSEBYP[]{
      2,
      1
    }; //< External Low Speed oscillator bypass
    constexpr static uint8_t RTCSEL[]{ 8, 2 }; //< RTC clock source selection
    constexpr static uint8_t RTCEN[]{ 15, 1 }; //< RTC clock enable
    constexpr static uint8_t BDRST[]{ 16, 1 }; //< Backup domain software reset
  };

  struct CSR
  {
    constexpr static uint8_t LSION[]{
      0,
      1
    }; //< Internal low speed oscillator enable
    constexpr static uint8_t LSIRDY[]{
      1,
      1
    }; //< Internal low speed oscillator ready
    constexpr static uint8_t RMVF[]{ 24, 1 };    //< Remove reset flag
    constexpr static uint8_t PINRSTF[]{ 26, 1 }; //< PIN reset flag
    constexpr static uint8_t PORRSTF[]{ 27, 1 }; //< POR/PDR reset flag
    constexpr static uint8_t SFTRSTF[]{ 28, 1 }; //< Software reset flag
    constexpr static uint8_t IWDGRSTF[]{
      29,
      1
    }; //< Independent watchdog reset flag
    constexpr static uint8_t WWDGRSTF[]{ 30, 1 }; //< Window watchdog reset flag
    constexpr static uint8_t LPWRRSTF[]{ 31, 1 }; //< Low-power reset flag
  };

  ///---------------------------------------------------------------------
  ///
  /// \brief Получение указателя на регистры
  /// \return указатель на регистры
  ///
  static volatile Regs *rg()
  {
    return reinterpret_cast<volatile Regs *>(base);
  }

  // Clock enable functions    static void clockDma1(bool en) {
  // setRegister(rg()->AHBENR, AHBENR::DMA1EN, en); }
  static void clockDma1(bool en)
  {
    tl::setRegister(rg()->AHBENR, AHBENR::DMA1EN, en);
  }
  static void clockDma2(bool en)
  {
    tl::setRegister(rg()->AHBENR, AHBENR::DMA2EN, en);
  }
  static void clockSram(bool en)
  {
    tl::setRegister(rg()->AHBENR, AHBENR::SRAMEN, en);
  }
  static void clockFlitf(bool en)
  {
    tl::setRegister(rg()->AHBENR, AHBENR::FLITFEN, en);
  }
  static void clockCrc(bool en)
  {
    tl::setRegister(rg()->AHBENR, AHBENR::CRCEN, en);
  }
  static void clockFsmc(bool en)
  {
    tl::setRegister(rg()->AHBENR, AHBENR::FSMCEN, en);
  }
  static void clockSdio(bool en)
  {
    tl::setRegister(rg()->AHBENR, AHBENR::SDIOEN, en);
  }
  static void clockAfio(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::AFIOEN, en);
  }
  static void clockIopA(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::IOPAEN, en);
  }
  static void clockIopB(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::IOPBEN, en);
  }
  static void clockIopC(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::IOPCEN, en);
  }
  static void clockIopD(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::IOPDEN, en);
  }
  static void clockIopE(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::IOPEEN, en);
  }
  static void clockIopF(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::IOPFEN, en);
  }
  static void clockIopG(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::IOPGEN, en);
  }
  static void clockAdc1(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::ADC1EN, en);
  }
  static void clockAdc2(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::ADC2EN, en);
  }
  static void clockTim1(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::TIM1EN, en);
  }
  static void clockSpi1(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::SPI1EN, en);
  }
  static void clockTim8(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::TIM8EN, en);
  }
  static void clockUsart1(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::USART1EN, en);
  }
  static void clockAdc3(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::ADC3EN, en);
  }
  static void clockTim9(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::TIM9EN, en);
  }
  static void clockTim10(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::TIM10EN, en);
  }
  static void clockTim11(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::TIM11EN, en);
  }
  static void clockTim2(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM2EN, en);
  }
  static void clockTim3(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM3EN, en);
  }
  static void clockTim4(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM4EN, en);
  }
  static void clockTim5(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM5EN, en);
  }
  static void clockTim6(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM6EN, en);
  }
  static void clockTim7(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM7EN, en);
  }
  static void clockTim12(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM12EN, en);
  }
  static void clockTim13(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM13EN, en);
  }
  static void clockTim14(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM14EN, en);
  }
  static void clockWwdg(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::WWDGEN, en);
  }
  static void clockSpi2(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::SPI2EN, en);
  }
  static void clockSpi3(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::SPI3EN, en);
  }
  static void clockUsart2(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::USART2EN, en);
  }
  static void clockUsart3(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::USART3EN, en);
  }
  static void clockUart4(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::UART4EN, en);
  }
  static void clockUart5(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::UART5EN, en);
  }
  static void clockI2c1(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::I2C1EN, en);
  }
  static void clockI2c2(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::I2C2EN, en);
  }
  static void clockUsb(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::USBEN, en);
  }
  static void clockCan(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::CANEN, en);
  }
  static void clockBkp(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::BKPEN, en);
  }
  static void clockPwr(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::PWREN, en);
  }
  static void clockDac(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::DACEN, en);
  }

  // Reset functions    static void resetAfio(bool en) {
  // setRegister(rg()->APB2RSTR, APB2RSTR::AFIORST, en); }
  static void resetIopA(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::IOPARST, en);
  }
  static void resetIopB(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::IOPBRST, en);
  }
  static void resetIopC(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::IOPCRST, en);
  }
  static void resetIopD(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::IOPDRST, en);
  }
  static void resetIopE(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::IOPERST, en);
  }
  static void resetIopF(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::IOPFRST, en);
  }
  static void resetIopG(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::IOPGRST, en);
  }
  static void resetAdc1(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::ADC1RST, en);
  }
  static void resetAdc2(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::ADC2RST, en);
  }
  static void resetTim1(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM1RST, en);
  }
  static void resetSpi1(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::SPI1RST, en);
  }
  static void resetTim8(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM8RST, en);
  }
  static void resetUsart1(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::USART1RST, en);
  }
  static void resetAdc3(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::ADC3RST, en);
  }
  static void resetTim9(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM9RST, en);
  }
  static void resetTim10(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM10RST, en);
  }
  static void resetTim11(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM11RST, en);
  }
  static void resetTim2(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM2RST, en);
  }
  static void resetTim3(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM3RST, en);
  }
  static void resetTim4(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM4RST, en);
  }
  static void resetTim5(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM5RST, en);
  }
  static void resetTim6(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM6RST, en);
  }
  static void resetTim7(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM7RST, en);
  }
  static void resetTim12(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM12RST, en);
  }
  static void resetTim13(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM13RST, en);
  }
  static void resetTim14(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM14RST, en);
  }
  static void resetWwdg(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::WWDGRST, en);
  }
  static void resetSpi2(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::SPI2RST, en);
  }
  static void resetSpi3(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::SPI3RST, en);
  }
  static void resetUsart2(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::USART2RST, en);
  }
  static void resetUsart3(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::USART3RST, en);
  }
  static void resetUart4(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::UART4RST, en);
  }
  static void resetUart5(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::UART5RST, en);
  }
  static void resetI2c1(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::I2C1RST, en);
  }
  static void resetI2c2(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::I2C2RST, en);
  }
  static void resetUsb(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::USBRST, en);
  }
  static void resetCan(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::CANRST, en);
  }
  static void resetBkp(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::BKPRST, en);
  }
  static void resetPwr(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::PWRRST, en);
  }
  static void resetDac(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::DACRST, en);
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Выбор источника тактирования
  /// \param src источник тактирования
  /// \return true если удачно
  ///
  static bool sysClockSelect(Sw src)
  {
    uint16_t timeout = timeoutValue;
    Sw       value;

    tl::setRegister(rg()->CFGR, CFGR::SW, static_cast<uint16_t>(src));

    do {
      value = static_cast<Sw>(tl::getRegField(rg()->CFGR, CFGR::SWS));
      timeout--;

    } while ((value != src) && (timeout != 0));

    if (!timeout)
      return false;

    return true;
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Включение кварцевого генератора
  /// \param en требуемое состояние
  /// \return true если удачно
  ///
  static bool hseEnable(bool en)
  {
    uint16_t timeout = timeoutValue;

    tl::setRegister(rg()->CR, CR::HSEON, en);

    do {

    } while (((tl::getRegField(rg()->CR, CR::HSERDY) != en)) && (timeout--));

    if (!timeout)
      return false;

    return true;
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Включение главной PLL
  /// \param en требуемое состояние
  /// \return true если удачно
  ///
  static bool pllEnable(bool en)
  {
    uint16_t timeout = timeoutValue;

    tl::setRegister(rg()->CR, CR::PLLON, en);

    do {

    } while (((tl::getRegField(rg()->CR, CR::PLLRDY) != en)) && (timeout--));

    if (!timeout)
      return false;

    return true;
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Установка параметров главной PLL
  /// \param mul multiplier
  ///
  static void pllSet(uint8_t mul)
  {
    tl::setRegister(rg()->CFGR, CFGR::PLLMUL, mul - 2);
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Выбор источника тактирования для главной Pll
  /// \param en true - hse, false - hsi /2
  ///
  static void pllClockSrcSelectHse(bool en, bool div_by_2 = false)
  {
    tl::setRegister(rg()->CFGR, CFGR::PLLSRC, en, CFGR::PLLXTPRE, div_by_2);
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Установка делителя APB1
  /// \param prescaler делитель
  ///
  static void setApb1Pre(Ppre prescaler)
  {
    tl::setRegister(rg()->CFGR, CFGR::PPRE1, static_cast<uint16_t>(prescaler));
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Установка делителя APB2
  /// \param prescaler делитель
  ///
  static void setApb2Pre(Ppre prescaler)
  {
    tl::setRegister(rg()->CFGR, CFGR::PPRE2, static_cast<uint16_t>(prescaler));
  }

  static void setAdcPre(AdcPsc prescaler)
  {
    tl::setRegister(rg()->CFGR, CFGR::ADCPRE, static_cast<uint8_t>(prescaler));
  }

  ///
  /// \brief Дефолтная конфигурация на 168 МГц
  /// \return
  ///
  static bool defaultConfigPll72(bool hse_div_by_2 = false)
  {
    clockPwr(true);
    if (!hseEnable(true))
      return false;

    pllSet(9); // 72 MHz

    pllClockSrcSelectHse(true, hse_div_by_2);

    if (!pllEnable(true))
      return false;

    // TODO: Flash latency
    Flash::setLatency(Flash::Latency::twoWaitStates);

    if (!sysClockSelect(Sw::pll))
      return false;

    systemCoreClock() = 72000000;

    setApb1Pre(Ppre::hclkDiv2);
    setApb2Pre(Ppre::hclkDiv2);
    apb2Clk() = systemCoreClock() / 2;

    return true;
  }

  ///
  /// \brief Получение ссылки на переменную, хранящую тактовую частоту системы
  /// \return ссылка на переменную, хранящую тактовую частоту системы
  ///
  static uint32_t &systemCoreClock()
  {
    static uint32_t sysCoreClock;

    return sysCoreClock;
  }

  static uint32_t &apb2Clk()
  {
    static uint32_t apb2Clock;

    return apb2Clock;
  }
};
#endif // __RCC_H
