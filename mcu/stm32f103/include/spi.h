#ifndef SPI_H
#define SPI_H
#include "log.h"
#include "nvic.h"
#include "rcc.h"
#include <cstdint>

template<int num>
struct spi_t;

template<>
struct spi_t<1>
{
  constexpr static uint32_t SPI_BASE = 0x40013000;

  static void clockEnable(const bool val)
  {
    Rcc::clockSpi1(val);
  }
  constexpr static uint32_t SPI_IRQn =
    Nvic::itSpi1; ///< I2C1 event global interrupt
};

template<>
struct spi_t<2>
{
  constexpr static uint32_t SPI_BASE = 0x40003800;

  static void clockEnable(const bool val)
  {
    Rcc::clockSpi2(val);
  }
  constexpr static uint32_t SPI_IRQn =
    Nvic::itSpi2; ///< I2C1 event global interrupt
};

template<>
struct spi_t<3>
{
  constexpr static uint32_t SPI_BASE = 0x40003C00;

  static void clockEnable(const bool val)
  {
    Rcc::clockSpi3(val);
  }
  constexpr static uint32_t SPI_IRQn =
    Nvic::itSpi3; ///< I2C1 event global interrupt
};

template<int num>
struct Spi
{

  struct CR1
  {
    constexpr static uint8_t BIDIMODE[]{ 15,
                                         1 }; //< Bidirectional data mode enable
    constexpr static uint8_t BIDIOE[]{
      14,
      1
    }; //< Output enable in bidirectional mode
    constexpr static uint8_t CRCEN[]{ 13,
                                      1 }; //< Hardware CRC calculation enable
    constexpr static uint8_t CRCNEXT[]{ 12, 1 }; //< CRC transfer next
    constexpr static uint8_t DFF[]{ 11, 1 };     //< Data frame format
    constexpr static uint8_t RXONLY[]{ 10, 1 };  //< Receive only
    constexpr static uint8_t SSM[]{ 9, 1 };      //< Software slave management
    constexpr static uint8_t SSI[]{ 8, 1 };      //< Internal slave select
    constexpr static uint8_t LSBFIRST[]{ 7, 1 }; //< Frame format
    constexpr static uint8_t SPE[]{ 6, 1 };      //< SPI enable
    constexpr static uint8_t BR[]{ 3, 3 };       //< Baud rate control
    constexpr static uint8_t MSTR[]{ 2, 1 };     //< Master selection
    constexpr static uint8_t CPOL[]{ 1, 1 };     //< Clock polarity
    constexpr static uint8_t CPHA[]{ 0, 1 };     //< Clock phase
  };

  struct CR2
  {
    constexpr static uint8_t TXEIE[]{ 7,
                                      1 }; //< Tx buffer empty interrupt enable
    constexpr static uint8_t RXNEIE[]{
      6,
      1
    }; //< RX buffer not empty interrupt enable
    constexpr static uint8_t ERRIE[]{ 5, 1 };   //< Error interrupt enable
    constexpr static uint8_t SSOE[]{ 2, 1 };    //< SS output enable
    constexpr static uint8_t TXDMAEN[]{ 1, 1 }; //< Tx buffer DMA enable
    constexpr static uint8_t RXDMAEN[]{ 0, 1 }; //< Rx buffer DMA enable
  };

  struct SR
  {
    constexpr static uint8_t BSY[]{ 7, 1 };    //< Busy flag
    constexpr static uint8_t OVR[]{ 6, 1 };    //< Overrun flag
    constexpr static uint8_t MODF[]{ 5, 1 };   //< Mode fault
    constexpr static uint8_t CRCERR[]{ 4, 1 }; //< CRC error flag
    constexpr static uint8_t UDR[]{ 3, 1 };    //< Underrun flag
    constexpr static uint8_t CHSIDE[]{ 2, 1 }; //< Channel side
    constexpr static uint8_t TXE[]{ 1, 1 };    //< Transmit buffer empty
    constexpr static uint8_t RXNE[]{ 0, 1 };   //< Receive buffer not empty
  };

  //    struct DR {
  //        constexpr static uint8_t DR[]{ 0, 16 }; 	//< Data register
  //    };

