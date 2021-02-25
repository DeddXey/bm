#ifndef __ADC1_H
#define __ADC1_H

#include "log/log.h"
#include "nvic.h"
#include "utility.h"
#include <cstdint>

// Base addresses
template<int adc>
struct adc_t;
template<>
struct adc_t<1>
{
  constexpr static uint32_t base = 0x40012400;
  static void INLINE        clockEnable(bool en)
  {
    Rcc::clockAdc1(en);
  }
  constexpr static uint32_t interrupt = Nvic::itAdc;
};

template<>
struct adc_t<2>
{
  constexpr static uint32_t base = 0x40012800;
  static void INLINE        clockEnable(bool en)
  {
    Rcc::clockAdc2(en);
  }
  constexpr static uint32_t interrupt = Nvic::itAdc;
};

template<>
struct adc_t<3>
{
  constexpr static uint32_t base = 0x40013C00;
  static void INLINE        clockEnable(bool en)
  {
    Rcc::clockAdc3(en);
  }
  constexpr static uint32_t interrupt = Nvic::itAdc3;
};

enum class AdcRegularTrigger : uint8_t
{
  tim1Cc1        = 0b000,
  tim1Cc2        = 0b001,
  tim1Cc3        = 0b010,
  tim2Cc2        = 0b011,
  tim3Trgo       = 0b100,
  tim4Cc4        = 0b101,
  exti11Tim8Trgo = 0b110,
  swstart        = 0b111,
};

enum class AdcSampleTime : uint8_t
{
  st1_5   = 0b000,
  st7_5   = 0b001,
  st13_5  = 0b010,
  st28_5  = 0b011,
  st41_5  = 0b100,
  st55_5  = 0b101,
  st71_5  = 0b110,
  st239_5 = 0b111,
};

struct AdcChannels
{
  uint8_t       channel;
  AdcSampleTime sampleTime;
};

template<int num>
struct Adc
{
  constexpr static uint32_t interrupt = Nvic::itAdc;

  struct Regs
  {
    uint32_t SR;      //< 0x0 status register
    uint32_t CR1;     //< 0x4 control register 1
    uint32_t CR2;     //< 0x8 control register 2
    uint32_t SMPR[2]; //< 0xC sample time register 1
    uint32_t JOFR1;   //< 0x14 injected channel data offset register x
    uint32_t JOFR2;   //< 0x18 injected channel data offset register x
    uint32_t JOFR3;   //< 0x1C injected channel data offset register x
    uint32_t JOFR4;   //< 0x20 injected channel data offset register x
    uint32_t HTR;     //< 0x24 watchdog higher threshold register
    uint32_t LTR;     //< 0x28 watchdog lower threshold register
    uint32_t SQR[3];  //< 0x2C regular sequence register 1
    uint32_t JSQR;    //< 0x38 injected sequence register
    uint32_t JDR[4];  //< 0x3C injected data register x
    uint32_t DR;      //< 0x4C regular data register
  };

  struct SR
  {
    constexpr static uint8_t STRT[]{ 4, 1 };  //< Regular channel start flag
    constexpr static uint8_t JSTRT[]{ 3, 1 }; //< Injected channel start flag
    constexpr static uint8_t JEOC[]{ 2,
                                     1 }; //< Injected channel end of conversion
    constexpr static uint8_t EOC[]{ 1,
                                    1 }; //< Regular channel end of conversion
    constexpr static uint8_t AWD[]{ 0, 1 }; //< Analog watchdog flag
  };

  struct CR1
  {
    constexpr static uint8_t AWDEN[]{
      23,
      1
    }; //< Analog watchdog enable on regular channels
    constexpr static uint8_t JAWDEN[]{
      22,
      1
    }; //< Analog watchdog enable on injected channels
    constexpr static uint8_t DUALMOD[]{ 16, 4 }; //< Dual mode selection
    constexpr static uint8_t DISCNUM[]{
      13,
      3
    }; //< Discontinuous mode channel count
    constexpr static uint8_t JDISCEN[]{
      12,
      1
    }; //< Discontinuous mode on injected channels
    constexpr static uint8_t DISCEN[]{
      11,
      1
    }; //< Discontinuous mode on regular channels
    constexpr static uint8_t JAUTO[]{
      10,
      1
    }; //< Automatic injected group conversion
    constexpr static uint8_t AWDSGL[]{
      9,
      1
    }; //< Enable the watchdog on a single channel in scan mode
    constexpr static uint8_t SCAN[]{ 8, 1 }; //< Scan mode
    constexpr static uint8_t JEOCIE[]{
      7,
      1
    }; //< Interrupt enable for injected channels
    constexpr static uint8_t AWDIE[]{ 6,
                                      1 }; //< Analog watchdog interrupt enable
    constexpr static uint8_t EOCIE[]{ 5, 1 }; //< Interrupt enable for EOC
    constexpr static uint8_t AWDCH[]{
      0,
      5
    }; //< Analog watchdog channel select bits
  };

