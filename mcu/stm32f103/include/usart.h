#ifndef __USART1_H
#define __USART1_H

#ifndef INLINE
#define INLINE __attribute__((__always_inline__)) inline
#endif

#include "log/log.h."
#include "nvic.h"
#include "rcc.h"
#include "utility.h"
#include <cstdint>

// Base addresses
template<int usart>
struct usart_t;
template<>
struct usart_t<1>
{
  constexpr static uint32_t base      = 0x40013800;
  constexpr static uint32_t interrupt = Nvic::itUsart1;
  static void INLINE        clockEnable(bool en)
  {
    Rcc::clockUsart1(en);
  }
};

template<>
struct usart_t<2>
{
  constexpr static uint32_t base      = 0x40004400;
  constexpr static uint32_t interrupt = Nvic::itUsart2;
  static void INLINE        clockEnable(bool en)
  {
    Rcc::clockUsart2(en);
  }
};

template<>
struct usart_t<3>
{
  constexpr static uint32_t base      = 0x40004800;
  constexpr static uint32_t interrupt = Nvic::itUsart3;
  static void INLINE        clockEnable(bool en)
  {
    Rcc::clockUsart3(en);
  }
};

// TODO uart
template<>
struct usart_t<4>
{
  constexpr static uint32_t base      = 0x40004C00;
  constexpr static uint32_t interrupt = Nvic::itUart4;
  static void INLINE        clockEnable(bool en)
  {
    Rcc::clockUart4(en);
  }
};

// TODO uart
template<>
struct usart_t<5>
{
  constexpr static uint32_t base      = 0x40005000;
  constexpr static uint32_t interrupt = Nvic::itUart5;
  static void INLINE        clockEnable(bool en)
  {
    Rcc::clockUart5(en);
  }
};

template<int usartNumber>
struct Usart
{

  constexpr static int num = usartNumber;

  struct Regs
  {
    uint32_t SR;   //< 0x0 Status register
    uint32_t DR;   //< 0x4 Data register
    uint32_t BRR;  //< 0x8 Baud rate register
    uint32_t CR1;  //< 0xC Control register 1
    uint32_t CR2;  //< 0x10 Control register 2
    uint32_t CR3;  //< 0x14 Control register 3
    uint32_t GTPR; //< 0x18 Guard time and prescaler register
  };

  struct SR
  {
    constexpr static uint8_t CTS[]{ 9, 1 };  //< CTS flag
    constexpr static uint8_t LBD[]{ 8, 1 };  //< LIN break detection flag
    constexpr static uint8_t TXE[]{ 7, 1 };  //< Transmit data register empty
    constexpr static uint8_t TC[]{ 6, 1 };   //< Transmission complete
    constexpr static uint8_t RXNE[]{ 5, 1 }; //< Read data register not empty
    constexpr static uint8_t IDLE[]{ 4, 1 }; //< IDLE line detected
    constexpr static uint8_t ORE[]{ 3, 1 };  //< Overrun error
    constexpr static uint8_t NE[]{ 2, 1 };   //< Noise error flag
    constexpr static uint8_t FE[]{ 1, 1 };   //< Framing error
    constexpr static uint8_t PE[]{ 0, 1 };   //< Parity error
  };

  struct DR
  {
    constexpr static uint8_t DR_[]{ 0, 9 }; //< Data value
  };

  struct BRR
  {
    constexpr static uint8_t DIV_Mantissa[]{ 4, 12 }; //< mantissa of USARTDIV
    constexpr static uint8_t DIV_Fraction[]{ 0, 4 };  //< fraction of USARTDIV
  };

  struct CR1
  {
    constexpr static uint8_t UE[]{ 13, 1 };   //< USART enable
    constexpr static uint8_t M[]{ 12, 1 };    //< Word length
    constexpr static uint8_t WAKE[]{ 11, 1 }; //< Wakeup method
    constexpr static uint8_t PCE[]{ 10, 1 };  //< Parity control enable
    constexpr static uint8_t PS[]{ 9, 1 };    //< Parity selection
    constexpr static uint8_t PEIE[]{ 8, 1 };  //< PE interrupt enable
    constexpr static uint8_t TXEIE[]{ 7, 1 }; //< TXE interrupt enable
    constexpr static uint8_t TCIE[]{
      6,
      1
    }; //< Transmission complete interrupt enable
    constexpr static uint8_t RXNEIE[]{ 5, 1 }; //< RXNE interrupt enable
    constexpr static uint8_t IDLEIE[]{ 4, 1 }; //< IDLE interrupt enable
    constexpr static uint8_t TE[]{ 3, 1 };     //< Transmitter enable
    constexpr static uint8_t RE[]{ 2, 1 };     //< Receiver enable
    constexpr static uint8_t RWU[]{ 1, 1 };    //< Receiver wakeup
    constexpr static uint8_t SBK[]{ 0, 1 };    //< Send break
  };

  struct CR2
  {
    constexpr static uint8_t LINEN[]{ 14, 1 }; //< LIN mode enable
    constexpr static uint8_t STOP[]{ 12, 2 };  //< STOP bits
    constexpr static uint8_t CLKEN[]{ 11, 1 }; //< Clock enable
    constexpr static uint8_t CPOL[]{ 10, 1 };  //< Clock polarity
    constexpr static uint8_t CPHA[]{ 9, 1 };   //< Clock phase
    constexpr static uint8_t LBCL[]{ 8, 1 };   //< Last bit clock pulse
    constexpr static uint8_t LBDIE[]{
      6,
      1
    }; //< LIN break detection interrupt enable
    constexpr static uint8_t LBDL[]{ 5, 1 }; //< lin break detection length
    constexpr static uint8_t ADD[]{ 0, 4 };  //< Address of the USART node
  };

