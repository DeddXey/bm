#ifndef RCC_H
#define RCC_H

#include "flash.h"
#include "utility.h"
#include <cstdint>

struct Rcc {

    constexpr static uint32_t base = 0x40023800;
    constexpr static uint32_t interrupt = 5;
    constexpr static uint16_t  timeoutValue = 0xffff;

    enum class PllP : uint8_t {
        p2 = 0b00,
        p4 = 0b01,
        p6 = 0b10,
        p8 = 0b11,
    };

    enum class SysClockSrc : uint8_t {
        hsi = 0b00,
        hse = 0b01,
        pll = 0b10,
    };

    enum class ApbPrescaler : uint8_t {
        prescaler1 = 0b000,
        prescaler2 = 0b100,
        prescaler4 = 0b101,
        prescaler8 = 0b110,
        prescaler16 = 0b111,
    };

    constexpr static uint8_t ApbPrescalerToValue[] {1, 1, 1, 1,
        2, 4, 8, 16};

    enum class McoPrescaler : uint8_t {
        prescaler1 = 0b000,
        prescaler2 = 0b100,
        prescaler3 = 0b101,
        prescaler4 = 0b110,
        prescaler5 = 0b111,
    };

    enum class Mco1Src : uint8_t {
        hsi = 0b00,
        lse = 0b01,
        hse = 0b10,
        pll = 0b11,
    };
    enum class Mco2Src : uint8_t {
        sysclk = 0b00,
        pll2s = 0b01,
        hse = 0b10,
        pll = 0b11,
    };

    enum class PllSaiDivr : uint8_t {
        divr2 = 0b000,
        divr4 = 0b01,
        divr8 = 0b10,
        divr16 = 0b11,

    };

    enum class RtcClkSrc : uint8_t {
        no   = 0b00,
        lse  = 0b01,
        lsi  = 0b10,
        hse  = 0b11
    };

    struct Regs {
         uint32_t CR; 	//< 0x0 clock control register
         uint32_t PLLCFGR; 	//< 0x4 PLL configuration register
         uint32_t CFGR; 	//< 0x8 clock configuration register
         uint32_t CIR; 	//< 0xC clock interrupt register
         uint32_t AHB1RSTR; 	//< 0x10 AHB1 peripheral reset register
         uint32_t AHB2RSTR; 	//< 0x14 AHB2 peripheral reset register
         uint32_t AHB3RSTR; 	//< 0x18 AHB3 peripheral reset register
         uint32_t reserved0; 	//< reserved
         uint32_t APB1RSTR; 	//< 0x20 APB1 peripheral reset register
         uint32_t APB2RSTR; 	//< 0x24 APB2 peripheral reset register
         uint32_t reserved1[2]; 	//< reserved
         uint32_t AHB1ENR; 	//< 0x30 AHB1 peripheral clock register
         uint32_t AHB2ENR; 	//< 0x34 AHB2 peripheral clock enable register
         uint32_t AHB3ENR; 	//< 0x38 AHB3 peripheral clock enable register
         uint32_t reserved2; 	//< reserved
         uint32_t APB1ENR; 	//< 0x40 APB1 peripheral clock enable register
         uint32_t APB2ENR; 	//< 0x44 APB2 peripheral clock enable register
         uint32_t reserved3[2]; 	//< reserved
         uint32_t AHB1LPENR; 	//< 0x50 AHB1 peripheral clock enable in low power mode register
         uint32_t AHB2LPENR; 	//< 0x54 AHB2 peripheral clock enable in low power mode register
         uint32_t AHB3LPENR; 	//< 0x58 AHB3 peripheral clock enable in low power mode register
         uint32_t reserved4; 	//< reserved
         uint32_t APB1LPENR; 	//< 0x60 APB1 peripheral clock enable in low power mode register
         uint32_t APB2LPENR; 	//< 0x64 APB2 peripheral clock enabled in low power mode register
         uint32_t reserved5[2]; 	//< reserved
         uint32_t BDCR; 	//< 0x70 Backup domain control register
         uint32_t CSR; 	//< 0x74 clock control & status register
         uint32_t reserved6[2]; 	//< reserved
         uint32_t SSCGR; 	//< 0x80 spread spectrum clock generation register
         uint32_t PLLI2SCFGR; 	//< 0x84 PLLI2S configuration register
         uint32_t PLLSAICFGR; 	//< 0x88 RCC PLL configuration register
         uint32_t DCKCFGR; 	//< 0x8C RCC Dedicated Clock Configuration Register
    };

    struct CR {
        constexpr static uint8_t PLLSAIRDY[]{ 29, 1 }; 	//< PLLI2S clock ready flag
        constexpr static uint8_t PLLSAION[]{ 28, 1 }; 	//< PLLI2S clock ready flag
        constexpr static uint8_t PLLI2SRDY[]{ 27, 1 }; 	//< PLLI2S clock ready flag
        constexpr static uint8_t PLLI2SON[]{ 26, 1 }; 	//< PLLI2S enable
        constexpr static uint8_t PLLRDY[]{ 25, 1 }; 	//< Main PLL (PLL) clock ready flag
        constexpr static uint8_t PLLON[]{ 24, 1 }; 	//< Main PLL (PLL) enable
        constexpr static uint8_t CSSON[]{ 19, 1 }; 	//< Clock security system enable
        constexpr static uint8_t HSEBYP[]{ 18, 1 }; 	//< HSE clock bypass
        constexpr static uint8_t HSERDY[]{ 17, 1 }; 	//< HSE clock ready flag
        constexpr static uint8_t HSEON[]{ 16, 1 }; 	//< HSE clock enable
        constexpr static uint8_t HSICAL[]{ 8, 8 }; 	//< Internal high-speed clock calibration
        constexpr static uint8_t HSITRIM[]{ 3, 5 }; 	//< Internal high-speed clock trimming
        constexpr static uint8_t HSIRDY[]{ 1, 1 }; 	//< Internal high-speed clock ready flag
        constexpr static uint8_t HSION[]{ 0, 1 }; 	//< Internal high-speed clock enable
    };

    struct PLLCFGR {
        constexpr static uint8_t PLLQ[]{ 24, 4 }; 	//< Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks
        constexpr static uint8_t PLLSRC[]{ 22, 1 }; 	//< Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
        constexpr static uint8_t PLLP[]{ 16, 2 }; 	//< Main PLL (PLL) division factor for main system clock
        constexpr static uint8_t PLLN[]{ 6, 9 }; 	//< Main PLL (PLL) multiplication factor for VCO
        constexpr static uint8_t PLLM[]{ 0, 6 }; 	//< Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock
    };

