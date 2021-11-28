#ifndef SPI_H
#define SPI_H
#include "log/log.h"
#include "nvic.h"
#include "rcc.h"
#include "gcem.hpp"
#include <cstdint>
#include <optional>

template<int num> struct spi_t;

template<> struct spi_t<1>
{
    constexpr static uint32_t SPI_BASE = 0x40013000;
    static void clockEnable(const bool en) { Rcc::clockSpi1(en);}
    constexpr static uint32_t SPI_IRQn                = Nvic::itSpi1;     ///< I2C1 event global interrupt
    static uint8_t getPrescaler() { return Rcc::getApb2Pre(); }

};

template<> struct spi_t<2>
{
    constexpr static uint32_t SPI_BASE = 0x40003800;
    static void clockEnable(const bool en) { Rcc::clockSpi2(en); }
    constexpr static uint32_t SPI_IRQn                = Nvic::itSpi2;     ///< I2C1 event global interrupt
    static uint8_t getPrescaler() { return Rcc::getApb1Pre(); }
};

template<> struct spi_t<3>
{
    constexpr static uint32_t SPI_BASE = 0x40003C00;
    static void clockEnable(const bool en) { Rcc::clockSpi3(en); }
    constexpr static uint32_t SPI_IRQn                = Nvic::itSpi3;     ///< I2C1 event global interrupt
    static uint8_t getPrescaler() { return Rcc::getApb1Pre(); }
};

template<> struct spi_t<4>
{
    constexpr static uint32_t SPI_BASE = 0x40013400;
    static void clockEnable(const bool en) { Rcc::clockSpi4(en); }
    constexpr static uint32_t SPI_IRQn                = Nvic::itSpi4;     ///< I2C1 event global interrupt
    static uint8_t getPrescaler() { return Rcc::getApb2Pre(); }
};

template<> struct spi_t<5>
{
    constexpr static uint32_t SPI_BASE = 0x40015000;
    static void clockEnable(const bool en) { Rcc::clockSpi5(en); }
    constexpr static uint32_t SPI_IRQn                = Nvic::itSpi5;     ///< I2C1 event global interrupt
    static uint8_t getPrescaler() { return 0; }
};

template<> struct spi_t<6>
{
    constexpr static uint32_t SPI_BASE = 0x40015400;
    static void clockEnable(const bool en) { Rcc::clockSpi6(en); }
    constexpr static uint32_t SPI_IRQn                = Nvic::itSpi6;     ///< I2C1 event global interrupt
    static uint8_t getPrescaler() { return 0; } //
};


template<int num>
struct Spi {

  constexpr static uint32_t maxCnt = 10165536;

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
    static void clockEnable(const bool en)
    {
        spi_t<num>::clockEnable(en);
    }


    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    static volatile Regs* rg()
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



    static uint8_t getIrqN() { return spi_t<num>::SPI_IRQn; }

    constexpr static void setBaudRate([[maybe_unused]] uint32_t br)
    {
        auto b = gcem::log2(Rcc::systemCoreClock() / spi_t<num>::getPrescaler());
        uint8_t d = b - 1;
        rg()->CR1.BR = d;
    }


    static void enable() { rg()->CR1.SPE = 1; }
    static void disable() { rg()->CR1.SPE = 0; }
    static volatile uint16_t* getDrAddress() {return  reinterpret_cast<volatile uint16_t*>(&(rg()->DR)); }

    static void rxNeIntEnable(bool en) { rg()->CR2.RXNEIE = en; }
    static void txeIntEnable(bool en) { rg()->CR2.TXEIE = en; }

    static void rxDmaEnable(bool en) { rg()->CR2.RXDMAEN = en; }
    static void txDmaEnable(bool en) { rg()->CR2.TXDMAEN = en; }
    static void setBiDirectionalMode(bool en) { rg()->CR1.BIDIMODE = en; }
    static void setRxOnly(bool en) { rg()->CR1.RXONLY = en; }
    static void setSoftwareSlaveManagenemt(bool en) { rg()->CR1.SSM = en; }
    static void setInternalSlaveSelect(bool en) { rg()->CR1.SSI = en; }
    static void setMasterMode() { rg()->CR1.MSTR = 1; }
    static void setSlaveMode() { rg()->CR1.MSTR = 0; }
    static void setClockPolarity(ClockPolarity cp) { rg()->CR1.CPOL = cp; }
    static void setClockPhase(ClockPhase cp) { rg()->CR1.CPHA = cp; }
    static void stubRead() { [[maybe_unused]] volatile uint16_t stub = rg()->DR.DR; }

