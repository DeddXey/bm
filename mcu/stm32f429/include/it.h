
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
    const uint32_t estack1;








    void (*Reset)               (void);
    void (*Nmi)                 (void);
    void (*HardFault)           (void);
    void (*MemManage)           (void);
    void (*BusFault)            (void);
    void (*UsageFault)          (void);
    void (*__unused0[4])        (void); //
    void (*Svc)                 (void);
    void (*DebugMon)            (void);
    void (*__unused1)           (void); //
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
    void (*Dma1Stream0)         (void);
    void (*Dma1Stream1)         (void);
    void (*Dma1Stream2)         (void);
    void (*Dma1Stream3)         (void);
    void (*Dma1Stream4)         (void);
    void (*Dma1Stream5)         (void);
    void (*Dma1Stream6)         (void);
    void (*Adc)                 (void);
    void (*Can1Tx)              (void);
    void (*Can1Rx0)             (void);
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
    void (*Dma1Stream7)         (void);
    void (*Fmc)                 (void);
    void (*Sdio)                (void);
    void (*Tim5)                (void);
    void (*Spi3)                (void);
    void (*Uart4)               (void);
    void (*Uart5)               (void);
    void (*Tim6Dac)             (void);
    void (*Tim7)                (void);
    void (*Dma2Stream0)         (void);
    void (*Dma2Stream1)         (void);
    void (*Dma2Stream2)         (void);
    void (*Dma2Stream3)         (void);
    void (*Dma2Stream4)         (void);
    void (*Eth)                 (void);
    void (*EthWkup)             (void);
    void (*Can2Tx)              (void);
    void (*Can2Rx0)             (void);
    void (*Can2Rx1)             (void);
    void (*Can2Sce)             (void);
    void (*OtgFs)               (void);
    void (*Dma2Stream5)         (void);
    void (*Dma2Stream6)         (void);
    void (*Dma2Stream7)         (void);
    void (*Usart6)              (void);
    void (*I2C3Ev)              (void);
    void (*I2C3Er)              (void);
    void (*OtgHsEp1Out)         (void);
    void (*OtgHsEp1In)          (void);
    void (*OtgHsWkup)           (void);
    void (*OtgHs)               (void);
    void (*Dcmi)                (void);
    void (*__unused2)           (void); //
    void (*Hash)                (void);
    void (*Fpu)                 (void);
    void (*Uart7)               (void);
    void (*Uart8)               (void);
    void (*Spi4)                (void);
    void (*Spi5)                (void);
    void (*Spi6)                (void);
    void (*Sai1)                (void);
    void (*Ltdc)                (void);
    void (*LtdcEr)              (void);
    void (*Dma2D)               (void);
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
void Dma1Stream0         (void);
void Dma1Stream1         (void);
void Dma1Stream2         (void);
void Dma1Stream3         (void);
void Dma1Stream4         (void);
void Dma1Stream5         (void);
void Dma1Stream6         (void);
void Adc                 (void);
void Can1Tx              (void);
void Can1Rx0             (void);
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
void Dma1Stream7         (void);
void Fmc                 (void);
void Sdio                (void);
void Tim5                (void);
void Spi3                (void);
void Uart4               (void);
void Uart5               (void);
void Tim6Dac             (void);
void Tim7                (void);
void Dma2Stream0         (void);
void Dma2Stream1         (void);
void Dma2Stream2         (void);
void Dma2Stream3         (void);
void Dma2Stream4         (void);
void Eth                 (void);
void EthWkup             (void);
void Can2Tx              (void);
void Can2Rx0             (void);
void Can2Rx1             (void);
void Can2Sce             (void);
void OtgFs               (void);
void Dma2Stream5         (void);
void Dma2Stream6         (void);
void Dma2Stream7         (void);
void Usart6              (void);
void I2C3Ev              (void);
void I2C3Er              (void);
void OtgHsEp1Out         (void);
void OtgHsEp1In          (void);
void OtgHsWkup           (void);
void OtgHs               (void);
void Dcmi                (void);
void Hash                (void);
void Fpu                 (void);
void Uart7               (void);
void Uart8               (void);
void Spi4                (void);
void Spi5                (void);
void Spi6                (void);
void Sai1                (void);
void Ltdc                (void);
void LtdcEr              (void);
void Dma2D               (void);
};

}


#endif // INTERRUPTS_H