    struct CFGR {
        constexpr static uint8_t MCO2[]{ 30, 2 }; 	//< Microcontroller clock output 2
        constexpr static uint8_t MCO2PRE[]{ 27, 3 }; 	//< MCO2 prescaler
        constexpr static uint8_t MCO1PRE[]{ 24, 3 }; 	//< MCO1 prescaler
        constexpr static uint8_t I2SSRC[]{ 23, 1 }; 	//< I2S clock selection
        constexpr static uint8_t MCO1[]{ 21, 2 }; 	//< Microcontroller clock output 1
        constexpr static uint8_t RTCPRE[]{ 16, 5 }; 	//< HSE division factor for RTC clock
        constexpr static uint8_t PPRE2[]{ 13, 3 }; 	//< APB high-speed prescaler (APB2)
        constexpr static uint8_t PPRE1[]{ 10, 3 }; 	//< APB Low speed prescaler (APB1)
        constexpr static uint8_t HPRE[]{ 4, 4 }; 	//< AHB prescaler
        constexpr static uint8_t SWS[]{ 2, 2 }; 	//< System clock switch status
        constexpr static uint8_t SW[]{ 0, 2 }; 	//< System clock switch
    };

    struct CIR {
        constexpr static uint8_t CSSC[]{ 23, 1 }; 	//< Clock security system interrupt clear
        constexpr static uint8_t PLLI2SRDYC[]{ 21, 1 }; 	//< PLLI2S ready interrupt clear
        constexpr static uint8_t PLLRDYC[]{ 20, 1 }; 	//< Main PLL(PLL) ready interrupt clear
        constexpr static uint8_t HSERDYC[]{ 19, 1 }; 	//< HSE ready interrupt clear
        constexpr static uint8_t HSIRDYC[]{ 18, 1 }; 	//< HSI ready interrupt clear
        constexpr static uint8_t LSERDYC[]{ 17, 1 }; 	//< LSE ready interrupt clear
        constexpr static uint8_t LSIRDYC[]{ 16, 1 }; 	//< LSI ready interrupt clear
        constexpr static uint8_t PLLI2SRDYIE[]{ 13, 1 }; 	//< PLLI2S ready interrupt enable
        constexpr static uint8_t PLLRDYIE[]{ 12, 1 }; 	//< Main PLL (PLL) ready interrupt enable
        constexpr static uint8_t HSERDYIE[]{ 11, 1 }; 	//< HSE ready interrupt enable
        constexpr static uint8_t HSIRDYIE[]{ 10, 1 }; 	//< HSI ready interrupt enable
        constexpr static uint8_t LSERDYIE[]{ 9, 1 }; 	//< LSE ready interrupt enable
        constexpr static uint8_t LSIRDYIE[]{ 8, 1 }; 	//< LSI ready interrupt enable
        constexpr static uint8_t CSSF[]{ 7, 1 }; 	//< Clock security system interrupt flag
        constexpr static uint8_t PLLI2SRDYF[]{ 5, 1 }; 	//< PLLI2S ready interrupt flag
        constexpr static uint8_t PLLRDYF[]{ 4, 1 }; 	//< Main PLL (PLL) ready interrupt flag
        constexpr static uint8_t HSERDYF[]{ 3, 1 }; 	//< HSE ready interrupt flag
        constexpr static uint8_t HSIRDYF[]{ 2, 1 }; 	//< HSI ready interrupt flag
        constexpr static uint8_t LSERDYF[]{ 1, 1 }; 	//< LSE ready interrupt flag
        constexpr static uint8_t LSIRDYF[]{ 0, 1 }; 	//< LSI ready interrupt flag
    };

    struct AHB1RSTR {
        constexpr static uint8_t OTGHSRST[]{ 29, 1 }; 	//< USB OTG HS module reset
        constexpr static uint8_t ETHMACRST[]{ 25, 1 }; 	//< Ethernet MAC reset
        constexpr static uint8_t DMA2RST[]{ 22, 1 }; 	//< DMA2 reset
        constexpr static uint8_t DMA1RST[]{ 21, 1 }; 	//< DMA2 reset
        constexpr static uint8_t CRCRST[]{ 12, 1 }; 	//< CRC reset
        constexpr static uint8_t GPIOIRST[]{ 8, 1 }; 	//< IO port I reset
        constexpr static uint8_t GPIOHRST[]{ 7, 1 }; 	//< IO port H reset
        constexpr static uint8_t GPIOGRST[]{ 6, 1 }; 	//< IO port G reset
        constexpr static uint8_t GPIOFRST[]{ 5, 1 }; 	//< IO port F reset
        constexpr static uint8_t GPIOERST[]{ 4, 1 }; 	//< IO port E reset
        constexpr static uint8_t GPIODRST[]{ 3, 1 }; 	//< IO port D reset
        constexpr static uint8_t GPIOCRST[]{ 2, 1 }; 	//< IO port C reset
        constexpr static uint8_t GPIOBRST[]{ 1, 1 }; 	//< IO port B reset
        constexpr static uint8_t GPIOARST[]{ 0, 1 }; 	//< IO port A reset
    };

    struct AHB2RSTR {
        constexpr static uint8_t OTGFSRST[]{ 7, 1 }; 	//< USB OTG FS module reset
        constexpr static uint8_t RNGRST[]{ 6, 1 }; 	//< Random number generator module reset
        constexpr static uint8_t HSAHRST[]{ 5, 1 }; 	//< Hash module reset
        constexpr static uint8_t CRYPRST[]{ 4, 1 }; 	//< Cryptographic module reset
        constexpr static uint8_t DCMIRST[]{ 0, 1 }; 	//< Camera interface reset
    };

    struct AHB3RSTR {
        constexpr static uint8_t FMCRST[]{ 0, 1 }; 	//< Flexible memory controller module reset
    };

