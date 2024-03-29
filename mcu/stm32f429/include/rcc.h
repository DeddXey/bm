#ifndef RCC_H
#define RCC_H

#include "flash.h"
#include "utility.h"
#include <cstdint>

struct Rcc
{

  constexpr static uint32_t base         = 0x40023800;
  constexpr static uint32_t interrupt    = 5;
  constexpr static uint16_t timeoutValue = 0xffff;

  enum class [[maybe_unused]] PllP : uint8_t{
    p2 [[maybe_unused]] = 0b00,
    p4 [[maybe_unused]] = 0b01,
    p6 [[maybe_unused]] = 0b10,
    p8 [[maybe_unused]] = 0b11,
  };

  enum class [[maybe_unused]] SysClockSrc : uint8_t{
    hsi [[maybe_unused]] = 0b00,
    hse [[maybe_unused]] = 0b01,
    pll [[maybe_unused]] = 0b10,
  };

  enum class [[maybe_unused]] AhbPrescaler : uint8_t{
    prescaler1 [[maybe_unused]]   = 0b0000,
    prescaler2 [[maybe_unused]]   = 0b1000,
    prescaler4 [[maybe_unused]]   = 0b1001,
    prescaler8 [[maybe_unused]]   = 0b1010,
    prescaler16 [[maybe_unused]]  = 0b1011,
    prescaler32 [[maybe_unused]]  = 0b1100, //?
    prescaler64 [[maybe_unused]]  = 0b1101, //?
    prescaler128 [[maybe_unused]] = 0b1110, //?
    prescaler256 [[maybe_unused]] = 0b1111, //?
    prescaler512 [[maybe_unused]] = 0b1111, //?
  };

  enum class [[maybe_unused]] ApbPrescaler : uint8_t{
    prescaler1 [[maybe_unused]] = 0b000,  prescaler2 [[maybe_unused]] = 0b100,
    prescaler4 [[maybe_unused]] = 0b101,  prescaler8 [[maybe_unused]] = 0b110,
    prescaler16 [[maybe_unused]] = 0b111,
  };

  constexpr static uint8_t ApbPrescalerToValue[]{ 1, 1, 1, 1, 2, 4, 8, 16 };

  enum class [[maybe_unused]] McoPrescaler : uint8_t{
    prescaler1 [[maybe_unused]] = 0b000, prescaler2 [[maybe_unused]] = 0b100,
    prescaler3 [[maybe_unused]] = 0b101, prescaler4 [[maybe_unused]] = 0b110,
    prescaler5 [[maybe_unused]] = 0b111,
  };

  enum class [[maybe_unused]] Mco1Src : uint8_t{
    hsi [[maybe_unused]] = 0b00,
    lse [[maybe_unused]] = 0b01,
    hse [[maybe_unused]] = 0b10,
    pll [[maybe_unused]] = 0b11,
  };
  enum class [[maybe_unused]] Mco2Src : uint8_t{
    sysclk [[maybe_unused]] = 0b00,
    pll2s [[maybe_unused]]  = 0b01,
    hse [[maybe_unused]]    = 0b10,
    pll [[maybe_unused]]    = 0b11,
  };

  enum class [[maybe_unused]] PllSaiDivr : uint8_t{
    divr2 [[maybe_unused]]  = 0b000,
    divr4 [[maybe_unused]]  = 0b01,
    divr8 [[maybe_unused]]  = 0b10,
    divr16 [[maybe_unused]] = 0b11,
  };

  enum class [[maybe_unused]] RtcClkSrc : uint8_t{ no [[maybe_unused]]  = 0b00,
                                                   lse [[maybe_unused]] = 0b01,
                                                   lsi [[maybe_unused]] = 0b10,
                                                   hse [[maybe_unused]] =
                                                     0b11 };

  struct [[maybe_unused]] Regs
  {
    [[maybe_unused]] uint32_t CR;        //< 0x0 clock control register
    [[maybe_unused]] uint32_t PLLCFGR;   //< 0x4 PLL configuration register
    [[maybe_unused]] uint32_t CFGR;      //< 0x8 clock configuration register
    [[maybe_unused]] uint32_t CIR;       //< 0xC clock interrupt register
    [[maybe_unused]] uint32_t AHB1RSTR;  //< 0x10 AHB1 peripheral reset register
    [[maybe_unused]] uint32_t AHB2RSTR;  //< 0x14 AHB2 peripheral reset register
    [[maybe_unused]] uint32_t AHB3RSTR;  //< 0x18 AHB3 peripheral reset register
    [[maybe_unused]] uint32_t reserved0; //< reserved
    [[maybe_unused]] uint32_t APB1RSTR;  //< 0x20 APB1 peripheral reset register
    [[maybe_unused]] uint32_t APB2RSTR;  //< 0x24 APB2 peripheral reset register
    [[maybe_unused]] uint32_t reserved1[2]; //< reserved
    [[maybe_unused]] uint32_t AHB1ENR; //< 0x30 AHB1 peripheral clock register
    [[maybe_unused]] uint32_t
      AHB2ENR; //< 0x34 AHB2 peripheral clock enable register
    [[maybe_unused]] uint32_t
      AHB3ENR; //< 0x38 AHB3 peripheral clock enable register
    [[maybe_unused]] uint32_t reserved2; //< reserved
    [[maybe_unused]] uint32_t
      APB1ENR; //< 0x40 APB1 peripheral clock enable register
    [[maybe_unused]] uint32_t
      APB2ENR; //< 0x44 APB2 peripheral clock enable register
    [[maybe_unused]] uint32_t reserved3[2]; //< reserved
    [[maybe_unused]] uint32_t
      AHB1LPENR; //< 0x50 AHB1 peripheral clock enable in low power mode
                 // register
    [[maybe_unused]] uint32_t
      AHB2LPENR; //< 0x54 AHB2 peripheral clock enable in low power mode
                 // register
    [[maybe_unused]] uint32_t
      AHB3LPENR; //< 0x58 AHB3 peripheral clock enable in low power mode
                 // register
    [[maybe_unused]] uint32_t reserved4; //< reserved
    [[maybe_unused]] uint32_t
      APB1LPENR; //< 0x60 APB1 peripheral clock enable in low power mode
                 // register
    [[maybe_unused]] uint32_t
      APB2LPENR; //< 0x64 APB2 peripheral clock enabled in low power mode
                 // register
    [[maybe_unused]] uint32_t reserved5[2]; //< reserved
    [[maybe_unused]] uint32_t BDCR; //< 0x70 Backup domain control register
    [[maybe_unused]] uint32_t CSR;  //< 0x74 clock control & status register
    [[maybe_unused]] uint32_t reserved6[2]; //< reserved
    [[maybe_unused]] uint32_t
      SSCGR; //< 0x80 spread spectrum clock generation register
    [[maybe_unused]] uint32_t PLLI2SCFGR; //< 0x84 PLLI2S configuration register
    [[maybe_unused]] uint32_t
      PLLSAICFGR; //< 0x88 RCC PLL configuration register
    [[maybe_unused]] uint32_t
      DCKCFGR; //< 0x8C RCC Dedicated Clock Configuration Register
  };

