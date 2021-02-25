// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*********************************************************
 * ISRstm32f10x_ld.cpp
 * Automatic generated source file for MCU stm32f10x_ld
 *
 *
 **/
//#include "stm32f0xx.h"
#include "it.h"


__attribute__((noreturn)) void Isr::DefaultHandler()
{

    for(;;) {

    }
    ;
}

extern "C" const uint32_t _estack;

#ifdef USE_MEMORY_ISR
__attribute__((section(".isr_vector"))) const ISR::ShortVectors interruptsVectorTable =
        #else
__attribute__((section(".isr_vector"), used )) const Isr::Vectors interruptsVectorTable =
        #endif
{
        #ifdef USE_MEMORY_ISR
        _estack,
        ISR::Reset
        };

__attribute__((section(".isr_vector2"))) ISR::Vectors MeminterruptsVectorTable =
{
        #endif
        _estack,
        Isr::Reset                ,
        Isr::Nmi                  ,
        Isr::HardFault            ,
        Isr::MemManage            ,
        Isr::BusFault             ,
        Isr::UsageFault           ,
{0, 0, 0, 0}         , //
        Isr::Svc                  ,
        Isr::DebugMon             ,
        0            , //
        Isr::PendSv               ,
        Isr::SysTickTimer         ,

        Isr::Wwdg                 ,
        Isr::Pvd                  ,
        Isr::Tamp                 ,
        Isr::Rtc                  ,
        Isr::Flash                ,
        Isr::Rcc                  ,
        Isr::Exti0                ,
        Isr::Exti1                ,
        Isr::Exti2                ,
        Isr::Exti3                ,
        Isr::Exti4                ,
        Isr::Dma1Stream0          ,
        Isr::Dma1Stream1          ,
        Isr::Dma1Stream2          ,
        Isr::Dma1Stream3          ,
        Isr::Dma1Stream4          ,
        Isr::Dma1Stream5          ,
        Isr::Dma1Stream6          ,
        Isr::Adc                  ,
        Isr::Can1Tx               ,
        Isr::Can1Rx0              ,
        Isr::Can1Rx1              ,
        Isr::Can1Sce              ,
        Isr::Exti9_5              ,
        Isr::Tim1BrkTim9          ,
        Isr::Tim1UpTim10          ,
        Isr::Tim1TrgComTim11      ,
        Isr::Tim1Cc               ,
        Isr::Tim2                 ,
        Isr::Tim3                 ,
        Isr::Tim4                 ,
        Isr::I2C1Ev               ,
        Isr::I2C1Er               ,
        Isr::I2C2Ev               ,
        Isr::I2C2Er               ,
        Isr::Spi1                 ,
        Isr::Spi2                 ,
        Isr::Usart1               ,
        Isr::Usart2               ,
        Isr::Usart3               ,
        Isr::Exti15_10            ,
        Isr::RtcAlarm             ,
        Isr::OtgFsWakeup          ,
        Isr::Tim8BrkTim12         ,
        Isr::Tim8UpTim13          ,
        Isr::Tim8TrgComTim14      ,
        Isr::Tim8Cc               ,
        Isr::Dma1Stream7          ,
        Isr::Fmc                  ,
        Isr::Sdio                 ,
        Isr::Tim5                 ,
        Isr::Spi3                 ,
        Isr::Uart4                ,
        Isr::Uart5                ,
        Isr::Tim6Dac              ,
        Isr::Tim7                 ,
        Isr::Dma2Stream0          ,
        Isr::Dma2Stream1          ,
        Isr::Dma2Stream2          ,
        Isr::Dma2Stream3          ,
        Isr::Dma2Stream4          ,
        Isr::Eth                  ,
        Isr::EthWkup              ,
        Isr::Can2Tx               ,
        Isr::Can2Rx0              ,
        Isr::Can2Rx1              ,
        Isr::Can2Sce              ,
        Isr::OtgFs                ,
        Isr::Dma2Stream5          ,
        Isr::Dma2Stream6          ,
        Isr::Dma2Stream7          ,
        Isr::Usart6               ,
        Isr::I2C3Ev               ,
        Isr::I2C3Er               ,
        Isr::OtgHsEp1Out          ,
        Isr::OtgHsEp1In           ,
        Isr::OtgHsWkup            ,
        Isr::OtgHs                ,
        Isr::Dcmi                 ,
        0            , //
        Isr::Hash                 ,
        Isr::Fpu                  ,
        Isr::Uart7                ,
        Isr::Uart8                ,
        Isr::Spi4                 ,
        Isr::Spi5                 ,
        Isr::Spi6                 ,
        Isr::Sai1                 ,
        Isr::Ltdc                 ,
        Isr::LtdcEr               ,
        Isr::Dma2D
        };

#pragma weak Reset               = DefaultHandler
#pragma weak Nmi                 = DefaultHandler
#pragma weak HardFault           = DefaultHandler
#pragma weak MemManage           = DefaultHandler
#pragma weak BusFault            = DefaultHandler
#pragma weak UsageFault          = DefaultHandler
#pragma weak Svc                 = DefaultHandler
#pragma weak DebugMon            = DefaultHandler
#pragma weak PendSv              = DefaultHandler
#pragma weak SysTickTimer        = DefaultHandler

