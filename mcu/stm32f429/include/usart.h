#ifndef USART_H
#define USART_H

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
  constexpr static uint32_t base      = 0x40011000;
  constexpr static uint32_t interrupt = Nvic::itUsart1;
  static void               clockEnable(bool en)
  {
    Rcc::clockUsart1(en);
  }
  [[maybe_unused]] static uint8_t getPrescaler()
  {
    return Rcc::getApb2Pre();
  }
};

template<>
struct usart_t<2>
{
  constexpr static uint32_t base      = 0x40004400;
  constexpr static uint32_t interrupt = Nvic::itUsart2;
  static void               clockEnable(bool en)
  {
    Rcc::clockUsart2(en);
  }
  [[maybe_unused]] static uint8_t getPrescaler()
  {
    return Rcc::getApb1Pre();
  }
};

template<>
struct usart_t<3>
{
  constexpr static uint32_t base      = 0x40004800;
  constexpr static uint32_t interrupt = Nvic::itUsart3;
  static void               clockEnable(bool en)
  {
    Rcc::clockUsart3(en);
  }
  [[maybe_unused]] static uint8_t getPrescaler()
  {
    return Rcc::getApb1Pre();
  }
};

// TODO uart
template<>
struct usart_t<4>
{
  constexpr static uint32_t base      = 0x40004C00;
  constexpr static uint32_t interrupt = Nvic::itUart4;
  static void               clockEnable(bool en)
  {
    Rcc::clockUart4(en);
  }
  [[maybe_unused]] static uint8_t getPrescaler()
  {
    return Rcc::getApb1Pre();
  }
};

// TODO uart
template<>
struct usart_t<5>
{
  constexpr static uint32_t base      = 0x40005000;
  constexpr static uint32_t interrupt = Nvic::itUart5;
  static void               clockEnable(bool en)
  {
    Rcc::clockUart5(en);
  }
  [[maybe_unused]] static uint8_t getPrescaler()
  {
    return Rcc::getApb1Pre();
  }
};

template<>
struct usart_t<6>
{
  constexpr static uint32_t base      = 0x40011400;
  constexpr static uint32_t interrupt = Nvic::itUsart6;
  static void               clockEnable(bool en)
  {
    Rcc::clockUsart6(en);
  }
  [[maybe_unused]] static uint8_t getPrescaler()
  {
    return Rcc::getApb2Pre();
  }
};
template<>
struct usart_t<7>
{
  constexpr static uint32_t base      = 0x40007800;
  constexpr static uint32_t interrupt = Nvic::itUart7;
  static void               clockEnable(bool en)
  {
    Rcc::clockUsart7(en);
  }
  [[maybe_unused]] static uint8_t getPrescaler()
  {
    return Rcc::getApb1Pre();
  }
};
template<>
struct usart_t<8>
{
  constexpr static uint32_t base      = 0x40007C00;
  constexpr static uint32_t interrupt = Nvic::itUart8;
  static void               clockEnable(bool en)
  {
    Rcc::clockUsart8(en);
  }
  [[maybe_unused]] static uint8_t getPrescaler()
  {
    return Rcc::getApb1Pre();
  }
};

//---------------------------------------------------------------------------
template<int usartNumber>
struct Usart
{

  constexpr static int num = usartNumber;

  //------------------------------------------------------------------------------
  // Register structures;
  struct [[maybe_unused]] Regs
  {
    [[maybe_unused]] uint32_t SR;   //< 0x0 Status register
    [[maybe_unused]] uint32_t DR;   //< 0x4 Data register
    [[maybe_unused]] uint32_t BRR;  //< 0x8 Baud rate register
    [[maybe_unused]] uint32_t CR1;  //< 0xC Control register 1
    [[maybe_unused]] uint32_t CR2;  //< 0x10 Control register 2
    [[maybe_unused]] uint32_t CR3;  //< 0x14 Control register 3
    [[maybe_unused]] uint32_t GTPR; //< 0x18 Guard time and prescaler register
  };