  struct [[maybe_unused]] CR
  {
    [[maybe_unused]] constexpr static uint8_t PLLSAIRDY[]{
      29,
      1
    }; //< PLLI2S clock ready flag
    [[maybe_unused]] constexpr static uint8_t PLLSAION[]{
      28,
      1
    }; //< PLLI2S clock ready flag
    [[maybe_unused]] constexpr static uint8_t PLLI2SRDY[]{
      27,
      1
    }; //< PLLI2S clock ready flag
    [[maybe_unused]] constexpr static uint8_t PLLI2SON[]{ 26,
                                                          1 }; //< PLLI2S enable
    [[maybe_unused]] constexpr static uint8_t PLLRDY[]{
      25,
      1
    }; //< Main PLL (PLL) clock ready flag
    [[maybe_unused]] constexpr static uint8_t PLLON[]{
      24,
      1
    }; //< Main PLL (PLL) enable
    [[maybe_unused]] constexpr static uint8_t CSSON[]{
      19,
      1
    }; //< Clock security system enable
    [[maybe_unused]] constexpr static uint8_t HSEBYP[]{
      18,
      1
    }; //< HSE clock bypass
    [[maybe_unused]] constexpr static uint8_t HSERDY[]{
      17,
      1
    }; //< HSE clock ready flag
    [[maybe_unused]] constexpr static uint8_t HSEON[]{ 16,
                                                       1 }; //< HSE clock enable
    [[maybe_unused]] constexpr static uint8_t HSICAL[]{
      8,
      8
    }; //< Internal high-speed clock calibration
    [[maybe_unused]] constexpr static uint8_t HSITRIM[]{
      3,
      5
    }; //< Internal high-speed clock trimming
    [[maybe_unused]] constexpr static uint8_t HSIRDY[]{
      1,
      1
    }; //< Internal high-speed clock ready flag
    [[maybe_unused]] constexpr static uint8_t HSION[]{
      0,
      1
    }; //< Internal high-speed clock enable
  };

  struct [[maybe_unused]] PLLCFGR
  {
    [[maybe_unused]] constexpr static uint8_t PLLQ[]{
      24,
      4
    }; //< Main PLL (PLL) division factor for USB OTG FS, SDIO and random number
       // generator clocks
    [[maybe_unused]] constexpr static uint8_t PLLSRC[]{
      22,
      1
    }; //< Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
    [[maybe_unused]] constexpr static uint8_t PLLP[]{
      16,
      2
    }; //< Main PLL (PLL) division factor for main system clock
    [[maybe_unused]] constexpr static uint8_t PLLN[]{
      6,
      9
    }; //< Main PLL (PLL) multiplication factor for VCO
    [[maybe_unused]] constexpr static uint8_t PLLM[]{
      0,
      6
    }; //< Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input
       // clock
  };

  struct [[maybe_unused]] CFGR
  {
    [[maybe_unused]] constexpr static uint8_t MCO2[]{
      30,
      2
    }; //< Microcontroller clock output 2
    [[maybe_unused]] constexpr static uint8_t MCO2PRE[]{ 27,
                                                         3 }; //< MCO2 prescaler
    [[maybe_unused]] constexpr static uint8_t MCO1PRE[]{ 24,
                                                         3 }; //< MCO1 prescaler
    [[maybe_unused]] constexpr static uint8_t I2SSRC[]{
      23,
      1
    }; //< I2S clock selection
    [[maybe_unused]] constexpr static uint8_t MCO1[]{
      21,
      2
    }; //< Microcontroller clock output 1
    [[maybe_unused]] constexpr static uint8_t RTCPRE[]{
      16,
      5
    }; //< HSE division factor for RTC clock
    [[maybe_unused]] constexpr static uint8_t PPRE2[]{
      13,
      3
    }; //< APB high-speed prescaler (APB2)
    [[maybe_unused]] constexpr static uint8_t PPRE1[]{
      10,
      3
    }; //< APB Low speed prescaler (APB1)
    [[maybe_unused]] constexpr static uint8_t HPRE[]{ 4, 4 }; //< AHB prescaler
    [[maybe_unused]] constexpr static uint8_t SWS[]{
      2,
      2
    }; //< System clock switch status
    [[maybe_unused]] constexpr static uint8_t SW[]{ 0,
                                                    2 }; //< System clock switch
  };

  struct [[maybe_unused]] CIR
  {
    [[maybe_unused]] constexpr static uint8_t CSSC[]{
      23,
      1
    }; //< Clock security system interrupt clear
    [[maybe_unused]] constexpr static uint8_t PLLI2SRDYC[]{
      21,
      1
    }; //< PLLI2S ready interrupt clear
    [[maybe_unused]] constexpr static uint8_t PLLRDYC[]{
      20,
      1
    }; //< Main PLL(PLL) ready interrupt clear
    [[maybe_unused]] constexpr static uint8_t HSERDYC[]{
      19,
      1
    }; //< HSE ready interrupt clear
    [[maybe_unused]] constexpr static uint8_t HSIRDYC[]{
      18,
      1
    }; //< HSI ready interrupt clear
    [[maybe_unused]] constexpr static uint8_t LSERDYC[]{
      17,
      1
    }; //< LSE ready interrupt clear
    [[maybe_unused]] constexpr static uint8_t LSIRDYC[]{
      16,
      1
    }; //< LSI ready interrupt clear
    [[maybe_unused]] constexpr static uint8_t PLLI2SRDYIE[]{
      13,
      1
    }; //< PLLI2S ready interrupt enable
    [[maybe_unused]] constexpr static uint8_t PLLRDYIE[]{
      12,
      1
    }; //< Main PLL (PLL) ready interrupt enable
    [[maybe_unused]] constexpr static uint8_t HSERDYIE[]{
      11,
      1
    }; //< HSE ready interrupt enable
    [[maybe_unused]] constexpr static uint8_t HSIRDYIE[]{
      10,
      1
    }; //< HSI ready interrupt enable
    [[maybe_unused]] constexpr static uint8_t LSERDYIE[]{
      9,
      1
    }; //< LSE ready interrupt enable
    [[maybe_unused]] constexpr static uint8_t LSIRDYIE[]{
      8,
      1
    }; //< LSI ready interrupt enable
    [[maybe_unused]] constexpr static uint8_t CSSF[]{
      7,
      1
    }; //< Clock security system interrupt flag
    [[maybe_unused]] constexpr static uint8_t PLLI2SRDYF[]{
      5,
      1
    }; //< PLLI2S ready interrupt flag
    [[maybe_unused]] constexpr static uint8_t PLLRDYF[]{
      4,
      1
    }; //< Main PLL (PLL) ready interrupt flag
    [[maybe_unused]] constexpr static uint8_t HSERDYF[]{
      3,
      1
    }; //< HSE ready interrupt flag
    [[maybe_unused]] constexpr static uint8_t HSIRDYF[]{
      2,
      1
    }; //< HSI ready interrupt flag
    [[maybe_unused]] constexpr static uint8_t LSERDYF[]{
      1,
      1
    }; //< LSE ready interrupt flag
    [[maybe_unused]] constexpr static uint8_t LSIRDYF[]{
      0,
      1
    }; //< LSI ready interrupt flag
  };