  struct CR3
  {
    constexpr static uint8_t CTSIE[]{ 10, 1 }; //< CTS interrupt enable
    constexpr static uint8_t CTSE[]{ 9, 1 };   //< CTS enable
    constexpr static uint8_t RTSE[]{ 8, 1 };   //< RTS enable
    constexpr static uint8_t DMAT[]{ 7, 1 };   //< DMA enable transmitter
    constexpr static uint8_t DMAR[]{ 6, 1 };   //< DMA enable receiver
    constexpr static uint8_t SCEN[]{ 5, 1 };   //< Smartcard mode enable
    constexpr static uint8_t NACK[]{ 4, 1 };   //< Smartcard NACK enable
    constexpr static uint8_t HDSEL[]{ 3, 1 };  //< Half-duplex selection
    constexpr static uint8_t IRLP[]{ 2, 1 };   //< IrDA low-power
    constexpr static uint8_t IREN[]{ 1, 1 };   //< IrDA mode enable
    constexpr static uint8_t EIE[]{ 0, 1 };    //< Error interrupt enable
  };

  struct GTPR
  {
    constexpr static uint8_t GT[]{ 8, 8 };  //< Guard time value
    constexpr static uint8_t PSC[]{ 0, 8 }; //< Prescaler value
  };

  ///---------------------------------------------------------------------
  ///
  /// \brief Получение указателя на регистры
  /// \return указатель на регистры
  ///
  constexpr static volatile Regs *rg()
  {
    return reinterpret_cast<volatile Regs *>(usart_t<usartNumber>::base);
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Включение тактирования
  ///
  static void clockEnable(bool en)
  {
    usart_t<usartNumber>::clockEnable(en);
  }

  ///
  /// \brief Set baud rate
  /// \param baud rate
  ///
  static void setBaudRate(uint32_t value)
  {
    if (usartNumber == 1) {
      uint32_t temp = Rcc::apb2Clk() / 4 + (value >> 1);
      temp /= value;
      rg()->BRR = temp;
    }
    else {

      uint32_t temp = Rcc::systemCoreClock() / 2 + (value >> 1);
      temp /= value;
      rg()->BRR = temp;
    }
  }

  ///
  /// \brief Enable USART
  /// \param enable
  ///
  static void enable(bool en)
  {
    tl::setRegister(rg()->CR1, CR1::UE, en);
  }

  //------------------------------------------------------------------------
  /// \brief Enable TX
  /// \param enable
  static void txEnable(bool en)
  {
    tl::setRegister(rg()->CR1, CR1::TE, en);
  }

  //------------------------------------------------------------------------
  /// \brief Enable RX
  /// \param enable
  static void rxEnable(bool en)
  {
    tl::setRegister(rg()->CR1, CR1::RE, en);
  }

  //------------------------------------------------------------------------
  static void defaultEnable(bool en)
  {
    tl::setRegister(rg()->CR1, CR1::RE, en, CR1::TE, en, CR1::UE, en);
  }

  //------------------------------------------------------------------------
  static void setIdleIt(const bool en)
  {
    tl::setRegister(rg()->CR1, CR1::IDLEIE, en);
  }

  //------------------------------------------------------------------------
  static void setRxNotEmptyIt(const bool en)
  {
    tl::setRegister(rg()->CR1, CR1::RXNEIE, en);
  }

  //------------------------------------------------------------------------
  static void setTransferCompleteIt(const bool en)
  {
    tl::setRegister(rg()->CR1, CR1::TCIE, en);
  }

  //------------------------------------------------------------------------
  static void setTxEmptyIt(const bool en)
  {
    tl::setRegister(rg()->CR1, CR1::TCIE, en);
  }

  //------------------------------------------------------------------------
  static void putChar(const unsigned char ch)
  {
    while (!(tl::getRegField(rg()->SR, SR::TXE))) {
      __NOP();
    }
    rg()->DR = ch;
  }

  //------------------------------------------------------------------------
  static void putDr(const unsigned char ch)
  {
    rg()->DR = ch;
  }
  //------------------------------------------------------------------------
  static uint8_t getDr()
  {
    return rg()->DR;
  }
  //------------------------------------------------------------------------
  static bool isTxEmpty()
  {
    return tl::getRegField(rg()->SR, SR::TXE);
  }

  //------------------------------------------------------------------------
  static bool isRxNotEmpty()
  {
    return tl::getRegField(rg()->SR, SR::RXNE);
  }

  //    static void dumpRegisters()
  //    {
  //        dbg << "USART: " << usartNumber << Use::endl;

  //        dbg << " SR    " << rg()->SR << Use::endl;
  //        dbg << " CR1   " << rg()->CR1 << Use::endl;
  //        dbg << " CR2   " << rg()->CR2 << Use::endl;
  //        dbg << " CR3   " << rg()->CR3 << Use::endl;
  //        dbg << " BRR" << rg()->BRR << Use::endl;
  //        dbg << " GTPR" << rg()->GTPR << Use::endl;
  //    }

  //------------------------------------------------------------------------
  static bool isOverrun()
  {
    return tl::getRegField(rg()->SR, SR::ORE);
  }
};
#endif // __USART1_H
