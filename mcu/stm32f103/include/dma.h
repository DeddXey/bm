#ifndef __DMA1_H
#define __DMA1_H

#include "terminal.h"
#include "nvic.h"
#include "rcc.h"
#include "utility.h"
#include <cstdint>

namespace Dma {
enum DmaDirection
{
  ddPeripheralToMemory = 0b00,
  ddMemoryToPeripheral = 0b01,
};

enum DataSize
{
  dsByte     = 0b00,
  dsHalfWord = 0b01,
  dsWord     = 0b10
};

enum PriorityLevel
{
  plLow      = 0b00,
  plMedium   = 0b01,
  plHigh     = 0b10,
  plVeryHigh = 0b11
};

enum Burst
{
  bSingle = 0b00,
  bIncr4  = 0b01,
  bIncr8  = 0b10,
  bIncr16 = 0b11
};

enum CurrentTarget
{
  ctMemory0 = 0,
  ctMemory1 = 1
};

enum FifoThreshold
{
  ft14   = 0,
  ft12   = 1,
  ft34   = 2,
  ftFull = 3
};
} // namespace Dma

template<int dma>
struct dma_t;
template<>
struct dma_t<1>
{
  constexpr static uint32_t base = 0x40020000;
  static void INLINE        clockEnable(const bool en)
  {
    Rcc::clockDma1(en);
  }
};
template<>
struct dma_t<2>
{
  constexpr static uint32_t base = 0;
  static void INLINE        clockEnable(const bool en)
  {
    Rcc::clockDma2(en);
  }
};

template<int dma>
struct DmaController
{

  struct DmaLisrChannel
  {
    uint8_t index;
    uint8_t offset;
  };

  //    static const DmaLisrChannel* streamDispatcher()
  //    {
  //        const static DmaLisrChannel sD[8] {{0, 0}, {0, 4}, {0, 8}, {0, 22},
  //                                           {0, 0}, {0, 6}, {0, 16}, {0,
  //                                           22}};
  //        return sD;
  //    }

  struct Regs
  {
    uint32_t ISR;
    uint32_t IFCR;
  };

  ///---------------------------------------------------------------------
  ///
  /// \brief Включение тактирования
  ///
  INLINE static void clockEnable(const bool en)
  {
    dma_t<dma>::clockEnable(en);
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Получение указателя на регистры
  /// \return указатель на регистры
  ///
  INLINE static volatile Regs *rg()
  {
    return reinterpret_cast<Regs *volatile>(dma_t<dma>::base);
  }

  //    INLINE static bool getTransferCompleteFlag(uint8_t stream)
  //    {
  //        uint8_t offset = stream * 4 + 1;
  //        uint8_t tmp[2] {offset, 4};

  //        return getRegField (rg()->ISR,
  //                                     tmp);
  //    }

  //    INLINE static bool getHalfTransferCompleteFlag(uint8_t stream)
  //    {
  //        uint8_t offset = stream * 4 + 2;
  //        uint8_t tmp[2] {offset, 4};

  //        return getRegField (rg()->ISR,
  //                                     tmp);
  //    }

  //    INLINE static bool getTransferErrorFlag(uint8_t stream)
  //    {
  //        uint8_t offset = stream * 4 + 3;
  //        uint8_t tmp[2] {offset, 4};

  //        return getRegField (rg()->ISR,
  //                                     tmp);
  //    }

  //    INLINE static bool getGlobalIntFlag(uint8_t stream)
  //    {
  //        uint8_t offset = stream * 4;
  //        uint8_t tmp[2] {offset, 4};

  //        return getRegField (rg()->ISR,
  //                                     tmp);
  //    }

  //    INLINE static void clearTransferCompleteFlag(uint8_t stream)
  //    {
  //        uint8_t offset = stream * 4 + 1;
  //        uint8_t tmp[2] {offset, 4};

  //        return setRegister (rg()->IFCR,
  //                                     tmp, 1);
  //    }

  //    INLINE static void clearHalfTransferCompleteFlag(uint8_t stream)
  //    {
  //        uint8_t offset = stream * 4 + 2;
  //        uint8_t tmp[2] {offset, 4};

  //        return setRegister (rg()->IFCR,
  //                                     tmp, 1);
  //    }

  //    INLINE static void clearTransferErrorFlag(uint8_t stream)
  //    {
  //        uint8_t offset = stream * 4 + 3;
  //        uint8_t tmp[2] {offset, 4};

  //        return setRegister (rg()->IFCR,
  //                                     tmp, 1);
  //    }

  //    INLINE static void clearGlobalIntFlag(uint8_t stream)
  //    {
  //        uint8_t offset = stream * 4;
  //        uint8_t tmp[2] {offset, 4};

  //        return setRegister (rg()->IFCR,
  //                                     tmp, 1);
  //    }

  //    INLINE static void clearAllFlags(uint8_t channel)
  //    {
  //        uint8_t offset = channel * 4;

  //        uint8_t tmp[2] {offset, 4};

  //        return setRegister (rg()->IFCR,
  //                                     tmp, 0xf);

  //    }
};

template<int dma, int stream>
struct DmaChannel_t;
//----DMA1----
template<>
struct DmaChannel_t<1, 1>
{
  constexpr static uint32_t      base          = 0x40020008;
  constexpr static Nvic::IrqType dmaChannelIrq = Nvic::itDma1Channel1;
};

template<>
struct DmaChannel_t<1, 2>
{
  constexpr static uint32_t      base          = 0x4002001c;
  constexpr static Nvic::IrqType dmaChannelIrq = Nvic::itDma1Channel2;
};

template<>
struct DmaChannel_t<1, 3>
{
  constexpr static uint32_t      base          = 0x40020030;
  constexpr static Nvic::IrqType dmaChannelIrq = Nvic::itDma1Channel3;
};

template<>
struct DmaChannel_t<1, 4>
{
  constexpr static uint32_t      base          = 0x40020044;
  constexpr static Nvic::IrqType dmaChannelIrq = Nvic::itDma1Channel4;
};

template<>
struct DmaChannel_t<1, 5>
{
  constexpr static uint32_t      base          = 0x40020058;
  constexpr static Nvic::IrqType dmaChannelIrq = Nvic::itDma1Channel5;
};

template<>
struct DmaChannel_t<1, 6>
{
  constexpr static uint32_t      base          = 0x4002006c;
  constexpr static Nvic::IrqType dmaChannelIrq = Nvic::itDma1Channel6;
};

template<>
struct DmaChannel_t<1, 7>
{
  constexpr static uint32_t      base          = 0x40020080;
  constexpr static Nvic::IrqType dmaChannelIrq = Nvic::itDma1Channel7;
};

template<int dma, int channel>
struct DmaChannel
{