  struct [[maybe_unused]] AHB1RSTR
  {
    [[maybe_unused]] constexpr static uint8_t OTGHSRST[]{
      29,
      1
    }; //< USB OTG HS module reset
    [[maybe_unused]] constexpr static uint8_t ETHMACRST[]{
      25,
      1
    }; //< Ethernet MAC reset
    [[maybe_unused]] constexpr static uint8_t DMA2RST[]{ 22, 1 }; //< DMA2 reset
    [[maybe_unused]] constexpr static uint8_t DMA1RST[]{ 21, 1 }; //< DMA2 reset
    [[maybe_unused]] constexpr static uint8_t CRCRST[]{ 12, 1 };  //< CRC reset
    [[maybe_unused]] constexpr static uint8_t GPIOIRST[]{
      8,
      1
    }; //< IO port I reset
    [[maybe_unused]] constexpr static uint8_t GPIOHRST[]{
      7,
      1
    }; //< IO port H reset
    [[maybe_unused]] constexpr static uint8_t GPIOGRST[]{
      6,
      1
    }; //< IO port G reset
    [[maybe_unused]] constexpr static uint8_t GPIOFRST[]{
      5,
      1
    }; //< IO port F reset
    [[maybe_unused]] constexpr static uint8_t GPIOERST[]{
      4,
      1
    }; //< IO port E reset
    [[maybe_unused]] constexpr static uint8_t GPIODRST[]{
      3,
      1
    }; //< IO port D reset
    [[maybe_unused]] constexpr static uint8_t GPIOCRST[]{
      2,
      1
    }; //< IO port C reset
    [[maybe_unused]] constexpr static uint8_t GPIOBRST[]{
      1,
      1
    }; //< IO port B reset
    [[maybe_unused]] constexpr static uint8_t GPIOARST[]{
      0,
      1
    }; //< IO port A reset
  };

  struct [[maybe_unused]] AHB2RSTR
  {
    [[maybe_unused]] constexpr static uint8_t OTGFSRST[]{
      7,
      1
    }; //< USB OTG FS module reset
    [[maybe_unused]] constexpr static uint8_t RNGRST[]{
      6,
      1
    }; //< Random number generator module reset
    [[maybe_unused]] constexpr static uint8_t HSAHRST[]{
      5,
      1
    }; //< Hash module reset
    [[maybe_unused]] constexpr static uint8_t CRYPRST[]{
      4,
      1
    }; //< Cryptographic module reset
    [[maybe_unused]] constexpr static uint8_t DCMIRST[]{
      0,
      1
    }; //< Camera interface reset
  };

  struct [[maybe_unused]] AHB3RSTR
  {
    [[maybe_unused]] constexpr static uint8_t FMCRST[]{
      0,
      1
    }; //< Flexible memory controller module reset
  };

  struct [[maybe_unused]] APB1RSTR
  {
    [[maybe_unused]] constexpr static uint8_t TIM2RST[]{ 0, 1 }; //< TIM2 reset
    [[maybe_unused]] constexpr static uint8_t TIM3RST[]{ 1, 1 }; //< TIM3 reset
    [[maybe_unused]] constexpr static uint8_t TIM4RST[]{ 2, 1 }; //< TIM4 reset
    [[maybe_unused]] constexpr static uint8_t TIM5RST[]{ 3, 1 }; //< TIM5 reset
    [[maybe_unused]] constexpr static uint8_t TIM6RST[]{ 4, 1 }; //< TIM6 reset
    [[maybe_unused]] constexpr static uint8_t TIM7RST[]{ 5, 1 }; //< TIM7 reset
    [[maybe_unused]] constexpr static uint8_t TIM12RST[]{ 6,
                                                          1 }; //< TIM12 reset
    [[maybe_unused]] constexpr static uint8_t TIM13RST[]{ 7,
                                                          1 }; //< TIM13 reset
    [[maybe_unused]] constexpr static uint8_t TIM14RST[]{ 8,
                                                          1 }; //< TIM14 reset
    [[maybe_unused]] constexpr static uint8_t WWDGRST[]{
      11,
      1
    }; //< Window watchdog reset
    [[maybe_unused]] constexpr static uint8_t SPI2RST[]{ 14,
                                                         1 }; //< SPI 2 reset
    [[maybe_unused]] constexpr static uint8_t SPI3RST[]{ 15,
                                                         1 }; //< SPI 3 reset
    [[maybe_unused]] constexpr static uint8_t UART2RST[]{ 17,
                                                          1 }; //< USART 2 reset
    [[maybe_unused]] constexpr static uint8_t UART3RST[]{ 18,
                                                          1 }; //< USART 3 reset
    [[maybe_unused]] constexpr static uint8_t UART4RST[]{ 19,
                                                          1 }; //< USART 4 reset
    [[maybe_unused]] constexpr static uint8_t UART5RST[]{ 20,
                                                          1 }; //< USART 5 reset
    [[maybe_unused]] constexpr static uint8_t I2C1RST[]{ 21,
                                                         1 }; //< I2C 1 reset
    [[maybe_unused]] constexpr static uint8_t I2C2RST[]{ 22,
                                                         1 }; //< I2C 2 reset
    [[maybe_unused]] constexpr static uint8_t I2C3RST[]{ 23, 1 }; //< I2C3 reset
    [[maybe_unused]] constexpr static uint8_t CAN1RST[]{ 25, 1 }; //< CAN1 reset
    [[maybe_unused]] constexpr static uint8_t CAN2RST[]{ 26, 1 }; //< CAN2 reset
    [[maybe_unused]] constexpr static uint8_t PWRRST[]{
      28,
      1
    }; //< Power interface reset
    [[maybe_unused]] constexpr static uint8_t DACRST[]{ 29, 1 }; //< DAC reset
  };

  struct [[maybe_unused]] APB2RSTR
  {
    [[maybe_unused]] constexpr static uint8_t TIM1RST[]{ 0, 1 }; //< TIM1 reset
    [[maybe_unused]] constexpr static uint8_t TIM8RST[]{ 1, 1 }; //< TIM8 reset
    [[maybe_unused]] constexpr static uint8_t USART1RST[]{ 4,
                                                           1 }; //< USART1 reset
    [[maybe_unused]] constexpr static uint8_t USART6RST[]{ 5,
                                                           1 }; //< USART6 reset
    [[maybe_unused]] constexpr static uint8_t ADCRST[]{
      8,
      1
    }; //< ADC interface reset (common to all ADCs)
    [[maybe_unused]] constexpr static uint8_t SDIORST[]{ 11, 1 }; //< SDIO reset
    [[maybe_unused]] constexpr static uint8_t SPI1RST[]{ 12,
                                                         1 }; //< SPI 1 reset
    [[maybe_unused]] constexpr static uint8_t SYSCFGRST[]{
      14,
      1
    }; //< System configuration controller reset
    [[maybe_unused]] constexpr static uint8_t TIM9RST[]{ 16, 1 }; //< TIM9 reset
    [[maybe_unused]] constexpr static uint8_t TIM10RST[]{ 17,
                                                          1 }; //< TIM10 reset
    [[maybe_unused]] constexpr static uint8_t TIM11RST[]{ 18,
                                                          1 }; //< TIM11 reset
  };

