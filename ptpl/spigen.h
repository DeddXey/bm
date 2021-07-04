#ifndef SMARTHEAD_SPIGEN_H
#define SMARTHEAD_SPIGEN_H

#include <cstdint>
#include <atomic>
#include "spi.h"

//struct SpiCfg {
//
//  constexpr static uint8_t mosiPort = 'E';
//  constexpr static uint8_t mosiPin = 14;
//
//  constexpr static uint8_t misoPort = 'E';
//  constexpr static uint8_t misoPin = 14;
//
//  constexpr static uint8_t sclkPort = 'E';
//  constexpr static uint8_t sclkPin = 2;
//
//  constexpr static uint8_t csPort = 'E';
//  constexpr static uint8_t csPin = 2;
//
//  constexpr static uint8_t spi = 3;
//  constexpr static uint8_t dmaStreamRx = 0;
//  constexpr static uint8_t dmaStreamTx = 0;
//  constexpr static uint8_t dmaChannelRx = 0;
//  constexpr static uint8_t dmaChannelTx = 0;
//
//  constexpr static bool useDmaRx = false;
//  constexpr static bool useDmaTx = false;
//
//  using SpiLL = Spi<spi>;
//  using DmaRxLL = DmaStream<dmaStreamRx>;
//  using DmaTxLL = DmaStream<dmaStreamTx>;
//
//
//  void init()
//  {
//    // MOSI
//    Gpio<mosiPort>::configPins(pmAlternate,
//                               sp100Mhz,
//                               poPushPull,
//                               pupdNone,
//                               mosiPin);
//
//    Gpio<mosiPort>::setAltFunc(afSpi3Ext, mosiPin);
//
//    // MISO
//    Gpio<misoPort>::configPins(pmAlternate,
//                               sp100Mhz,
//                               poPushPull,
//                               pupdNone,
//                               misoPin);
//
//    Gpio<misoPort>::setAltFunc(afSpi3Ext, misoPin);
//
//    //SCLK
//    Gpio<sclkPort>::configPins(pmAlternate,
//                               sp100Mhz,
//                               poPushPull,
//                               pupdNone,
//                               sclkPin);
//    Gpio<sclkPort>::setAltFunc(afSpi3Ext, sclkPin);
//
//  }
//
//
//
//
//};

template <typename I>
class SpiGen {

  std::atomic_flag busy =  ATOMIC_FLAG_INIT;
  constexpr static uint32_t maxCnt = 10165536;
public:
  void init()
  {
    I::init();

    I::SpiLL::clockEnable(true);

    I::SpiLL::setBaudRate(I::SpiP::br4);
    I::SpiLL::setBiDirectionalMode(true);
    I::SpiLL::setRxOnly(true);
    I::SpiLL::setSoftwareSlaveManagenemt(true);
    I::SpiLL::setInternalSlaveSelect(true);
    I::SpiLL::setMasterMode();
    I::SpiLL::setClockPhase(I::SpiP::cpFirstEdge);
    I::SpiLL::setClockPolarity(I::SpiP::cpIdleLow);

    if constexpr (I::useDmaTx) {
      I::DmaTxLL::rxDmaEnable(true);
      I::DmaTxLL::clockEnable(true);
      I::DmaTxLL::setChannel(I::spiDmaChannel);
      I::DmaTxLL::memoryIncrement(true);
      I::DmaTxLL::setPriorityLevel(Dma::plVeryHigh);
      I::DmaTxLL::intTransferComplete(true);
      I::DmaTxLL::setPeripheralDataSize(Dma::DataSize::dsByte);
      I::DmaTxLL::setMemoryDataSize(Dma::DataSize::dsByte);
      I::DmaTxLL::setPeripheralAddress(
        reinterpret_cast<uint32_t>(I::SpiLL::getDrAddress()));
      I::SpiLL::txDmaEnable(true);
    }

    if constexpr (I::useDmaRx) {
      I::DmaRxLL::rxDmaEnable(true);
      I::DmaRxLL::clockEnable(true);
      I::DmaRxLL::setChannel(I::spiDmaChannel);
      I::DmaRxLL::memoryIncrement(true);
      I::DmaRxLL::setPriorityLevel(Dma::plVeryHigh);
      I::DmaRxLL::intTransferComplete(true);
      I::DmaRxLL::setPeripheralDataSize(Dma::DataSize::dsByte);
      I::DmaRxLL::setMemoryDataSize(Dma::DataSize::dsByte);
      I::DmaRxLL::setPeripheralAddress(
        reinterpret_cast<uint32_t>(I::SpiLL::getDrAddress()));
      I::SpiLL::rxDmaEnable(true);
    }

  }



  void writeAsync(uint8_t* pBuf, uint16_t len)
  {
    while (busy.test_and_set(std::memory_order_acquire)) {}

    I::DmaTxLL::dmaSetMemoryAddress0(reinterpret_cast<uint32_t>(&pBuf));
    I::DmaTxLL::dmaSetTransferSize(len);

    I::SpiLL::stubRead();
    I::DmaTxLL::dmaEnableStream(true);
    I::SpiLL::spiEnable();

  }

  void readAsync(uint8_t* pBuf, uint16_t len)
  {
    while (busy.test_and_set(std::memory_order_acquire)) {}

    I::DmaTxLL::dmaSetMemoryAddress0(reinterpret_cast<uint32_t>(&pBuf));
    I::DmaTxLL::dmaSetTransferSize(len);

    I::SpiLL::stubRead();
    I::DmaTxLL::dmaEnableStream(true);
    I::SpiLL::spiEnable();
  }

  uint8_t readByte()
  {
    auto out = I::SpiLL::readByte();
    if (out)
      return out.value();
    else
      return 0;
  }

  void writeByte(const uint8_t byte)
  {
    I::SpiLL::writeByte(byte);
  }

  bool dmaIsBusy() {}

  void dmaIrQ()
  {
    busy.clear(std::memory_order_release);
  }
};


#endif // SMARTHEAD_SPIGEN_H
