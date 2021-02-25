#ifndef COMMON_H
#define COMMON_H

#include "dbg.h_"

template<char a>
static void gpioPrintRegs()
{
    dbg << "GPIO" <<  a << ": " << Use::endl
        << Use::w8 << Use::hex;

    dbg << "  MODER:   "
        << ::asWord(Gpio<a>::rgRaw()->MODER)
        << Use::endl;
    dbg << "  OTYPER:  "
        << ::asWord(Gpio<a>::rgRaw()->OTYPER)
        << Use::endl;
    dbg << "  OSPEEDR: "
        << ::asWord(Gpio<a>::rgRaw()->OSPEEDR)
        << Use::endl;
    dbg << "  PUPDR:   "
        << ::asWord(Gpio<a>::rgRaw()->PUPDR)
        << Use::endl;
    dbg << "  IDR:     "
        << ::asWord(Gpio<a>::rgRaw()->IDR)
        << Use::endl;
    dbg << "  ODR:     "
        << ::asWord(Gpio<a>::rgRaw()->ODR)
        << Use::endl;
    dbg << "  BSRR:    "
        << ::asWord(Gpio<a>::rgRaw()->BSRR)
        << Use::endl;
    dbg << "  LCKR:    "
        << ::asWord(Gpio<a>::rgRaw()->LCKR)
        << Use::endl;
    dbg << "  AFR[0]:  "
        << ::asWord(Gpio<a>::rgRaw()->AFR[0])
            << Use::endl;
    dbg << "  AFR[1]:  "
        << ::asWord(Gpio<a>::rgRaw()->AFR[1])
            << Use::endl;

}




#endif // COMMON_H