  struct [[maybe_unused]] AHB1ENR
  {
    [[maybe_unused]] constexpr static uint8_t OTGHSULPIEN[]{
      30,
      1
    }; //< USB OTG HSULPI clock enable
    [[maybe_unused]] constexpr static uint8_t OTGHSEN[]{
      29,
      1
    }; //< USB OTG HS clock enable
    [[maybe_unused]] constexpr static uint8_t ETHMACPTPEN[]{
      28,
      1
    }; //< Ethernet PTP clock enable
    [[maybe_unused]] constexpr static uint8_t ETHMACRXEN[]{
      27,
      1
    }; //< Ethernet Reception clock enable
    [[maybe_unused]] constexpr static uint8_t ETHMACTXEN[]{
      26,
      1
    }; //< Ethernet Transmission clock enable
    [[maybe_unused]] constexpr static uint8_t ETHMACEN[]{
      25,
      1
    }; //< Ethernet MAC clock enable
    [[maybe_unused]] constexpr static uint8_t DMA2DEN[]{
      23,
      1
    }; //< DMA2D clock enable
    [[maybe_unused]] constexpr static uint8_t DMA2EN[]{
      22,
      1
    }; //< DMA2 clock enable
    [[maybe_unused]] constexpr static uint8_t DMA1EN[]{
      21,
      1
    }; //< DMA1 clock enable
    [[maybe_unused]] constexpr static uint8_t CCMDATARAMEN[]{
      20,
      1
    }; //< CCM data RAM clock enable
    [[maybe_unused]] constexpr static uint8_t BKPSRAMEN[]{
      18,
      1
    }; //< Backup SRAM interface clock enable
    [[maybe_unused]] constexpr static uint8_t CRCEN[]{ 12,
                                                       1 }; //< CRC clock enable
    [[maybe_unused]] constexpr static uint8_t GPIOIEN[]{
      8,
      1
    }; //< IO port I clock enable
    [[maybe_unused]] constexpr static uint8_t GPIOHEN[]{
      7,
      1
    }; //< IO port H clock enable
    [[maybe_unused]] constexpr static uint8_t GPIOGEN[]{
      6,
      1
    }; //< IO port G clock enable
    [[maybe_unused]] constexpr static uint8_t GPIOFEN[]{
      5,
      1
    }; //< IO port F clock enable
    [[maybe_unused]] constexpr static uint8_t GPIOEEN[]{
      4,
      1
    }; //< IO port E clock enable
    [[maybe_unused]] constexpr static uint8_t GPIODEN[]{
      3,
      1
    }; //< IO port D clock enable
    [[maybe_unused]] constexpr static uint8_t GPIOCEN[]{
      2,
      1
    }; //< IO port C clock enable
    [[maybe_unused]] constexpr static uint8_t GPIOBEN[]{
      1,
      1
    }; //< IO port B clock enable
    [[maybe_unused]] constexpr static uint8_t GPIOAEN[]{
      0,
      1
    }; //< IO port A clock enable
  };

  struct [[maybe_unused]] AHB2ENR
  {
    [[maybe_unused]] constexpr static uint8_t OTGFSEN[]{
      7,
      1
    }; //< USB OTG FS clock enable
    [[maybe_unused]] constexpr static uint8_t RNGEN[]{
      6,
      1
    }; //< Random number generator clock enable
    [[maybe_unused]] constexpr static uint8_t HASHEN[]{
      5,
      1
    }; //< Hash modules clock enable
    [[maybe_unused]] constexpr static uint8_t CRYPEN[]{
      4,
      1
    }; //< Cryptographic modules clock enable
    [[maybe_unused]] constexpr static uint8_t DCMIEN[]{
      0,
      1
    }; //< Camera interface enable
  };

  struct [[maybe_unused]] AHB3ENR
  {
    [[maybe_unused]] constexpr static uint8_t FMCEN[]{
      0,
      1
    }; //< Flexible memory controller module clock enable
  };

  struct [[maybe_unused]] APB1ENR
  {
    [[maybe_unused]] constexpr static uint8_t TIM2EN[]{
      0,
      1
    }; //< TIM2 clock enable
    [[maybe_unused]] constexpr static uint8_t TIM3EN[]{
      1,
      1
    }; //< TIM3 clock enable
    [[maybe_unused]] constexpr static uint8_t TIM4EN[]{
      2,
      1
    }; //< TIM4 clock enable
    [[maybe_unused]] constexpr static uint8_t TIM5EN[]{
      3,
      1
    }; //< TIM5 clock enable
    [[maybe_unused]] constexpr static uint8_t TIM6EN[]{
      4,
      1
    }; //< TIM6 clock enable
    [[maybe_unused]] constexpr static uint8_t TIM7EN[]{
      5,
      1
    }; //< TIM7 clock enable
    [[maybe_unused]] constexpr static uint8_t TIM12EN[]{
      6,
      1
    }; //< TIM12 clock enable
    [[maybe_unused]] constexpr static uint8_t TIM13EN[]{
      7,
      1
    }; //< TIM13 clock enable
    [[maybe_unused]] constexpr static uint8_t TIM14EN[]{
      8,
      1
    }; //< TIM14 clock enable
    [[maybe_unused]] constexpr static uint8_t WWDGEN[]{
      11,
      1
    }; //< Window watchdog clock enable
    [[maybe_unused]] constexpr static uint8_t SPI2EN[]{
      14,
      1
    }; //< SPI2 clock enable
    [[maybe_unused]] constexpr static uint8_t SPI3EN[]{
      15,
      1
    }; //< SPI3 clock enable
    [[maybe_unused]] constexpr static uint8_t USART2EN[]{
      17,
      1
    }; //< USART 2 clock enable
    [[maybe_unused]] constexpr static uint8_t USART3EN[]{
      18,
      1
    }; //< USART3 clock enable
    [[maybe_unused]] constexpr static uint8_t UART4EN[]{
      19,
      1
    }; //< UART4 clock enable
    [[maybe_unused]] constexpr static uint8_t UART5EN[]{
      20,
      1
    }; //< UART5 clock enable
    [[maybe_unused]] constexpr static uint8_t I2C1EN[]{
      21,
      1
    }; //< I2C1 clock enable
    [[maybe_unused]] constexpr static uint8_t I2C2EN[]{
      22,
      1
    }; //< I2C2 clock enable
    [[maybe_unused]] constexpr static uint8_t I2C3EN[]{
      23,
      1
    }; //< I2C3 clock enable
    [[maybe_unused]] constexpr static uint8_t CAN1EN[]{
      25,
      1
    }; //< CAN 1 clock enable
    [[maybe_unused]] constexpr static uint8_t CAN2EN[]{
      26,
      1
    }; //< CAN 2 clock enable
    [[maybe_unused]] constexpr static uint8_t PWREN[]{
      28,
      1
    }; //< Power interface clock enable
    [[maybe_unused]] constexpr static uint8_t DACEN[]{
      29,
      1
    }; //< DAC interface clock enable
    [[maybe_unused]] constexpr static uint8_t UART7EN[]{
      30,
      1
    }; //< UART7 clock enable
    [[maybe_unused]] constexpr static uint8_t UART8EN[]{
      31,
      1
    }; //< UART8 clock enable
  };