    struct APB1RSTR {
        constexpr static uint8_t TIM2RST[]{ 0, 1 }; 	//< TIM2 reset
        constexpr static uint8_t TIM3RST[]{ 1, 1 }; 	//< TIM3 reset
        constexpr static uint8_t TIM4RST[]{ 2, 1 }; 	//< TIM4 reset
        constexpr static uint8_t TIM5RST[]{ 3, 1 }; 	//< TIM5 reset
        constexpr static uint8_t TIM6RST[]{ 4, 1 }; 	//< TIM6 reset
        constexpr static uint8_t TIM7RST[]{ 5, 1 }; 	//< TIM7 reset
        constexpr static uint8_t TIM12RST[]{ 6, 1 }; 	//< TIM12 reset
        constexpr static uint8_t TIM13RST[]{ 7, 1 }; 	//< TIM13 reset
        constexpr static uint8_t TIM14RST[]{ 8, 1 }; 	//< TIM14 reset
        constexpr static uint8_t WWDGRST[]{ 11, 1 }; 	//< Window watchdog reset
        constexpr static uint8_t SPI2RST[]{ 14, 1 }; 	//< SPI 2 reset
        constexpr static uint8_t SPI3RST[]{ 15, 1 }; 	//< SPI 3 reset
        constexpr static uint8_t UART2RST[]{ 17, 1 }; 	//< USART 2 reset
        constexpr static uint8_t UART3RST[]{ 18, 1 }; 	//< USART 3 reset
        constexpr static uint8_t UART4RST[]{ 19, 1 }; 	//< USART 4 reset
        constexpr static uint8_t UART5RST[]{ 20, 1 }; 	//< USART 5 reset
        constexpr static uint8_t I2C1RST[]{ 21, 1 }; 	//< I2C 1 reset
        constexpr static uint8_t I2C2RST[]{ 22, 1 }; 	//< I2C 2 reset
        constexpr static uint8_t I2C3RST[]{ 23, 1 }; 	//< I2C3 reset
        constexpr static uint8_t CAN1RST[]{ 25, 1 }; 	//< CAN1 reset
        constexpr static uint8_t CAN2RST[]{ 26, 1 }; 	//< CAN2 reset
        constexpr static uint8_t PWRRST[]{ 28, 1 }; 	//< Power interface reset
        constexpr static uint8_t DACRST[]{ 29, 1 }; 	//< DAC reset
    };

    struct APB2RSTR {
        constexpr static uint8_t TIM1RST[]{ 0, 1 }; 	//< TIM1 reset
        constexpr static uint8_t TIM8RST[]{ 1, 1 }; 	//< TIM8 reset
        constexpr static uint8_t USART1RST[]{ 4, 1 }; 	//< USART1 reset
        constexpr static uint8_t USART6RST[]{ 5, 1 }; 	//< USART6 reset
        constexpr static uint8_t ADCRST[]{ 8, 1 }; 	//< ADC interface reset (common to all ADCs)
        constexpr static uint8_t SDIORST[]{ 11, 1 }; 	//< SDIO reset
        constexpr static uint8_t SPI1RST[]{ 12, 1 }; 	//< SPI 1 reset
        constexpr static uint8_t SYSCFGRST[]{ 14, 1 }; 	//< System configuration controller reset
        constexpr static uint8_t TIM9RST[]{ 16, 1 }; 	//< TIM9 reset
        constexpr static uint8_t TIM10RST[]{ 17, 1 }; 	//< TIM10 reset
        constexpr static uint8_t TIM11RST[]{ 18, 1 }; 	//< TIM11 reset
    };

    struct AHB1ENR {
        constexpr static uint8_t OTGHSULPIEN[]{ 30, 1 }; 	//< USB OTG HSULPI clock enable
        constexpr static uint8_t OTGHSEN[]{ 29, 1 }; 	//< USB OTG HS clock enable
        constexpr static uint8_t ETHMACPTPEN[]{ 28, 1 }; 	//< Ethernet PTP clock enable
        constexpr static uint8_t ETHMACRXEN[]{ 27, 1 }; 	//< Ethernet Reception clock enable
        constexpr static uint8_t ETHMACTXEN[]{ 26, 1 }; 	//< Ethernet Transmission clock enable
        constexpr static uint8_t ETHMACEN[]{ 25, 1 }; 	//< Ethernet MAC clock enable
        constexpr static uint8_t DMA2DEN[]{ 23, 1 }; 	//< DMA2D clock enable
        constexpr static uint8_t DMA2EN[]{ 22, 1 }; 	//< DMA2 clock enable
        constexpr static uint8_t DMA1EN[]{ 21, 1 }; 	//< DMA1 clock enable
        constexpr static uint8_t CCMDATARAMEN[]{ 20, 1 }; 	//< CCM data RAM clock enable
        constexpr static uint8_t BKPSRAMEN[]{ 18, 1 }; 	//< Backup SRAM interface clock enable
        constexpr static uint8_t CRCEN[]{ 12, 1 }; 	//< CRC clock enable
        constexpr static uint8_t GPIOIEN[]{ 8, 1 }; 	//< IO port I clock enable
        constexpr static uint8_t GPIOHEN[]{ 7, 1 }; 	//< IO port H clock enable
        constexpr static uint8_t GPIOGEN[]{ 6, 1 }; 	//< IO port G clock enable
        constexpr static uint8_t GPIOFEN[]{ 5, 1 }; 	//< IO port F clock enable
        constexpr static uint8_t GPIOEEN[]{ 4, 1 }; 	//< IO port E clock enable
        constexpr static uint8_t GPIODEN[]{ 3, 1 }; 	//< IO port D clock enable
        constexpr static uint8_t GPIOCEN[]{ 2, 1 }; 	//< IO port C clock enable
        constexpr static uint8_t GPIOBEN[]{ 1, 1 }; 	//< IO port B clock enable
        constexpr static uint8_t GPIOAEN[]{ 0, 1 }; 	//< IO port A clock enable
    };

    struct AHB2ENR {
        constexpr static uint8_t OTGFSEN[]{ 7, 1 }; 	//< USB OTG FS clock enable
        constexpr static uint8_t RNGEN[]{ 6, 1 }; 	//< Random number generator clock enable
        constexpr static uint8_t HASHEN[]{ 5, 1 }; 	//< Hash modules clock enable
        constexpr static uint8_t CRYPEN[]{ 4, 1 }; 	//< Cryptographic modules clock enable
        constexpr static uint8_t DCMIEN[]{ 0, 1 }; 	//< Camera interface enable
    };

    struct AHB3ENR {
        constexpr static uint8_t FMCEN[]{ 0, 1 }; 	//< Flexible memory controller module clock enable
    };

