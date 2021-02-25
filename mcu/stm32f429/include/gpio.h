#ifndef GPIO_H
#define GPIO_H


#include "rcc.h"

#include "bits.h"
#include "utility.h"


// Base addresses
template<char a> struct gpio_t;
template<> struct gpio_t<'A'>
{
    constexpr static uint32_t GPIO_BASE = 0x40020000;
    static void INLINE clockEnable(bool en) { Rcc::clockGpioA(en); }
};

template<> struct gpio_t<'B'>
{
    constexpr static uint32_t GPIO_BASE = 0x40020400;
    static void INLINE clockEnable(bool en) { Rcc::clockGpioB(en); }
};

template<> struct gpio_t<'C'>
{
    constexpr static uint32_t GPIO_BASE = 0x40020800;
    static void INLINE clockEnable(bool en) { Rcc::clockGpioC(en); }
};

template<> struct gpio_t<'D'>
{
    constexpr static uint32_t GPIO_BASE = 0x40020C00;
    static void INLINE clockEnable(bool en) { Rcc::clockGpioD(en); }
};

template<> struct gpio_t<'E'>
{
    constexpr static uint32_t GPIO_BASE = 0x40021000;
    static void INLINE clockEnable(bool en) { Rcc::clockGpioE(en); }
};

template<> struct gpio_t<'F'>
{
    constexpr static uint32_t GPIO_BASE = 0x40021400;
    static void INLINE clockEnable(bool en) { Rcc::clockGpioF(en); }
};

template<> struct gpio_t<'G'>
{
    constexpr static uint32_t GPIO_BASE = 0x40021800;
    static void INLINE clockEnable(bool en) { Rcc::clockGpioG(en); }
};

template<> struct gpio_t<'H'>
{
    constexpr static uint32_t GPIO_BASE = 0x40021C00;
    static void INLINE clockEnable(bool en) { Rcc::clockGpioH(en); }
};

template<> struct gpio_t<'I'>
{
    constexpr static uint32_t GPIO_BASE = 0x40022000;
    static void INLINE clockEnable(bool en) { Rcc::clockGpioI(en); }
};


/**
 * PinMode enumeration. Defines all possible values for MODER register.
 */
enum PinMode
{
    pmInput  = 0,
    pmOutput  = 1,
    pmAlternate  = 2,
    pmAnalog  = 3
};

/**
 * PullUpMode enumeration. Defines all possible values for PUPDR register.
 */
enum PullUpMode
{
    pupdNone  = 0,
    pupdUp = 1,
    pupdDown = 2
};

/**
 * PinSpeed enumeration. Defines all possible values for OSPEEDR register.
 */
enum PinSpeed
{
    sp2Mhz = 0,
    sp25Mhz = 1,
    sp50Mhz = 2,
    sp100Mhz = 3
};

/**
 * PinOutputType enumeration. Defines all possible values for OTYPER register.
 */
enum PinOutputType
{
    poPushPull = 0,
    poOpenDrain = 1
};

/**
 * PinAltFunction enumeration. Defines all possible arguments for Alternate() function.
 */
enum PinAltFunction
{
    afRtc50Hz   = 0x00,          ///< RTC_50Hz Alternate Function mapping
    afMco       = 0x00,          ///< MCO (MCO1 and MCO2) Alternate Function mapping
    afTamper    = 0x00,          ///< TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping
    afSwj       = 0x00,          ///< SWJ (SWD and JTAG) Alternate Function mapping
    afTrace     = 0x00,          ///< TRACE Alternate Function mapping

    afTim1      = 0x01,          ///< TIM1 Alternate Function mapping
    afTim2      = 0x01,          ///< TIM2 Alternate Function mapping

    afTim3      = 0x02,          ///< TIM3 Alternate Function mapping
    afTim4      = 0x02,          ///< TIM4 Alternate Function mapping
    afTim5      = 0x02,          ///< TIM5 Alternate Function mapping

    afTim8      = 0x03,          ///< TIM8 Alternate Function mapping
    afTim9      = 0x03,          ///< TIM9 Alternate Function mapping
    afTim10     = 0x03,          ///< TIM10 Alternate Function mapping
    afTim11     = 0x03,          ///< TIM11 Alternate Function mapping

