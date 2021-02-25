#ifndef ADC_H
#define ADC_H
//#include "stm32f4xx.h"
#include "rcc.h"
#include "nvic.h"


// Base addresses
template<int adc> struct adc_t;
template<> struct adc_t<1>
{
    constexpr static uint32_t BASE = 0x40012000;
    static void INLINE clockEnable(const bool en) { Rcc::clockAdc1(en); }

};

template<> struct adc_t<2>
{
    constexpr static uint32_t BASE = 0x40012100;
    static void INLINE clockEnable(const bool en) { Rcc::clockAdc2(en); }
};

template<> struct adc_t<3>
{
    constexpr static uint32_t BASE = 0x40012200;
    static void INLINE clockEnable(const bool en) { Rcc::clockAdc3(en); }
};


enum AdcResolution {
    ar12bit = 0,
    ar10bit = 1,
    ar8bit =  2,
    ar6bit =  3
};

enum AdcEvent {
    EV_TIMER1_CC1   = 0b0000, //Timer 1 CC1 event
    EV_TIMER1_CC2   = 0b0001, //Timer 1 CC2 event
    EV_TIMER1_CC3   = 0b0010, //Timer 1 CC3 event
    EV_TIMER2_CC2   = 0b0011, //Timer 2 CC2 event
    EV_TIMER2_CC3   = 0b0100, //Timer 2 CC3 event
    EV_TIMER2_CC4   = 0b0101, //Timer 2 CC4 event
    EV_TIMER2_TRGO  = 0b0110, //Timer 2 TRGO event
    EV_TIMER3_CC1   = 0b0111, //Timer 3 CC1 event
    EV_TIMER3_TRGO  = 0b1000, //Timer 3 TRGO event
    EV_TIMER4_CC4   = 0b1001, //Timer 4 CC4 event
    EV_TIMER5_CC1   = 0b1010, //Timer 5 CC1 event
    EV_TIMER5_CC2   = 0b1011, //Timer 5 CC2 event
    EV_TIMER5_CC3   = 0b1100, //Timer 5 CC3 event
    EV_TIMER8_CC1   = 0b1101, //Timer 8 CC1 event
    EV_TIMER8_TRGO  = 0b1110, //Timer 8 TRGO event
    EV_EXTI11       = 0b1111  //EXTI line11
};



template <int num>
struct Adc {

    constexpr static uint32_t COMMON_BASE = 0x40012300;

    struct SR_t {
        uint32_t    AWD:1;
        uint32_t    EOC:1;
        uint32_t    JEOC:1;
        uint32_t    JSTRT:1;
        uint32_t    STRT:1;
        uint32_t    OVR:1;
    };

    struct CR1_t {
        uint32_t    AWDCH:5;
        uint32_t    EOCIE:1;
        uint32_t    AWDIE:1;
        uint32_t    JEOCIE:1;
        uint32_t    SCAN:1;
        uint32_t    AWDSGL:1;
        uint32_t    JAUTO:1;
        uint32_t    DISCEN:1;
        uint32_t    JDISCEN:1;
        uint32_t    DISCNUM:3;
        uint32_t    RESERVED1:6;
        uint32_t    JAWDEN:1;
        uint32_t    AWDEN:1;
        uint32_t    RES:2;
        uint32_t    OVRIE:1;
    };

    struct CR2_t {
        uint32_t    ADON:1;
        uint32_t    CONT:1;
        uint32_t    RESERVED1:6;
        uint32_t    DMA:1;
        uint32_t    DDS:1;
        uint32_t    EOCS:1;
        uint32_t    ALIGN:1;
        uint32_t    RESERVED2:4;
        uint32_t    JEXTSEL:4;
        uint32_t    JEXTEN:2;
        uint32_t    JSWSTART:1;
        uint32_t    RESERVED3:1;
        uint32_t    EXTSEL:4;
        uint32_t    EXTEN:2;
        uint32_t    SWSTART:1;
    };

    struct SMPR1_t {
        uint32_t    SMP10:3;
        uint32_t    SMP11:3;
        uint32_t    SMP12:3;
        uint32_t    SMP13:3;
        uint32_t    SMP14:3;
        uint32_t    SMP15:3;
        uint32_t    SMP16:3;
        uint32_t    SMP17:3;
        uint32_t    SMP18:3;
    };

    struct SMPR2_t {
        uint32_t    SMP0:3;
        uint32_t    SMP1:3;
        uint32_t    SMP2:3;
        uint32_t    SMP3:3;
        uint32_t    SMP4:3;
        uint32_t    SMP5:3;
        uint32_t    SMP6:3;
        uint32_t    SMP7:3;
        uint32_t    SMP8:3;
        uint32_t    SMP9:3;
    };

    struct JOFR_t {
        uint32_t    JOFFSET:12;
    };

    struct HTR_t {
        uint32_t    HT:12;
    };

    struct LTR_t {
        uint32_t    LT:12;
    };

