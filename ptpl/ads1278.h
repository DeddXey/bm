#ifndef ADS1278_H
#define ADS1278_H

#include "dma.h"
#include "gpio.h"
#include "intpri.h"
#include "nvic.h"
#include "spi.h"

enum class Ads1278Format : uint8_t
{
  fSpiTdmDynamic       = 0b000,
  fSpiTdmFixed         = 0b001,
  fSpiDiscrete         = 0b010,
  fFrameSyncTdmDynamic = 0b011,
  fFrameSyncTdmFixed   = 0b100,
  fFrameSyncDiscrete   = 0b101,
  fModulator           = 0b110
};

enum class Ads1278Mode : uint8_t
{
  mHighSpeed      = 0b00,
  mHighResolution = 0b01,
  mLowPower       = 0b10,
  mLowSpeed       = 0b11
};

///
/// Класс для работы с АЦП Ads1278
/// \todo добавить конфигурацию режимов и формата
///
template<typename I>
class Ads1278
{

public:
  ///
  /// \brief Первичная инициализация периферии
  ///
  static void init()
  {
    I::preInit();

    I::SpiP::clockEnable(true);

    I::SpiP::setBaudRate(I::SpiP::br16);
    I::SpiP::setBiDirectionalMode(true);
    I::SpiP::setRxOnly(true);
    I::SpiP::setSoftwareSlaveManagenemt(true);
    I::SpiP::setInternalSlaveSelect(true);
    I::SpiP::setMasterMode();
    I::SpiP::setClockPhase(I::SpiP::cpFirstEdge);
    I::SpiP::setClockPolarity(I::SpiP::cpIdleLow);

    I::SpiP::rxDmaEnable(true);

    I::SpiDmaStream::clockEnable(true);
    I::SpiDmaStream::setChannel(I::spiDmaChannel);
    I::SpiDmaStream::memoryIncrement(true);
    I::SpiDmaStream::setPriorityLevel(Dma::plVeryHigh);
    I::SpiDmaStream::intTransferComplete(true);

    I::SpiDmaStream::setPeripheralDataSize(Dma::DataSize::dsByte);
    I::SpiDmaStream::setMemoryDataSize(Dma::DataSize::dsByte);

    I::SpiDmaStream::setPeripheralAddress(
      reinterpret_cast<uint32_t>(I::SpiP::getDrAddress()));

    //		I::ExtiDrdy::setMask(false);
    //		I::ExtiDrdy::setFalling(true);
    //		I::ExtiDrdy::clearPending();
    ////		I::ExtiDrdy::setMask(true);
    //		I::ExtiDrdy::assignLine();

    setIrq(false);
    // TODO add thresholder|median?

    clearDmaAllFlags();

    I::postInit();
  }

  static void setIrq(const bool en = false)
  {
    I::ExtiDrdy::setMask(false);
    I::ExtiDrdy::setFalling(true);
    I::ExtiDrdy::clearPending();
    I::ExtiDrdy::setMask(en);
    I::ExtiDrdy::assignLine();
    Nvic::setPriority(I::SpiDmaStream::getIrqNumber(),
                      IntPriority::spiDmaIrqPrio);
    Nvic::enableIrq(I::SpiDmaStream::getIrqNumber());
    Nvic::setPriority(static_cast<Nvic::IrqType>(I::ExtiDrdy::getIrqNumber()),
                      IntPriority::drdyPrio);
    Nvic::enableIrq(static_cast<Nvic::IrqType>(I::ExtiDrdy::getIrqNumber()));
  }

  inline static bool isDmaTransferComplete()
  {
    return DmaController<I::spiDmaNumber>::getTransferCompleteFlag(
      I::spiDmaStream);
  }

  inline static void spiDisable()
  {
    I::SpiP::disable();
  }
  inline static void spiEnable()
  {
    I::SpiP::enable();
  }

  inline static void clearDmaAllFlags()
  {
    I::SpiDma::clearAllFlags(I::spiDmaStream);
  }

  inline static bool isExtiDrdyPending()
  {
    return I::ExtiDrdy::isPending();
  }

  inline static void clearExtiDrdyPending()
  {
    I::ExtiDrdy::clearPending();
  }

  inline static void dmaSetMemoryAddress0(const uint32_t addr)
  {
    I::SpiDmaStream::setMemoryAddress0(addr);
  }

  inline static void dmaSetTransferSize(const uint32_t num)
  {
    I::SpiDmaStream::setTransferSize(num);
  }

  inline static void spiStub()
  {
    volatile uint16_t stub = I::SpiP::rg()->DR.DR;
    (void)stub;
  }

  inline static void dmaEnableStream(const bool en)
  {
    I::SpiDmaStream::enable(en);
  }

  static void ads1278Sync(bool value)
  {
    Gpio<I::syncPort>::setOut(value, I::syncPin);
  }

  inline static void setExtiMask(const bool val)
  {
    I::ExtiDrdy::setMask(val);
  }

  inline static void setDrdyPriority(const uint8_t priority)
  {
    Nvic::setPriority(I::ExtiDrdy::getIrqN(), priority);
  }

  static void start()
  {
    ads1278Sync(false);
    //		simpleDelay(1000);

    for (volatile uint32_t i = 0; i < 1000; ++i) {
      asm("nop"); // чтобы оптимизатор не оптимизировал
    }

    ads1278Sync(true);
    I::ExtiDrdy::clearPending();
    I::ExtiDrdy::setMask(true);
  }

  static void stop()
  {
    I::ExtiDrdy::setMask(false);
    ads1278Sync(false);
    tl::simpleDelay(20);
  }

  static void setFormat(const Ads1278Format format)
  {
    const uint8_t format8 = static_cast<uint8_t>(format);

    //		Gpio<I::formatPort>::setOut(0, I::mode0Pin, I::mode1Pin);
    Gpio<I::formatPort>::setOut((format8 & 0b001), I::formatPin0);
    Gpio<I::formatPort>::setOut((format8 & 0b010) >> 1, I::formatPin1);
    Gpio<I::formatPort>::setOut((format8 & 0b100) >> 2, I::formatPin2);
  }

  static void setMode(const Ads1278Mode mode)
  {
    const uint8_t mode8 = static_cast<uint8_t>(mode);

    //		Gpio<I::modePort>::setOut(0, I::mode0Pin, I::mode1Pin);
    Gpio<I::modePort>::setOut((mode8 & 0b01), I::modePin0);
    Gpio<I::modePort>::setOut((mode8 & 0b10) >> 1, I::modePin1);
  }

  static float getVoltageCoeff()
  {
    return I::voltageCoeff;
  }
};

#endif // ADS1278_H