  struct CRCPR
  {
    constexpr static uint8_t CRCPOLY[]{ 0, 16 }; //< CRC polynomial register
  };

  struct RXCRCR
  {
    constexpr static uint8_t RxCRC[]{ 0, 16 }; //< Rx CRC register
  };

  struct TXCRCR
  {
    constexpr static uint8_t TxCRC[]{ 0, 16 }; //< Tx CRC register
  };

  struct I2SCFGR
  {
    constexpr static uint8_t I2SMOD[]{ 11, 1 }; //< I2S mode selection
    constexpr static uint8_t I2SE[]{ 10, 1 };   //< I2S Enable
    constexpr static uint8_t I2SCFG[]{ 8, 2 };  //< I2S configuration mode
    constexpr static uint8_t PCMSYNC[]{ 7, 1 }; //< PCM frame synchronization
    constexpr static uint8_t I2SSTD[]{ 4, 2 };  //< I2S standard selection
    constexpr static uint8_t CKPOL[]{ 3, 1 };   //< Steady state clock polarity
    constexpr static uint8_t DATLEN[]{ 1, 2 }; //< Data length to be transferred
    constexpr static uint8_t CHLEN[]{
      0,
      1
    }; //< Channel length (number of bits per audio channel)
  };

  struct I2SPR
  {
    constexpr static uint8_t MCKOE[]{ 9, 1 };  //< Master clock output enable
    constexpr static uint8_t ODD[]{ 8, 1 };    //< Odd factor for the prescaler
    constexpr static uint8_t I2SDIV[]{ 0, 8 }; //< I2S Linear prescaler
  };

  struct Regs
  {
    uint32_t CR1;     //< 0x0 control register 1
    uint32_t CR2;     //< 0x4 control register 2
    uint32_t SR;      //< 0x8 status register
    uint32_t DR;      //< 0xC data register
    uint32_t CRCPR;   //< 0x10 CRC polynomial register
    uint32_t RXCRCR;  //< 0x14 RX CRC register
    uint32_t TXCRCR;  //< 0x18 TX CRC register
    uint32_t I2SCFGR; //< 0x1C I2S configuration register
    uint32_t I2SPR;   //< 0x20 I2S prescaler register
  };

#ifdef DEBUG
  volatile Regs *const debug = reinterpret_cast<Regs *>(spi_t<num>::SPI_BASE);
#endif

  constexpr static uint32_t addressDr = spi_t<num>::SPI_BASE + (4 * 3);

  ///
  /// \brief Включение тактирования
  ///
  static void clockEnable(const bool value)
  {
    spi_t<num>::clockEnable(value);
  }

  ///
  /// \brief Получение указателя на регистры
  /// \return указатель на регистры
  ///
  static volatile Regs *rg()
  {
    return reinterpret_cast<volatile Regs *volatile>(spi_t<num>::SPI_BASE);
  }

  enum ClockPhase {
    cpFirstEdge  = 0,
    cpSecondEdge = 1
  };

  enum ClockPolarity {
    cpIdleLow  = 0,
    cpIdleHigh = 1
  };

  enum BaudRate {
    br2   = 0b000,
    br4   = 0b001,
    br8   = 0b010,
    br16  = 0b011,
    br32  = 0b100,
    br64  = 0b101,
    br128 = 0b110,
    br256 = 0b111,
  };

  static void initMasterDefault(Spi<num>::BaudRate baudRate,
                                ClockPolarity      clockPolarity,
                                ClockPhase         clockPhase,
                                bool               softSlaveManagement,
                                bool               softSlaveSelect)
  {
    clockEnable(true);

    tl::setRegister(rg()->CR1,
                    CR1::BR,
                    static_cast<uint8_t>(baudRate),
                    CR1::MSTR,
                    1,
                    CR1::CPOL,
                    clockPolarity,
                    CR1::CPHA,
                    clockPhase,
                    CR1::SSM,
                    softSlaveManagement,
                    CR1::SSI,
                    softSlaveSelect);
  }

  static uint8_t getIrqN()
  {
    return spi_t<num>::SPI_IRQn;
  }