    afI2C1      = 0x04,          ///< I2C1 Alternate Function mapping
    afI2C2      = 0x04,          ///< I2C2 Alternate Function mapping
    afI2C3      = 0x04,          ///< I2C3 Alternate Function mapping

    afSpi1      = 0x05,          ///< SPI1 Alternate Function mapping
    afSpi2      = 0x05,          ///< SPI2/I2S2 Alternate Function mapping
    afSpi3      = 0x05,          ///< SPI1 Alternate Function mapping
    afSpi4      = 0x05,          ///< SPI2/I2S2 Alternate Function mapping
    afSpi5      = 0x05,          ///< SPI1 Alternate Function mapping
    afSpi6      = 0x05,          ///< SPI2/I2S2 Alternate Function mapping

    afSpi2Ext   = 0x06,          ///< SPI3/I2S3 Alternate Function mapping
    afSpi3Ext   = 0x06,          ///< SPI3/I2S3 Alternate Function mapping

    afUsart1    = 0x07,          ///< USART1 Alternate Function mapping
    afUsart2    = 0x07,          ///< USART2 Alternate Function mapping
    afUsart3    = 0x07,          ///< USART3 Alternate Function mapping
    afI2S3Ext   = 0x07,          ///< I2S3ext Alternate Function mapping

    afUart4     = 0x08,          ///< UART4 Alternate Function mapping
    afUart5     = 0x08,          ///< UART5 Alternate Function mapping
	afUart6     = 0x08,          ///< USART6 Alternate Function mapping
	afUart7     = 0x08,          ///< USART7 Alternate Function mapping
	afUart8     = 0x08,          ///< USART8 Alternate Function mapping

    afCan1      = 0x09,          ///< CAN1 Alternate Function mapping
    afCan2      = 0x09,          ///< CAN2 Alternate Function mapping
    afTim12     = 0x09,          ///< TIM12 Alternate Function mapping
    afTim13     = 0x09,          ///< TIM13 Alternate Function mapping
    afTim14     = 0x09,          ///< TIM14 Alternate Function mapping
    afLcd9      = 0x09,          ///< LCD Alternate Function mapping


    afOtgFs    = 0x0A,          ///< OTG_FS Alternate Function mapping
    afOtgHs    = 0x0A,          ///< OTG_HS Alternate Function mapping

    afEth       = 0x0B,          ///< ETHERNET Alternate Function mapping

    afFsmc      = 0x0C,          ///< FSMC Alternate Function mapping
    afFmc       = 0x0C,          ///< FSMC Alternate Function mapping
    afOtgHsFs   = 0x0C,          ///< OTG HS configured in FS, Alternate Function mapping
    afSdio      = 0x0C,          ///< SDIO Alternate Function mapping

    afDcmi      = 0x0D,          ///< DCMI Alternate Function mapping

    afLcd14       = 0x0E,          ///< LCD Alternate Function mapping

    afEventout  = 0x0F           ///< EVENTOUT Alternate Function mapping
};

#include "dbg.h_"

template <char a>
struct Gpio {