  struct [[maybe_unused]] SR
  {
    [[maybe_unused]] constexpr static uint8_t CTS[]{ 9, 1 }; //< CTS flag
    [[maybe_unused]] constexpr static uint8_t LBD[]{
      8,
      1
    }; //< LIN break detection flag
    [[maybe_unused]] constexpr static uint8_t TXE[]{
      7,
      1
    }; //< Transmit data register empty
    [[maybe_unused]] constexpr static uint8_t TC[]{
      6,
      1
    }; //< Transmission complete
    [[maybe_unused]] constexpr static uint8_t RXNE[]{
      5,
      1
    }; //< Read data register not empty
    [[maybe_unused]] constexpr static uint8_t IDLE[]{
      4,
      1
    }; //< IDLE line detected
    [[maybe_unused]] constexpr static uint8_t ORE[]{ 3, 1 }; //< Overrun error
    [[maybe_unused]] constexpr static uint8_t NF[]{ 2,
                                                    1 }; //< Noise detected flag
    [[maybe_unused]] constexpr static uint8_t FE[]{ 1, 1 }; //< Framing error
    [[maybe_unused]] constexpr static uint8_t PE[]{ 0, 1 }; //< Parity error
  };

  struct [[maybe_unused]] DR
  {
    [[maybe_unused]] constexpr static uint8_t DR_[]{ 0, 9 }; //< Data value
  };

  struct [[maybe_unused]] BRR
  {
    [[maybe_unused]] constexpr static uint8_t DIV_Mantissa[]{
      4,
      12
    }; //< mantissa of USARTDIV
    [[maybe_unused]] constexpr static uint8_t DIV_Fraction[]{
      0,
      4
    }; //< fraction of USARTDIV
  };

  struct [[maybe_unused]] CR1
  {
    [[maybe_unused]] constexpr static uint8_t OVER8[]{
      15,
      1
    }; //< Oversampling mode
    [[maybe_unused]] constexpr static uint8_t UE[]{ 13, 1 };   //< USART enable
    [[maybe_unused]] constexpr static uint8_t M[]{ 12, 1 };    //< Word length
    [[maybe_unused]] constexpr static uint8_t WAKE[]{ 11, 1 }; //< Wakeup method
    [[maybe_unused]] constexpr static uint8_t PCE[]{
      10,
      1
    }; //< Parity control enable
    [[maybe_unused]] constexpr static uint8_t PS[]{ 9, 1 }; //< Parity selection
    [[maybe_unused]] constexpr static uint8_t PEIE[]{
      8,
      1
    }; //< PE interrupt enable
    [[maybe_unused]] constexpr static uint8_t TXEIE[]{
      7,
      1
    }; //< TXE interrupt enable
    [[maybe_unused]] constexpr static uint8_t TCIE[]{
      6,
      1
    }; //< Transmission complete interrupt enable
    [[maybe_unused]] constexpr static uint8_t RXNEIE[]{
      5,
      1
    }; //< RXNE interrupt enable
    [[maybe_unused]] constexpr static uint8_t IDLEIE[]{
      4,
      1
    }; //< IDLE interrupt enable
    [[maybe_unused]] constexpr static uint8_t TE[]{ 3,
                                                    1 }; //< Transmitter enable
    [[maybe_unused]] constexpr static uint8_t RE[]{ 2, 1 };  //< Receiver enable
    [[maybe_unused]] constexpr static uint8_t RWU[]{ 1, 1 }; //< Receiver wakeup
    [[maybe_unused]] constexpr static uint8_t SBK[]{ 0, 1 }; //< Send break
  };

  struct [[maybe_unused]] CR2
  {
    [[maybe_unused]] constexpr static uint8_t LINEN[]{ 14,
                                                       1 }; //< LIN mode enable
    [[maybe_unused]] constexpr static uint8_t STOP[]{ 12, 2 };  //< STOP bits
    [[maybe_unused]] constexpr static uint8_t CLKEN[]{ 11, 1 }; //< Clock enable
    [[maybe_unused]] constexpr static uint8_t CPOL[]{ 10,
                                                      1 };    //< Clock polarity
    [[maybe_unused]] constexpr static uint8_t CPHA[]{ 9, 1 }; //< Clock phase
    [[maybe_unused]] constexpr static uint8_t LBCL[]{
      8,
      1
    }; //< Last bit clock pulse
    [[maybe_unused]] constexpr static uint8_t LBDIE[]{
      6,
      1
    }; //< LIN break detection interrupt enable
    [[maybe_unused]] constexpr static uint8_t LBDL[]{
      5,
      1
    }; //< lin break detection length
    [[maybe_unused]] constexpr static uint8_t ADD[]{
      0,
      4
    }; //< Address of the USART node
  };

