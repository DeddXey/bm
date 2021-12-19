
/*********************************************************
 * ISRstm32f10x_ld.h
 * Automatic generated header file for MCU stm32f10x_ld
 *
 *
 **/
#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include <cstdint>

//#define USE_MEMORY_ISR
// extern "C" const uint32_t _estack;
extern "C" {
namespace Isr {
  [[noreturn]] [[noreturn]] void DefaultHandler();
  struct ShortVectors
  {
    uint32_t estack;
    void (*Reset)();
  };

  struct Vectors
  {
    const uint32_t estack1;

    void (*Reset)();
    void (*Nmi)();
    void (*HardFault)();
    void (*MemManage)();
    void (*BusFault)();
    void (*UsageFault)();
    void (*unused0[4])(); //
    void (*Svc)();
    void (*DebugMon)();
    void (*unused1)(); //
    void (*PendSv)();
    void (*SysTickTimer)();

    void (*Wwdg)();
    void (*Pvd)();
    void (*Tamp)();
    void (*Rtc)();
    void (*Flash)();
    void (*Rcc)();
    void (*Exti0)();
    void (*Exti1)();
    void (*Exti2)();
    void (*Exti3)();
    void (*Exti4)();
    void (*Dma1Stream0)();
    void (*Dma1Stream1)();
    void (*Dma1Stream2)();
    void (*Dma1Stream3)();
    void (*Dma1Stream4)();
    void (*Dma1Stream5)();
    void (*Dma1Stream6)();
    void (*Adc)();
    void (*Can1Tx)();
    void (*Can1Rx0)();
    void (*Can1Rx1)();
    void (*Can1Sce)();
    void (*Exti9_5)();
    void (*Tim1BrkTim9)();
    void (*Tim1UpTim10)();
    void (*Tim1TrgComTim11)();
    void (*Tim1Cc)();
    void (*Tim2)();
    void (*Tim3)();
    void (*Tim4)();
    void (*I2C1Ev)();
    void (*I2C1Er)();
    void (*I2C2Ev)();
    void (*I2C2Er)();
    void (*Spi1)();
    void (*Spi2)();
    void (*Usart1)();
    void (*Usart2)();
    void (*Usart3)();
    void (*Exti15_10)();
    void (*RtcAlarm)();
    void (*OtgFsWakeup)();
    void (*Tim8BrkTim12)();
    void (*Tim8UpTim13)();
    void (*Tim8TrgComTim14)();
    void (*Tim8Cc)();
    void (*Dma1Stream7)();
    void (*Fmc)();
    void (*Sdio)();
    void (*Tim5)();
    void (*Spi3)();
    void (*Uart4)();
    void (*Uart5)();
    void (*Tim6Dac)();
    void (*Tim7)();
    void (*Dma2Stream0)();
    void (*Dma2Stream1)();
    void (*Dma2Stream2)();
    void (*Dma2Stream3)();
    void (*Dma2Stream4)();
    void (*Eth)();
    void (*EthWkup)();
    void (*Can2Tx)();
    void (*Can2Rx0)();
    void (*Can2Rx1)();
    void (*Can2Sce)();
    void (*OtgFs)();
    void (*Dma2Stream5)();
    void (*Dma2Stream6)();
    void (*Dma2Stream7)();
    void (*Usart6)();
    void (*I2C3Ev)();
    void (*I2C3Er)();
    void (*OtgHsEp1Out)();
    void (*OtgHsEp1In)();
    void (*OtgHsWkup)();
    void (*OtgHs)();
    void (*Dcmi)();
    void (*__unused2)(); //
    void (*Hash)();
    void (*Fpu)();
    void (*Uart7)();
    void (*Uart8)();
    void (*Spi4)();
    void (*Spi5)();
    void (*Spi6)();
    void (*Sai1)();
    void (*Ltdc)();
    void (*LtdcEr)();
    void (*Dma2D)();
  };

  void Reset();
  void Nmi();
  void HardFault();
  void MemManage();
  void BusFault();
  void UsageFault();
  void Svc();
  void DebugMon();
  void PendSv();
  void SysTickTimer();

  void Wwdg();
  void Pvd();
  void Tamp();
  void Rtc();
  void Flash();
  void Rcc();
  void Exti0();
  void Exti1();
  void Exti2();
  void Exti3();
  void Exti4();
  void Dma1Stream0();
  void Dma1Stream1();
  void Dma1Stream2();
  void Dma1Stream3();
  void Dma1Stream4();
  void Dma1Stream5();
  void Dma1Stream6();
  void Adc();
  void Can1Tx();
  void Can1Rx0();
  void Can1Rx1();
  void Can1Sce();
  void Exti9_5();
  void Tim1BrkTim9();
  void Tim1UpTim10();
  void Tim1TrgComTim11();
  void Tim1Cc();
  void Tim2();
  void Tim3();
  void Tim4();
  void I2C1Ev();
  void I2C1Er();
  void I2C2Ev();
  void I2C2Er();
  void Spi1();
  void Spi2();
  void Usart1();
  void Usart2();
  void Usart3();
  void Exti15_10();
  void RtcAlarm();
  void OtgFsWakeup();
  void Tim8BrkTim12();
  void Tim8UpTim13();
  void Tim8TrgComTim14();
  void Tim8Cc();
  void Dma1Stream7();
  void Fmc();
  void Sdio();
  void Tim5();
  void Spi3();
  void Uart4();
  void Uart5();
  void Tim6Dac();
  void Tim7();
  void Dma2Stream0();
  void Dma2Stream1();
  void Dma2Stream2();
  void Dma2Stream3();
  void Dma2Stream4();
  void Eth();
  void EthWkup();
  void Can2Tx();
  void Can2Rx0();
  void Can2Rx1();
  void Can2Sce();
  void OtgFs();
  void Dma2Stream5();
  void Dma2Stream6();
  void Dma2Stream7();
  void Usart6();
  void I2C3Ev();
  void I2C3Er();
  void OtgHsEp1Out();
  void OtgHsEp1In();
  void OtgHsWkup();
  void OtgHs();
  void Dcmi();
  void Hash();
  void Fpu();
  void Uart7();
  void Uart8();
  void Spi4();
  void Spi5();
  void Spi6();
  void Sai1();
  void Ltdc();
  void LtdcEr();
  void Dma2D();
} // namespace Isr
}

#endif // INTERRUPTS_H
