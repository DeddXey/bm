#ifndef __TIM1_H
#define __TIM1_H

#include "nvic.h"
#include "rcc.h"
#include "utility.h"
#include <cstdint>

// Base addresses
template<int tim>
struct tim_t;

template<>
struct tim_t<1>
{
  constexpr static uint32_t base         = 0x40012C00;
  constexpr static uint32_t interruptUp  = Nvic::itTim1UpTim10;
  constexpr static uint32_t interruptBrk = Nvic::itTim1BrkTim9;
  constexpr static uint32_t interruptCc  = Nvic::itTim1Cc;
  constexpr static uint32_t interruptTrg = Nvic::itTim1TrgComTim11;

  static void clockEnable(const bool value)
  {
    Rcc::clockTim1(value);
  }
};

template<int tim>
struct tim_t;

template<>
struct tim_t<3>
{
  constexpr static uint32_t base         = 0x40000400;
  constexpr static uint32_t interruptUp  = Nvic::itTim3;
  constexpr static uint32_t interruptBrk = Nvic::itTim3;
  constexpr static uint32_t interruptCc  = Nvic::itTim3;
  constexpr static uint32_t interruptTrg = Nvic::itTim3;

  static void clockEnable(const bool value)
  {
    Rcc::clockTim3(value);
  }
};

struct Timer
{

  enum Trgo {
    tReset         = 0,
    tEnable        = 1,
    tUpdate        = 2,
    tComparePulse  = 3,
    tCompareOC1REF = 4,
    tCompareOC2REF = 5,
    tCompareOC3REF = 6,
    tCompareOC4REF = 7
  };

  enum PwmMode {
    pmFrozen        = 0b000,
    pmActiveLevel   = 0b001,
    pmInactiveLevel = 0b010,
    pmToggle        = 0b011,
    pmForceInactive = 0b100,
    pmForceActive   = 0b101,
    pmPwm1          = 0b110,
    pmPwm2          = 0b111
  };

  enum CcMode {
    ccmOutput   = 0b00,
    cc1InputTi1 = 0b01,
    cc1InputTi2 = 0b10,
    cc2InputTi2 = 0b01,
    cc2InputTi1 = 0b10,
    cc3InputTi3 = 0b01,
    cc3InputTi4 = 0b10,
    cc4InputTi4 = 0b01,
    cc4InputTi3 = 0b10,
    ccInputTrc  = 0b11
  };

  enum CcPolarity {
    ccpActiveHigh = 0,
    ccpActiveLow  = 1
  };

  enum Ti1Selection {
    t1sChannel1      = 0,
    t1sChannel123Xor = 1
  };

  enum SlaveMode {
    smDisabled      = 0b000,
    smEncoder1      = 0b001,
    smEncoder2      = 0b010,
    smEncoder3      = 0b011,
    smReset         = 0b100,
    smGated         = 0b101,
    smTrigger       = 0b110,
    smExternalClock = 0b111
  };

  enum TriggerSelection {
    tsTrigger0             = 0b000,
    tsTrigger1             = 0b001,
    tsTrigger2             = 0b010,
    tsTrigger3             = 0b011,
    tsTi1Edge              = 0b100,
    tsFilteredTimerInput1  = 0b101,
    tsFilteredTimerInput2  = 0b110,
    tsExternalTriggerInput = 0b111
  };

  enum InputCaptureFilter {
    icfNoFlilter = 0b0000,
    icfFckIntN2  = 0b0001,
    icfFckIntN4  = 0b0010,
    icfFckIntN8  = 0b0011,
    icfFdts2N6   = 0b0100,
    icfFdts2N8   = 0b0101,
    icfFdts4N6   = 0b0110,
    icfFdts4N8   = 0b0111,
    icfFdts8N6   = 0b1000,
    icfFdts8N8   = 0b1001,
    icfFdts16N5  = 0b1010,
    icfFdts16N6  = 0b1011,
    icfFdts16N8  = 0b1100,
    icfFdts32N5  = 0b1101,
    icfFdts32N6  = 0b1110,
    icfFdts32N8  = 0b1111,
  };
};

template<int num>
struct Tim
{
  constexpr static uint32_t base      = 0x40012C00;
  constexpr static uint32_t interrupt = 24;