  struct Regs
  {
    uint32_t CCR;   //< 0x8 DMA channel configuration register (DMA_CCR)
    uint32_t CNDTR; //< 0xC DMA channel 1 number of data register
    uint32_t CPAR;  //< 0x10 DMA channel 1 peripheral address register
    uint32_t CMAR;  //< 0x14 DMA channel 1 memory address register
  };

  struct CCR
  {
    constexpr static uint8_t EN[]{ 0, 1 }; //< Channel enable
    constexpr static uint8_t TCIE[]{ 1,
                                     1 }; //< Transfer complete interrupt enable
    constexpr static uint8_t HTIE[]{ 2, 1 }; //< Half Transfer interrupt enable
    constexpr static uint8_t TEIE[]{ 3, 1 }; //< Transfer error interrupt enable
    constexpr static uint8_t DIR[]{ 4, 1 };  //< Data transfer direction
    constexpr static uint8_t CIRC[]{ 5, 1 }; //< Circular mode
    constexpr static uint8_t PINC[]{ 6, 1 }; //< Peripheral increment mode
    constexpr static uint8_t MINC[]{ 7, 1 }; //< Memory increment mode
    constexpr static uint8_t PSIZE[]{ 8, 2 };    //< Peripheral size
    constexpr static uint8_t MSIZE[]{ 10, 2 };   //< Memory size
    constexpr static uint8_t PL[]{ 12, 2 };      //< Channel Priority level
    constexpr static uint8_t MEM2MEM[]{ 14, 1 }; //< Memory to memory mode
  };

  static void printRegs()
  {
    con.debug() << "DMA " << Use::dec << Use::w0 << dma << " channel " << channel
              << ": " << Use::endl
              << Use::w8 << Use::hex;
    con.debug() << " CCR:   " << rg()->CCR << Use::endl;
    con.debug() << " CNDTR: " << rg()->CNDTR << Use::endl;
    con.debug() << " CMAR:  " << rg()->CMAR << Use::endl;
    con.debug() << " CPAR:  " << rg()->CPAR << Use::endl;
    con.debug() << " ISR:   " << DmaController<dma>::rg()->ISR << Use::endl;
  }

  //------------------------------------------------------------------------
  static bool getTransferCompleteFlag()
  {
    uint8_t offset = (channel - 1) * 4 + 1;
    uint8_t tmp[2]{ offset, 4 };

    return tl::getRegField(DmaController<dma>::rg()->ISR, tmp);
  }

  //------------------------------------------------------------------------
  static bool isTransferComplete()
  {
    return getTransferCompleteFlag();
  }

  //------------------------------------------------------------------------
  static bool getHalfTransferCompleteFlag()
  {
    uint8_t offset = (channel - 1) * 4 + 2;
    uint8_t tmp[2]{ offset, 4 };

    return tl::getRegField(DmaController<dma>::rg()->ISR, tmp);
  }

