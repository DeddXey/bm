#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>

struct Flash {

    struct ACR_t {
        uint32_t    LATENCY:4;
        uint32_t    RESERVED1:4;
        uint32_t    PRFTEN:1;
        uint32_t    ICEN:1;
        uint32_t    DCEN:1;
        uint32_t    ICRST:1;
        uint32_t    DCRST:1;
        uint32_t    RESERVED2:19;
    };


    struct SR_t {
        uint32_t    EOP:1;
        uint32_t    OPERR:1;
        uint32_t    RESERVED1:2;
        uint32_t    WRPERR:1;
        uint32_t    PGAERR:1;
        uint32_t    PGPERR:1;
        uint32_t    PGSERR:1;
        uint32_t    RDERR:1;
        uint32_t    RESERVED2:23;
    };

    struct CR_t {
        uint32_t    PG:1;
        uint32_t    SER:1;
        uint32_t    MER:1;
        uint32_t    SNB:5;
        uint32_t    PSIZE:2;
        uint32_t    RESERVED1:5;
        uint32_t    MER1:1;
        uint32_t    STRT:1;
        uint32_t    RESERVED2:7;
        uint32_t    EOPIE:1;
        uint32_t    ERRIE:1;
        uint32_t    RESERVED3:5;
        uint32_t    LOCK:1;
    };

    struct OPTCR_t {
        uint32_t    OPTLOCK:1;
        uint32_t    OPTSTRT:1;
        uint32_t    BOR_LEV:2;
        uint32_t    BFB2:1;
        uint32_t    WDG_SW:1;
        uint32_t    nRST_STOP:1;
        uint32_t    nRST_STDBY:1;
        uint32_t    RDP:8;
        uint32_t    nWRP:12;
        uint32_t    RESERVED1:2;
        uint32_t    DB1M:1;
        uint32_t    SPRMOD:1;
    };

    struct OPTCR1_t {
        uint32_t    RESERVED1:16;
        uint32_t    nWRP:12;
        uint32_t    RESERVED2:4;
    };


    struct Regs {
      ACR_t     ACR;
      uint32_t  KEYR;
      uint32_t  OPTKEYR;
      SR_t      SR;
      CR_t      CR;
      OPTCR_t   OPTCR;
      OPTCR1_t  OPTCR1;
    };

    constexpr static uint32_t BASE = 0x40023C00;

#ifdef DEBUG
    volatile Regs* const debug = reinterpret_cast<Regs*>(BASE);
#endif
//    constexpr static volatile Regs* const flash = /*static_cast<Regs*>*/(Regs*)(BASE);

    static volatile Regs* rg()
    {
        return reinterpret_cast<Regs*>(BASE);
    }


    ///---------------------------------------------------------------------
    ///
    /// \brief Установка времени запаздывания
    /// \param latency
    ///
    static void setLatency(uint8_t latency)
    {
        //flash->ACR.LATENCY = latency;
        rg()->ACR.LATENCY = latency;
    }

};





#endif // FLASH_H
