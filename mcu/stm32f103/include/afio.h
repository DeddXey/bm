#ifndef __AFIO_H
#define __AFIO_H

#include "utility.h"
#include <cstdint>

struct Afio
{
  constexpr static uint32_t base = 0x40010000;

  struct Regs
  {
    uint32_t EVCR; //< 0x0 Event Control Register (AFIO_EVCR)
    uint32_t
      MAPR; //< 0x4 AF remap and debug I/O configuration register (AFIO_MAPR)
    uint32_t EXTICR[4]; //< 0x8 External interrupt configuration register
    uint32_t reserved0; //< reserved
    uint32_t MAPR2;     //< 0x1C AF remap and debug I/O configuration register
  };

  struct EVCR
  {
    constexpr static uint8_t PIN[]{ 0, 4 };  //< Pin selection
    constexpr static uint8_t PORT[]{ 4, 3 }; //< Port selection
    constexpr static uint8_t EVOE[]{ 7, 1 }; //< Event Output Enable
  };

  struct MAPR
  {
    constexpr static uint8_t SPI1_REMAP[]{ 0, 1 };   //< SPI1 remapping
    constexpr static uint8_t I2C1_REMAP[]{ 1, 1 };   //< I2C1 remapping
    constexpr static uint8_t USART1_REMAP[]{ 2, 1 }; //< USART1 remapping
    constexpr static uint8_t USART2_REMAP[]{ 3, 1 }; //< USART2 remapping
    constexpr static uint8_t USART3_REMAP[]{ 4, 2 }; //< USART3 remapping
    constexpr static uint8_t TIM1_REMAP[]{ 6, 2 };   //< TIM1 remapping
    constexpr static uint8_t TIM2_REMAP[]{ 8, 2 };   //< TIM2 remapping
    constexpr static uint8_t TIM3_REMAP[]{ 10, 2 };  //< TIM3 remapping
    constexpr static uint8_t TIM4_REMAP[]{ 12, 1 };  //< TIM4 remapping
    constexpr static uint8_t CAN_REMAP[]{ 13, 2 };   //< CAN1 remapping
    constexpr static uint8_t PD01_REMAP[]{
      15,
      1
    }; //< Port D0/Port D1 mapping on OSCIN/OSCOUT
    constexpr static uint8_t TIM5CH4_IREMAP[]{
      16,
      1
    }; //< Set and cleared by software
    constexpr static uint8_t ADC1_ETRGINJ_REMAP[]{
      17,
      1
    }; //< ADC 1 External trigger injected conversion remapping
    constexpr static uint8_t ADC1_ETRGREG_REMAP[]{
      18,
      1
    }; //< ADC 1 external trigger regular conversion remapping
    constexpr static uint8_t ADC2_ETRGINJ_REMAP[]{
      19,
      1
    }; //< ADC 2 external trigger injected conversion remapping
    constexpr static uint8_t ADC2_ETRGREG_REMAP[]{
      20,
      1
    }; //< ADC 2 external trigger regular conversion remapping
    constexpr static uint8_t SWJ_CFG[]{ 24,
                                        3 }; //< Serial wire JTAG configuration
  };

  struct EXTICR1
  {
    constexpr static uint8_t EXTI0[]{ 0, 4 };  //< EXTI0 configuration
    constexpr static uint8_t EXTI1[]{ 4, 4 };  //< EXTI1 configuration
    constexpr static uint8_t EXTI2[]{ 8, 4 };  //< EXTI2 configuration
    constexpr static uint8_t EXTI3[]{ 12, 4 }; //< EXTI3 configuration
  };

  struct EXTICR2
  {
    constexpr static uint8_t EXTI4[]{ 0, 4 };  //< EXTI4 configuration
    constexpr static uint8_t EXTI5[]{ 4, 4 };  //< EXTI5 configuration
    constexpr static uint8_t EXTI6[]{ 8, 4 };  //< EXTI6 configuration
    constexpr static uint8_t EXTI7[]{ 12, 4 }; //< EXTI7 configuration
  };

  struct EXTICR3
  {
    constexpr static uint8_t EXTI8[]{ 0, 4 };   //< EXTI8 configuration
    constexpr static uint8_t EXTI9[]{ 4, 4 };   //< EXTI9 configuration
    constexpr static uint8_t EXTI10[]{ 8, 4 };  //< EXTI10 configuration
    constexpr static uint8_t EXTI11[]{ 12, 4 }; //< EXTI11 configuration
  };

  struct EXTICR4
  {
    constexpr static uint8_t EXTI12[]{ 0, 4 };  //< EXTI12 configuration
    constexpr static uint8_t EXTI13[]{ 4, 4 };  //< EXTI13 configuration
    constexpr static uint8_t EXTI14[]{ 8, 4 };  //< EXTI14 configuration
    constexpr static uint8_t EXTI15[]{ 12, 4 }; //< EXTI15 configuration
  };

  struct MAPR2
  {
    constexpr static uint8_t TIM9_REMAP[]{ 5, 1 };  //< TIM9 remapping
    constexpr static uint8_t TIM10_REMAP[]{ 6, 1 }; //< TIM10 remapping
    constexpr static uint8_t TIM11_REMAP[]{ 7, 1 }; //< TIM11 remapping
    constexpr static uint8_t TIM13_REMAP[]{ 8, 1 }; //< TIM13 remapping
    constexpr static uint8_t TIM14_REMAP[]{ 9, 1 }; //< TIM14 remapping
    constexpr static uint8_t FSMC_NADV[]{ 10, 1 };  //< NADV connect/disconnect
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

  static void assignLine(uint8_t reg, uint8_t line)
  {
    const uint8_t index = line >> 2;
    const uint8_t pos   = line & 0b11;

    rg()->EXTICR[index] =
      (rg()->EXTICR[index] & ~(0b1111 << pos)) | (reg << pos);
  }
};
#endif // __AFIO_H
