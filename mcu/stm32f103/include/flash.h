#ifndef FLASH_H
#define FLASH_H

#include "utility.h"
#include <cstdint>

struct Flash
{
  constexpr static uint32_t base = 0x40022000; //< Базовый адрес периферии

  ///
  /// \brief Структура регистров
  ///
  struct Regs
  {
    uint32_t ACR; ///< Регистр контроля доступа
  };

  ///
  /// \brief Структура описания полей регистра контроля доступа
  /// Каждое поле есть массив из двух элементов. Первый - смещение поля, второй
  /// - размер
  ///
  struct ACR
  {
    constexpr static uint8_t LATENCY[]{ 0, 3 };
    constexpr static uint8_t HLFCYA[]{ 3, 1 };
    constexpr static uint8_t PRFTBE[]{ 4, 1 };
    constexpr static uint8_t PRFTBS[]{ 5, 1 };
  };

  ///
  /// \brief Состояния поля LATENCY
  ///
  enum class Latency : uint8_t
  {
    zeroWaitState = 0b000,
    oneWaitState  = 0b001,
    twoWaitStates = 0b010
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

  ///
  /// \brief Функция установки времени ожидания и буфера упреждающей выборки
  /// \param latency время ожидания
  /// \param prefetchBufferEnable включение буфера упреждающей выборки
  ///
  static void setLatency(Flash::Latency latency,
                         bool           prefetchBufferEnable = false)
  {
    tl::setRegister(rg()->ACR,
                    ACR::LATENCY,
                    static_cast<uint8_t>(latency),
                    ACR::PRFTBE,
                    prefetchBufferEnable);
  }

  static bool getLatencyPrefetch()
  {
    return tl::isRegFieldsSet(rg()->ACR, ACR::LATENCY, ACR::PRFTBE);
  }
};

#endif // FLASH_H