    struct APB1ENR {
        constexpr static uint8_t TIM2EN[]{ 0, 1 }; 	//< TIM2 clock enable
        constexpr static uint8_t TIM3EN[]{ 1, 1 }; 	//< TIM3 clock enable
        constexpr static uint8_t TIM4EN[]{ 2, 1 }; 	//< TIM4 clock enable
        constexpr static uint8_t TIM5EN[]{ 3, 1 }; 	//< TIM5 clock enable
        constexpr static uint8_t TIM6EN[]{ 4, 1 }; 	//< TIM6 clock enable
        constexpr static uint8_t TIM7EN[]{ 5, 1 }; 	//< TIM7 clock enable
        constexpr static uint8_t TIM12EN[]{ 6, 1 }; 	//< TIM12 clock enable
        constexpr static uint8_t TIM13EN[]{ 7, 1 }; 	//< TIM13 clock enable
        constexpr static uint8_t TIM14EN[]{ 8, 1 }; 	//< TIM14 clock enable
        constexpr static uint8_t WWDGEN[]{ 11, 1 }; 	//< Window watchdog clock enable
        constexpr static uint8_t SPI2EN[]{ 14, 1 }; 	//< SPI2 clock enable
        constexpr static uint8_t SPI3EN[]{ 15, 1 }; 	//< SPI3 clock enable
        constexpr static uint8_t USART2EN[]{ 17, 1 }; 	//< USART 2 clock enable
        constexpr static uint8_t USART3EN[]{ 18, 1 }; 	//< USART3 clock enable
        constexpr static uint8_t UART4EN[]{ 19, 1 }; 	//< UART4 clock enable
        constexpr static uint8_t UART5EN[]{ 20, 1 }; 	//< UART5 clock enable
        constexpr static uint8_t I2C1EN[]{ 21, 1 }; 	//< I2C1 clock enable
        constexpr static uint8_t I2C2EN[]{ 22, 1 }; 	//< I2C2 clock enable
        constexpr static uint8_t I2C3EN[]{ 23, 1 }; 	//< I2C3 clock enable
        constexpr static uint8_t CAN1EN[]{ 25, 1 }; 	//< CAN 1 clock enable
        constexpr static uint8_t CAN2EN[]{ 26, 1 }; 	//< CAN 2 clock enable
        constexpr static uint8_t PWREN[]{ 28, 1 }; 	//< Power interface clock enable
        constexpr static uint8_t DACEN[]{ 29, 1 }; 	//< DAC interface clock enable
		constexpr static uint8_t UART7EN[]{ 30, 1 }; 	//< UART7 clock enable
		constexpr static uint8_t UART8EN[]{ 31, 1 }; 	//< UART8 clock enable
	};

    struct APB2ENR {
        constexpr static uint8_t TIM1EN[]{ 0, 1 }; 	//< TIM1 clock enable
        constexpr static uint8_t TIM8EN[]{ 1, 1 }; 	//< TIM8 clock enable
        constexpr static uint8_t USART1EN[]{ 4, 1 }; 	//< USART1 clock enable
        constexpr static uint8_t USART6EN[]{ 5, 1 }; 	//< USART6 clock enable
        constexpr static uint8_t ADC1EN[]{ 8, 1 }; 	//< ADC1 clock enable
        constexpr static uint8_t ADC2EN[]{ 9, 1 }; 	//< ADC2 clock enable
        constexpr static uint8_t ADC3EN[]{ 10, 1 }; 	//< ADC3 clock enable
        constexpr static uint8_t SDIOEN[]{ 11, 1 }; 	//< SDIO clock enable
        constexpr static uint8_t SPI1EN[]{ 12, 1 }; 	//< SPI1 clock enable
        constexpr static uint8_t SPI4EN[]{ 13, 1 }; 	//< SPI4 clock enable
        constexpr static uint8_t SYSCFGEN[]{ 14, 1 }; 	//< System configuration controller clock enable
        constexpr static uint8_t TIM9EN[]{ 16, 1 }; 	//< TIM9 clock enable
        constexpr static uint8_t TIM10EN[]{ 17, 1 }; 	//< TIM10 clock enable
        constexpr static uint8_t TIM11EN[]{ 18, 1 }; 	//< TIM11 clock enable
        constexpr static uint8_t SPI5EN[]{ 20, 1 }; 	//< SPI5 clock enable
        constexpr static uint8_t SPI6EN[]{ 21, 1 }; 	//< SPI6 clock enable
        constexpr static uint8_t LTDCEN[]{ 26, 1 }; 	//< LTDC clock enable

    };

    struct AHB1LPENR {
        constexpr static uint8_t GPIOALPEN[]{ 0, 1 }; 	//< IO port A clock enable during sleep mode
        constexpr static uint8_t GPIOBLPEN[]{ 1, 1 }; 	//< IO port B clock enable during Sleep mode
        constexpr static uint8_t GPIOCLPEN[]{ 2, 1 }; 	//< IO port C clock enable during Sleep mode
        constexpr static uint8_t GPIODLPEN[]{ 3, 1 }; 	//< IO port D clock enable during Sleep mode
        constexpr static uint8_t GPIOELPEN[]{ 4, 1 }; 	//< IO port E clock enable during Sleep mode
        constexpr static uint8_t GPIOFLPEN[]{ 5, 1 }; 	//< IO port F clock enable during Sleep mode
        constexpr static uint8_t GPIOGLPEN[]{ 6, 1 }; 	//< IO port G clock enable during Sleep mode
        constexpr static uint8_t GPIOHLPEN[]{ 7, 1 }; 	//< IO port H clock enable during Sleep mode
        constexpr static uint8_t GPIOILPEN[]{ 8, 1 }; 	//< IO port I clock enable during Sleep mode
        constexpr static uint8_t CRCLPEN[]{ 12, 1 }; 	//< CRC clock enable during Sleep mode
        constexpr static uint8_t FLITFLPEN[]{ 15, 1 }; 	//< Flash interface clock enable during Sleep mode
        constexpr static uint8_t SRAM1LPEN[]{ 16, 1 }; 	//< SRAM 1interface clock enable during Sleep mode
        constexpr static uint8_t SRAM2LPEN[]{ 17, 1 }; 	//< SRAM 2 interface clock enable during Sleep mode
        constexpr static uint8_t BKPSRAMLPEN[]{ 18, 1 }; 	//< Backup SRAM interface clock enable during Sleep mode
        constexpr static uint8_t DMA1LPEN[]{ 21, 1 }; 	//< DMA1 clock enable during Sleep mode
        constexpr static uint8_t DMA2LPEN[]{ 22, 1 }; 	//< DMA2 clock enable during Sleep mode
        constexpr static uint8_t ETHMACLPEN[]{ 25, 1 }; 	//< Ethernet MAC clock enable during Sleep mode
        constexpr static uint8_t ETHMACTXLPEN[]{ 26, 1 }; 	//< Ethernet transmission clock enable during Sleep mode
        constexpr static uint8_t ETHMACRXLPEN[]{ 27, 1 }; 	//< Ethernet reception clock enable during Sleep mode
        constexpr static uint8_t ETHMACPTPLPEN[]{ 28, 1 }; 	//< Ethernet PTP clock enable during Sleep mode
        constexpr static uint8_t OTGHSLPEN[]{ 29, 1 }; 	//< USB OTG HS clock enable during Sleep mode
        constexpr static uint8_t OTGHSULPILPEN[]{ 30, 1 }; 	//< USB OTG HS ULPI clock enable during Sleep mode
    };

