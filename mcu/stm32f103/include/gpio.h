#ifndef GPIO_H
#define GPIO_H

#include "rcc.h"
#include "utility.h"

// Base addresses
template<char a>
struct gpio_t;

template<>
struct gpio_t<'A'>
{
  constexpr static uint32_t GPIO_BASE = 0x40010800;

  static void clockEnable(bool value)
  {
    Rcc::clockIopA(value);
  }
};

template<>
struct gpio_t<'B'>
{
  constexpr static uint32_t GPIO_BASE = 0x40010C00;

  static void clockEnable(bool value)
  {
    Rcc::clockIopB(value);
  }
};

template<>
struct gpio_t<'C'>
{
  constexpr static uint32_t GPIO_BASE = 0x40011000;

  static void clockEnable(bool value)
  {
    Rcc::clockIopC(value);
  }
};

template<>
struct gpio_t<'D'>
{
  constexpr static uint32_t GPIO_BASE = 0x40011400;

  static void clockEnable(bool value)
  {
    Rcc::clockIopD(value);
  }
};

template<>
struct gpio_t<'E'>
{
  constexpr static uint32_t GPIO_BASE = 0x40011800;

  static void clockEnable(bool value)
  {
    Rcc::clockIopE(value);
  }
};

/**
 * PinMode enumeration. Defines all possible values for MODER register.
 */
enum PinMode {
  pmInput       = 0,
  pmOutput10Mhz = 1,
  pmOutput2Mhz  = 2,
  pmOutput50Mhz = 3
};

enum PinConfiguration {
  imAnalog       = 0,
  imFloating     = 1,
  imPull         = 2,
  omPushPull     = 0,
  omOpenDrain    = 1,
  omAltPushPull  = 2,
  omAltOpenDrain = 3,
};

struct GpioRawRegs
{
  uint32_t CR[2];
  uint32_t IDR;
  uint32_t ODR;
  uint32_t BSRR;
  uint32_t BRR;
  uint32_t LCKR;
};

template<char a>
struct Gpio
{

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

  struct MAPR2
  {
    constexpr static uint8_t TIM9_REMAP[]{ 5, 1 };  //< TIM9 remapping
    constexpr static uint8_t TIM10_REMAP[]{ 6, 1 }; //< TIM10 remapping
    constexpr static uint8_t TIM11_REMAP[]{ 7, 1 }; //< TIM11 remapping
    constexpr static uint8_t TIM13_REMAP[]{ 8, 1 }; //< TIM13 remapping
    constexpr static uint8_t TIM14_REMAP[]{ 9, 1 }; //< TIM14 remapping
    constexpr static uint8_t FSMC_NADV[]{ 10, 1 };  //< NADV connect/disconnect
  };

  struct Afio
  {
    uint32_t EVCR;
    uint32_t MAPR;
    uint32_t EXTICR[4];
    uint32_t RESERVED;
    uint32_t MAPR2;
  };

  /// \brief Получение указателя на регистры в "сыром" виде
  /// \return указатель на регистры в "сыром" виде
   static volatile GpioRawRegs *rgRaw()
  {
    return reinterpret_cast<GpioRawRegs *>(gpio_t<a>::GPIO_BASE);
  }

  static volatile Afio *rgAfio()
  {
    return reinterpret_cast<Afio *>(0x40010000);
  }

  /// \brief Включение тактирования
  static void clockEnable(bool value)
  {
    gpio_t<a>::clockEnable(value);
  }

    /// \brief Установка альтернативной функции
    /// \param val альтернативная функция
    /// \param args список номеров пинов
     template<typename T>
    static void setMode(const PinMode          mode,
                        const PinConfiguration configuration,
                        const T                pos)
  {
    uint32_t       index = (pos & 0x8) >> 3;
    const T        pos8  = pos & 0x7;
    uint32_t       mask  = tl::setBitGroup(4, (1 << 4) - 1, pos8);
    const uint32_t cfg   = mode | (configuration << 2);

    uint32_t value = tl::setBitGroup(4, cfg, pos8);

    rgRaw()->CR[index] = (rgRaw()->CR[index] & (~mask)) | value;
  }

  /// \brief Установка альтернативной функции
  /// \param val альтернативная функция
  /// \param args список номеров пинов
   template<typename T, typename... Args>
  static void setMode(const PinMode          mode,
                      const PinConfiguration configuration,
                      const T                pos,
                      const Args... args)
  {
    uint32_t       index = (pos & 0x8) >> 3;
    const T        pos8  = pos & 0x7;
    uint32_t       mask  = tl::setBitGroup(4, (1 << 4) - 1, pos8);
    const uint32_t cfg   = mode | (configuration << 2);

    uint32_t value = tl::setBitGroup(4, cfg, pos8);

    rgRaw()->CR[index] = (rgRaw()->CR[index] & (~mask)) | value;

    setMode(mode, configuration, args...);
  }

  template<typename... Args>
  static void setPin(const Args... args)
  {
    uint32_t value = tl::setBitGroup(1, 1, args...);

    rgRaw()->BSRR = rgRaw()->BSRR | value;
  }

  /// \brief Установка пинов в 0
  /// \param args список номеров пинов
   template<typename... Args>
  static void resetPin(const Args... args)
  {
    uint32_t value = tl::setBitGroup(1, 1, args...);

    rgRaw()->BSRR = rgRaw()->BSRR | (value << 16);
  }

  /// \brief Установка состояния пинов
  /// \param val выходное значение
  /// \param args список номеров пинов
  template<typename... Args>
  static void setOut(uint8_t val, const Args... args)
  {
    uint32_t mask  = tl::setBitGroup(1, (1 << 1) - 1, args...);
    uint32_t value = tl::setBitGroup(1, val, args...);

    rgRaw()->ODR = (rgRaw()->ODR & (~mask)) | value;
  }

  /// \brief Получение значения пина
  /// \param pin номер пина
  static bool get(uint8_t pin)
  {
    return (rgRaw()->IDR & (1 << pin));
  }
};

// Dynamic GPIO section
GpioRawRegs *gpio_get_regs(const uint8_t port)
{
  constexpr uint32_t regs[]{
    0x40010800, 0x40010C00, 0x40011000, 0x40011400, 0x40011800,
  };

  return reinterpret_cast<GpioRawRegs *>(regs[port - 'A']);
}

void gpio_set_mode(const uint8_t          port,
                   const PinMode          mode,
                   const PinConfiguration configuration,
                   const uint8_t          pin)
{
  uint32_t       index = (pin & 0x8) >> 3;
  const uint8_t  pos8  = pin & 0x7;
  uint32_t       mask  = tl::setBitGroup(4, (1 << 4) - 1, pos8);
  const uint32_t cfg   = mode | (configuration << 2);

  uint32_t value = tl::setBitGroup(4, cfg, pos8);

  gpio_get_regs(port)->CR[index] =
    (gpio_get_regs(port)->CR[index] & (~mask)) | value;
}

#endif // GPIO_H
