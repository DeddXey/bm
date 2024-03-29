#ifndef DMA_H
#define DMA_H

#include "log/log.h"
#include "nvic.h"
#include "rcc.h"
#include <cstdint>

template<int dma>
struct dma_t;
template<>
struct dma_t<1>
{
  constexpr static uint32_t DMA_BASE = 0x40026000;
  static void INLINE        clockEnable(const bool en)
  {
    Rcc::clockDma1(en);
  }
};
template<>
struct dma_t<2>
{
  constexpr static uint32_t DMA_BASE = 0x40026400;
  static void INLINE        clockEnable(const bool en)
  {
    Rcc::clockDma2(en);
  }
};

namespace Dma {
enum DmaDirection
{
  ddPeripheralToMemory = 0b00,
  ddMemoryToPeripheral = 0b01,
  ddMemoryToMemory     = 0b10
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
struct DmaController
{

  struct DmaLisrChannel
  {
    uint8_t index;
    uint8_t offset;
  };

  static const DmaLisrChannel *streamDispatcher()
  {
    const static DmaLisrChannel sD[8]{
      { 0, 0 }, { 0, 6 }, { 0, 16 }, { 0, 22 },
      { 0, 0 }, { 0, 6 }, { 0, 16 }, { 0, 22 }
    };
    return sD;
  }

  struct Regs
  {
    uint32_t xISR[2];
    uint32_t xIFCR[2];
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
  static volatile Regs *rg()
  {
    return reinterpret_cast<Regs *volatile>(dma_t<dma>::DMA_BASE);
  }

  static bool getTransferCompleteFlag(uint8_t stream)
  {
    return (((rg()->xISR[streamDispatcher()[stream].index])
             >> (streamDispatcher()[stream].offset + 5))
            & 0x1);
  }

  static bool getHalfTransferCompleteFlag(uint8_t stream)
  {
    return (((rg()->xISR[streamDispatcher()[stream].index])
             >> (streamDispatcher()[stream].offset + 4))
            & 0x1);
  }

  static bool getTransferErrorFlag(uint8_t stream)
  {
    return (((rg()->xISR[streamDispatcher()[stream].index])
             >> (streamDispatcher()[stream].offset + 3))
            & 0x1);
  }

  static bool getDirectModeErrorFlag(uint8_t stream)
  {
    return (((rg()->xISR[streamDispatcher()[stream].index])
             >> (streamDispatcher()[stream].offset + 2))
            & 0x1);
  }

  static bool getFifoErrorFlag(uint8_t stream)
  {
    return (((rg()->xISR[streamDispatcher()[stream].index])
             >> (streamDispatcher()[stream].offset))
            & 0x1);
  }

  static void clearTransferCompleteFlag(uint8_t stream)
  {
    rg()->xIFCR[streamDispatcher()[stream].index] |=
      (1 << (streamDispatcher()[stream].offset + 5));
  }

  static void clearHalfTransferCompleteFlag(uint8_t stream)
  {
    rg()->xIFCR[streamDispatcher()[stream].index] |=
      (1 << (streamDispatcher()[stream].offset + 4));
  }

  static void clearTransferErrorFlag(uint8_t stream)
  {
    rg()->xIFCR[streamDispatcher()[stream].index] |=
      (1 << (streamDispatcher()[stream].offset + 3));
  }

  static void clearDirectModeErrorFlag(uint8_t stream)
  {
    rg()->xIFCR[streamDispatcher()[stream].index] |=
      (1 << (streamDispatcher()[stream].offset + 2));
  }

  static void clearFifoErrorFlag(uint8_t stream)
  {
    rg()->xIFCR[streamDispatcher()[stream].index] |=
      (1 << (streamDispatcher()[stream].offset));
  }