  struct Regs
  {
    uint32_t CR1;     //< 0x0 control register 1
    uint32_t CR2;     //< 0x4 control register 2
    uint32_t SMCR;    //< 0x8 slave mode control register
    uint32_t DIER;    //< 0xC DMA/Interrupt enable register
    uint32_t SR;      //< 0x10 status register
    uint32_t EGR;     //< 0x14 event generation register
    uint32_t CCMR[2]; //< 0x18 capture/compare mode register (output mode)
    uint32_t CCER;    //< 0x20 capture/compare enable register
    uint32_t CNT;     //< 0x24 counter
    uint32_t PSC;     //< 0x28 prescaler
    uint32_t ARR;     //< 0x2C auto-reload register
    uint32_t RCR;     //< 0x30 repetition counter register
    uint32_t CCR[4];  //< 0x34 capture/compare register 1
    uint32_t BDTR;    //< 0x44 break and dead-time register
    uint32_t DCR;     //< 0x48 DMA control register
    uint32_t DMAR;    //< 0x4C DMA address for full transfer
  };

  struct CR1
  {
    constexpr static uint8_t CKD[]{ 8, 2 };  //< Clock division
    constexpr static uint8_t ARPE[]{ 7, 1 }; //< Auto-reload preload enable
    constexpr static uint8_t CMS[]{ 5, 2 };  //< Center-aligned mode selection
    constexpr static uint8_t DIR[]{ 4, 1 };  //< Direction
    constexpr static uint8_t OPM[]{ 3, 1 };  //< One-pulse mode
    constexpr static uint8_t URS[]{ 2, 1 };  //< Update request source
    constexpr static uint8_t UDIS[]{ 1, 1 }; //< Update disable
    constexpr static uint8_t CEN[]{ 0, 1 };  //< Counter enable
  };

  struct CR2
  {
    constexpr static uint8_t OIS4[]{ 14, 1 };  //< Output Idle state 4
    constexpr static uint8_t OIS3N[]{ 13, 1 }; //< Output Idle state 3
    constexpr static uint8_t OIS3[]{ 12, 1 };  //< Output Idle state 3
    constexpr static uint8_t OIS2N[]{ 11, 1 }; //< Output Idle state 2
    constexpr static uint8_t OIS2[]{ 10, 1 };  //< Output Idle state 2
    constexpr static uint8_t OIS1N[]{ 9, 1 };  //< Output Idle state 1
    constexpr static uint8_t OIS1[]{ 8, 1 };   //< Output Idle state 1
    constexpr static uint8_t TI1S[]{ 7, 1 };   //< TI1 selection
    constexpr static uint8_t MMS[]{ 4, 3 };    //< Master mode selection
    constexpr static uint8_t CCDS[]{ 3, 1 };   //< Capture/compare DMA selection
    constexpr static uint8_t CCUS[]{
      2,
      1
    }; //< Capture/compare control update selection
    constexpr static uint8_t CCPC[]{ 0,
                                     1 }; //< Capture/compare preloaded control
  };

  struct SMCR
  {
    constexpr static uint8_t ETP[]{ 15, 1 };  //< External trigger polarity
    constexpr static uint8_t ECE[]{ 14, 1 };  //< External clock enable
    constexpr static uint8_t ETPS[]{ 12, 2 }; //< External trigger prescaler
    constexpr static uint8_t ETF[]{ 8, 4 };   //< External trigger filter
    constexpr static uint8_t MSM[]{ 7, 1 };   //< Master/Slave mode
    constexpr static uint8_t TS[]{ 4, 3 };    //< Trigger selection
    constexpr static uint8_t SMS[]{ 0, 3 };   //< Slave mode selection
  };