  //------------------------------------------------------------------------
  static bool getTransferErrorFlag()
  {
    uint8_t offset = (channel - 1) * 4 + 3;
    uint8_t tmp[2]{ offset, 4 };

    return tl::getRegField(DmaController<dma>::rg()->ISR, tmp);
  }

  //------------------------------------------------------------------------
  static bool getGlobalIntFlag()
  {
    uint8_t offset = (channel - 1) * 4;
    uint8_t tmp[2]{ offset, 4 };

    return tl::getRegField(DmaController<dma>::rg()->ISR, tmp);
  }

  //------------------------------------------------------------------------
  static void clearTransferCompleteFlag()
  {
    uint8_t offset = (channel - 1) * 4 + 1;
    uint8_t tmp[2]{ offset, 4 };

    tl::setRegister(DmaController<dma>::rg()->IFCR, tmp, 1);
  }

  //------------------------------------------------------------------------
  static void clearHalfTransferCompleteFlag()
  {
    uint8_t offset = (channel - 1) * 4 + 2;
    uint8_t tmp[2]{ offset, 4 };

    tl::setRegister(DmaController<dma>::rg()->IFCR, tmp, 1);
  }

  //------------------------------------------------------------------------
  static void clearTransferErrorFlag()
  {
    uint8_t offset = (channel - 1) * 4 + 3;
    uint8_t tmp[2]{ offset, 4 };

    tl::setRegister(DmaController<dma>::rg()->IFCR, tmp, 1);
  }

  //------------------------------------------------------------------------
  static void clearGlobalIntFlag()
  {
    uint8_t offset = (channel - 1) * 4;
    uint8_t tmp[2]{ offset, 4 };

    tl::setRegister(DmaController<dma>::rg()->IFCR, tmp, 1);
  }

  //------------------------------------------------------------------------
  static void clearAllFlags()
  {
    uint8_t offset = (channel - 1) * 4;
    uint8_t tmp[2]{ offset, 4 };

    tl::setRegister(DmaController<dma>::rg()->IFCR, tmp, 0xf);
  }

  ///---------------------------------------------------------------------
  ///
  /// \brief Получение указателя на регистры
  /// \return указатель на регистры
  ///
  //------------------------------------------------------------------------
  constexpr static volatile Regs *rg()
  {
    return reinterpret_cast<volatile Regs *>(DmaChannel_t<dma, channel>::base);
  }
  using Controller = DmaController<dma>;

  //------------------------------------------------------------------------
  static void clockEnable(const bool val)
  {
    Controller::clockEnable(val);
  }

  //------------------------------------------------------------------------
  static void enable(bool en)
  {
    tl::setRegister(rg()->CCR, CCR::EN, en);
  }

  //------------------------------------------------------------------------
  static void intTransferError(bool en)
  {
    rg()->CCR.TEIE = en;
  }

  //------------------------------------------------------------------------
  static void intHalfTransfer(bool en)
  {
    rg()->CCR.HTIE = en;
  }

  //------------------------------------------------------------------------
  static void intTransferComplete(bool en)
  {
    tl::setRegister(rg()->CCR, CCR::TCIE, en);
  }

  //------------------------------------------------------------------------
  static void setDmaDirection(Dma::DmaDirection dir)
  {
    tl::setRegister(rg()->CCR, CCR::DIR, dir);
  }

  //------------------------------------------------------------------------
  static void circularMode(bool en)
  {
    rg()->CCR.CIRC = en;
  }

  //------------------------------------------------------------------------
  static void peripheralIncrement(bool en)
  {
    rg()->CCR.PINC = en;
  }

  //------------------------------------------------------------------------
  static void memoryIncrement(bool en)
  {
    tl::setRegister(rg()->CCR, CCR::MINC, en);
  }

  //------------------------------------------------------------------------
  static void setPeripheralDataSize(Dma::DataSize sz)
  {
    tl::setRegister(rg()->CCR, CCR::PSIZE, sz);
  }

  //------------------------------------------------------------------------
  static void setMemoryDataSize(Dma::DataSize sz)
  {
    tl::setRegister(rg()->CCR, CCR::MSIZE, sz);
  }

  //------------------------------------------------------------------------
  static void setPriorityLevel(Dma::PriorityLevel pl)
  {
    tl::setRegister(rg()->CCR, CCR::PL, static_cast<uint8_t>(pl));
  }

  //------------------------------------------------------------------------
  static void setMemoryAddress0(uint32_t address)
  {
    rg()->CMAR = address;
  }

  //------------------------------------------------------------------------
  static void setPeripheralAddress(uint32_t address)
  {
    rg()->CPAR = address;
  }

  //------------------------------------------------------------------------
  static void setTransferSize(uint32_t sz)
  {
    rg()->CNDTR = sz;
  }

  //------------------------------------------------------------------------
  static Nvic::IrqType getIrqNumber()
  {
    return DmaChannel_t<dma, channel>::dmaChannelIrq;
  }
};
#endif // __DMA1_H
