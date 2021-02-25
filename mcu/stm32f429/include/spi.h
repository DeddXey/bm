#ifndef SPI_H
#define SPI_H
#include "dbg.h_"
#include "nvic.h"
#include "rcc.h"
#include <cmath>
#include <stdint.h>
#include <stdio.h>

template<int num> struct spi_t;

template<> struct spi_t<1>
{
    constexpr static uint32_t SPI_BASE = 0x40013000;
    static void INLINE clockEnable(const bool en) { Rcc::clockSpi1(en);}
    constexpr static uint32_t SPI_IRQn                = Nvic::itSpi1;     ///< I2C1 event global interrupt
    static uint8_t INLINE getPrescaler() { return Rcc::getApb2Pre(); }

};

template<> struct spi_t<2>
{
    constexpr static uint32_t SPI_BASE = 0x40003800;
    static void INLINE clockEnable(const bool en) { Rcc::clockSpi2(en); }
    constexpr static uint32_t SPI_IRQn                = Nvic::itSpi2;     ///< I2C1 event global interrupt
    static uint8_t INLINE getPrescaler() { return Rcc::getApb1Pre(); }
};

template<> struct spi_t<3>
{
    constexpr static uint32_t SPI_BASE = 0x40003C00;
    static void INLINE clockEnable(const bool en) { Rcc::clockSpi3(en); }
    constexpr static uint32_t SPI_IRQn                = Nvic::itSpi3;     ///< I2C1 event global interrupt
    static uint8_t INLINE getPrescaler() { return Rcc::getApb1Pre(); }
};

template<> struct spi_t<4>
{
    constexpr static uint32_t SPI_BASE = 0x40013400;
    static void INLINE clockEnable(const bool en) { Rcc::clockSpi4(en); }
    constexpr static uint32_t SPI_IRQn                = Nvic::itSpi4;     ///< I2C1 event global interrupt
    static uint8_t INLINE getPrescaler() { return Rcc::getApb2Pre(); }
};

template<> struct spi_t<5>
{
    constexpr static uint32_t SPI_BASE = 0x40015000;
    static void INLINE clockEnable(const bool en) { Rcc::clockSpi5(en); }
    constexpr static uint32_t SPI_IRQn                = Nvic::itSpi5;     ///< I2C1 event global interrupt
    static uint8_t INLINE getPrescaler() { return 0; }
};

template<> struct spi_t<6>
{
    constexpr static uint32_t SPI_BASE = 0x40015400;
    static void INLINE clockEnable(const bool en) { Rcc::clockSpi6(en); }
    constexpr static uint32_t SPI_IRQn                = Nvic::itSpi6;     ///< I2C1 event global interrupt
    static uint8_t INLINE getPrescaler() { return 0; } //
};


template<int num>
struct Spi {


    struct CR1_t {
        uint32_t  CPHA:1;
        uint32_t  CPOL:1;
        uint32_t  MSTR:1;
        uint32_t  BR:3;
        uint32_t  SPE:1;
        uint32_t  LSBFIRST:1;
        uint32_t  SSI:1;
        uint32_t  SSM:1;
        uint32_t  RXONLY:1;
        uint32_t  DFF:1;
        uint32_t  CRCNEXT:1;
        uint32_t  CRCEN:1;
        uint32_t  BIDIOE:1;
        uint32_t  BIDIMODE:1;
        uint32_t  RESERVED:16;
    };

    struct CR2_t {
        uint32_t  RXDMAEN:1;
        uint32_t  TXDMAEN:1;
        uint32_t  SSOE:1;
        uint32_t  RESERVED1:1;
        uint32_t  FRF:1;
        uint32_t  ERRIE:1;
        uint32_t  RXNEIE:1;
        uint32_t  TXEIE:1;
        uint32_t  RESERVED2:16;
    };

    struct SR_t {
        uint32_t  RXNE:1;
        uint32_t  TXE:1;
        uint32_t  CHSIDE:1;
        uint32_t  UDR:1;
        uint32_t  CRCERR:1;
        uint32_t  MODF:1;
        uint32_t  OVR:1;
        uint32_t  BSY:1;
        uint32_t  FRE:1;
    };

    struct DR_t {
        uint32_t  DR:16;
    };

    struct CRCPR_t {
        uint32_t  CRCPOLY:16;
    };

    struct RXCRCR_t {
        uint32_t  RXCRCR:16;
    };

    struct TXCRCR_t {
        uint32_t  TXCRCR:16;
    };

    struct I2SCFGR_t {
        uint32_t  CHLEN:1;
        uint32_t  DATLEN:1;
        uint32_t  CKPOL:1;
        uint32_t  I2SSTD:1;
        uint32_t  RESERVED1:1;
        uint32_t  PCMSYNC:1;
        uint32_t  I2SCFG:2;
        uint32_t  I2SE:1;
        uint32_t  I2SMOD:1;
    };

    struct I2SPR_t {
        uint32_t  I2SDIV:8;
        uint32_t  ODD:1;
        uint32_t  MCKOE:1;
    };