    struct AHB2LPENR {
        constexpr static uint8_t OTGFSLPEN[]{ 7, 1 }; 	//< USB OTG FS clock enable during Sleep mode
        constexpr static uint8_t RNGLPEN[]{ 6, 1 }; 	//< Random number generator clock enable during Sleep mode
        constexpr static uint8_t HASHLPEN[]{ 5, 1 }; 	//< Hash modules clock enable during Sleep mode
        constexpr static uint8_t CRYPLPEN[]{ 4, 1 }; 	//< Cryptography modules clock enable during Sleep mode
        constexpr static uint8_t DCMILPEN[]{ 0, 1 }; 	//< Camera interface enable during Sleep mode
    };

    struct AHB3LPENR {
        constexpr static uint8_t FMCLPEN[]{ 0, 1 }; 	//< Flexible memory controller module clock enable during Sleep mode
    };

    struct APB1LPENR {
        constexpr static uint8_t TIM2LPEN[]{ 0, 1 }; 	//< TIM2 clock enable during Sleep mode
        constexpr static uint8_t TIM3LPEN[]{ 1, 1 }; 	//< TIM3 clock enable during Sleep mode
        constexpr static uint8_t TIM4LPEN[]{ 2, 1 }; 	//< TIM4 clock enable during Sleep mode
        constexpr static uint8_t TIM5LPEN[]{ 3, 1 }; 	//< TIM5 clock enable during Sleep mode
        constexpr static uint8_t TIM6LPEN[]{ 4, 1 }; 	//< TIM6 clock enable during Sleep mode
        constexpr static uint8_t TIM7LPEN[]{ 5, 1 }; 	//< TIM7 clock enable during Sleep mode
        constexpr static uint8_t TIM12LPEN[]{ 6, 1 }; 	//< TIM12 clock enable during Sleep mode
        constexpr static uint8_t TIM13LPEN[]{ 7, 1 }; 	//< TIM13 clock enable during Sleep mode
        constexpr static uint8_t TIM14LPEN[]{ 8, 1 }; 	//< TIM14 clock enable during Sleep mode
        constexpr static uint8_t WWDGLPEN[]{ 11, 1 }; 	//< Window watchdog clock enable during Sleep mode
        constexpr static uint8_t SPI2LPEN[]{ 14, 1 }; 	//< SPI2 clock enable during Sleep mode
        constexpr static uint8_t SPI3LPEN[]{ 15, 1 }; 	//< SPI3 clock enable during Sleep mode
        constexpr static uint8_t USART2LPEN[]{ 17, 1 }; 	//< USART2 clock enable during Sleep mode
        constexpr static uint8_t USART3LPEN[]{ 18, 1 }; 	//< USART3 clock enable during Sleep mode
        constexpr static uint8_t UART4LPEN[]{ 19, 1 }; 	//< UART4 clock enable during Sleep mode
        constexpr static uint8_t UART5LPEN[]{ 20, 1 }; 	//< UART5 clock enable during Sleep mode
        constexpr static uint8_t I2C1LPEN[]{ 21, 1 }; 	//< I2C1 clock enable during Sleep mode
        constexpr static uint8_t I2C2LPEN[]{ 22, 1 }; 	//< I2C2 clock enable during Sleep mode
        constexpr static uint8_t I2C3LPEN[]{ 23, 1 }; 	//< I2C3 clock enable during Sleep mode
        constexpr static uint8_t CAN1LPEN[]{ 25, 1 }; 	//< CAN 1 clock enable during Sleep mode
        constexpr static uint8_t CAN2LPEN[]{ 26, 1 }; 	//< CAN 2 clock enable during Sleep mode
        constexpr static uint8_t PWRLPEN[]{ 28, 1 }; 	//< Power interface clock enable during Sleep mode
        constexpr static uint8_t DACLPEN[]{ 29, 1 }; 	//< DAC interface clock enable during Sleep mode
    };

    struct APB2LPENR {
        constexpr static uint8_t TIM1LPEN[]{ 0, 1 }; 	//< TIM1 clock enable during Sleep mode
        constexpr static uint8_t TIM8LPEN[]{ 1, 1 }; 	//< TIM8 clock enable during Sleep mode
        constexpr static uint8_t USART1LPEN[]{ 4, 1 }; 	//< USART1 clock enable during Sleep mode
        constexpr static uint8_t USART6LPEN[]{ 5, 1 }; 	//< USART6 clock enable during Sleep mode
        constexpr static uint8_t ADC1LPEN[]{ 8, 1 }; 	//< ADC1 clock enable during Sleep mode
        constexpr static uint8_t ADC2LPEN[]{ 9, 1 }; 	//< ADC2 clock enable during Sleep mode
        constexpr static uint8_t ADC3LPEN[]{ 10, 1 }; 	//< ADC 3 clock enable during Sleep mode
        constexpr static uint8_t SDIOLPEN[]{ 11, 1 }; 	//< SDIO clock enable during Sleep mode
        constexpr static uint8_t SPI1LPEN[]{ 12, 1 }; 	//< SPI 1 clock enable during Sleep mode
        constexpr static uint8_t SYSCFGLPEN[]{ 14, 1 }; 	//< System configuration controller clock enable during Sleep mode
        constexpr static uint8_t TIM9LPEN[]{ 16, 1 }; 	//< TIM9 clock enable during sleep mode
        constexpr static uint8_t TIM10LPEN[]{ 17, 1 }; 	//< TIM10 clock enable during Sleep mode
        constexpr static uint8_t TIM11LPEN[]{ 18, 1 }; 	//< TIM11 clock enable during Sleep mode
    };

    struct BDCR {
        constexpr static uint8_t BDRST[]{ 16, 1 }; 	//< Backup domain software reset
        constexpr static uint8_t RTCEN[]{ 15, 1 }; 	//< RTC clock enable
        constexpr static uint8_t RTCSEL[]{ 8, 2 }; 	//< RTC clock source selection
        constexpr static uint8_t LSEBYP[]{ 2, 1 }; 	//< External low-speed oscillator bypass
        constexpr static uint8_t LSERDY[]{ 1, 1 }; 	//< External low-speed oscillator ready
        constexpr static uint8_t LSEON[]{ 0, 1 }; 	//< External low-speed oscillator enable
    };

