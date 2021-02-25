/**

Now only external interrupts 0-15 supported
RCC clock is enabled only for SYSCFG

Example of usage:

typedef Exti<'A', 8> StrobeExti;
StrobeExti::set(0x3, 2, 0);
StrobeExti::enable();

 */
#ifndef EXTI_H
#define EXTI_H

#include "afio.h"
#include "nvic.h"
#include "rcc.h"
#include <cstddef>
#include <cstdint>

///
/// Definition of the interrupt number for current pin
///
template<int pin>
struct ExtiIrqN;
template<>
struct ExtiIrqN<0>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti0;
};
template<>
struct ExtiIrqN<1>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti1;
};
template<>
struct ExtiIrqN<2>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti2;
};
template<>
struct ExtiIrqN<3>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti3;
};
template<>
struct ExtiIrqN<4>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti4;
};
template<>
struct ExtiIrqN<5>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti9_5;
};
template<>
struct ExtiIrqN<6>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti9_5;
};
template<>
struct ExtiIrqN<7>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti9_5;
};
template<>
struct ExtiIrqN<8>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti9_5;
};
template<>
struct ExtiIrqN<9>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti9_5;
};
template<>
struct ExtiIrqN<10>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti15_10;
};
template<>
struct ExtiIrqN<11>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti15_10;
};
template<>
struct ExtiIrqN<12>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti15_10;
};
template<>
struct ExtiIrqN<13>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti15_10;
};
template<>
struct ExtiIrqN<14>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti15_10;
};
template<>
struct ExtiIrqN<15>
{
  constexpr static Nvic::IrqType extiIrqN = Nvic::itExti15_10;
};

///
/// Template to control EXTI interrupts
///
template<char port, int pin>
struct Exti
{
  constexpr static uint32_t base = 0x40010400;

  struct Regs
  {
    uint32_t IMR;
    uint32_t EMR;
    uint32_t RTSR;
    uint32_t FTSR;
    uint32_t SWIER;
    uint32_t PR;
  };
#ifdef DEBUG
  volatile Regs *const debug = reinterpret_cast<Regs *>(base);
#endif
  //    constexpr static volatile Regs* const rcc =
  //    /*reinterpret_cast<Regs*>*/(Regs*)(BASE);

  ///---------------------------------------------------------------------
  ///
  /// \brief Получение указателя на регистры
  /// \return указатель на регистры
  ///
  static volatile Regs *rg()
  {
    return reinterpret_cast<Regs *volatile>(base);
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Включение тактирования
  ///
  static void clockEnable(const bool en)
  {
    //  Rcc::clockSyscfg(en);
  }

  static void setMask(bool value)
  {
    rg()->IMR = (rg()->IMR & (~(1 << pin))) | (value << pin);
  }

  static void setEvent(bool value)
  {
    rg()->EMR = (rg()->EMR & (~(1 << pin))) | (value << pin);
  }

  static void setRising(bool value)
  {
    rg()->RTSR = (rg()->RTSR & (~(1 << pin))) | (value << pin);
  }

  static void setFalling(bool value)
  {
    rg()->FTSR = (rg()->FTSR & (~(1 << pin))) | (value << pin);
  }

  static void clearPending()
  {
    rg()->PR |= (1 << pin);
  }

  static bool isPending()
  {
    return (rg()->PR & (1 << pin));
  }

  static void assignLine()
  {
    Afio::assignLine(port, pin);
  }

  static Nvic::IrqType getIrqN()
  {
    return ExtiIrqN<pin>::extiIrqN;
  }
};

#endif // EXTI_H