  struct [[maybe_unused]] APB2ENR
  {
    [[maybe_unused]] constexpr static uint8_t TIM1EN[]{
      0,
      1
    }; //< TIM1 clock enable
    [[maybe_unused]] constexpr static uint8_t TIM8EN[]{
      1,
      1
    }; //< TIM8 clock enable
    [[maybe_unused]] constexpr static uint8_t USART1EN[]{
      4,
      1
    }; //< USART1 clock enable
    [[maybe_unused]] constexpr static uint8_t USART6EN[]{
      5,
      1
    }; //< USART6 clock enable
    [[maybe_unused]] constexpr static uint8_t ADC1EN[]{
      8,
      1
    }; //< ADC1 clock enable
    [[maybe_unused]] constexpr static uint8_t ADC2EN[]{
      9,
      1
    }; //< ADC2 clock enable
    [[maybe_unused]] constexpr static uint8_t ADC3EN[]{
      10,
      1
    }; //< ADC3 clock enable
    [[maybe_unused]] constexpr static uint8_t SDIOEN[]{
      11,
      1
    }; //< SDIO clock enable
    [[maybe_unused]] constexpr static uint8_t SPI1EN[]{
      12,
      1
    }; //< SPI1 clock enable
    [[maybe_unused]] constexpr static uint8_t SPI4EN[]{
      13,
      1
    }; //< SPI4 clock enable
    [[maybe_unused]] constexpr static uint8_t SYSCFGEN[]{
      14,
      1
    }; //< System configuration controller clock enable
    [[maybe_unused]] constexpr static uint8_t TIM9EN[]{
      16,
      1
    }; //< TIM9 clock enable
    [[maybe_unused]] constexpr static uint8_t TIM10EN[]{
      17,
      1
    }; //< TIM10 clock enable
    [[maybe_unused]] constexpr static uint8_t TIM11EN[]{
      18,
      1
    }; //< TIM11 clock enable
    [[maybe_unused]] constexpr static uint8_t SPI5EN[]{
      20,
      1
    }; //< SPI5 clock enable
    [[maybe_unused]] constexpr static uint8_t SPI6EN[]{
      21,
      1
    }; //< SPI6 clock enable
    [[maybe_unused]] constexpr static uint8_t LTDCEN[]{
      26,
      1
    }; //< LTDC clock enable
  };