    struct CSR {
        constexpr static uint8_t LPWRRSTF[]{ 31, 1 }; 	//< Low-power reset flag
        constexpr static uint8_t WWDGRSTF[]{ 30, 1 }; 	//< Window watchdog reset flag
        constexpr static uint8_t WDGRSTF[]{ 29, 1 }; 	//< Independent watchdog reset flag
        constexpr static uint8_t SFTRSTF[]{ 28, 1 }; 	//< Software reset flag
        constexpr static uint8_t PORRSTF[]{ 27, 1 }; 	//< POR/PDR reset flag
        constexpr static uint8_t PADRSTF[]{ 26, 1 }; 	//< PIN reset flag
        constexpr static uint8_t BORRSTF[]{ 25, 1 }; 	//< BOR reset flag
        constexpr static uint8_t RMVF[]{ 24, 1 }; 	//< Remove reset flag
        constexpr static uint8_t LSIRDY[]{ 1, 1 }; 	//< Internal low-speed oscillator ready
        constexpr static uint8_t LSION[]{ 0, 1 }; 	//< Internal low-speed oscillator enable
    };

    struct SSCGR {
        constexpr static uint8_t SSCGEN[]{ 31, 1 }; 	//< Spread spectrum modulation enable
        constexpr static uint8_t SPREADSEL[]{ 30, 1 }; 	//< Spread Select
        constexpr static uint8_t INCSTEP[]{ 13, 15 }; 	//< Incrementation step
        constexpr static uint8_t MODPER[]{ 0, 13 }; 	//< Modulation period
    };

    struct PLLI2SCFGR {
        constexpr static uint8_t PLLI2SR[]{ 28, 3 }; 	//< PLLI2S division factor for I2S clocks
        constexpr static uint8_t PLLI2SQ[]{ 24, 4 }; 	//< PLLI2S division factor for SAI1 clock
        constexpr static uint8_t PLLI2SN[]{ 6, 9 }; 	//< PLLI2S multiplication factor for VCO
    };

    struct PLLSAICFGR {
        constexpr static uint8_t PLLSAIR[]{ 28, 3 }; 	//< PLLSAI division factor for LCD clock
        constexpr static uint8_t PLLSAIQ[]{ 24, 4 }; 	//< PLLSAI division factor for SAI1 clock
        constexpr static uint8_t PLLSAIN[]{ 6, 9 }; 	//< PLLSAI division factor for VCO
    };

    struct DCKCFGR {
        constexpr static uint8_t PLLI2SDIVQ[]{ 0, 5 }; 	//< PLLI2S division factor for SAI1 clock
        constexpr static uint8_t PLLSAIDIVQ[]{ 8, 5 }; 	//< PLLSAI division factor for SAI1 clock
        constexpr static uint8_t PLLSAIDIVR[]{ 16, 2 }; 	//< division factor for LCD_CLK
        constexpr static uint8_t SAI1ASRC[]{ 20, 2 }; 	//< SAI1-A clock source selection
        constexpr static uint8_t SAI1BSRC[]{ 22, 2 }; 	//< SAI1-B clock source selection
        constexpr static uint8_t TIMPRE[]{ 24, 1 }; 	//< Timers clocks prescalers selection
    };


    template<typename T, uint32_t addr>
    struct AddrPtr
    {
        static constexpr T* ptr = reinterpret_cast<T*>(addr);   
    };



//    constexpr static volatile Regs* r = reinterpret_cast<volatile Regs*>(base);

    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    // INLINE constexpr static volatile Regs* rg()
    // {
    //     return reinterpret_cast<volatile Regs*>(base);
    // }
    constexpr static volatile Regs* rg()
    {
        return AddrPtr<Regs, base>::ptr;
    }