  struct CR2
  {
    constexpr static uint8_t TSVREFE[]{
      23,
      1
    }; //< Temperature sensor and VREFINT enable
    constexpr static uint8_t SWSTART[]{
      22,
      1
    }; //< Start conversion of regular channels
    constexpr static uint8_t JSWSTART[]{
      21,
      1
    }; //< Start conversion of injected channels
    constexpr static uint8_t EXTTRIG[]{
      20,
      1
    }; //< External trigger conversion mode for regular channels
    constexpr static uint8_t EXTSEL[]{
      17,
      3
    }; //< External event select for regular group
    constexpr static uint8_t JEXTTRIG[]{
      15,
      1
    }; //< External trigger conversion mode for injected channels
    constexpr static uint8_t JEXTSEL[]{
      12,
      3
    }; //< External event select for injected group
    constexpr static uint8_t ALIGN[]{ 11, 1 }; //< Data alignment
    constexpr static uint8_t DMA[]{ 8, 1 };    //< Direct memory access mode
    constexpr static uint8_t RSTCAL[]{ 3, 1 }; //< Reset calibration
    constexpr static uint8_t CAL[]{ 2, 1 };    //< A/D calibration
    constexpr static uint8_t CONT[]{ 1, 1 };   //< Continuous conversion
    constexpr static uint8_t ADON[]{ 0, 1 };   //< A/D converter ON / OFF
  };

  struct SMPR1
  {
    constexpr static uint8_t SMP10[]{ 0,
                                      3 }; //< Channel 10 sample time selection
    constexpr static uint8_t SMP11[]{ 3,
                                      3 }; //< Channel 11 sample time selection
    constexpr static uint8_t SMP12[]{ 6,
                                      3 }; //< Channel 12 sample time selection
    constexpr static uint8_t SMP13[]{ 9,
                                      3 }; //< Channel 13 sample time selection
    constexpr static uint8_t SMP14[]{ 12,
                                      3 }; //< Channel 14 sample time selection
    constexpr static uint8_t SMP15[]{ 15,
                                      3 }; //< Channel 15 sample time selection
    constexpr static uint8_t SMP16[]{ 18,
                                      3 }; //< Channel 16 sample time selection
    constexpr static uint8_t SMP17[]{ 21,
                                      3 }; //< Channel 17 sample time selection
  };

  struct SMPR2
  {
    constexpr static uint8_t SMP0[]{ 0, 3 }; //< Channel 0 sample time selection
    constexpr static uint8_t SMP1[]{ 3, 3 }; //< Channel 1 sample time selection
    constexpr static uint8_t SMP2[]{ 6, 3 }; //< Channel 2 sample time selection
    constexpr static uint8_t SMP3[]{ 9, 3 }; //< Channel 3 sample time selection
    constexpr static uint8_t SMP4[]{ 12,
                                     3 }; //< Channel 4 sample time selection
    constexpr static uint8_t SMP5[]{ 15,
                                     3 }; //< Channel 5 sample time selection
    constexpr static uint8_t SMP6[]{ 18,
                                     3 }; //< Channel 6 sample time selection
    constexpr static uint8_t SMP7[]{ 21,
                                     3 }; //< Channel 7 sample time selection
    constexpr static uint8_t SMP8[]{ 24,
                                     3 }; //< Channel 8 sample time selection
    constexpr static uint8_t SMP9[]{ 27,
                                     3 }; //< Channel 9 sample time selection
  };

  struct JOFR1
  {
    constexpr static uint8_t JOFFSET1[]{
      0,
      12
    }; //< Data offset for injected channel x
  };

  struct JOFR2
  {
    constexpr static uint8_t JOFFSET2[]{
      0,
      12
    }; //< Data offset for injected channel x
  };

  struct JOFR3
  {
    constexpr static uint8_t JOFFSET3[]{
      0,
      12
    }; //< Data offset for injected channel x
  };

  struct JOFR4
  {
    constexpr static uint8_t JOFFSET4[]{
      0,
      12
    }; //< Data offset for injected channel x
  };

  struct HTR
  {
    constexpr static uint8_t HT[]{ 0, 12 }; //< Analog watchdog higher threshold
  };