    struct RawRegs {
        uint32_t    MODER;
        uint32_t    OTYPER;
        uint32_t    OSPEEDR;
        uint32_t    PUPDR;
        uint32_t    IDR;
        uint32_t    ODR;
        uint32_t    BSRR;
        uint32_t    LCKR;
        uint32_t    AFR[2];
    };

    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры в "сыром" виде
    /// \return указатель на регистры в "сыром" виде
    ///
    INLINE static volatile RawRegs* rgRaw()
    {
        return reinterpret_cast<RawRegs*>(gpio_t<a>::GPIO_BASE);
    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Включение тактирования
    ///
    INLINE static void clockEnable(bool en)
    {
        gpio_t<a>::clockEnable(en);
    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Установка альтернативной функции
    /// \param val альтернативная функция
    /// \param args список номеров пинов
    ///
    template<typename T>
    inline static void  setAltFunc(const int val, const T pos)
    {
        uint32_t mask = setBits(4, (1 << 4) - 1, pos);
        uint32_t value = setBits(4, val, pos);
        uint32_t index = (pos & 0x8) >> 3;

        rgRaw()->AFR[index] = (rgRaw()->AFR[index] & (~mask)) | value;

    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Установка альтернативной функции
    /// \param val альтернативная функция
    /// \param args список номеров пинов
    ///
    template<typename T, typename... Args>
    inline static void  setAltFunc(const int val, const T pos, const Args... args)
    {
        uint32_t mask = setBits(4, (1 << 4) - 1, pos);
        uint32_t value = setBits(4, val, pos);
        uint32_t index = (pos & 0x08) >> 3;

        rgRaw()->AFR[index] = (rgRaw()->AFR[index] & (~mask)) | value;

        setAltFunc(val, args...);
    }


    ///---------------------------------------------------------------------
    ///
    /// \brief Конфигурирование пина
    /// \param mode режим
    /// \param speed скорость
    /// \param type тип выхода
    /// \param pupd тип подтяжки
    /// \param args список номеров пинов
    ///
    template<typename... Args>
    INLINE static void configPins(const PinMode mode,
                                  const PinSpeed speed,
                                  const PinOutputType type,
                                  const PullUpMode pupd,
                                  const Args... args)
    {
       setMode(mode, args...);
       setSpeed(speed, args...);
       setOType(type, args...);
       setPuPd(pupd, args...);
    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Установка скорости
    /// \param speed скорость
    /// \param args список номеров пинов
    ///
    template<typename... Args>
    INLINE static void setSpeed(const PinSpeed speed, const Args... args)
    {
        uint32_t mask = setBits(2, (1 << 2) - 1, args...);
        uint32_t value = setBits(2, speed, args...);

        rgRaw()->OSPEEDR = (rgRaw()->OSPEEDR & (~mask)) | value;

    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Установка режима работы
    /// \param mode режим
    /// \param args список номеров пинов
    ///
    template<typename... Args>
    INLINE static void setMode(const PinMode mode, const Args... args)
    {
        uint32_t mask = setBits(2, (1 << 2) - 1, args...);
        uint32_t value = setBits(2, mode, args...);

        rgRaw()->MODER = (rgRaw()->MODER & (~mask)) | value;

    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Установка типа выхода
    /// \param type тип выхода
    /// \param args список номеров пинов
    ///
    template<typename... Args>
    INLINE static void setOType(const PinOutputType type, const Args... args)
    {
        uint32_t mask = setBits(1, (1 << 1) - 1, args...);
        uint32_t value = setBits(1, type, args...);

        rgRaw()->OTYPER = (rgRaw()->OTYPER & (~mask)) | value;

    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Установка подтяжки выхода
    /// \param mode тип подтяжки
    /// \param args список номеров пинов
    ///
    template<typename... Args>
    INLINE static void  setPuPd(PullUpMode mode, const Args... args)
    {
        uint32_t mask = setBits(2, (1 << 2) - 1, args...);
        uint32_t value = setBits(2, mode, args...);

        rgRaw()->PUPDR = (rgRaw()->PUPDR & (~mask)) | value;
    }


    ///---------------------------------------------------------------------
    ///
    /// \brief Установка состояния пинов
    /// \param val выходное значение
    /// \param args список номеров пинов
    ///
    template<typename... Args>
    INLINE static void  setOut(uint8_t val, const Args... args)
    {
        uint32_t mask = setBits(1, (1 << 1) - 1, args...);
        uint32_t value = setBits(1, val, args...);

        rgRaw()->ODR = (rgRaw()->ODR & (~mask)) | value;

    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Установка пинов в 1
    /// \param args список номеров пинов
    ///
    template<typename... Args>
    INLINE static void setPin (const Args... args)
    {
        uint32_t value = setBits(1, 1, args...);

        rgRaw()->BSRR = rgRaw()->BSRR | value;

    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Установка пинов в 0
    /// \param args список номеров пинов
    ///
    template<typename... Args>
    INLINE static void resetPin (const Args... args)
    {
        uint32_t value = setBits(1, 1, args...);

        rgRaw()->BSRR = rgRaw()->BSRR | (value << 16);

    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Получение значения пина
    /// \param pin номер пина
    ///
    INLINE static bool get(uint8_t pin)
    {
        return (rgRaw()->IDR & (1 << pin));
    }


    ///---------------------------------------------------------------------
    ///
    /// \brief Инверсия значения пинов
    /// \param args список номеров пинова
    ///
    template<typename... Args>
    INLINE static void cpl (const Args... args)
    {
         uint32_t value = setBits(1, 1, args...);

        rgRaw()->BSRR = rgRaw()->ODR ^ (value);
    }




};






#endif // GPIO_H