    ///---------------------------------------------------------------------
    ///
    /// \brief Выбор источника тактирования
    /// \param src источник тактирования
    /// \return true если удачно
    ///
    INLINE static bool sysClockSelect(SysClockSrc src)
    {
        uint16_t timeout = timeoutValue;
        SysClockSrc  value;

        tl::setRegister(rg()->CFGR, CFGR::SW, static_cast<uint16_t>(src));

        do {
            value = static_cast<SysClockSrc>(tl::getRegField(rg()->CFGR, CFGR::SWS));
            timeout--;

        }while ((value != src) && (timeout != 0));

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
    INLINE static bool hseEnable(bool en)
    {
        uint16_t timeout = timeoutValue;

        tl::setRegister(rg()->CR, CR::HSEON, en);

        do {

        }while (((tl::getRegField(rg()->CR, CR::HSERDY) != en)) && (timeout--));

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
    INLINE static bool pllEnable(bool en)
    {
        uint16_t timeout = timeoutValue;

        tl::setRegister(rg()->CR, CR::PLLON, en);

        do {

        }while (((tl::getRegField(rg()->CR, CR::PLLRDY) != en)) && (timeout--));

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
    INLINE static void pllSet(uint8_t m, uint16_t n, uint8_t q = 4, PllP p = Rcc::PllP::p2)
    {
        tl::setRegister(rg()->PLLCFGR,
                             PLLCFGR::PLLM, m,
                             PLLCFGR::PLLN, n,
                             PLLCFGR::PLLQ, q,
                             PLLCFGR::PLLP, static_cast<uint32_t>(p));
    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Выбор источника тактирования для главной Pll
    /// \param en true - hse, false - hsi
    ///
    INLINE static void pllClockSrcSelectHse(bool en)
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
    INLINE static void pllSaiSet(uint16_t n, uint8_t r, uint8_t q = 4)
    {
        tl::setRegister(rg()->PLLSAICFGR,
                             PLLSAICFGR::PLLSAIR, r,
                             PLLSAICFGR::PLLSAIN, n,
                             PLLSAICFGR::PLLSAIQ, q);
    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Установка делителя APB1
    /// \param prescaler делитель
    ///
    INLINE static void setApb1Pre(ApbPrescaler prescaler)
    {
        tl::setRegister(rg()->CFGR, CFGR::PPRE1, static_cast<uint16_t>(prescaler));
    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Установка делителя APB2
    /// \param prescaler делитель
    ///
    INLINE static void setApb2Pre(ApbPrescaler prescaler)
    {
        tl::setRegister(rg()->CFGR, CFGR::PPRE2, static_cast<uint16_t>(prescaler));
    }

    ///
    /// \brief Получение коэффициента деления для APB1
    /// \return
    ///
    INLINE static uint8_t getApb1Pre()
    {
        return ApbPrescalerToValue[tl::getRegField(rg()->CFGR,
                             CFGR::PPRE1)];
    }

    ///
    /// \brief Получение коэффициента деления для APB2
    /// \return
    ///
    INLINE static uint8_t getApb2Pre()
    {
        return ApbPrescalerToValue[tl::getRegField(rg()->CFGR,
                             CFGR::PPRE2)];
    }




    ///---------------------------------------------------------------------
    ///
    /// \brief Включение PLL SAI
    /// \param en требуемое состояние
    /// \return true если удачно
    ///
    INLINE static bool pllSaiEnable(bool en)
    {
        uint16_t timeout = timeoutValue;

        tl::setRegister(rg()->CR, CR::PLLSAION, en);

        do {

        }while (((tl::getRegField(rg()->CR, CR::PLLSAIRDY) != en)) && (timeout--));

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
        if (!hseEnable(true))
            return false;

        pllSet(8, 336, 7); // 168 MHz

        pllClockSrcSelectHse(true);

        if (!pllEnable(true))
            return false;

        //TODO: Flash latency
        Flash::setLatency(6);

        if (!sysClockSelect(SysClockSrc::pll))
            return false;

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
    INLINE static uint32_t& systemCoreClock()
    {
        static uint32_t sysCoreClock;

        return sysCoreClock;
    }

    INLINE static void setLtdcClkDiv(Rcc::PllSaiDivr div)
    {
        tl::setRegister(rg()->DCKCFGR, DCKCFGR::PLLSAIDIVR, static_cast<uint16_t>(div));
    }

    INLINE static void rtcEnable(bool en)
    {
        tl::setRegister(rg()->BDCR, BDCR::RTCEN, en);
    }

    INLINE static bool isRtcEnable()
    {
        return (tl::getRegField(rg()->BDCR, BDCR::RTCEN));
    }

    INLINE static void setRtcHseDiv(uint8_t div)
    {
        tl::setRegister(rg()->CFGR, CFGR::RTCPRE, div);
    }

    INLINE static void setRtcClkSrc(RtcClkSrc src)
    {
        tl::setRegister(rg()->BDCR, BDCR::RTCSEL, static_cast<uint16_t>(src));
    }


    INLINE static void lseEnable(bool en)
    {
        tl::setRegister(rg()->BDCR, BDCR::LSEON, en);
    }

    INLINE static bool lseReady()
    {
        return (tl::getRegField(rg()->BDCR, BDCR::LSERDY));
    }

    INLINE static void lsiEnable(bool en)
    {
        tl::setRegister(rg()->CSR, CSR::LSION, en);
    }

    INLINE static bool lsiReady()
    {
        return (tl::getRegField(rg()->CSR, CSR::LSIRDY));
    }

    INLINE static void rtcReset(bool en)
    {
        tl::setRegister(rg()->BDCR, BDCR::BDRST, en);
    }

    INLINE static void setMco1(Rcc::Mco1Src src, Rcc::McoPrescaler psc)
    {
        tl::setRegister(rg()->CFGR,
                             CFGR::MCO1, static_cast<uint8_t>(src),
                             CFGR::MCO1PRE, static_cast<uint8_t>(psc));
    }

    INLINE static void setMco2(Rcc::Mco2Src src, Rcc::McoPrescaler psc)
    {
        tl::setRegister(rg()->CFGR,
                             CFGR::MCO2, static_cast<uint8_t>(src),
                             CFGR::MCO2PRE, static_cast<uint8_t>(psc));
    }

    // Clock enable functions    INLINE static void clockOtghsulpi(bool en) { Utility::setRegister(rg()->AHB1ENR, AHB1ENR::OTGHSULPIEN, en); }
	INLINE static void clockOtgHsUlpi(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::OTGHSULPIEN, en); }
	INLINE static void clockOtgHs(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::OTGHSEN, en); }
	INLINE static void clockEthmacptp(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::ETHMACPTPEN, en); }
    INLINE static void clockEthmacrx(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::ETHMACRXEN, en); }
    INLINE static void clockEthmactx(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::ETHMACTXEN, en); }
    INLINE static void clockEthmac(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::ETHMACEN, en); }
    INLINE static void clockDma2d(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::DMA2DEN, en); }
    INLINE static void clockDma2(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::DMA2EN, en); }
    INLINE static void clockDma1(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::DMA1EN, en); }
    INLINE static void clockCcmdataram(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::CCMDATARAMEN, en); }
    INLINE static void clockBkpsram(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::BKPSRAMEN, en); }
    INLINE static void clockCrc(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::CRCEN, en); }
    INLINE static void clockGpioI(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOIEN, en); }
    INLINE static void clockGpioH(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOHEN, en); }
    INLINE static void clockGpioG(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOGEN, en); }
    INLINE static void clockGpioF(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOFEN, en); }
    INLINE static void clockGpioE(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOEEN, en); }
    INLINE static void clockGpioD(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIODEN, en); }
    INLINE static void clockGpioC(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOCEN, en); }
    INLINE static void clockGpioB(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOBEN, en); }
    INLINE static void clockGpioA(bool en) { tl::setRegister(rg()->AHB1ENR, AHB1ENR::GPIOAEN, en); }
	INLINE static void clockOtgFs(bool en) { tl::setRegister(rg()->AHB2ENR, AHB2ENR::OTGFSEN, en); }
    INLINE static void clockRng(bool en) { tl::setRegister(rg()->AHB2ENR, AHB2ENR::RNGEN, en); }
    INLINE static void clockHash(bool en) { tl::setRegister(rg()->AHB2ENR, AHB2ENR::HASHEN, en); }
    INLINE static void clockCryp(bool en) { tl::setRegister(rg()->AHB2ENR, AHB2ENR::CRYPEN, en); }
    INLINE static void clockDcmi(bool en) { tl::setRegister(rg()->AHB2ENR, AHB2ENR::DCMIEN, en); }
    INLINE static void clockFmc(bool en) { tl::setRegister(rg()->AHB3ENR, AHB3ENR::FMCEN, en); }
    INLINE static void clockTim2(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::TIM2EN, en); }
    INLINE static void clockTim3(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::TIM3EN, en); }
    INLINE static void clockTim4(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::TIM4EN, en); }
    INLINE static void clockTim5(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::TIM5EN, en); }
    INLINE static void clockTim6(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::TIM6EN, en); }
    INLINE static void clockTim7(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::TIM7EN, en); }
    INLINE static void clockTim12(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::TIM12EN, en); }
    INLINE static void clockTim13(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::TIM13EN, en); }
    INLINE static void clockTim14(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::TIM14EN, en); }
    INLINE static void clockWwdg(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::WWDGEN, en); }
    INLINE static void clockSpi2(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::SPI2EN, en); }
    INLINE static void clockSpi3(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::SPI3EN, en); }
    INLINE static void clockUsart2(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::USART2EN, en); }
    INLINE static void clockUsart3(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::USART3EN, en); }
    INLINE static void clockUart4(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::UART4EN, en); }
    INLINE static void clockUart5(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::UART5EN, en); }
    INLINE static void clockI2c1(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::I2C1EN, en); }
    INLINE static void clockI2c2(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::I2C2EN, en); }
    INLINE static void clockI2c3(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::I2C3EN, en); }
    INLINE static void clockCan1(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::CAN1EN, en); }
    INLINE static void clockCan2(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::CAN2EN, en); }
    INLINE static void clockPwr(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::PWREN, en); }
    INLINE static void clockDac(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::DACEN, en); }
    INLINE static void clockTim1(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::TIM1EN, en); }
    INLINE static void clockTim8(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::TIM8EN, en); }
    INLINE static void clockUsart1(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::USART1EN, en); }
	INLINE static void clockUsart6(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::USART6EN, en); }
	INLINE static void clockUsart7(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::UART7EN, en); }
	INLINE static void clockUsart8(bool en) { tl::setRegister(rg()->APB1ENR, APB1ENR::UART8EN, en); }
	INLINE static void clockAdc1(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::ADC1EN, en); }
    INLINE static void clockAdc2(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::ADC2EN, en); }
    INLINE static void clockAdc3(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::ADC3EN, en); }
    INLINE static void clockSdio(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::SDIOEN, en); }
    INLINE static void clockSpi1(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::SPI1EN, en); }
    INLINE static void clockSpi4(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::SPI4EN, en); }
    INLINE static void clockSyscfg(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::SYSCFGEN, en); }
    INLINE static void clockTim9(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::TIM9EN, en); }
    INLINE static void clockTim10(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::TIM10EN, en); }
    INLINE static void clockTim11(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::TIM11EN, en); }
    INLINE static void clockSpi5(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::SPI5EN, en); }
    INLINE static void clockSpi6(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::SPI6EN, en); }
    INLINE static void clockLtdc(bool en) { tl::setRegister(rg()->APB2ENR, APB2ENR::LTDCEN, en); }

    // Reset functions    INLINE static void resetOtghs(bool en) { Utility::setRegister(rg()->AHB1RSTR, AHB1RSTR::OTGHSRST, en); }
    INLINE static void resetEthmac(bool en) { tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::ETHMACRST, en); }
    INLINE static void resetDma2(bool en) { tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::DMA2RST, en); }
    INLINE static void resetDma1(bool en) { tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::DMA1RST, en); }
    INLINE static void resetCrc(bool en) { tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::CRCRST, en); }
    INLINE static void resetGpioi(bool en) { tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOIRST, en); }
    INLINE static void resetGpioh(bool en) { tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOHRST, en); }
    INLINE static void resetGpiog(bool en) { tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOGRST, en); }
    INLINE static void resetGpiof(bool en) { tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOFRST, en); }
    INLINE static void resetGpioe(bool en) { tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOERST, en); }
    INLINE static void resetGpiod(bool en) { tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIODRST, en); }
    INLINE static void resetGpioc(bool en) { tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOCRST, en); }
    INLINE static void resetGpiob(bool en) { tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOBRST, en); }
    INLINE static void resetGpioa(bool en) { tl::setRegister(rg()->AHB1RSTR, AHB1RSTR::GPIOARST, en); }
    INLINE static void resetOtgfs(bool en) { tl::setRegister(rg()->AHB2RSTR, AHB2RSTR::OTGFSRST, en); }
    INLINE static void resetRng(bool en) { tl::setRegister(rg()->AHB2RSTR, AHB2RSTR::RNGRST, en); }
    INLINE static void resetHsah(bool en) { tl::setRegister(rg()->AHB2RSTR, AHB2RSTR::HSAHRST, en); }
    INLINE static void resetCryp(bool en) { tl::setRegister(rg()->AHB2RSTR, AHB2RSTR::CRYPRST, en); }
    INLINE static void resetDcmi(bool en) { tl::setRegister(rg()->AHB2RSTR, AHB2RSTR::DCMIRST, en); }
    INLINE static void resetFmc(bool en) { tl::setRegister(rg()->AHB3RSTR, AHB3RSTR::FMCRST, en); }
    INLINE static void resetTim2(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM2RST, en); }
    INLINE static void resetTim3(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM3RST, en); }
    INLINE static void resetTim4(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM4RST, en); }
    INLINE static void resetTim5(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM5RST, en); }
    INLINE static void resetTim6(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM6RST, en); }
    INLINE static void resetTim7(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM7RST, en); }
    INLINE static void resetTim12(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM12RST, en); }
    INLINE static void resetTim13(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM13RST, en); }
    INLINE static void resetTim14(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::TIM14RST, en); }
    INLINE static void resetWwdg(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::WWDGRST, en); }
    INLINE static void resetSpi2(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::SPI2RST, en); }
    INLINE static void resetSpi3(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::SPI3RST, en); }
    INLINE static void resetUart2(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::UART2RST, en); }
    INLINE static void resetUart3(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::UART3RST, en); }
    INLINE static void resetUart4(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::UART4RST, en); }
    INLINE static void resetUart5(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::UART5RST, en); }
    INLINE static void resetI2c1(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::I2C1RST, en); }
    INLINE static void resetI2c2(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::I2C2RST, en); }
    INLINE static void resetI2c3(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::I2C3RST, en); }
    INLINE static void resetCan1(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::CAN1RST, en); }
    INLINE static void resetCan2(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::CAN2RST, en); }
    INLINE static void resetPwr(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::PWRRST, en); }
    INLINE static void resetDac(bool en) { tl::setRegister(rg()->APB1RSTR, APB1RSTR::DACRST, en); }
    INLINE static void resetTim1(bool en) { tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM1RST, en); }
    INLINE static void resetTim8(bool en) { tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM8RST, en); }
    INLINE static void resetUsart1(bool en) { tl::setRegister(rg()->APB2RSTR, APB2RSTR::USART1RST, en); }
    INLINE static void resetUsart6(bool en) { tl::setRegister(rg()->APB2RSTR, APB2RSTR::USART6RST, en); }
    INLINE static void resetAdc(bool en) { tl::setRegister(rg()->APB2RSTR, APB2RSTR::ADCRST, en); }
    INLINE static void resetSdio(bool en) { tl::setRegister(rg()->APB2RSTR, APB2RSTR::SDIORST, en); }
    INLINE static void resetSpi1(bool en) { tl::setRegister(rg()->APB2RSTR, APB2RSTR::SPI1RST, en); }
    INLINE static void resetSyscfg(bool en) { tl::setRegister(rg()->APB2RSTR, APB2RSTR::SYSCFGRST, en); }
    INLINE static void resetTim9(bool en) { tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM9RST, en); }
    INLINE static void resetTim10(bool en) { tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM10RST, en); }
    INLINE static void resetTim11(bool en) { tl::setRegister(rg()->APB2RSTR, APB2RSTR::TIM11RST, en); }


};





#endif // RCC_H