  struct [[maybe_unused]] CR3
  {
    [[maybe_unused]] constexpr static uint8_t ONEBIT[]{
      11,
      1
    }; //< One sample bit method enable
    [[maybe_unused]] constexpr static uint8_t CTSIE[]{
      10,
      1
    }; //< CTS interrupt enable
    [[maybe_unused]] constexpr static uint8_t CTSE[]{ 9, 1 }; //< CTS enable
    [[maybe_unused]] constexpr static uint8_t RTSE[]{ 8, 1 }; //< RTS enable
    [[maybe_unused]] constexpr static uint8_t DMAT[]{
      7,
      1
    }; //< DMA enable transmitter
    [[maybe_unused]] constexpr static uint8_t DMAR[]{
      6,
      1
    }; //< DMA enable receiver
    [[maybe_unused]] constexpr static uint8_t SCEN[]{
      5,
      1
    }; //< Smartcard mode enable
    [[maybe_unused]] constexpr static uint8_t NACK[]{
      4,
      1
    }; //< Smartcard NACK enable
    [[maybe_unused]] constexpr static uint8_t HDSEL[]{
      3,
      1
    }; //< Half-duplex selection
    [[maybe_unused]] constexpr static uint8_t IRLP[]{ 2, 1 }; //< IrDA low-power
    [[maybe_unused]] constexpr static uint8_t IREN[]{ 1,
                                                      1 }; //< IrDA mode enable
    [[maybe_unused]] constexpr static uint8_t EIE[]{
      0,
      1
    }; //< Error interrupt enable
  };

  struct [[maybe_unused]] GTPR
  {
    [[maybe_unused]] constexpr static uint8_t GT[]{ 8, 8 }; //< Guard time value
    [[maybe_unused]] constexpr static uint8_t PSC[]{ 0, 8 }; //< Prescaler value
  };

  enum [[maybe_unused]] Interrupts{ Idle, RxNe, Tc, TxE };
  /// \brief Получение указателя на регистры
  /// \return указатель на регистры
  static volatile Regs *rg()
  {
    return reinterpret_cast<volatile Regs *volatile>(
      usart_t<usartNumber>::base);
  }

  /// \brief Включение тактирования
  static void clockEnable(bool en)
  {
    usart_t<usartNumber>::clockEnable(en);
  }

  /// \brief Set baud rate
  /// \param baud rate
  static void setBaudRate(uint32_t value)
  {
    uint32_t temp =
      Rcc::systemCoreClock() / usart_t<usartNumber>::getPrescaler()
      + (value >> 1);
    temp /= value;
    rg()->BRR = temp;
  }

  /// \brief Enable USART
  /// \param enable
    static void enable(bool en)
  {
    tl::setRegister(rg()->CR1, CR1::UE, en);
  }

  /// \brief Enable TX
  /// \param enable
  [[maybe_unused]] static void txEnable(bool en)
  {
    tl::setRegister(rg()->CR1, CR1::TE, en);
  }

  /// \brief Enable RX
  /// \param enable
  [[maybe_unused]] static void rxEnable(bool en)
  {
    tl::setRegister(rg()->CR1, CR1::RE, en);
  }

  static void defaultEnable(bool en)
  {
    tl::setRegister(rg()->CR1, CR1::RE, en, CR1::TE, en, CR1::UE, en);
  }

  [[maybe_unused]] static void setIdleIt(const bool en)
  {
    tl::setRegister(rg()->CR1, CR1::IDLEIE, en);
  }

  static void setRxNotEmptyIt(const bool en)
  {
    tl::setRegister(rg()->CR1, CR1::RXNEIE, en);
  }

  [[maybe_unused]] static void setTransferCompleteIt(const bool en)
  {
    tl::setRegister(rg()->CR1, CR1::TCIE, en);
  }

  static void setTxEmptyIt(const bool en)
  {
    tl::setRegister(rg()->CR1, CR1::TCIE, en);
  }

  static void putChar(const unsigned char ch)
  {
    while (!(tl::getRegField(rg()->SR, SR::TXE))) {
      cpu::nop();
    }
    rg()->DR = ch;
  }

  static void putDr(const unsigned char ch)
  {
    rg()->DR = ch;
  }

  static uint8_t getDr()
  {
    return rg()->DR;
  }

  static bool isTxEmpty()
  {
    return tl::getRegField(rg()->SR, SR::TXE);
  }

  static bool isRxNotEmpty()
  {
    return tl::getRegField(rg()->SR, SR::RXNE);
  }

 //------------------------------------------------------------------------
  static bool isOverrun()
  {
    return tl::getRegField(rg()->SR, SR::ORE);
  }
};

#endif // USART_H
