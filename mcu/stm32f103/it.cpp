#include "it.h"

void Isr::DefaultHandler()
{
  for (;;) {}
}

extern "C" const uint32_t _estack;

#ifdef USE_MEMORY_ISR
__attribute__((section(".isr_vector")))
const ISR::ShortVectors interruptsVectorTable =
#else
__attribute__((section(".isr_vector"), used))
const Isr::Vectors interruptsVectorTable =
#endif
    {
#ifdef USE_MEMORY_ISR
        _estack, ISR::Reset};

__attribute__((section(".isr_vector2")))
ISR::Vectors MeminterruptsVectorTable = {
#endif
    reinterpret_cast<uint32_t>(&_estack),
    Isr::Reset,
    Isr::Nmi,
    Isr::HardFault,
    Isr::MemManage,
    Isr::BusFault,
    Isr::UsageFault,
    {nullptr, nullptr, nullptr, nullptr}, //
    Isr::Svc,
    Isr::DebugMon,
    nullptr, //
    Isr::PendSv,
    Isr::SysTickTimer,

    Isr::Wwdg,
    Isr::Pvd,
    Isr::Tamp,
    Isr::Rtc,
    Isr::Flash,
    Isr::Rcc,
    Isr::Exti0,
    Isr::Exti1,
    Isr::Exti2,
    Isr::Exti3,
    Isr::Exti4,
    Isr::Dma1Channel1,
    Isr::Dma1Channel2,
    Isr::Dma1Channel3,
    Isr::Dma1Channel4,
    Isr::Dma1Channel5,
    Isr::Dma1Channel6,
    Isr::Dma1Channel7,
    Isr::Adci,
    Isr::Can1Tx_UsbHp,
    Isr::Can1Rx0_UsbLp,
    Isr::Can1Rx1,
    Isr::Can1Sce,
    Isr::Exti9_5,
    Isr::Tim1BrkTim9,
    Isr::Tim1UpTim10,
    Isr::Tim1TrgComTim11,
    Isr::Tim1Cc,
    Isr::Tim2,
    Isr::Tim3,
    Isr::Tim4,
    Isr::I2C1Ev,
    Isr::I2C1Er,
    Isr::I2C2Ev,
    Isr::I2C2Er,
    Isr::Spi1,
    Isr::Spi2,
    Isr::Usart1,
    Isr::Usart2,
    Isr::Usart3,
    Isr::Exti15_10,
    Isr::RtcAlarm,
    Isr::OtgFsWakeup,
    Isr::Tim8BrkTim12,
    Isr::Tim8UpTim13,
    Isr::Tim8TrgComTim14,
    Isr::Tim8Cc,
    Isr::Adc3,
    Isr::Fsmc,
    Isr::Sdio,
    Isr::Tim5,
    Isr::Spi3,
    Isr::Uart4,
    Isr::Uart5,
    Isr::Tim6,
    Isr::Tim7,
    Isr::Dma2Channel1,
    Isr::Dma2Channel2,
    Isr::Dma2Channel3,
    Isr::Dma2Channel4_5};

#pragma weak Reset = DefaultHandler
#pragma weak Nmi = DefaultHandler
#pragma weak HardFault = DefaultHandler
#pragma weak MemManage = DefaultHandler
#pragma weak BusFault = DefaultHandler
#pragma weak UsageFault = DefaultHandler
#pragma weak Svc = DefaultHandler
#pragma weak DebugMon = DefaultHandler
#pragma weak PendSv = DefaultHandler
#pragma weak SysTickTimer = DefaultHandler

#pragma weak Wwdg = DefaultHandler
#pragma weak Pvd = DefaultHandler
#pragma weak Tamp = DefaultHandler
#pragma weak Rtc = DefaultHandler
#pragma weak Flash = DefaultHandler
#pragma weak Rcc = DefaultHandler
#pragma weak Exti0 = DefaultHandler
#pragma weak Exti1 = DefaultHandler
#pragma weak Exti2 = DefaultHandler
#pragma weak Exti3 = DefaultHandler
#pragma weak Exti4 = DefaultHandler
#pragma weak Dma1Channel1 = DefaultHandler
#pragma weak Dma1Channel2 = DefaultHandler
#pragma weak Dma1Channel3 = DefaultHandler
#pragma weak Dma1Channel4 = DefaultHandler
#pragma weak Dma1Channel5 = DefaultHandler
#pragma weak Dma1Channel6 = DefaultHandler
#pragma weak Dma1Channel7 = DefaultHandler
#pragma weak Adci = DefaultHandler
#pragma weak Can1Tx_UsbHp = DefaultHandler
#pragma weak Can1Rx0_UsbLp = DefaultHandler
#pragma weak Can1Rx1 = DefaultHandler
#pragma weak Can1Sce = DefaultHandler
#pragma weak Exti9_5 = DefaultHandler
#pragma weak Tim1BrkTim9 = DefaultHandler
#pragma weak Tim1UpTim10 = DefaultHandler
#pragma weak Tim1TrgComTim11 = DefaultHandler
#pragma weak Tim1Cc = DefaultHandler
#pragma weak Tim2 = DefaultHandler
#pragma weak Tim3 = DefaultHandler
#pragma weak Tim4 = DefaultHandler
#pragma weak I2C1Ev = DefaultHandler
#pragma weak I2C1Er = DefaultHandler
#pragma weak I2C2Ev = DefaultHandler
#pragma weak I2C2Er = DefaultHandler
#pragma weak Spi1 = DefaultHandler
#pragma weak Spi2 = DefaultHandler
#pragma weak Usart1 = DefaultHandler
#pragma weak Usart2 = DefaultHandler
#pragma weak Usart3 = DefaultHandler
#pragma weak Exti15_10 = DefaultHandler
#pragma weak RtcAlarm = DefaultHandler
#pragma weak OtgFsWakeup = DefaultHandler
#pragma weak Tim8BrkTim12 = DefaultHandler
#pragma weak Tim8UpTim13 = DefaultHandler
#pragma weak Tim8TrgComTim14 = DefaultHandler
#pragma weak Tim8Cc = DefaultHandler
#pragma weak Adc3 = DefaultHandler
#pragma weak Fsmc = DefaultHandler
#pragma weak Sdio = DefaultHandler
#pragma weak Tim5 = DefaultHandler
#pragma weak Spi3 = DefaultHandler
#pragma weak Uart4 = DefaultHandler
#pragma weak Uart5 = DefaultHandler
#pragma weak Tim6 = DefaultHandler
#pragma weak Tim7 = DefaultHandler
#pragma weak Dma2Channel1 = DefaultHandler
#pragma weak Dma2Channel2 = DefaultHandler
#pragma weak Dma2Channel3 = DefaultHandler
#pragma weak Dma2Channel4_5 = DefaultHandler