    struct JSQR_t {
        uint32_t    JSQ1:5;
        uint32_t    JSQ2:5;
        uint32_t    JSQ3:5;
        uint32_t    JSQ4:5;
        uint32_t    JL:2;
    };

    struct JDR_t {
        uint32_t    JDATA:16;
    };

    struct DR_t {
        uint32_t    DR:16;
    };


    struct CSR_t {
        uint32_t    AWD1:1;
        uint32_t    EOC1:1;
        uint32_t    JEOC1:1;
        uint32_t    JSTRT1:1;
        uint32_t    STRT1:1;
        uint32_t    OVR1:1;
        uint32_t    RESERVED1:2;
        uint32_t    AWD2:1;
        uint32_t    EOC2:1;
        uint32_t    JEOC2:1;
        uint32_t    JSTRT2:1;
        uint32_t    STRT2:1;
        uint32_t    OVR2:1;
        uint32_t    RESERVED2:2;
        uint32_t    AWD3:1;
        uint32_t    EOC3:1;
        uint32_t    JEOC3:1;
        uint32_t    JSTRT3:1;
        uint32_t    STRT3:1;
        uint32_t    OVR3:1;
        uint32_t    RESERVED3:2;
    };

    struct CCR_t {
        uint32_t    MULTI:5;
        uint32_t    RESERVED1:3;
        uint32_t    DELAY:4;
        uint32_t    RESERVED2:1;
        uint32_t    DDS:1;
        uint32_t    DMA:2;
        uint32_t    ADCPRE:2;
        uint32_t    RESERVED3:4;
        uint32_t    VBATE:1;
        uint32_t    TSVREFE:1;
    };

    struct CDR_t {
        uint32_t    DATA1:16;
        uint32_t    DATA2:16;
    };

    struct Regs {
        SR_t        SR;
        CR1_t       CR1;
        CR2_t       CR2;
        uint32_t    SMPR1;
        uint32_t    SMPR2;
        uint32_t    JOFR[4];
        HTR_t       HTR;
        LTR_t       LTR;
        uint32_t    SQR[3];
        JSQR_t      JSQR;
        JDR_t       JDR1;
        JDR_t       JDR2;
        JDR_t       JDR3;
        JDR_t       JDR4;
        DR_t        DR;
    };

    struct CommonRegs {
        CSR_t   CSR;
        CCR_t   CCR;
        CDR_t   CDR;
    };


//#ifdef DEBUG
//    volatile Regs* const debugAdc = reinterpret_cast<Regs*>(adc_t<adcNum>::BASE);
//    volatile CommonRegs* const debugCommon = reinterpret_cast<CommonRegs*>(COMMON_BASE);
//#endif

//    constexpr static volatile Regs* const adc = (Regs*)(adc_t<adcNum>::BASE);
//    constexpr static volatile CommonRegs* const adcCommon = (CommonRegs*)(RCC_BASE);

    constexpr static uint32_t ADC_IRQn = Nvic::itAdc;

    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    INLINE static volatile Regs* rg()
    {
        return reinterpret_cast<volatile Regs * volatile>(adc_t<num>::BASE);
    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    INLINE static volatile CommonRegs* commonRg()
    {
        return reinterpret_cast<volatile CommonRegs * volatile>(COMMON_BASE);
    }


    ///---------------------------------------------------------------------
    ///
    /// \brief Включение тактирования
    ///
    INLINE static void clockEnable(const bool en)
    {
        adc_t<num>::clockEnable(en);
    }



    INLINE static void enable(bool en) { rg()->CR2.ADON = en; }
    INLINE static void startRegular() { rg()->CR2.SWSTART = 1; }
    INLINE static bool endOfConversion() { return rg()->SR.EOC; }
    INLINE static uint16_t getData() { return rg()->DR.DR; }

    /// sequence 1 - 16
    /// TODO variadic template
    INLINE static void setChannel(uint8_t sequence, uint8_t channel)
    {
        uint8_t index = (sequence- 1) / 6 ;
        uint8_t offset = (sequence- 1) % 6;
        uint32_t mask = ((1 << 5) - 1U) << offset;
        uint32_t value = channel << offset;

        rg()->SQR[2 - index] = (rg()->SQR[2 - index] & (~mask)) | value;
    }


    INLINE static void setConversionLengtht(uint8_t lenght)
    {
        uint32_t maskL = ((1 << 4) - 1U) << 20;
        uint32_t valueL = (lenght - 1U) << 20U;
        rg()->SQR[0] = (rg()->SQR[0] & (~maskL)) | valueL;

    }

    // Unchecked

    INLINE static void enableEocInterrupt(bool en) { rg()->CR1.EOCIE = en; }
    INLINE static void clearEocInterruptFlag() { rg()->SR.EOC = 0; }
    INLINE static bool eocInterruptFlag() { return (rg()->SR.EOC == 1); }
    INLINE static void setResolution(AdcResolution resolution = ar12bit) { rg()->CR1.RES = resolution; }
    INLINE static void setEvent(AdcEvent event) { rg()->CR2.EXTSEL = event; }




};



#endif // ADC_H
