
/*********************************************************
 * ISRstm32f10x_ld.h
 * Automatic generated header file for MCU stm32f10x_ld
 *
 *
 **/
#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include <stdint.h>



//#define USE_MEMORY_ISR
//extern "C" const uint32_t _estack;
extern "C"
{
namespace Isr
{
  void DefaultHandler();
struct ShortVectors
{
    uint32_t estack;
    void (*Reset )(void);
};

struct Vectors
{
    const uint32_t estack;

    void (*Reset)               ();
    void (*Nmi)                 ();
    void (*HardFault)           ();
    void (*MemManage)           ();
    void (*BusFault)            ();
    void (*UsageFault)          ();
    void (*__unused0[4])        ();
    void (*Svc)                 ();
    void (*DebugMon)            ();
    void (*__unused1)           ();
    void (*PendSv)              ();
    void (*SysTickTimer)        ();

    void (*Wwdg)                ();
    void (*Pvd)                 ();
    void (*Tamp)                ();
    void (*Rtc)                 ();
    void (*Flash)               ();
    void (*Rcc)                 ();
    void (*Exti0)               ();
    void (*Exti1)               ();
    void (*Exti2)               ();
    void (*Exti3)               ();
    void (*Exti4)               ();
    void (*Dma1Channel1)        (); //
    void (*Dma1Channel2)        ();//
    void (*Dma1Channel3)        ();//
    void (*Dma1Channel4)        ();//
    void (*Dma1Channel5)        ();//
    void (*Dma1Channel6)        ();//
    void (*Dma1Channel7)        ();//
    void (*Adci)                ();
    void (*Can1Tx_UsbHp)        (); //*
    void (*Can1Rx0_UsbLp)       (); //*
    void (*Can1Rx1)             ();
    void (*Can1Sce)             ();
    void (*Exti9_5)             ();
    void (*Tim1BrkTim9)         ();
    void (*Tim1UpTim10)         ();
    void (*Tim1TrgComTim11)     ();
    void (*Tim1Cc)              ();
    void (*Tim2)                ();
    void (*Tim3)                ();
    void (*Tim4)                ();
    void (*I2C1Ev)              ();
    void (*I2C1Er)              ();
    void (*I2C2Ev)              ();
    void (*I2C2Er)              ();
    void (*Spi1)                ();
    void (*Spi2)                ();
    void (*Usart1)              ();
    void (*Usart2)              ();
    void (*Usart3)              ();
    void (*Exti15_10)           ();
    void (*RtcAlarm)            ();
    void (*OtgFsWakeup)         ();
    void (*Tim8BrkTim12)        ();
    void (*Tim8UpTim13)         ();
    void (*Tim8TrgComTim14)     ();
    void (*Tim8Cc)              ();
    void (*Adc3)                (); //
    void (*Fsmc)                ();//
    void (*Sdio)                ();
    void (*Tim5)                ();
    void (*Spi3)                ();
    void (*Uart4)               ();
    void (*Uart5)               ();
    void (*Tim6)                ();//
    void (*Tim7)                ();
    void (*Dma2Channel1)        ();
    void (*Dma2Channel2)        ();
    void (*Dma2Channel3)        ();
    void (*Dma2Channel4_5)      ();//

};

void Reset               ();
void Nmi                 ();
void HardFault           ();
void MemManage           ();
void BusFault            ();
void UsageFault          ();
void Svc                 ();
void DebugMon            ();
void PendSv              ();
void SysTickTimer        ();

void Wwdg                ();
void Pvd                 ();
void Tamp                ();
void Rtc                 ();
void Flash               ();
void Rcc                 ();
void Exti0               ();
void Exti1               ();
void Exti2               ();
void Exti3               ();
void Exti4               ();
void Dma1Channel1        ();
void Dma1Channel2        ();
void Dma1Channel3        ();
void Dma1Channel4        ();
void Dma1Channel5        ();
void Dma1Channel6        ();
void Dma1Channel7        ();
void Adci                ();
void Can1Tx_UsbHp        ();
void Can1Rx0_UsbLp       ();
void Can1Rx1             ();
void Can1Sce             ();
void Exti9_5             ();
void Tim1BrkTim9         ();
void Tim1UpTim10         ();
void Tim1TrgComTim11     ();
void Tim1Cc              ();
void Tim2                ();
void Tim3                ();
void Tim4                ();
void I2C1Ev              ();
void I2C1Er              ();
void I2C2Ev              ();
void I2C2Er              ();
void Spi1                ();
void Spi2                ();
void Usart1              ();
void Usart2              ();
void Usart3              ();
void Exti15_10           ();
void RtcAlarm            ();
void OtgFsWakeup         ();
void Tim8BrkTim12        ();
void Tim8UpTim13         ();
void Tim8TrgComTim14     ();
void Tim8Cc              ();
void Adc3                ();
void Fsmc                ();
void Sdio                ();
void Tim5                ();
void Spi3                ();
void Uart4               ();
void Uart5               ();
void Tim6                ();
void Tim7                ();
void Dma2Channel1        ();
void Dma2Channel2        ();
void Dma2Channel3        ();
void Dma2Channel4_5      ();
}

}


#endif // INTERRUPTS_H