#pragma weak Wwdg                = DefaultHandler
#pragma weak Pvd                 = DefaultHandler
#pragma weak Tamp                = DefaultHandler
#pragma weak Rtc                 = DefaultHandler
#pragma weak Flash               = DefaultHandler
#pragma weak Rcc                 = DefaultHandler
#pragma weak Exti0               = DefaultHandler
#pragma weak Exti1               = DefaultHandler
#pragma weak Exti2               = DefaultHandler
#pragma weak Exti3               = DefaultHandler
#pragma weak Exti4               = DefaultHandler
#pragma weak Dma1Stream0         = DefaultHandler
#pragma weak Dma1Stream1         = DefaultHandler
#pragma weak Dma1Stream2         = DefaultHandler
#pragma weak Dma1Stream3         = DefaultHandler
#pragma weak Dma1Stream4         = DefaultHandler
#pragma weak Dma1Stream5         = DefaultHandler
#pragma weak Dma1Stream6         = DefaultHandler
#pragma weak Adc                 = DefaultHandler
#pragma weak Can1Tx              = DefaultHandler
#pragma weak Can1Rx0             = DefaultHandler
#pragma weak Can1Rx1             = DefaultHandler
#pragma weak Can1Sce             = DefaultHandler
#pragma weak Exti9_5             = DefaultHandler
#pragma weak Tim1BrkTim9         = DefaultHandler
#pragma weak Tim1UpTim10         = DefaultHandler
#pragma weak Tim1TrgComTim11     = DefaultHandler
#pragma weak Tim1Cc              = DefaultHandler
#pragma weak Tim2                = DefaultHandler
#pragma weak Tim3                = DefaultHandler
#pragma weak Tim4                = DefaultHandler
#pragma weak I2C1Ev              = DefaultHandler
#pragma weak I2C1Er              = DefaultHandler
#pragma weak I2C2Ev              = DefaultHandler
#pragma weak I2C2Er              = DefaultHandler
#pragma weak Spi1                = DefaultHandler
#pragma weak Spi2                = DefaultHandler
#pragma weak Usart1              = DefaultHandler
#pragma weak Usart2              = DefaultHandler
#pragma weak Usart3              = DefaultHandler
#pragma weak Exti15_10           = DefaultHandler
#pragma weak RtcAlarm            = DefaultHandler
#pragma weak OtgFsWakeup         = DefaultHandler
#pragma weak Tim8BrkTim12        = DefaultHandler
#pragma weak Tim8UpTim13         = DefaultHandler
#pragma weak Tim8TrgComTim14     = DefaultHandler
#pragma weak Tim8Cc              = DefaultHandler
#pragma weak Dma1Stream7         = DefaultHandler
#pragma weak Fmc                 = DefaultHandler
#pragma weak Sdio                = DefaultHandler
#pragma weak Tim5                = DefaultHandler
#pragma weak Spi3                = DefaultHandler
#pragma weak Uart4               = DefaultHandler
#pragma weak Uart5               = DefaultHandler
#pragma weak Tim6Dac             = DefaultHandler
#pragma weak Tim7                = DefaultHandler
#pragma weak Dma2Stream0         = DefaultHandler
#pragma weak Dma2Stream1         = DefaultHandler
#pragma weak Dma2Stream2         = DefaultHandler
#pragma weak Dma2Stream3         = DefaultHandler
#pragma weak Dma2Stream4         = DefaultHandler
#pragma weak Eth                 = DefaultHandler
#pragma weak EthWkup             = DefaultHandler
#pragma weak Can2Tx              = DefaultHandler
#pragma weak Can2Rx0             = DefaultHandler
#pragma weak Can2Rx1             = DefaultHandler
#pragma weak Can2Sce             = DefaultHandler
#pragma weak OtgFs               = DefaultHandler
#pragma weak Dma2Stream5         = DefaultHandler
#pragma weak Dma2Stream6         = DefaultHandler
#pragma weak Dma2Stream7         = DefaultHandler
#pragma weak Usart6              = DefaultHandler
#pragma weak I2C3Ev              = DefaultHandler
#pragma weak I2C3Er              = DefaultHandler
#pragma weak OtgHsEp1Out         = DefaultHandler
#pragma weak OtgHsEp1In          = DefaultHandler
#pragma weak OtgHsWkup           = DefaultHandler
#pragma weak OtgHs               = DefaultHandler
#pragma weak Dcmi                = DefaultHandler
#pragma weak Hash                = DefaultHandler
#pragma weak Fpu                 = DefaultHandler
#pragma weak Uart7               = DefaultHandler
#pragma weak Uart8               = DefaultHandler
#pragma weak Spi4                = DefaultHandler
#pragma weak Spi5                = DefaultHandler
#pragma weak Spi6                = DefaultHandler
#pragma weak Sai1                = DefaultHandler
#pragma weak Ltdc                = DefaultHandler
#pragma weak LtdcEr              = DefaultHandler
#pragma weak Dma2D               = DefaultHandler