  struct LTR
  {
    constexpr static uint8_t LT[]{ 0, 12 }; //< Analog watchdog lower threshold
  };

  struct SQR1
  {
    constexpr static uint8_t L[]{ 20, 4 }; //< Regular channel sequence length
    constexpr static uint8_t SQ16[]{
      15,
      5
    }; //< 16th conversion in regular sequence
    constexpr static uint8_t SQ15[]{
      10,
      5
    }; //< 15th conversion in regular sequence
    constexpr static uint8_t SQ14[]{
      5,
      5
    }; //< 14th conversion in regular sequence
    constexpr static uint8_t SQ13[]{
      0,
      5
    }; //< 13th conversion in regular sequence
  };

  struct SQR2
  {
    constexpr static uint8_t SQ12[]{
      25,
      5
    }; //< 12th conversion in regular sequence
    constexpr static uint8_t SQ11[]{
      20,
      5
    }; //< 11th conversion in regular sequence
    constexpr static uint8_t SQ10[]{
      15,
      5
    }; //< 10th conversion in regular sequence
    constexpr static uint8_t SQ9[]{ 10,
                                    5 }; //< 9th conversion in regular sequence
    constexpr static uint8_t SQ8[]{ 5,
                                    5 }; //< 8th conversion in regular sequence
    constexpr static uint8_t SQ7[]{ 0,
                                    5 }; //< 7th conversion in regular sequence
  };

  struct SQR3
  {
    constexpr static uint8_t SQ6[]{ 25,
                                    5 }; //< 6th conversion in regular sequence
    constexpr static uint8_t SQ5[]{ 20,
                                    5 }; //< 5th conversion in regular sequence
    constexpr static uint8_t SQ4[]{ 15,
                                    5 }; //< 4th conversion in regular sequence
    constexpr static uint8_t SQ3[]{ 10,
                                    5 }; //< 3rd conversion in regular sequence
    constexpr static uint8_t SQ2[]{ 5,
                                    5 }; //< 2nd conversion in regular sequence
    constexpr static uint8_t SQ1[]{ 0,
                                    5 }; //< 1st conversion in regular sequence
  };

  struct JSQR
  {
    constexpr static uint8_t JL[]{ 20, 2 }; //< Injected sequence length
    constexpr static uint8_t JSQ4[]{
      15,
      5
    }; //< 4th conversion in injected sequence
    constexpr static uint8_t JSQ3[]{
      10,
      5
    }; //< 3rd conversion in injected sequence
    constexpr static uint8_t JSQ2[]{
      5,
      5
    }; //< 2nd conversion in injected sequence
    constexpr static uint8_t JSQ1[]{
      0,
      5
    }; //< 1st conversion in injected sequence
  };

  struct JDR1
  {
    constexpr static uint8_t JDATA[]{ 0, 16 }; //< Injected data
  };

  struct JDR2
  {
    constexpr static uint8_t JDATA[]{ 0, 16 }; //< Injected data
  };

  struct JDR3
  {
    constexpr static uint8_t JDATA[]{ 0, 16 }; //< Injected data
  };

  struct JDR4
  {
    constexpr static uint8_t JDATA[]{ 0, 16 }; //< Injected data
  };

  struct DR
  {
    constexpr static uint8_t DATA[]{ 0, 16 };      //< Regular data
    constexpr static uint8_t ADC2DATA[]{ 16, 16 }; //< ADC2 data
  };

  ///---------------------------------------------------------------------
  ///
  /// \brief Получение указателя на регистры
  /// \return указатель на регистры
  ///
  INLINE constexpr static volatile Regs *rg()
  {
    return reinterpret_cast<volatile Regs *>(adc_t<num>::base);
  }

  //------------------------------------------------------------------------
  template<typename T>
  INLINE static void initCommonSequence(T &  initSequence,
                                        bool enableExtTrigger,
                                        const AdcRegularTrigger trg,
                                        bool                    dmaEnable)
  {
    constexpr static uint8_t chNum = sizeof(T) / sizeof(AdcChannels);

    Adc<1>::clockEnable(true);

    tl::setRegister(rg()->CR2, CR2::ADON, true);

    simpleDelay(100000);

    tl::setRegister(rg()->CR2, CR2::RSTCAL, true);

    while (tl::getRegField(rg()->CR2, CR2::RSTCAL)) {}

    tl::setRegister(rg()->CR2, CR2::CAL, true);

    while (tl::getRegField(rg()->CR2, CR2::CAL)) {}

    //        setRegister(rg()->CR2,
    //                              CR2::ADON, true);

    for (uint8_t i = 0; i < chNum; ++i) {
      Adc<1>::setChannelSequence(i, initSequence[i].channel);

      Adc<1>::setSampleTime(initSequence[i].channel,
                            initSequence[i].sampleTime);
    }

    Adc<1>::setScanNumber(chNum);

    tl::setRegister(rg()->CR1, CR1::SCAN, true);

    tl::setRegister(rg()->CR2,
                    CR2::EXTSEL,
                    static_cast<uint8_t>(trg),
                    CR2::EXTTRIG,
                    enableExtTrigger,
                    CR2::DMA,
                    dmaEnable,
                    CR2::ADON,
                    true);
  }