    struct Regs {
        CR1_t       CR1;
        CR2_t       CR2;
        SR_t        SR;
        DR_t        DR;
        CRCPR_t     CRCPR;
        RXCRCR_t    RXCRCR;
        TXCRCR_t    TXCRCR;
        I2SCFGR_t   I2SCFGR;
        I2SPR_t     I2SPR;
    };

#ifdef DEBUG
    volatile Regs* const debug = reinterpret_cast<Regs*>(spi_t<num>::SPI_BASE);
#endif
    //    constexpr static volatile Regs* const i2c = /*reinterpret_cast<Regs*>*/(Regs*)(I2C_BASE);

    constexpr static uint32_t addressDr = spi_t<num>::SPI_BASE + (4 * 3);

    ///---------------------------------------------------------------------
    ///
    /// \brief Включение тактирования
    ///
    INLINE static void clockEnable(const bool en)
    {
        spi_t<num>::clockEnable(en);
    }


    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    INLINE static volatile Regs* rg()
    {
        return reinterpret_cast<volatile Regs* volatile>(spi_t<num>::SPI_BASE);
    }

    enum ClockPhase {
        cpFirstEdge = 0,
        cpSecondEdge = 1
    };

    enum ClockPolarity {
        cpIdleLow = 0,
        cpIdleHigh = 1
    };

    enum BaudRate {
        br2 = 0b000,
        br4 = 0b001,
        br8 = 0b010,
        br16 = 0b011,
        br32 = 0b100,
        br64 = 0b101,
        br128 = 0b110,
        br256 = 0b111,
    };



    INLINE static uint8_t getIrqN() { return spi_t<num>::SPI_IRQn; }
//    INLINE static void setBaudRate(Spi<num>::BaudRate br) { rg()->CR1.BR = br; }
    INLINE static void setBaudRate(uint32_t br)
    {
        auto b = log2f(Rcc::systemCoreClock() / spi_t<num>::getPrescaler());
        uint8_t d = b - 1;


        rg()->CR1.BR = d;
    }


    INLINE static void enable() { rg()->CR1.SPE = 1; }
    INLINE static void disable() { rg()->CR1.SPE = 0; }
    INLINE static volatile uint16_t* getDrAddress() {return  reinterpret_cast<volatile uint16_t*>(&(rg()->DR)); }

    INLINE static void rxneIntEnable(bool en) { rg()->CR2.RXNEIE = en; }
    INLINE static void txeIntEnable(bool en) { rg()->CR2.TXEIE = en; }

    INLINE static void rxDmaEnable(bool en) { rg()->CR2.RXDMAEN = en; }
    INLINE static void txDmaEnable(bool en) { rg()->CR2.TXDMAEN = en; }
    INLINE static void setBiDirectionalMode(bool en) { rg()->CR1.BIDIMODE = en; }
    INLINE static void setRxOnly(bool en) { rg()->CR1.RXONLY = en; }
    INLINE static void setSoftwareSlaveManagenemt(bool en) { rg()->CR1.SSM = en; }
    INLINE static void setInternalSlaveSelect(bool en) { rg()->CR1.SSI = en; }
    INLINE static void setMasterMode() { rg()->CR1.MSTR = 1; }
    INLINE static void setSlaveMode() { rg()->CR1.MSTR = 0; }
    INLINE static void setClockPolarity(ClockPolarity cp) { rg()->CR1.CPOL = cp; }
    INLINE static void setClockPhase(ClockPhase cp) { rg()->CR1.CPHA = cp; }
    INLINE static void stubRead() { UNUSED volatile uint16_t stub = rg()->DR.DR; }

    //------------------------------------------------------------------------
    template <typename T, typename S>
    static bool transaction(T& in, S& out)
    {

        constexpr uint32_t maxCnt = 10165536;

        auto j = std::begin(out);

        uint32_t cnt = maxCnt;

        for (auto &i : in) {

            while (!rg()->SR.TXE)
            {
                --cnt;
                if (0 == cnt) {
                    return false;
                }
            }
            rg()->DR.DR = i;

            if (j != std::end(out)) {

                cnt = maxCnt;

                while (!rg()->SR.RXNE)
                {
                    --cnt;
                    if (0 == cnt) {
                        return false;
                    }
                }
                *j = rg()->DR.DR;
                ++j;
            }
        }
        return true;
    }



    //------------------------------------------------------------------------
    static void printRegs()
    {
        dbg << "SPI " <<  Use::dec << Use::w0
            << num << ": " << Use::endl
            << Use::w8 << Use::hex;
        dbg << Use::w8 << "  CR1:     " << ::asWord(rg()->CR1) << Use::endl;
        dbg << Use::w8 << "  CR2:     " << ::asWord(rg()->CR2) << Use::endl;
        dbg << Use::w8 << "  SR:      " << ::asWord(rg()->SR) << Use::endl;
        dbg << Use::w8 << "  DR:      " << ::asWord(rg()->DR) << Use::endl;
        dbg << Use::w8 << "  CRCPR:   " << ::asWord(rg()->CRCPR) << Use::endl;
        dbg << Use::w8 << "  RXCRCR:  " << ::asWord(rg()->RXCRCR) << Use::endl;
        dbg << Use::w8 << "  TXCRCR:  " << ::asWord(rg()->TXCRCR) << Use::endl;
        dbg << Use::w8 << "  I2SCFGR: " << ::asWord(rg()->I2SCFGR) << Use::endl;
        dbg << Use::w8 << "  I2SPR:   " << ::asWord(rg()->I2SPR) << Use::endl;
    }

};



#endif // SPI_H
