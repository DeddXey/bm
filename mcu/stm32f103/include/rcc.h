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
    hclkDiv1  = 0b0,
    hclkDiv2  = 0b100,
    hclkDiv4  = 0b101,
    hclkDiv8  = 0b110,
    hclkDiv16 = 0b111,
  };

  enum class Hpre : uint8_t
  {
    hclkDiv1   = 0b0,
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

  // Clock enable functions    static void clockDma1(bool value) {
  // setRegister(rg()->AHBENR, AHBENR::DMA1EN, value); }
  static void clockDma1(bool value)
  {
    tl::setRegister(rg()->AHBENR, AHBENR::DMA1EN, value);
  }
  static void clockDma2(bool value)
  {
    tl::setRegister(rg()->AHBENR, AHBENR::DMA2EN, value);
  }
  static void clockSram(bool value)
  {
    tl::setRegister(rg()->AHBENR, AHBENR::SRAMEN, value);
  }
  static void clockFlitf(bool value)
  {
    tl::setRegister(rg()->AHBENR, AHBENR::FLITFEN, value);
  }
  static void clockCrc(bool value)
  {
    tl::setRegister(rg()->AHBENR, AHBENR::CRCEN, value);
  }
  static void clockFsmc(bool value)
  {
    tl::setRegister(rg()->AHBENR, AHBENR::FSMCEN, value);
  }
  static void clockSdio(bool value)
  {
    tl::setRegister(rg()->AHBENR, AHBENR::SDIOEN, value);
  }
  static void clockAfio(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::AFIOEN, value);
  }
  static void clockIopA(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::IOPAEN, value);
  }
  static void clockIopB(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::IOPBEN, value);
  }
  static void clockIopC(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::IOPCEN, value);
  }
  static void clockIopD(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::IOPDEN, value);
  }
  static void clockIopE(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::IOPEEN, value);
  }
  static void clockIopF(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::IOPFEN, value);
  }
  static void clockIopG(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::IOPGEN, value);
  }
  static void clockAdc1(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::ADC1EN, value);
  }
  static void clockAdc2(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::ADC2EN, value);
  }
  static void clockTim1(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::TIM1EN, value);
  }
  static void clockSpi1(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::SPI1EN, value);
  }
  static void clockTim8(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::TIM8EN, value);
  }
  static void clockUsart1(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::USART1EN, value);
  }
  static void clockAdc3(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::ADC3EN, value);
  }
  static void clockTim9(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::TIM9EN, value);
  }
  static void clockTim10(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::TIM10EN, value);
  }
  static void clockTim11(bool value)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::TIM11EN, value);
  }
  static void clockTim2(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM2EN, value);
  }
  static void clockTim3(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM3EN, value);
  }
  static void clockTim4(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM4EN, value);
  }
  static void clockTim5(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM5EN, value);
  }
  static void clockTim6(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM6EN, value);
  }
  static void clockTim7(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM7EN, value);
  }
  static void clockTim12(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM12EN, value);
  }
  static void clockTim13(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM13EN, value);
  }
  static void clockTim14(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::TIM14EN, value);
  }
  static void clockWwdg(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::WWDGEN, value);
  }
  static void clockSpi2(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::SPI2EN, value);
  }
  static void clockSpi3(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::SPI3EN, value);
  }
  static void clockUsart2(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::USART2EN, value);
  }
  static void clockUsart3(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::USART3EN, value);
  }
  static void clockUart4(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::UART4EN, value);
  }
  static void clockUart5(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::UART5EN, value);
  }
  static void clockI2c1(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::I2C1EN, value);
  }
  static void clockI2c2(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::I2C2EN, value);
  }
  static void clockUsb(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::USBEN, value);
  }
  static void clockCan(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::CANEN, value);
  }
  static void clockBkp(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::BKPEN, value);
  }
  static void clockPwr(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::PWREN, value);
  }
  static void clockDac(bool value)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::DACEN, value);
  }

  // Reset functions    static void resetAfio(bool value) {
  // setRegister(rg()->APB2RSTR, APB2RSTR::AFIORST, value); }
  static void resetIopA(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::IOPARST, value);
  }
  static void resetIopB(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::IOPBRST, value);
  }
  static void resetIopC(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::IOPCRST, value);
  }
  static void resetIopD(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::IOPDRST, value);
  }
  static void resetIopE(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::IOPERST, value);
  }
  static void resetIopF(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::IOPFRST, value);
  }
  static void resetIopG(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::IOPGRST, value);
  }
  static void resetAdc1(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::ADC1RST, value);
  }
  static void resetAdc2(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::ADC2RST, value);
  }
  static void resetTim1(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM1RST, value);
  }
  static void resetSpi1(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::SPI1RST, value);
  }
  static void resetTim8(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM8RST, value);
  }
  static void resetUsart1(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::USART1RST, value);
  }
  static void resetAdc3(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::ADC3RST, value);
  }
  static void resetTim9(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM9RST, value);
  }
  static void resetTim10(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM10RST, value);
  }
  static void resetTim11(bool value)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM11RST, value);
  }
  static void resetTim2(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM2RST, value);
  }
  static void resetTim3(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM3RST, value);
  }
  static void resetTim4(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM4RST, value);
  }
  static void resetTim5(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM5RST, value);
  }
  static void resetTim6(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM6RST, value);
  }
  static void resetTim7(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM7RST, value);
  }
  static void resetTim12(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM12RST, value);
  }
  static void resetTim13(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM13RST, value);
  }
  static void resetTim14(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM14RST, value);
  }
  static void resetWwdg(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::WWDGRST, value);
  }
  static void resetSpi2(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::SPI2RST, value);
  }
  static void resetSpi3(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::SPI3RST, value);
  }
  static void resetUsart2(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::USART2RST, value);
  }
  static void resetUsart3(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::USART3RST, value);
  }
  static void resetUart4(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::UART4RST, value);
  }
  static void resetUart5(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::UART5RST, value);
  }
  static void resetI2c1(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::I2C1RST, value);
  }
  static void resetI2c2(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::I2C2RST, value);
  }
  static void resetUsb(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::USBRST, value);
  }
  static void resetCan(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::CANRST, value);
  }
  static void resetBkp(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::BKPRST, value);
  }
  static void resetPwr(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::PWRRST, value);
  }
  static void resetDac(bool value)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::DACRST, value);
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
  /// \param value требуемое состояние
  /// \return true если удачно
  ///
  static bool hseEnable(bool value)
  {
    uint16_t timeout = timeoutValue;

    tl::setRegister(rg()->CR, CR::HSEON, value);

    do {

    } while (((tl::getRegField(rg()->CR, CR::HSERDY) != value)) && (timeout--));

    if (!timeout)
      return false;

    return true;
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Включение главной PLL
  /// \param value требуемое состояние
  /// \return true если удачно
  ///
  static bool pllEnable(bool value)
  {
    uint16_t timeout = timeoutValue;

    tl::setRegister(rg()->CR, CR::PLLON, value);

    do {

    } while (((tl::getRegField(rg()->CR, CR::PLLRDY) != value)) && (timeout--));

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
  /// \param value true - hse, false - hsi /2
  ///
  static void pllClockSrcSelectHse(bool value, bool div_by_2 = false)
  {
    tl::setRegister(rg()->CFGR, CFGR::PLLSRC, value, CFGR::PLLXTPRE, div_by_2);
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

  static void setAhbPre(Hpre prescaler)
  {
    tl::setRegister(rg()->CFGR, CFGR::HPRE, static_cast<uint16_t>(prescaler));
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

    setAhbPre(Hpre::hclkDiv1);

    setApb1Pre(Ppre::hclkDiv2);
    apb1Clk() = systemCoreClock() / 2;

    setApb2Pre(Ppre::hclkDiv1);
    apb2Clk() = systemCoreClock() / 1;

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

  static uint32_t &apb1Clk()
  {
    static uint32_t apb1Clock;

    return apb1Clock;
  }
};
#endif // __RCC_H
