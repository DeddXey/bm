#ifndef NVIC_H
#define NVIC_H

//#include "mcu.h"
//#include "stm32f42/scb.h"

#include "utility.h"
#include <cstdint>
#include "rcc.h"
#include "scb.h"
#include "instr.h"


struct Nvic {

    enum IrqType {
        itNonMaskableInt          = -14,    /*!< 2 Non Maskable Interrupt                                          */
        itMemoryManagement        = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
        itBusFault                = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
        itUsageFault              = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
        itSVCall                  = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
        itDebugMonitor            = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
        itPendSV                  = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
        itSysTick                 = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */

        itWwdg                    = 0,      /*!< Window WatchDog Interrupt                                         */
        itPvd                     = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
        itTampStamp               = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
        itRtcWkup                 = 3,      /*!< RTC Wakeup interrupt through the EXTI line                        */
        itFlash                   = 4,      /*!< FLASH global Interrupt                                            */
        itRcc                     = 5,      /*!< RCC global Interrupt                                              */
        itExti0                   = 6,      /*!< EXTI Line0 Interrupt                                              */
        itExti1                   = 7,      /*!< EXTI Line1 Interrupt                                              */
        itExti2                   = 8,      /*!< EXTI Line2 Interrupt                                              */
        itExti3                   = 9,      /*!< EXTI Line3 Interrupt                                              */
        itExti4                   = 10,     /*!< EXTI Line4 Interrupt                                              */
        itDma1Channel1            = 11,     /*!< DMA1 Stream 0 global Interrupt                                    */
        itDma1Channel2            = 12,     /*!< DMA1 Stream 1 global Interrupt                                    */
        itDma1Channel3            = 13,     /*!< DMA1 Stream 2 global Interrupt                                    */
        itDma1Channel4            = 14,     /*!< DMA1 Stream 3 global Interrupt                                    */
        itDma1Channel5            = 15,     /*!< DMA1 Stream 4 global Interrupt                                    */
        itDma1Channel6            = 16,     /*!< DMA1 Stream 5 global Interrupt                                    */
        itDma1Channel7            = 17,     /*!< DMA1 Stream 6 global Interrupt                                    */
        itAdc                     = 18,     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
        itCan1Tx_UsbHp            = 19,     /*!< CAN1 TX Interrupt                                                 */
        itCan1Rx0_UsbLp           = 20,     /*!< CAN1 RX0 Interrupt                                                */
        itCan1Rx1                 = 21,     /*!< CAN1 RX1 Interrupt                                                */
        itCan1Sce                 = 22,     /*!< CAN1 SCE Interrupt                                                */
        itExti9_5                 = 23,     /*!< External Line[9:5] Interrupts                                     */
        itTim1BrkTim9             = 24,     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
        itTim1UpTim10             = 25,     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
        itTim1TrgComTim11         = 26,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
        itTim1Cc                  = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
        itTim2                    = 28,     /*!< TIM2 global Interrupt                                             */
        itTim3                    = 29,     /*!< TIM3 global Interrupt                                             */
        itTim4                    = 30,     /*!< TIM4 global Interrupt                                             */
        itI2c1Ev                  = 31,     /*!< I2C1 Event Interrupt                                              */
        itI2c1Er                  = 32,     /*!< I2C1 Error Interrupt                                              */
        itI2c2Ev                  = 33,     /*!< I2C2 Event Interrupt                                              */
        itI2c2Er                  = 34,     /*!< I2C2 Error Interrupt                                              */
        itSpi1                    = 35,     /*!< SPI1 global Interrupt                                             */
        itSpi2                    = 36,     /*!< SPI2 global Interrupt                                             */
        itUsart1                  = 37,     /*!< USART1 global Interrupt                                           */
        itUsart2                  = 38,     /*!< USART2 global Interrupt                                           */
        itUsart3                  = 39,     /*!< USART3 global Interrupt                                           */
        itExti15_10               = 40,     /*!< External Line[15:10] Interrupts                                   */
        itRtcAlarm                = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
        itOtgFsWkup               = 42,     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
        itTtim8BrkTim12           = 43,     /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
        itTim8UpTim13             = 44,     /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
        itTim8TrgComTim14         = 45,     /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
        itTim8Cc                  = 46,     /*!< TIM8 Capture Compare global interrupt                             */
        itAdc3                    = 47,     /*!< DMA1 Stream7 Interrupt                                            */
        itFsmc                    = 48,     /*!< FMC global Interrupt                                              */
        itSdio                    = 49,     /*!< SDIO global Interrupt                                             */
        itTim5                    = 50,     /*!< TIM5 global Interrupt                                             */
        itSpi3                    = 51,     /*!< SPI3 global Interrupt                                             */
        itUart4                   = 52,     /*!< UART4 global Interrupt                                            */
        itUart5                   = 53,     /*!< UART5 global Interrupt                                            */
        itTim6                    = 54,     /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
        itTim7                    = 55,     /*!< TIM7 global interrupt                                             */
        itDma2Channel1            = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
        itDma2Channel2            = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
        itDma2Channel3            = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
        itDma2Channel4_5          = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
 };