  struct DIER
  {
    constexpr static uint8_t TDE[]{ 14, 1 };   //< Trigger DMA request enable
    constexpr static uint8_t COMDE[]{ 13, 1 }; //< COM DMA request enable
    constexpr static uint8_t CC4DE[]{
      12,
      1
    }; //< Capture/Compare 4 DMA request enable
    constexpr static uint8_t CC3DE[]{
      11,
      1
    }; //< Capture/Compare 3 DMA request enable
    constexpr static uint8_t CC2DE[]{
      10,
      1
    }; //< Capture/Compare 2 DMA request enable
    constexpr static uint8_t CC1DE[]{
      9,
      1
    }; //< Capture/Compare 1 DMA request enable
    constexpr static uint8_t UDE[]{ 8, 1 }; //< Update DMA request enable
    constexpr static uint8_t TIE[]{ 6, 1 }; //< Trigger interrupt enable
    constexpr static uint8_t CC4IE[]{
      4,
      1
    }; //< Capture/Compare 4 interrupt enable
    constexpr static uint8_t CC3IE[]{
      3,
      1
    }; //< Capture/Compare 3 interrupt enable
    constexpr static uint8_t CC2IE[]{
      2,
      1
    }; //< Capture/Compare 2 interrupt enable
    constexpr static uint8_t CC1IE[]{
      1,
      1
    }; //< Capture/Compare 1 interrupt enable
    constexpr static uint8_t UIE[]{ 0, 1 };   //< Update interrupt enable
    constexpr static uint8_t BIE[]{ 7, 1 };   //< Break interrupt enable
    constexpr static uint8_t COMIE[]{ 5, 1 }; //< COM interrupt enable
  };

  struct SR
  {
    constexpr static uint8_t CC4OF[]{
      12,
      1
    }; //< Capture/Compare 4 overcapture flag
    constexpr static uint8_t CC3OF[]{
      11,
      1
    }; //< Capture/Compare 3 overcapture flag
    constexpr static uint8_t CC2OF[]{
      10,
      1
    }; //< Capture/compare 2 overcapture flag
    constexpr static uint8_t CC1OF[]{
      9,
      1
    }; //< Capture/Compare 1 overcapture flag
    constexpr static uint8_t BIF[]{ 7, 1 };   //< Break interrupt flag
    constexpr static uint8_t TIF[]{ 6, 1 };   //< Trigger interrupt flag
    constexpr static uint8_t COMIF[]{ 5, 1 }; //< COM interrupt flag
    constexpr static uint8_t CC4IF[]{ 4,
                                      1 }; //< Capture/Compare 4 interrupt flag
    constexpr static uint8_t CC3IF[]{ 3,
                                      1 }; //< Capture/Compare 3 interrupt flag
    constexpr static uint8_t CC2IF[]{ 2,
                                      1 }; //< Capture/Compare 2 interrupt flag
    constexpr static uint8_t CC1IF[]{ 1,
                                      1 };  //< Capture/compare 1 interrupt flag
    constexpr static uint8_t UIF[]{ 0, 1 }; //< Update interrupt flag
  };

  struct EGR
  {
    constexpr static uint8_t BG[]{ 7, 1 }; //< Break generation
    constexpr static uint8_t TG[]{ 6, 1 }; //< Trigger generation
    constexpr static uint8_t COMG[]{
      5,
      1
    }; //< Capture/Compare control update generation
    constexpr static uint8_t CC4G[]{ 4, 1 }; //< Capture/compare 4 generation
    constexpr static uint8_t CC3G[]{ 3, 1 }; //< Capture/compare 3 generation
    constexpr static uint8_t CC2G[]{ 2, 1 }; //< Capture/compare 2 generation
    constexpr static uint8_t CC1G[]{ 1, 1 }; //< Capture/compare 1 generation
    constexpr static uint8_t UG[]{ 0, 1 };   //< Update generation
  };

  struct CCMR1_OUT
  {
    constexpr static uint8_t OC2CE[]{ 15, 1 }; //< Output Compare 2 clear enable
    constexpr static uint8_t OC2M[]{ 12, 3 };  //< Output Compare 2 mode
    constexpr static uint8_t OC2PE[]{ 11,
                                      1 }; //< Output Compare 2 preload enable
    constexpr static uint8_t OC2FE[]{ 10, 1 }; //< Output Compare 2 fast enable
    constexpr static uint8_t CC2S[]{ 8, 2 };   //< Capture/Compare 2 selection
    constexpr static uint8_t OC1CE[]{ 7, 1 };  //< Output Compare 1 clear enable
    constexpr static uint8_t OC1M[]{ 4, 3 };   //< Output Compare 1 mode
    constexpr static uint8_t OC1PE[]{ 3,
                                      1 }; //< Output Compare 1 preload enable
    constexpr static uint8_t OC1FE[]{ 2, 1 }; //< Output Compare 1 fast enable
    constexpr static uint8_t CC1S[]{ 0, 2 };  //< Capture/Compare 1 selection
  };

