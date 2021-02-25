
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

    void (*Reset)               (void);
    void (*Nmi)                 (void);
    void (*HardFault)           (void);
    void (*MemManage)           (void);
    void (*BusFault)            (void);
    void (*UsageFault)          (void);
    void (*__unused0[4])        (void);
    void (*Svc)                 (void);
    void (*DebugMon)            (void);
    void (*__unused1)           (void);
    void (*PendSv)              (void);
    void (*SysTickTimer)        (void);

    void (*Wwdg)                (void);
    void (*Pvd)                 (void);
    void (*Tamp)                (void);
    void (*Rtc)                 (void);
    void (*Flash)               (void);
    void (*Rcc)                 (void);
    void (*Exti0)               (void);
    void (*Exti1)               (void);
    void (*Exti2)               (void);
    void (*Exti3)               (void);
    void (*Exti4)               (void);
    void (*Dma1Channel1)        (void); //
    void (*Dma1Channel2)        (void);//
    void (*Dma1Channel3)        (void);//
    void (*Dma1Channel4)        (void);//
    void (*Dma1Channel5)        (void);//
    void (*Dma1Channel6)        (void);//
    void (*Dma1Channel7)        (void);//
    void (*Adci)                (void);
    void (*Can1Tx_UsbHp)        (void); //*
    void (*Can1Rx0_UsbLp)       (void); //*
    void (*Can1Rx1)             (void);
    void (*Can1Sce)             (void);
    void (*Exti9_5)             (void);
    void (*Tim1BrkTim9)         (void);
    void (*Tim1UpTim10)         (void);
    void (*Tim1TrgComTim11)     (void);
    void (*Tim1Cc)              (void);
    void (*Tim2)                (void);
    void (*Tim3)                (void);
    void (*Tim4)                (void);
    void (*I2C1Ev)              (void);
    void (*I2C1Er)              (void);
    void (*I2C2Ev)              (void);
    void (*I2C2Er)              (void);
    void (*Spi1)                (void);
    void (*Spi2)                (void);
    void (*Usart1)              (void);
    void (*Usart2)              (void);
    void (*Usart3)              (void);
    void (*Exti15_10)           (void);
    void (*RtcAlarm)            (void);
    void (*OtgFsWakeup)         (void);
    void (*Tim8BrkTim12)        (void);
    void (*Tim8UpTim13)         (void);
    void (*Tim8TrgComTim14)     (void);
    void (*Tim8Cc)              (void);
    void (*Adc3)                (void); //
    void (*Fsmc)                (void);//
    void (*Sdio)                (void);
    void (*Tim5)                (void);
    void (*Spi3)                (void);
    void (*Uart4)               (void);
    void (*Uart5)               (void);
    void (*Tim6)                (void);//
    void (*Tim7)                (void);
    void (*Dma2Channel1)        (void);
    void (*Dma2Channel2)        (void);
    void (*Dma2Channel3)        (void);
    void (*Dma2Channel4_5)      (void);//

};

void Reset               (void);
void Nmi                 (void);
void HardFault           (void);
void MemManage           (void);
void BusFault            (void);
void UsageFault          (void);
void Svc                 (void);
void DebugMon            (void);
void PendSv              (void);
void SysTickTimer        (void);

void Wwdg                (void);
void Pvd                 (void);
void Tamp                (void);
void Rtc                 (void);
void Flash               (void);
void Rcc                 (void);
void Exti0               (void);
void Exti1               (void);
void Exti2               (void);
void Exti3               (void);
void Exti4               (void);
void Dma1Channel1        (void);
void Dma1Channel2        (void);
void Dma1Channel3        (void);
void Dma1Channel4        (void);
void Dma1Channel5        (void);
void Dma1Channel6        (void);
void Dma1Channel7        (void);
void Adci                (void);
void Can1Tx_UsbHp        (void);
void Can1Rx0_UsbLp       (void);
void Can1Rx1             (void);
void Can1Sce             (void);
void Exti9_5             (void);
void Tim1BrkTim9         (void);
void Tim1UpTim10         (void);
void Tim1TrgComTim11     (void);
void Tim1Cc              (void);
void Tim2                (void);
void Tim3                (void);
void Tim4                (void);
void I2C1Ev              (void);
void I2C1Er              (void);
void I2C2Ev              (void);
void I2C2Er              (void);
void Spi1                (void);
void Spi2                (void);
void Usart1              (void);
void Usart2              (void);
void Usart3              (void);
void Exti15_10           (void);
void RtcAlarm            (void);
void OtgFsWakeup         (void);
void Tim8BrkTim12        (void);
void Tim8UpTim13         (void);
void Tim8TrgComTim14     (void);
void Tim8Cc              (void);
void Adc3                (void);
void Fsmc                (void);
void Sdio                (void);
void Tim5                (void);
void Spi3                (void);
void Uart4               (void);
void Uart5               (void);
void Tim6                (void);
void Tim7                (void);
void Dma2Channel1        (void);
void Dma2Channel2        (void);
void Dma2Channel3        (void);
void Dma2Channel4_5      (void);
};

}


#endif // INTERRUPTS_H
