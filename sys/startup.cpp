
//#include "mcu.h"
#include"it.h"



//extern unsigned long _etext;
extern unsigned long _sidata;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;
extern unsigned long __ctors_start__;
extern unsigned long __ctors_end__;

//extern unsigned long __dtors_start__;
//extern unsigned long __dtors_end__;

extern int main(void);
void __Init_Data(void);

extern "C" void __libc_init_array();

///**********************************************************
/// \brief ISR::Reset
///
[[noreturn]] void Isr::Reset(void) {
    __asm ("ldr   r0, =_estack");
    __asm ("mov   sp, r0");

    // Enable FPU http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0553a/BEHBJHIG.html
#if FPU == 1
    __asm ("ldr.w   r0, =0xe000ed88");
    __asm ("ldr     r1, [r0]");
    __asm ("orr     r1, r1, #(0xf << 20)");
    __asm ("str     r1, [r0]");
    __asm ("dsb");
    __asm ("isb");
#endif
    __Init_Data();

    main();

    while(true) {};
}

/// \brief __Init_Data
///
void __Init_Data(void)
{
    unsigned long *pulSrc, *pulDest;

    pulSrc = &_sidata;

    for(pulDest = &_sdata; pulDest < &_edata; )
        *(pulDest++) = *(pulSrc++);

    for(pulDest = &_sbss; pulDest < &_ebss; )
        *(pulDest++) = 0;

    __asm__ __volatile__ ("cpsid i");
    __libc_init_array();                                            // low-level init & ctor loop
    __asm__ __volatile__ ("cpsie i");

    /* Call constructors */
    unsigned long *ctors;
    for(ctors = &__ctors_start__; ctors < &__ctors_end__; )
        ((void(*)())(*ctors++))();
}