    static bool writeByte(const uint8_t byte)
    {
      constexpr uint32_t maxCnt = 10165536;
      uint32_t cnt = maxCnt;
      rg()->CR1.SPE = 1;
      while (!rg()->SR.TXE) {
        --cnt;
        if (0 == cnt) {
          return false;
        }
      }

      rg()->DR.DR = byte;
      cnt = maxCnt;
      while (rg()->SR.BSY) {
        --cnt;
        if (0 == cnt) {
          rg()->CR1.SPE = 0;
          return false;
        }
      }
      rg()->CR1.SPE = 0;
      return true;
    }

    static std::optional<uint8_t>readByte()
    {
      constexpr uint32_t maxCnt = 10165536;
      uint32_t cnt = maxCnt;

      rg()->CR1.SPE = 1;
      rg()->DR.DR = 0;
      while (!rg()->SR.RXNE) {
        --cnt;
        if (0 == cnt) {
          rg()->CR1.SPE = 0;
          return std::nullopt;
        }
      }

      uint8_t byte = rg()->DR.DR;
      rg()->CR1.SPE = 0;
      return std::optional<uint8_t>{ byte };
    }

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

    static void printRegs()
    {
      con.debug() << "SPI " <<  Use::dec << Use::w0
            << num << ": " << Use::endl
            << Use::w8 << Use::hex;
      con.debug() << Use::w8 << "  CR1:     " << tl::asWord(rg()->CR1) << Use::endl;
      con.debug() << Use::w8 << "  CR2:     " << tl::asWord(rg()->CR2) << Use::endl;
      con.debug() << Use::w8 << "  SR:      " << tl::asWord(rg()->SR) << Use::endl;
      con.debug() << Use::w8 << "  DR:      " << tl::asWord(rg()->DR) << Use::endl;
      con.debug() << Use::w8 << "  CRCPR:   " << tl::asWord(rg()->CRCPR) << Use::endl;
      con.debug() << Use::w8 << "  RXCRCR:  " << tl::asWord(rg()->RXCRCR) << Use::endl;
      con.debug() << Use::w8 << "  TXCRCR:  " << tl::asWord(rg()->TXCRCR) << Use::endl;
      con.debug() << Use::w8 << "  I2SCFGR: " << tl::asWord(rg()->I2SCFGR) << Use::endl;
      con.debug() << Use::w8 << "  I2SPR:   " << tl::asWord(rg()->I2SPR) << Use::endl;
    }

  static bool write(uint8_t* pBuf, uint16_t len)
  {
    uint32_t cnt = maxCnt;

    rg()->CR1.SPE = 1;
    for (uint16_t idx = 0; idx < len; ++idx) {

      while (!rg()->SR.TXE) {
        --cnt;
        if (0 == cnt) {
          return false;
        }
      }
      rg()->DR.DR = pBuf[idx];
    }
    cnt = maxCnt;
    while (rg()->SR.BSY) {
      --cnt;
      if (0 == cnt) {
        rg()->CR1.SPE = 0;
        return false;
      }
    }
    rg()->CR1.SPE = 0;
    return true;
  }

  static bool read(uint8_t* pBuf, uint16_t len)
  {
    uint32_t cnt = maxCnt;
    rg()->CR1.SPE = 1;
    for (uint16_t idx = 0; idx < len; ++idx) {

      rg()->DR.DR = 0;

      while (!rg()->SR.RXNE) {
        --cnt;
        if (0 == cnt) {
          return false;
        }
      }
      pBuf[idx] = rg()->DR.DR;
    }
    cnt = maxCnt;
    while (rg()->SR.BSY) {
      --cnt;
      if (0 == cnt) {
        rg()->CR1.SPE = 0;
        return false;
      }
    }
    rg()->CR1.SPE = 0;
    return true;
  }



};

#endif // SPI_H