  struct CCMR1_IN
  {
    constexpr static uint8_t IC2F[]{ 12, 4 };   //< Input capture 2 filter
    constexpr static uint8_t IC2PCS[]{ 10, 2 }; //< Input capture 2 prescaler
    constexpr static uint8_t CC2S[]{ 8, 2 };    //< Capture/Compare 2 selection
    constexpr static uint8_t IC1F[]{ 4, 4 };    //< Input capture 1 filter
    constexpr static uint8_t ICPCS[]{ 2, 2 };   //< Input capture 1 prescaler
    constexpr static uint8_t CC1S[]{ 0, 2 };    //< Capture/Compare 1 selection
  };

  struct CCMR2_OUT
  {
    constexpr static uint8_t OC4CE[]{ 15, 1 }; //< Output compare 4 clear enable
    constexpr static uint8_t OC4M[]{ 12, 3 };  //< Output compare 4 mode
    constexpr static uint8_t OC4PE[]{ 11,
                                      1 }; //< Output compare 4 preload enable
    constexpr static uint8_t OC4FE[]{ 10, 1 }; //< Output compare 4 fast enable
    constexpr static uint8_t CC4S[]{ 8, 2 };   //< Capture/Compare 4 selection
    constexpr static uint8_t OC3CE[]{ 7, 1 };  //< Output compare 3 clear enable
    constexpr static uint8_t OC3M[]{ 4, 3 };   //< Output compare 3 mode
    constexpr static uint8_t OC3PE[]{ 3,
                                      1 }; //< Output compare 3 preload enable
    constexpr static uint8_t OC3FE[]{ 2, 1 }; //< Output compare 3 fast enable
    constexpr static uint8_t CC3S[]{ 0, 2 };  //< Capture/Compare 3 selection
  };

  struct CCMR2_IN
  {
    constexpr static uint8_t IC4F[]{ 12, 4 };   //< Input capture 4 filter
    constexpr static uint8_t IC4PSC[]{ 10, 2 }; //< Input capture 4 prescaler
    constexpr static uint8_t CC4S[]{ 8, 2 };    //< Capture/Compare 4 selection
    constexpr static uint8_t IC3F[]{ 4, 4 };    //< Input capture 3 filter
    constexpr static uint8_t IC3PSC[]{ 2, 2 };  //< Input capture 3 prescaler
    constexpr static uint8_t CC3S[]{ 0, 2 };    //< Capture/compare 3 selection
  };

  struct CCER
  {
    constexpr static uint8_t CC4P[]{ 13,
                                     1 }; //< Capture/Compare 3 output Polarity
    constexpr static uint8_t CC4E[]{ 12,
                                     1 }; //< Capture/Compare 4 output enable
    constexpr static uint8_t CC3NP[]{ 11,
                                      1 }; //< Capture/Compare 3 output Polarity
    constexpr static uint8_t CC3NE[]{
      10,
      1
    }; //< Capture/Compare 3 complementary output enable
    constexpr static uint8_t CC3P[]{ 9,
                                     1 }; //< Capture/Compare 3 output Polarity
    constexpr static uint8_t CC3E[]{ 8, 1 }; //< Capture/Compare 3 output enable
    constexpr static uint8_t CC2NP[]{ 7,
                                      1 }; //< Capture/Compare 2 output Polarity
    constexpr static uint8_t CC2NE[]{
      6,
      1
    }; //< Capture/Compare 2 complementary output enable
    constexpr static uint8_t CC2P[]{ 5,
                                     1 }; //< Capture/Compare 2 output Polarity
    constexpr static uint8_t CC2E[]{ 4, 1 }; //< Capture/Compare 2 output enable
    constexpr static uint8_t CC1NP[]{ 3,
                                      1 }; //< Capture/Compare 1 output Polarity
    constexpr static uint8_t CC1NE[]{
      2,
      1
    }; //< Capture/Compare 1 complementary output enable
    constexpr static uint8_t CC1P[]{ 1,
                                     1 }; //< Capture/Compare 1 output Polarity
    constexpr static uint8_t CC1E[]{ 0, 1 }; //< Capture/Compare 1 output enable
  };