  static void clearAllFlags(uint8_t stream)
  {
    rg()->xIFCR[streamDispatcher()[stream].index] =
      rg()->xIFCR[streamDispatcher()[stream].index]
      | (0x3f << (streamDispatcher()[stream].offset));
  }
};

template<int dma, int stream>
struct DmaStream_t;
//----DMA1----
template<>
struct DmaStream_t<1, 0>
{
  constexpr static uint32_t      streamBase   = 0x40026010;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma1Stream0; ///<
};

template<>
struct DmaStream_t<1, 1>
{
  constexpr static uint32_t      streamBase   = 0x40026028;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma1Stream1; ///<
};

template<>
struct DmaStream_t<1, 2>
{
  constexpr static uint32_t      streamBase   = 0x40026040;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma1Stream2; ///<
};

template<>
struct DmaStream_t<1, 3>
{
  constexpr static uint32_t      streamBase   = 0x40026058;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma1Stream3; ///<
};

template<>
struct DmaStream_t<1, 4>
{
  constexpr static uint32_t      streamBase   = 0x40026070;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma1Stream4; ///<
};

template<>
struct DmaStream_t<1, 5>
{
  constexpr static uint32_t      streamBase   = 0x40026088;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma1Stream5; ///<
};

template<>
struct DmaStream_t<1, 6>
{
  constexpr static uint32_t      streamBase   = 0x400260a0;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma1Stream6; ///<
};

template<>
struct DmaStream_t<1, 7>
{
  constexpr static uint32_t      streamBase   = 0x400260b8;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma1Stream7; ///<
};

//----DMA2----
template<>
struct DmaStream_t<2, 0>
{
  constexpr static uint32_t      streamBase   = 0x40026410;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma2Stream0; ///<
};

template<>
struct DmaStream_t<2, 1>
{
  constexpr static uint32_t      streamBase   = 0x40026428;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma2Stream1; ///<
};

template<>
struct DmaStream_t<2, 2>
{
  constexpr static uint32_t      streamBase   = 0x40026440;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma2Stream2; ///<
};

template<>
struct DmaStream_t<2, 3>
{
  constexpr static uint32_t      streamBase   = 0x40026458;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma2Stream3; ///<
};

template<>
struct DmaStream_t<2, 4>
{
  constexpr static uint32_t      streamBase   = 0x40026470;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma2Stream4; ///<
};

template<>
struct DmaStream_t<2, 5>
{
  constexpr static uint32_t      streamBase   = 0x40026488;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma2Stream5; ///<
};

template<>
struct DmaStream_t<2, 6>
{
  constexpr static uint32_t      streamBase   = 0x400264a0;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma2Stream6; ///<
};

template<>
struct DmaStream_t<2, 7>
{
  constexpr static uint32_t      streamBase   = 0x400264b8;
  constexpr static Nvic::IrqType dmaStreamIrq = Nvic::itDma2Stream7; ///<
};

template<int dma, int stream>
struct DmaStream
{

  struct SxCR_t
  {
    uint32_t EN : 1;
    uint32_t DMEIE : 1;
    uint32_t TEIE : 1;
    uint32_t HTIE : 1;
    uint32_t TCIE : 1;
    uint32_t PFCTRL : 1;
    uint32_t DIR : 2;
    uint32_t CIRC : 1;
    uint32_t PINC : 1;
    uint32_t MINC : 1;
    uint32_t PSIZE : 2;
    uint32_t MSIZE : 2;
    uint32_t PINCOS : 1;
    uint32_t PL : 2;
    uint32_t DBM : 1;
    uint32_t CT : 1;
    uint32_t RESERVED1 : 1;
    uint32_t PBURST : 2;
    uint32_t MBURST : 2;
    uint32_t CHSEL : 3;
  };

  struct SxFCR_t
  {
    uint32_t FTH : 2;
    uint32_t DMDIS : 1;
    uint32_t FS : 2;
    uint32_t RESERVED1 : 1;
    uint32_t FEIE : 1;
    uint32_t RESERVED2 : 25;
  };

  struct Regs
  {
    SxCR_t   CR;
    uint32_t NDTR;
    uint32_t PAR;
    uint32_t M0AR;
    uint32_t M1AR;
    SxFCR_t  FCR;
  };

  using Controller = DmaController<dma>;