  struct [[maybe_unused]] AHB1LPENR
  {
    [[maybe_unused]] constexpr static uint8_t GPIOALPEN[]{
      0,
      1
    }; //< IO port A clock enable during sleep mode
    [[maybe_unused]] constexpr static uint8_t GPIOBLPEN[]{
      1,
      1
    }; //< IO port B clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t GPIOCLPEN[]{
      2,
      1
    }; //< IO port C clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t GPIODLPEN[]{
      3,
      1
    }; //< IO port D clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t GPIOELPEN[]{
      4,
      1
    }; //< IO port E clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t GPIOFLPEN[]{
      5,
      1
    }; //< IO port F clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t GPIOGLPEN[]{
      6,
      1
    }; //< IO port G clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t GPIOHLPEN[]{
      7,
      1
    }; //< IO port H clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t GPIOILPEN[]{
      8,
      1
    }; //< IO port I clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t CRCLPEN[]{
      12,
      1
    }; //< CRC clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t FLITFLPEN[]{
      15,
      1
    }; //< Flash interface clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t SRAM1LPEN[]{
      16,
      1
    }; //< SRAM 1interface clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t SRAM2LPEN[]{
      17,
      1
    }; //< SRAM 2 interface clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t BKPSRAMLPEN[]{
      18,
      1
    }; //< Backup SRAM interface clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t DMA1LPEN[]{
      21,
      1
    }; //< DMA1 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t DMA2LPEN[]{
      22,
      1
    }; //< DMA2 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t ETHMACLPEN[]{
      25,
      1
    }; //< Ethernet MAC clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t ETHMACTXLPEN[]{
      26,
      1
    }; //< Ethernet transmission clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t ETHMACRXLPEN[]{
      27,
      1
    }; //< Ethernet reception clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t ETHMACPTPLPEN[]{
      28,
      1
    }; //< Ethernet PTP clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t OTGHSLPEN[]{
      29,
      1
    }; //< USB OTG HS clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t OTGHSULPILPEN[]{
      30,
      1
    }; //< USB OTG HS ULPI clock enable during Sleep mode
  };

  struct [[maybe_unused]] AHB2LPENR
  {
    [[maybe_unused]] constexpr static uint8_t OTGFSLPEN[]{
      7,
      1
    }; //< USB OTG FS clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t RNGLPEN[]{
      6,
      1
    }; //< Random number generator clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t HASHLPEN[]{
      5,
      1
    }; //< Hash modules clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t CRYPLPEN[]{
      4,
      1
    }; //< Cryptography modules clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t DCMILPEN[]{
      0,
      1
    }; //< Camera interface enable during Sleep mode
  };

  struct [[maybe_unused]] AHB3LPENR
  {
    [[maybe_unused]] constexpr static uint8_t FMCLPEN[]{
      0,
      1
    }; //< Flexible memory controller module clock enable during Sleep mode
  };

  struct [[maybe_unused]] APB1LPENR
  {
    [[maybe_unused]] constexpr static uint8_t TIM2LPEN[]{
      0,
      1
    }; //< TIM2 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t TIM3LPEN[]{
      1,
      1
    }; //< TIM3 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t TIM4LPEN[]{
      2,
      1
    }; //< TIM4 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t TIM5LPEN[]{
      3,
      1
    }; //< TIM5 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t TIM6LPEN[]{
      4,
      1
    }; //< TIM6 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t TIM7LPEN[]{
      5,
      1
    }; //< TIM7 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t TIM12LPEN[]{
      6,
      1
    }; //< TIM12 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t TIM13LPEN[]{
      7,
      1
    }; //< TIM13 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t TIM14LPEN[]{
      8,
      1
    }; //< TIM14 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t WWDGLPEN[]{
      11,
      1
    }; //< Window watchdog clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t SPI2LPEN[]{
      14,
      1
    }; //< SPI2 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t SPI3LPEN[]{
      15,
      1
    }; //< SPI3 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t USART2LPEN[]{
      17,
      1
    }; //< USART2 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t USART3LPEN[]{
      18,
      1
    }; //< USART3 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t UART4LPEN[]{
      19,
      1
    }; //< UART4 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t UART5LPEN[]{
      20,
      1
    }; //< UART5 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t I2C1LPEN[]{
      21,
      1
    }; //< I2C1 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t I2C2LPEN[]{
      22,
      1
    }; //< I2C2 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t I2C3LPEN[]{
      23,
      1
    }; //< I2C3 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t CAN1LPEN[]{
      25,
      1
    }; //< CAN 1 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t CAN2LPEN[]{
      26,
      1
    }; //< CAN 2 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t PWRLPEN[]{
      28,
      1
    }; //< Power interface clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t DACLPEN[]{
      29,
      1
    }; //< DAC interface clock enable during Sleep mode
  };

  struct [[maybe_unused]] APB2LPENR
  {
    [[maybe_unused]] constexpr static uint8_t TIM1LPEN[]{
      0,
      1
    }; //< TIM1 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t TIM8LPEN[]{
      1,
      1
    }; //< TIM8 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t USART1LPEN[]{
      4,
      1
    }; //< USART1 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t USART6LPEN[]{
      5,
      1
    }; //< USART6 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t ADC1LPEN[]{
      8,
      1
    }; //< ADC1 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t ADC2LPEN[]{
      9,
      1
    }; //< ADC2 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t ADC3LPEN[]{
      10,
      1
    }; //< ADC 3 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t SDIOLPEN[]{
      11,
      1
    }; //< SDIO clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t SPI1LPEN[]{
      12,
      1
    }; //< SPI 1 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t SYSCFGLPEN[]{
      14,
      1
    }; //< System configuration controller clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t TIM9LPEN[]{
      16,
      1
    }; //< TIM9 clock enable during sleep mode
    [[maybe_unused]] constexpr static uint8_t TIM10LPEN[]{
      17,
      1
    }; //< TIM10 clock enable during Sleep mode
    [[maybe_unused]] constexpr static uint8_t TIM11LPEN[]{
      18,
      1
    }; //< TIM11 clock enable during Sleep mode
  };

  struct [[maybe_unused]] BDCR
  {
    [[maybe_unused]] constexpr static uint8_t BDRST[]{
      16,
      1
    }; //< Backup domain software reset
    [[maybe_unused]] constexpr static uint8_t RTCEN[]{ 15,
                                                       1 }; //< RTC clock enable
    [[maybe_unused]] constexpr static uint8_t RTCSEL[]{
      8,
      2
    }; //< RTC clock source selection
    [[maybe_unused]] constexpr static uint8_t LSEBYP[]{
      2,
      1
    }; //< External low-speed oscillator bypass
    [[maybe_unused]] constexpr static uint8_t LSERDY[]{
      1,
      1
    }; //< External low-speed oscillator ready
    [[maybe_unused]] constexpr static uint8_t LSEON[]{
      0,
      1
    }; //< External low-speed oscillator enable
  };

  struct [[maybe_unused]] CSR
  {
    [[maybe_unused]] constexpr static uint8_t LPWRRSTF[]{
      31,
      1
    }; //< Low-power reset flag
    [[maybe_unused]] constexpr static uint8_t WWDGRSTF[]{
      30,
      1
    }; //< Window watchdog reset flag
    [[maybe_unused]] constexpr static uint8_t WDGRSTF[]{
      29,
      1
    }; //< Independent watchdog reset flag
    [[maybe_unused]] constexpr static uint8_t SFTRSTF[]{
      28,
      1
    }; //< Software reset flag
    [[maybe_unused]] constexpr static uint8_t PORRSTF[]{
      27,
      1
    }; //< POR/PDR reset flag
    [[maybe_unused]] constexpr static uint8_t PADRSTF[]{ 26,
                                                         1 }; //< PIN reset flag
    [[maybe_unused]] constexpr static uint8_t BORRSTF[]{ 25,
                                                         1 }; //< BOR reset flag
    [[maybe_unused]] constexpr static uint8_t RMVF[]{ 24,
                                                      1 }; //< Remove reset flag
    [[maybe_unused]] constexpr static uint8_t LSIRDY[]{
      1,
      1
    }; //< Internal low-speed oscillator ready
    [[maybe_unused]] constexpr static uint8_t LSION[]{
      0,
      1
    }; //< Internal low-speed oscillator enable
  };

  struct [[maybe_unused]] SSCGR
  {
    [[maybe_unused]] constexpr static uint8_t SSCGEN[]{
      31,
      1
    }; //< Spread spectrum modulation enable
    [[maybe_unused]] constexpr static uint8_t SPREADSEL[]{
      30,
      1
    }; //< Spread Select
    [[maybe_unused]] constexpr static uint8_t INCSTEP[]{
      13,
      15
    }; //< Incrementation step
    [[maybe_unused]] constexpr static uint8_t MODPER[]{
      0,
      13
    }; //< Modulation period
  };

  struct [[maybe_unused]] PLLI2SCFGR
  {
    [[maybe_unused]] constexpr static uint8_t PLLI2SR[]{
      28,
      3
    }; //< PLLI2S division factor for I2S clocks
    [[maybe_unused]] constexpr static uint8_t PLLI2SQ[]{
      24,
      4
    }; //< PLLI2S division factor for SAI1 clock
    [[maybe_unused]] constexpr static uint8_t PLLI2SN[]{
      6,
      9
    }; //< PLLI2S multiplication factor for VCO
  };

  struct [[maybe_unused]] PLLSAICFGR
  {
    [[maybe_unused]] constexpr static uint8_t PLLSAIR[]{
      28,
      3
    }; //< PLLSAI division factor for LCD clock
    [[maybe_unused]] constexpr static uint8_t PLLSAIQ[]{
      24,
      4
    }; //< PLLSAI division factor for SAI1 clock
    [[maybe_unused]] constexpr static uint8_t PLLSAIN[]{
      6,
      9
    }; //< PLLSAI division factor for VCO
  };

  struct [[maybe_unused]] DCKCFGR
  {
    [[maybe_unused]] constexpr static uint8_t PLLI2SDIVQ[]{
      0,
      5
    }; //< PLLI2S division factor for SAI1 clock
    [[maybe_unused]] constexpr static uint8_t PLLSAIDIVQ[]{
      8,
      5
    }; //< PLLSAI division factor for SAI1 clock
    [[maybe_unused]] constexpr static uint8_t PLLSAIDIVR[]{
      16,
      2
    }; //< division factor for LCD_CLK
    [[maybe_unused]] constexpr static uint8_t SAI1ASRC[]{
      20,
      2
    }; //< SAI1-A clock source selection
    [[maybe_unused]] constexpr static uint8_t SAI1BSRC[]{
      22,
      2
    }; //< SAI1-B clock source selection
    [[maybe_unused]] constexpr static uint8_t TIMPRE[]{
      24,
      1
    }; //< Timers clocks prescalers selection
  };

  template<typename T, uint32_t addr>
  struct [[maybe_unused]] AddrPtr
  {
    static constexpr T *ptr = reinterpret_cast<T *>(addr);
  };

  //    constexpr static volatile Regs* r = reinterpret_cast<volatile
  //    Regs*>(base);

  ///
  /// \brief Получение указателя на регистры
  /// \return указатель на регистры
  ///
  static volatile Regs *rg()
  {
    return reinterpret_cast<volatile Regs *>(base);
  }

  ///
  /// \brief Выбор источника тактирования
  /// \param src источник тактирования
  /// \return true если удачно
  ///
  static bool sysClockSelect(SysClockSrc src)
  {
    uint16_t    timeout = timeoutValue;
    SysClockSrc value;

    tl::setRegister(rg()->CFGR, CFGR::SW, static_cast<uint16_t>(src));

    do {
      value = static_cast<SysClockSrc>(tl::getRegField(rg()->CFGR, CFGR::SWS));
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
  /// \param n multiplier
  /// \param m divider
  /// \param q divider for usb
  /// \param p divider for sysclock
  ///
  static void
  pllSet(uint8_t m, uint16_t n, uint8_t q = 4, PllP p = Rcc::PllP::p2)
  {

    uint32_t tmp = 0;
    tl::setRegister(tmp, PLLCFGR::PLLN, n);

    tl::setRegister(rg()->PLLCFGR,
                    PLLCFGR::PLLM,
                    m,
                    PLLCFGR::PLLN,
                    n,
                    PLLCFGR::PLLQ,
                    q,
                    PLLCFGR::PLLP,
                    static_cast<uint32_t>(p));
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Выбор источника тактирования для главной Pll
  /// \param en true - hse, false - hsi
  ///
  static void pllClockSrcSelectHse(bool en)
  {
    tl::setRegister(rg()->PLLCFGR, PLLCFGR::PLLSRC, en);
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Установка параметров главной PLL
  /// \param n multiplier
  /// \param q divider
  /// \param r divider
  ///
  static void pllSaiSet(uint16_t n, uint8_t r, uint8_t q = 4)
  {
    tl::setRegister(rg()->PLLSAICFGR,
                    PLLSAICFGR::PLLSAIR,
                    r,
                    PLLSAICFGR::PLLSAIN,
                    n,
                    PLLSAICFGR::PLLSAIQ,
                    q);
  }

  ///
  /// \brief Установка делителя APB1
  /// \param prescaler делитель
  ///
  static void setAhbPre(AhbPrescaler prescaler)
  {
    tl::setRegister(rg()->CFGR, CFGR::HPRE, static_cast<uint16_t>(prescaler));
  }

  ///
  /// \brief Установка делителя APB1
  /// \param prescaler делитель
  ///
  static void setApb1Pre(ApbPrescaler prescaler)
  {
    tl::setRegister(rg()->CFGR, CFGR::PPRE1, static_cast<uint16_t>(prescaler));
  }

  ///
  /// \brief Установка делителя APB2
  /// \param prescaler делитель
  ///
  static void setApb2Pre(ApbPrescaler prescaler)
  {
    tl::setRegister(rg()->CFGR, CFGR::PPRE2, static_cast<uint16_t>(prescaler));
  }

  ///
  /// \brief Получение коэффициента деления для APB1
  /// \return
  ///
  static uint8_t getApb1Pre()
  {
    return ApbPrescalerToValue[tl::getRegField(rg()->CFGR, CFGR::PPRE1)];
  }

  ///
  /// \brief Получение коэффициента деления для APB2
  /// \return
  ///
  static uint8_t getApb2Pre()
  {
    return ApbPrescalerToValue[tl::getRegField(rg()->CFGR, CFGR::PPRE2)];
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Включение PLL SAI
  /// \param en требуемое состояние
  /// \return true если удачно
  ///
  static bool pllSaiEnable(bool en)
  {
    uint16_t timeout = timeoutValue;

    tl::setRegister(rg()->CR, CR::PLLSAION, en);

    do {

    } while (((tl::getRegField(rg()->CR, CR::PLLSAIRDY) != en)) && (timeout--));

    if (!timeout)
      return false;

    return true;
  }

  ///
  /// \brief Дефолтная конфигурация на 168 МГц
  /// \return
  ///
  static bool defaultConfigPll168()
  {

    clockPwr(true);

    sysClockSelect(SysClockSrc::hsi);

    if (!hseEnable(true))
      return false;

    pllEnable(false);
    pllSet(8, 336, 7); // 168 MHz

    pllClockSrcSelectHse(true);

    if (!pllEnable(true))
      return false;

    // TODO: Flash latency
    Flash::setLatency(6);

    if (!sysClockSelect(SysClockSrc::pll))
      return false;

    setAhbPre(AhbPrescaler::prescaler1);

    systemCoreClock() = 168000000;

    setApb1Pre(ApbPrescaler::prescaler4);
    setApb2Pre(ApbPrescaler::prescaler2);

    pllSaiSet(192, 3);

    if (!pllSaiEnable(true))
      return false;

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

  [[maybe_unused]] static void setLtdcClkDiv(Rcc::PllSaiDivr div)
  {
    tl::setRegister(
      rg()->DCKCFGR, DCKCFGR::PLLSAIDIVR, static_cast<uint16_t>(div));
  }

  [[maybe_unused]] static void rtcEnable(bool en)
  {
    tl::setRegister(rg()->BDCR, BDCR::RTCEN, en);
  }

  [[maybe_unused]] static bool isRtcEnable()
  {
    return (tl::getRegField(rg()->BDCR, BDCR::RTCEN));
  }

  [[maybe_unused]] static void setRtcHseDiv(uint8_t div)
  {
    tl::setRegister(rg()->CFGR, CFGR::RTCPRE, div);
  }

  [[maybe_unused]]  static void setRtcClkSrc(RtcClkSrc src)
  {
    tl::setRegister(rg()->BDCR, BDCR::RTCSEL, static_cast<uint16_t>(src));
  }

  [[maybe_unused]] static void lseEnable(bool en)
  {
    tl::setRegister(rg()->BDCR, BDCR::LSEON, en);
  }

  [[maybe_unused]] static bool lseReady()
  {
    return (tl::getRegField(rg()->BDCR, BDCR::LSERDY));
  }

  [[maybe_unused]] static void lsiEnable(bool en)
  {
    tl::setRegister(rg()->CSR, CSR::LSION, en);
  }

  [[maybe_unused]] static bool lsiReady()
  {
    return (tl::getRegField(rg()->CSR, CSR::LSIRDY));
  }

  [[maybe_unused]] static void rtcReset(bool en)
  {
    tl::setRegister(rg()->BDCR, BDCR::BDRST, en);
  }

  [[maybe_unused]] static void setMco1(Rcc::Mco1Src src, Rcc::McoPrescaler psc)
  {
    tl::setRegister(rg()->CFGR,
                    CFGR::MCO1,
                    static_cast<uint8_t>(src),
                    CFGR::MCO1PRE,
                    static_cast<uint8_t>(psc));
  }

  [[maybe_unused]] static void setMco2(Rcc::Mco2Src src, Rcc::McoPrescaler psc)
  {
    tl::setRegister(rg()->CFGR,
                    CFGR::MCO2,
                    static_cast<uint8_t>(src),
                    CFGR::MCO2PRE,
                    static_cast<uint8_t>(psc));
  }

  // Clock enable functions    static void clockOtghsulpi(bool en) {
  // Utility::setRegister(rg()->AHB1ENR, AHB1ENR::OTGHSULPIEN, en); }
  [[maybe_unused]] static void clockOtgHsUlpi(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::OTGHSULPIEN, en);
  }
  static void clockOtgHs(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::OTGHSEN, en);
  }
  [[maybe_unused]] static void clockEthmacptp(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::ETHMACPTPEN, en);
  }
  [[maybe_unused]] static void clockEthmacrx(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::ETHMACRXEN, en);
  }
  [[maybe_unused]] static void clockEthmactx(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::ETHMACTXEN, en);
  }
  [[maybe_unused]] static void clockEthmac(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::ETHMACEN, en);
  }
  [[maybe_unused]] static void clockDma2d(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::DMA2DEN, en);
  }
  [[maybe_unused]] static void clockDma2(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::DMA2EN, en);
  }
  [[maybe_unused]] static void clockDma1(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::DMA1EN, en);
  }
  [[maybe_unused]] static void clockCcmdataram(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::CCMDATARAMEN, en);
  }
  [[maybe_unused]] static void clockBkpsram(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::BKPSRAMEN, en);
  }
  [[maybe_unused]] static void clockCrc(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::CRCEN, en);
  }
  static void clockGpioI(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOIEN, en);
  }
  static void clockGpioH(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOHEN, en);
  }
  static void clockGpioG(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOGEN, en);
  }
  static void clockGpioF(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOFEN, en);
  }
  static void clockGpioE(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOEEN, en);
  }
  static void clockGpioD(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIODEN, en);
  }
  static void clockGpioC(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOCEN, en);
  }
  static void clockGpioB(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOBEN, en);
  }
  static void clockGpioA(bool en)
  {
    tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOAEN, en);
  }
  static void clockOtgFs(bool en)
  {
    tl::setRegister(rg()->AHB2ENR, AHB2ENR::OTGFSEN, en);
  }
  [[maybe_unused]] static void clockRng(bool en)
  {
    tl::setRegister(rg()->AHB2ENR, AHB2ENR::RNGEN, en);
  }
  [[maybe_unused]] static void clockHash(bool en)
  {
    tl::setRegister(rg()->AHB2ENR, AHB2ENR::HASHEN, en);
  }
  [[maybe_unused]] static void clockCryp(bool en)
  {
    tl::setRegister(rg()->AHB2ENR, AHB2ENR::CRYPEN, en);
  }
  [[maybe_unused]] static void clockDcmi(bool en)
  {
    tl::setRegister(rg()->AHB2ENR, AHB2ENR::DCMIEN, en);
  }
  [[maybe_unused]] static void clockFmc(bool en)
  {
    tl::setRegister(rg()->AHB3ENR, AHB3ENR::FMCEN, en);
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
  [[maybe_unused]] static void clockWwdg(bool en)
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
  [[maybe_unused]] static void clockI2c1(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::I2C1EN, en);
  }
  [[maybe_unused]] static void clockI2c2(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::I2C2EN, en);
  }
  [[maybe_unused]] static void clockI2c3(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::I2C3EN, en);
  }
  [[maybe_unused]] static void clockCan1(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::CAN1EN, en);
  }
  [[maybe_unused]] static void clockCan2(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::CAN2EN, en);
  }
  static void clockPwr(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::PWREN, en);
  }
  [[maybe_unused]] static void clockDac(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::DACEN, en);
  }
  static void clockTim1(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::TIM1EN, en);
  }
  static void clockTim8(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::TIM8EN, en);
  }
  static void clockUsart1(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::USART1EN, en);
  }
  static void clockUsart6(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::USART6EN, en);
  }
  static void clockUsart7(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::UART7EN, en);
  }
  static void clockUsart8(bool en)
  {
    tl::setRegister(rg()->APB1ENR, APB1ENR::UART8EN, en);
  }
  [[maybe_unused]] static void clockAdc1(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::ADC1EN, en);
  }
  [[maybe_unused]] static void clockAdc2(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::ADC2EN, en);
  }
  [[maybe_unused]] static void clockAdc3(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::ADC3EN, en);
  }
  [[maybe_unused]] static void clockSdio(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::SDIOEN, en);
  }
  static void clockSpi1(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::SPI1EN, en);
  }
  static void clockSpi4(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::SPI4EN, en);
  }
  static void clockSyscfg(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::SYSCFGEN, en);
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
  static void clockSpi5(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::SPI5EN, en);
  }
  static void clockSpi6(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::SPI6EN, en);
  }
  [[maybe_unused]] static void clockLtdc(bool en)
  {
    tl::setRegister(rg()->APB2ENR, APB2ENR::LTDCEN, en);
  }

  // Reset functions
  static void resetOtgHs(bool en)
  {
    tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::OTGHSRST, en);
  }
  [[maybe_unused]] static void resetEthmac(bool en)
  {
    tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::ETHMACRST, en);
  }
  [[maybe_unused]] static void resetDma2(bool en)
  {
    tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::DMA2RST, en);
  }
  [[maybe_unused]] static void resetDma1(bool en)
  {
    tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::DMA1RST, en);
  }
  [[maybe_unused]] static void resetCrc(bool en)
  {
    tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::CRCRST, en);
  }
  [[maybe_unused]] static void resetGpioi(bool en)
  {
    tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOIRST, en);
  }
  [[maybe_unused]] static void resetGpioh(bool en)
  {
    tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOHRST, en);
  }
  [[maybe_unused]] static void resetGpiog(bool en)
  {
    tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOGRST, en);
  }
  [[maybe_unused]] static void resetGpiof(bool en)
  {
    tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOFRST, en);
  }
  [[maybe_unused]] static void resetGpioe(bool en)
  {
    tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOERST, en);
  }
  [[maybe_unused]] static void resetGpiod(bool en)
  {
    tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIODRST, en);
  }
  [[maybe_unused]] static void resetGpioc(bool en)
  {
    tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOCRST, en);
  }
  [[maybe_unused]] static void resetGpiob(bool en)
  {
    tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOBRST, en);
  }
  [[maybe_unused]] static void resetGpioa(bool en)
  {
    tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOARST, en);
  }
  [[maybe_unused]] static void resetOtgFs(bool en)
  {
    tl::setRegister(rg()->AHB2RSTR, AHB2RSTR::OTGFSRST, en);
  }
  [[maybe_unused]] static void resetRng(bool en)
  {
    tl::setRegister(rg()->AHB2RSTR, AHB2RSTR::RNGRST, en);
  }
  [[maybe_unused]] static void resetHsah(bool en)
  {
    tl::setRegister(rg()->AHB2RSTR, AHB2RSTR::HSAHRST, en);
  }
  [[maybe_unused]] static void resetCryp(bool en)
  {
    tl::setRegister(rg()->AHB2RSTR, AHB2RSTR::CRYPRST, en);
  }
  [[maybe_unused]] static void resetDcmi(bool en)
  {
    tl::setRegister(rg()->AHB2RSTR, AHB2RSTR::DCMIRST, en);
  }
  [[maybe_unused]] static void resetFmc(bool en)
  {
    tl::setRegister(rg()->AHB3RSTR, AHB3RSTR::FMCRST, en);
  }
  [[maybe_unused]] static void resetTim2(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM2RST, en);
  }
  [[maybe_unused]] static void resetTim3(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM3RST, en);
  }
  [[maybe_unused]] static void resetTim4(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM4RST, en);
  }
  [[maybe_unused]] static void resetTim5(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM5RST, en);
  }
  [[maybe_unused]] static void resetTim6(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM6RST, en);
  }
  [[maybe_unused]] static void resetTim7(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM7RST, en);
  }
  [[maybe_unused]] static void resetTim12(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM12RST, en);
  }
  [[maybe_unused]] static void resetTim13(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM13RST, en);
  }
  [[maybe_unused]] static void resetTim14(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM14RST, en);
  }
  [[maybe_unused]] static void resetWwdg(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::WWDGRST, en);
  }
  [[maybe_unused]] static void resetSpi2(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::SPI2RST, en);
  }
  [[maybe_unused]] static void resetSpi3(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::SPI3RST, en);
  }
  [[maybe_unused]] static void resetUart2(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::UART2RST, en);
  }
  [[maybe_unused]] static void resetUart3(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::UART3RST, en);
  }
  [[maybe_unused]] static void resetUart4(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::UART4RST, en);
  }
  [[maybe_unused]] static void resetUart5(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::UART5RST, en);
  }
  [[maybe_unused]] static void resetI2c1(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::I2C1RST, en);
  }
  [[maybe_unused]] static void resetI2c2(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::I2C2RST, en);
  }
  [[maybe_unused]] static void resetI2c3(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::I2C3RST, en);
  }
  [[maybe_unused]] static void resetCan1(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::CAN1RST, en);
  }
  [[maybe_unused]] static void resetCan2(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::CAN2RST, en);
  }
  [[maybe_unused]] static void resetPwr(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::PWRRST, en);
  }
  [[maybe_unused]] static void resetDac(bool en)
  {
    tl::setRegister(rg()->APB1RSTR, APB1RSTR::DACRST, en);
  }
  [[maybe_unused]] static void resetTim1(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM1RST, en);
  }
  [[maybe_unused]] static void resetTim8(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM8RST, en);
  }
  [[maybe_unused]] static void resetUsart1(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::USART1RST, en);
  }
  [[maybe_unused]] static void resetUsart6(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::USART6RST, en);
  }
  [[maybe_unused]] static void resetAdc(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::ADCRST, en);
  }
  [[maybe_unused]] static void resetSdio(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::SDIORST, en);
  }
  [[maybe_unused]] static void resetSpi1(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::SPI1RST, en);
  }
  [[maybe_unused]] static void resetSyscfg(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::SYSCFGRST, en);
  }
  [[maybe_unused]] static void resetTim9(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM9RST, en);
  }
  [[maybe_unused]] static void resetTim10(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM10RST, en);
  }
  [[maybe_unused]] static void resetTim11(bool en)
  {
    tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM11RST, en);
  }
};

#endif // RCC_H