  struct BDTR
  {
    constexpr static uint8_t MOE[]{ 15, 1 }; //< Main output enable
    constexpr static uint8_t AOE[]{ 14, 1 }; //< Automatic output enable
    constexpr static uint8_t BKP[]{ 13, 1 }; //< Break polarity
    constexpr static uint8_t BKE[]{ 12, 1 }; //< Break enable
    constexpr static uint8_t OSSR[]{ 11,
                                     1 }; //< Off-state selection for Run mode
    constexpr static uint8_t OSSI[]{ 10,
                                     1 }; //< Off-state selection for Idle mode
    constexpr static uint8_t LOCK[]{ 8, 2 }; //< Lock configuration
    constexpr static uint8_t DTG[]{ 0, 8 };  //< Dead-time generator setup
  };

  struct DCR
  {
    constexpr static uint8_t DBL[]{ 8, 5 }; //< DMA burst length
    constexpr static uint8_t DBA[]{ 0, 5 }; //< DMA base address
  };

  struct DMAR
  {
    constexpr static uint8_t DMAB[]{ 0,
                                     16 }; //< DMA register for burst accesses
  };

  ///
  /// \brief Получение указателя на регистры
  /// \return указатель на регистры
  ///
  constexpr static volatile Regs *rg()
  {
    return reinterpret_cast<volatile Regs *>(tim_t<num>::base);
  }

  ///
  /// \brief Включение тактирования
  ///
  static void clockEnable(const bool value)
  {
    tim_t<num>::clockEnable(value);
  }

  static void enable(bool value)
  {
    tl::setRegister(rg()->CR1, CR1::CEN, value);
  }

  static void setTRGO(Timer::Trgo trgo)
  {
    tl::setRegister(rg()->CR2, CR2::MMS, static_cast<uint8_t>(trgo));
  }

  static void setCounter(uint16_t counter)
  {
    rg()->CNT.CNTK = counter;
  }

  static void setArr(uint16_t arr)
  {
    rg()->ARR.ARR = arr;
  }

  static void setUpdateRequestSource(bool urs)
  {
    rg()->CR1.URS = urs;
  }

  static void updateGeneration(bool ug = true)
  {
    rg()->EGR.UG = ug;
  }

  static void presetForUpdate(uint16_t prescaler, uint32_t arr)
  {
    //        rg()->CR1.ARPE = 1;          // ARR is buffered
    rg()->PSC = prescaler;
    rg()->ARR = arr;
  }

  static void setUpdateInterrupt(uint32_t                  priorityGroup,
                                 uint32_t                  preemptPriority,
                                 [[maybe_unused]] uint32_t subPriority = 0)
  {
    Nvic::setPriority(static_cast<Nvic::IrqType>(tim_t<num>::interruptUp),
                      preemptPriority); // TODO: add subpriority
    Nvic::enableIrq(static_cast<Nvic::IrqType>(tim_t<num>::interruptUp));
  }

  static void setCcInterrupt(/*uint32_t priorityGroup,*/
                             uint32_t                  preemptPriority,
                             [[maybe_unused]] uint32_t subPriority = 0)
  {
    Nvic::setPriority(static_cast<Nvic::IrqType>(tim_t<num>::interruptCc),
                      preemptPriority); // TODO: add subpriority
    Nvic::enableIrq(static_cast<Nvic::IrqType>(tim_t<num>::interruptCc));
  }

  static void enableUpdateInterrupt(bool value)
  {
    tl::setRegister(rg()->DIER, DIER::UIE, value);
  }

  static void enableCc1Interrupt(bool value)
  {
    tl::setRegister(rg()->DIER, DIER::CC1IE, value);
  }

  static void enableCc2Interrupt(bool value)
  {
    tl::setRegister(rg()->DIER, DIER::CC2IE, value);
  }

  static void enableCc3Interrupt(bool value)
  {
    tl::setRegister(rg()->DIER, DIER::CC3IE, value);
  }

