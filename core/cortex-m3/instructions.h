#pragma once
#include <cstdint>


struct cpu {
    static void nop(void) {
        __asm volatile ("nop");
    }

    // Synchronization
    static uint32_t ldrex(volatile uint32_t *addr) {
        uint32_t result;
        __asm volatile ("ldrex %0, %1" :
        "=r" (result) : "Q" (*addr));
        return result;
    }

    static uint16_t ldrex(volatile uint16_t *addr) {
        uint16_t result;
        __asm volatile ("ldrexh %0, %1" :
        "=r" (result) : "Q" (*addr));
        return result;
    }

    static uint8_t ldrex(volatile uint8_t *addr) {
        uint8_t result;
        __asm volatile ("ldrexb %0, %1" :
        "=r" (result) : "Q" (*addr));
        return result;
    }

    static bool ldrex(volatile bool *addr) {
        bool result;
        __asm volatile ("ldrexb %0, %1" :
        "=r" (result) : "Q" (*addr));
        return result;
    }

    static bool strex(uint32_t value, volatile uint32_t *addr) {
        bool result;
        __asm volatile ("strex %0, %2, %1" :
        "=&r" (result), "=Q" (*addr) :
        "r" (value));
        return (result);
    }

    static bool strex(uint16_t value, volatile uint16_t *addr) {
        bool result;
        __asm volatile ("strexh %0, %2, %1" :
        "=&r" (result), "=Q" (*addr) :
        "r" (value));
        return (result);
    }

    static bool strex(uint8_t value, volatile uint8_t *addr) {
        bool result;
        __asm volatile ("strexb %0, %2, %1" :
        "=&r" (result), "=Q" (*addr) :
        "r" (value));
        return (result);
    }

    static bool strex(bool value, volatile bool *addr) {
        bool result;
        __asm volatile ("strexb %0, %2, %1" :
        "=&r" (result), "=Q" (*addr) :
        "r" (value));
        return (result);
    }


    //----------------------------------------------------------------------------
    static void dmb(void) {
        __asm volatile ("dmb 0xF":: :"memory");
    }

    static void isb(void) {
        __asm volatile ("isb");
    }

    static void dsb(void) {
        __asm volatile ("dsb");
    }

    // Interrupts
    static void cpsie(void) {
        __asm volatile ("cpsie i");
    }

    static void cpsid(void) {
        __asm volatile ("cpsid i");
    }

    static void enableIrq(void) {
        __asm volatile ("cpsie i");
    }

    static void disableIrq(void) {
        __asm volatile ("cpsid i");
    }

    static uint32_t rev(uint32_t value) {
        uint32_t result;
        __asm volatile ("rev %0, %1" : "=r" (result) : "r" (value));

        return result;
    }

    static uint32_t rev16u(uint16_t value) {
        uint16_t result;
        __asm volatile ("rev16 %0, %1" : "=r" (result) : "r" (value));

        return result;
    }

    static int16_t rev16s(int16_t value) {
        int16_t result;
        __asm volatile ("rev16 %0, %1" : "=r" (result) : "r" (value));

        return result;
    }

    static uint32_t get_msp()
    {
      uint32_t regMainStackPointer;
      __asm volatile ("mrs %0, msp": "=r" (regMainStackPointer));
      return(regMainStackPointer);
    }
};