  //------------------------------------------------------------------------
  static void INLINE clockEnable(bool en)
  {
    adc_t<num>::clockEnable(en);
  }

  //------------------------------------------------------------------------
  INLINE static void setSampleTime(uint8_t channel, AdcSampleTime sampleTime)
  {
    uint8_t index  = 1 - (channel) / 10;
    uint8_t offset = channel % 10;
    uint8_t tmp[2]{ offset, 3 };

    tl::setRegister(rg()->SMPR[index], tmp, static_cast<uint8_t>(sampleTime));
  }

  //------------------------------------------------------------------------
  INLINE static void setChannelSequence(uint8_t position, uint8_t channel)
  {

    uint8_t index  = 2 - (position) / 6;
    uint8_t offset = ((position) % 6) * 5;
    uint8_t tmp[2]{ offset, 5 };

    tl::setRegister(rg()->SQR[index], tmp, channel);
  }

  //------------------------------------------------------------------------
  INLINE static void setScanNumber(uint8_t number)
  {
    tl::setRegister(rg()->SQR[0], SQR1::L, number - 1);
  }

  //------------------------------------------------------------------------
  INLINE static void enableEocInterrupt(bool en)
  {
    tl::setRegister(rg()->CR1, CR1::EOCIE, en);
  }

  //------------------------------------------------------------------------
  INLINE static void enableDiscontinousMode(bool en)
  {
    tl::setRegister(rg()->CR1, CR1::DISCEN, en);
  }

  //------------------------------------------------------------------------
  INLINE static void enableJeocInterrupt(bool en)
  {
    tl::setRegister(rg()->CR1, CR1::JEOCIE, en);
  }

  //------------------------------------------------------------------------
  INLINE static void enableScanMode(bool en)
  {
    tl::setRegister(rg()->CR1, CR1::SCAN, en);
  }

  //------------------------------------------------------------------------
  INLINE static void setDiscontinuesChannelCount(const uint8_t cnt)
  {
    tl::setRegister(rg()->CR1, CR1::DISCNUM, (cnt & 0x7) - 1);
  }

  //------------------------------------------------------------------------
  INLINE static void selectExternalTrigger(const AdcRegularTrigger trg)
  {
    tl::setRegister(rg()->CR2, CR2::EXTSEL, static_cast<uint8_t>(trg));
  }

  //------------------------------------------------------------------------
  INLINE static void enableExternalTrigger(bool en)
  {
    tl::setRegister(rg()->CR2, CR2::EXTTRIG, en);
  }

  //------------------------------------------------------------------------
  INLINE static void enableDma(bool en)
  {
    tl::setRegister(rg()->CR2, CR2::DMA, en);
  }

  //------------------------------------------------------------------------
  INLINE static void enable(bool en)
  {
    tl::setRegister(rg()->CR2, CR2::ADON, en);
  }
  //------------------------------------------------------------------------
  INLINE static void clearEocFlag()
  {
    tl::setRegister(rg()->SR, SR::EOC, 0);
  }
  //------------------------------------------------------------------------
  INLINE static bool getEocFlag()
  {
    return tl::getRegField(rg()->SR, SR::EOC);
  }

  static void dumpRegisters()
  {
    con.debug() << "ADC: " << num << Use::endl;

    con.debug() << " SR    " << rg()->SR << Use::endl;
    con.debug() << " CR1   " << rg()->CR1 << Use::endl;
    con.debug() << " CR2   " << rg()->CR2 << Use::endl;
    con.debug() << " SQR[0]" << rg()->SQR[0] << Use::endl;
    con.debug() << " SQR[1]" << rg()->SQR[1] << Use::endl;
    con.debug() << " SQR[2]" << rg()->SQR[2] << Use::endl;
    con.debug() << " SMPR1 " << rg()->SMPR[0] << Use::endl;
    con.debug() << " SMPR2 " << rg()->SMPR[1] << Use::endl;
  }
};
#endif // __ADC1_H