  ///---------------------------------------------------------------------
  ///
  /// \brief Получение указателя на регистры
  /// \return указатель на регистры
  ///
  static volatile Regs *rg()
  {
    return reinterpret_cast<Regs *volatile>(
      DmaStream_t<dma, stream>::streamBase);
  }

  static void clockEnable(const bool val)
  {
    Controller::clockEnable(val);
  }

  static void enable(bool val)
  {
    rg()->CR.EN = val;
  }
  static void intDirectModeError(bool en)
  {
    rg()->CR.DMEIE = en;
  }
  static void intTransferError(bool en)
  {
    rg()->CR.TEIE = en;
  }
  static void intHalfTransfer(bool en)
  {
    rg()->CR.HTIE = en;
  }
  static void intTransferComplete(bool en)
  {
    rg()->CR.TCIE = en;
  }
  static void peripheralFlowController(bool en)
  {
    rg()->CR.PFCTRL = en;
  }
  static void setDmaDirection(Dma::DmaDirection dir)
  {
    rg()->CR.DIR = dir;
  }
  static void circularMode(bool en)
  {
    rg()->CR.CIRC = en;
  }
  static void peripheralIncrement(bool en)
  {
    rg()->CR.PINC = en;
  }
  static void memoryIncrement(bool en)
  {
    rg()->CR.MINC = en;
  }
  static void setPeripheralDataSize(Dma::DataSize sz)
  {
    rg()->CR.PSIZE = sz;
  }
  static void setMemoryDataSize(Dma::DataSize sz)
  {
    rg()->CR.MSIZE = sz;
  }
  static void setPeripheralIncrementOffsetTo4(bool en)
  {
    rg()->CR.PINCOS = en;
  }
  static void setPriorityLevel(Dma::PriorityLevel pl)
  {
    rg()->CR.PL = pl;
  }
  static void doubleBufferMode(bool en)
  {
    rg()->CR.DBM = en;
  }
  static void setCurrentTarget(Dma::CurrentTarget target)
  {
    rg()->CR.CT = target;
  }
  static void setMemoryBurst(Dma::Burst burst)
  {
    rg()->CR.MBURST = burst;
  }
  static void setPeripheralBurst(Dma::Burst burst)
  {
    rg()->CR.PBURST = burst;
  }
  static void setChannel(uint8_t channel)
  {
    rg()->CR.CHSEL = channel;
  }

  static void setMemoryAddress0(uint32_t address)
  {
    rg()->M0AR = address;
  }
  static void setMemoryAddress1(uint32_t address)
  {
    rg()->M1AR = address;
  }
  static void setPeripheralAddress(uint32_t address)
  {
    rg()->PAR = address;
  }
  static void setTransferSize(uint32_t sz)
  {
    rg()->NDTR = sz;
  }
  static void setFifoMode(const bool en)
  {
    rg()->FCR.DMDIS = en;
  }
  static void setFifoThreshold(const Dma::FifoThreshold ft)
  {
    rg()->FCR.FTH = ft;
  }

  static bool isTransferComplete()
  {
    return DmaController<dma>::getTransferCompleteFlag(stream);
  }
  static void clearAllFlags()
  {
    DmaController<dma>::clearAllFlags(stream);
  }

  INLINE static Nvic::IrqType getIrqNumber()
  {
    return DmaStream_t<dma, stream>::dmaStreamIrq;
  }

  static void printRegs()
  {
    con.debug() << "DMA " << Use::dec << Use::w0 << dma << " stream " << stream
                << ": " << Use::endl
                << Use::w8 << Use::hex;
    con.debug() << "  CR:   " << tl::asWord(rg()->CR) << Use::endl;
    con.debug() << "  NDTR: " << tl::asWord(rg()->NDTR) << Use::endl;
    con.debug() << "  PAR:  " << tl::asWord(rg()->PAR) << Use::endl;
    con.debug() << "  M0AR: " << tl::asWord(rg()->M0AR) << Use::endl;
    con.debug() << "  M1AR: " << tl::asWord(rg()->M1AR) << Use::endl;
    con.debug() << "  FCR:  " << tl::asWord(rg()->FCR) << Use::endl;
  }
};

#endif // DMA_H