    struct ISER_t {

    };

    struct Regs {
        uint32_t ISER[8];
        uint32_t RESERVED0[24];
        uint32_t ICER[8];
        uint32_t RSERVED1[24];
        uint32_t ISPR[8];
        uint32_t RESERVED2[24];
        uint32_t ICPR[8];
        uint32_t RESERVED3[24];
        uint32_t IABR[8];
        uint32_t RESERVED4[56];
        uint8_t  IP[240];
        uint32_t RESERVED5[644];
        uint32_t STIR;

    };


    constexpr static uint32_t base = 0xE000E100;
    constexpr static uint32_t nvicPrioBits = 4;

    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    static volatile Regs* rg()
    {
        return (volatile Regs *) base;
    }


    static void setPriorityGrouping(Scb::PriorityGrouping priorityGrouping)
    {
        Scb::rg()->AIRCR = (Scb::aircrKey << 16) + ((priorityGrouping & 0xf) << Scb::aircrPriGroupPos);
    }

    static uint32_t getPriorityGrouping() { return ((Scb::rg()->AIRCR >> Scb::aircrPriGroupPos) & 0x0f); }

    static void enableIrq(Nvic::IrqType it) { rg()->ISER[it >> 5] = (1 << (it & 0x1f)); }
    static void disableIrq(Nvic::IrqType it) { rg()->ICER[it >> 5] = (1 << (it & 0x1f)); }
    static bool getPendingIrq(Nvic::IrqType it) { return (rg()->ISPR[it >> 5] & (1 << (it & 0x1f))) != 0; }
    static void setPendingIrq(Nvic::IrqType it) { rg()->ISPR[it >> 5] = (1 << (it & 0x1f)); }
    static void clearPendingIrq(Nvic::IrqType it) { rg()->ICPR[it >> 5] = (1 << (it & 0x1f)); }
    static bool getActive(Nvic::IrqType it) { return (rg()->IABR[it >> 5] & (1 << (it & 0x1f))) != 0; }
    static void setPriority(Nvic::IrqType it, uint32_t priority)
    {
        if(it < 0) {
            Scb::rg()->SHPR[(it & 0xf) - 4] = ((priority <<(8 - nvicPrioBits)) & 0xff);
        }
        else {
            rg()->IP[it] = ((priority <<(8 - nvicPrioBits)) & 0xff);
        }

    }

    static uint32_t getPriority(Nvic::IrqType it)
    {
        if(it < 0) {
            return (Scb::rg()->SHPR[(it & 0xf) - 4] >> (8 - nvicPrioBits));
        }
        else {
            return (rg()->IP[it] >> (8 - nvicPrioBits));
        }
    }

    static __attribute__((noreturn))  void systemReset()
    {
        __DSB();

        Scb::rg()->AIRCR = (Scb::aircrKey << 16) + (1 << Scb::aircrSysResetPos);

        __DSB();

        while(1);

    }

};


#endif // NVIC_H