  static void setBaudRate(Spi<num>::BaudRate baud_rate)
  {
    tl::setRegister(rg()->CR1, CR1::BR, static_cast<uint8_t>(baud_rate));
  }



  constexpr static void setBaudRate(uint32_t baud_rate)
  {
    uint8_t log = 0;
    uint32_t frequency = Rcc::apb1Clk() / baud_rate;

    while (frequency) {
      ++log;
      frequency >>= 1;
    }
    tl::setRegister(rg()->CR1, CR1::BR, log);
  }

  static void enable(const bool value)
  {
    tl::setRegister(rg()->CR1, CR1::SPE, value);
  }

  static volatile uint16_t *getDrAddress()
  {
    return reinterpret_cast<volatile uint16_t *>(&(rg()->DR));
  }

  static void rxneIntEnable(bool value)
  {
    tl::setRegister(rg()->CR2, CR2::RXNEIE, value);
  }

  static void txeIntEnable(bool value)
  {
    tl::setRegister(rg()->CR2, CR2::TXEIE, value);
  }

  static void rxDmaEnable(bool value)
  {
    tl::setRegister(rg()->CR2, CR2::RXDMAEN, value);
  }

  static void txDmaEnable(bool value)
  {
    tl::setRegister(rg()->CR2, CR2::TXDMAEN, value);
  }

  static void setBiDirectionalMode(bool value)
  {
    tl::setRegister(rg()->CR1, CR1::BIDIMODE, value);
  }

  static void setRxOnly(bool value)
  {
    tl::setRegister(rg()->CR12, CR1::RXONLY, value);
  }

  static void setSoftwareSlaveManagement(bool value)
  {
    tl::setRegister(rg()->CR1, CR1::SSM, value);
  }

  static void setInternalSlaveSelect(bool value)
  {
    tl::setRegister(rg()->CR1, CR1::SSI, value);
  }

  static void setMasterMode()
  {
    tl::setRegister(rg()->CR1, CR1::MSTR, 1);
  }

  static void setSlaveMode()
  {
    tl::setRegister(rg()->CR1, CR1::MSTR, 0);
  }

  static void setClockPolarity(ClockPolarity clockPolarity)
  {
    tl::setRegister(rg()->CR1, CR1::CPOL, clockPolarity);
  }

  static void setClockPhase(ClockPhase clockPhase)
  {
    tl::setRegister(rg()->CR1, CR1::CPHA, clockPhase);
  }

  template<typename T>
  static void set_dr(T value)
  {
    rg()->DR = value;
  }
  static uint16_t get_dr()
  {
    return rg()->DR;
  }

  static void stubRead()
  {
    volatile uint16_t stub = rg()->DR;
  }

  static bool is_tx_empty()
  {
    return tl::getRegField(rg()->SR, SR::TXE);
  }

  static bool is_rx_not_empty()
  {
    return tl::getRegField(rg()->SR, SR::TXE);
  }

  static bool is_busy()
  {
    return tl::getRegField(rg()->SR, SR::BSY);
  }

//  static bool wait_for_txe(uint32_t counter) {}

  static void printRegs()
  {
    con.debug() << "SPI " << Use::dec << Use::w0 << num << ": " << Use::endl
                << Use::w8 << Use::hex;
    con.debug() << Use::w8 << "  CR1:     " << rg()->CR1 << Use::endl;
    con.debug() << Use::w8 << "  CR2:     " << rg()->CR2 << Use::endl;
    con.debug() << Use::w8 << "  SR:      " << rg()->SR << Use::endl;
    con.debug() << Use::w8 << "  DR:      " << rg()->DR << Use::endl;
    con.debug() << Use::w8 << "  CRCPR:   " << rg()->CRCPR << Use::endl;
    con.debug() << Use::w8 << "  RXCRCR:  " << rg()->RXCRCR << Use::endl;
    con.debug() << Use::w8 << "  TXCRCR:  " << rg()->TXCRCR << Use::endl;
    con.debug() << Use::w8 << "  I2SCFGR: " << rg()->I2SCFGR << Use::endl;
    con.debug() << Use::w8 << "  I2SPR:   " << rg()->I2SPR << Use::endl;
  }
};

#endif // SPI_H