  static void enableCc4Interrupt(bool value)
  {
    tl::setRegister(rg()->DIER, DIER::CC4IE, value);
  }

  static void clearCc1InterruptFlag()
  {
    tl::setRegister(rg()->SR, SR::CC1IF, 0);
  }

  static void enableUpdateDma(bool value)
  {
    rg()->DIER.UDE = value;
  }

  static void clearUpdateInterruptFlag()
  {
    rg()->SR.UIF = 0;
  }

  static bool updateInterruptFlag()
  {
    return (rg()->SR.UIF == 1);
  }

  static void enableMainOutput([[maybe_unused]] const bool value)
  {

    if constexpr ((num == 1) || (num == 8)) {
      rg()->BDTR.MOE = value;
    }

  } // TODO add specialization

  static void selectTi1(Timer::Ti1Selection selection)
  {
    rg()->CR2.TI1S = selection;
  }

  static void selectSlaveMode(Timer::SlaveMode mode)
  {
    rg()->SMCR.SMS = mode;
  }

  static void selectSlaveTrigger(Timer::TriggerSelection selection)
  {
    rg()->SMCR.TS = selection;
  }

  static uint32_t getCounter()
  {
    return rg()->CNT.CNTK;
  }

  static void setCcMode(uint8_t channel, Timer::CcMode mode)
  {
    uint32_t index = ((channel - 1) >> 1) & 0b01;
    uint32_t pos   = (channel - 1) & 0b01;
    uint32_t mask  = 3U << (pos * 8);
    uint32_t value = static_cast<uint32_t>(mode) << (pos * 8);

    rg()->CCMR[index] = (rg()->CCMR[index] & (~mask)) | value;
  }

  static void setCcInputFilter(uint8_t                   channel,
                               Timer::InputCaptureFilter filter)
  {
    uint32_t index = ((channel - 1) >> 1) & 0b01;
    uint32_t pos   = (channel - 1) & 0b01;
    uint32_t mask  = 15U << (pos * 8);
    uint32_t value = static_cast<uint32_t>(filter) << (pos * 8 + 4);

    rg()->CCMR[index] = (rg()->CCMR[index] & (~mask)) | value;
  }

  static void setOutputCompareMode(uint8_t channel, Timer::PwmMode mode)
  {
    uint32_t index = ((channel - 1) >> 1) & 0b01;
    uint32_t pos   = (channel - 1) & 0b01;
    uint32_t mask  = 7U << (pos * 8 + 4);
    uint32_t value = static_cast<uint32_t>(mode) << (pos * 8 + 4);

    rg()->CCMR[index] = (rg()->CCMR[index] & (~mask)) | value;
  }

  static void setCcPolarity(uint8_t channel, Timer::CcPolarity polarity)
  {
    uint32_t mask  = 1U << ((channel - 1) * 4 + 1);
    uint32_t value = static_cast<uint32_t>(polarity) << ((channel - 1) * 4 + 1);

    rg()->CCER = (rg()->CCER & (~mask)) | value;
  }

  static void setCcPolarityN(uint8_t channel, Timer::CcPolarity polarity)
  {
    uint32_t mask  = 1U << ((channel - 1) * 4 + 3);
    uint32_t value = static_cast<uint32_t>(polarity) << ((channel - 1) * 4 + 3);

    rg()->CCER = (rg()->CCER & (~mask)) | value;
  }

  static void enableCcOutput(uint8_t channel, bool value)
  {
    uint32_t mask  = 1U << ((channel - 1) * 4);
    uint32_t val = static_cast<uint32_t>(value) << ((channel - 1) * 4);

    rg()->CCER = (rg()->CCER & (~mask)) | val;
  }

  static void enableCcOutputN(uint8_t channel, bool value)
  {
    uint32_t mask  = 1U << ((channel - 1) * 4 + 2);
    uint32_t val = static_cast<uint32_t>(value) << ((channel - 1) * 4 + 2);

    rg()->CCER = (rg()->CCER & (~mask)) | val;
  }

  static void setCcValue(uint8_t channel, uint32_t value)
  {
    rg()->CCR[(channel - 1)] = value;
  }

  static uint8_t getIrqnUp()
  {
    return tim_t<num>::UP_IRQn;
  }
};

#endif // __TIM1_H
