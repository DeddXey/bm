#ifndef TIM_H
#define TIM_H
//#include "stm32f4xx.h"

#include "bits.h"
#include "rcc.h"
#include "nvic.h"
//#pragma anon_unions

// Base addresses
template<int tim> struct tim_t;
template<> struct tim_t<1>
{
    constexpr static uint32_t TIM_BASE = 0x40010000;
    static void INLINE clockEnable(const bool en) { Rcc::clockTim1(en); }
    constexpr static uint32_t BRK_IRQn          = 24;     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
    constexpr static uint32_t UP_IRQn           = 25;     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
    constexpr static uint32_t TRG_COM_IRQn      = 26;     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
    constexpr static uint32_t CC_IRQn           = 27;     /*!< TIM1 Capture Compare Interrupt                                    */
};
template<> struct tim_t<2>
{
    constexpr static uint32_t TIM_BASE = 0x40000000;
    static void INLINE clockEnable(const bool en) { Rcc::clockTim2(en); }
    constexpr static uint32_t BRK_IRQn          = 28;
    constexpr static uint32_t UP_IRQn           = 28;
    constexpr static uint32_t TRG_COM_IRQn      = 28;
    constexpr static uint32_t CC_IRQn           = 28;
};
template<> struct tim_t<3>
{
    constexpr static uint32_t TIM_BASE = 0x40000400;
    static void INLINE clockEnable(const bool en) { Rcc::clockTim3(en); }
    constexpr static uint32_t BRK_IRQn          = 29;
    constexpr static uint32_t UP_IRQn           = 29;
    constexpr static uint32_t TRG_COM_IRQn      = 29;
    constexpr static uint32_t CC_IRQn           = 29;
};
template<> struct tim_t<4>
{
    constexpr static uint32_t TIM_BASE = 0x40000800;
    static void INLINE clockEnable(const bool en) { Rcc::clockTim4(en); }
    constexpr static uint32_t BRK_IRQn          = 30;
    constexpr static uint32_t UP_IRQn           = 30;
    constexpr static uint32_t TRG_COM_IRQn      = 30;
    constexpr static uint32_t CC_IRQn           = 30;
};
template<> struct tim_t<5>
{
    constexpr static uint32_t TIM_BASE = 0x40000c00;
    static void INLINE clockEnable(const bool en) { Rcc::clockTim5(en); }
    constexpr static uint32_t BRK_IRQn          = 50;
    constexpr static uint32_t UP_IRQn           = 50;
    constexpr static uint32_t TRG_COM_IRQn      = 50;
    constexpr static uint32_t CC_IRQn           = 50;
};
template<> struct tim_t<6>
{
    constexpr static uint32_t TIM_BASE = 0x40001000;
    static void INLINE clockEnable(const bool en) { Rcc::clockTim6(en); }
    constexpr static uint32_t BRK_IRQn          = 54;
    constexpr static uint32_t UP_IRQn           = 54;
    constexpr static uint32_t TRG_COM_IRQn      = 54;
    constexpr static uint32_t CC_IRQn           = 54;
};
template<> struct tim_t<7>
{
    constexpr static uint32_t TIM_BASE = 0x40001400;
    static void INLINE clockEnable(const bool en) { Rcc::clockTim7(en); }
    constexpr static uint32_t BRK_IRQn          = 55;
    constexpr static uint32_t UP_IRQn           = 55;
    constexpr static uint32_t TRG_COM_IRQn      = 55;
    constexpr static uint32_t CC_IRQn           = 55;
};
template<> struct tim_t<8>
{
    constexpr static uint32_t TIM_BASE = 0x40010400;
    static void INLINE clockEnable(const bool en) { Rcc::clockTim8(en); }
    constexpr static uint32_t BRK_IRQn      = 43;     /*!< TIM8 Break interrupt and TIM9 global interrupt                    */
    constexpr static uint32_t UP_IRQn       = 44;     /*!< TIM8 Update Interrupt and TIM10 global interrupt                  */
    constexpr static uint32_t TRG_COM_IRQn  = 45;     /*!< TIM8 Trigger and Commutation Interrupt and TIM11 global interrupt */
    constexpr static uint32_t CC_IRQn       = 46;     /*!< TIM8 Capture Compare Interrupt                                    */

};
template<> struct tim_t<9>
{
    constexpr static uint32_t TIM_BASE = 0x40014000;
    static void INLINE clockEnable(const bool en) { Rcc::clockTim9(en); }
    constexpr static uint32_t BRK_IRQn          = 24;
    constexpr static uint32_t UP_IRQn           = 24;
    constexpr static uint32_t TRG_COM_IRQn      = 24;
    constexpr static uint32_t CC_IRQn           = 24;
};
template<> struct tim_t<10>
{
    constexpr static uint32_t TIM_BASE = 0x40014400;
    static void INLINE clockEnable(const bool en) { Rcc::clockTim10(en); }
    constexpr static uint32_t BRK_IRQn          = 25;
    constexpr static uint32_t UP_IRQn           = 25;
    constexpr static uint32_t TRG_COM_IRQn      = 25;
    constexpr static uint32_t CC_IRQn           = 25;
};
template<> struct tim_t<11>
{
    constexpr static uint32_t TIM_BASE = 0x40014800;
    static void INLINE clockEnable(const bool en) { Rcc::clockTim11(en); }
    constexpr static uint32_t BRK_IRQn          = 26;
    constexpr static uint32_t UP_IRQn           = 26;
    constexpr static uint32_t TRG_COM_IRQn      = 26;
    constexpr static uint32_t CC_IRQn           = 26;
};
template<> struct tim_t<12>
{
    constexpr static uint32_t TIM_BASE = 0x40001800;
    static void INLINE clockEnable(const bool en) { Rcc::clockTim12(en); }
    constexpr static uint32_t BRK_IRQn          = 43;
    constexpr static uint32_t UP_IRQn           = 43;
    constexpr static uint32_t TRG_COM_IRQn      = 43;
    constexpr static uint32_t CC_IRQn           = 43;
};
template<> struct tim_t<13>
{
    constexpr static uint32_t TIM_BASE = 0x40001c00;
    static void INLINE clockEnable(const bool en) { Rcc::clockTim13(en); }
    constexpr static uint32_t BRK_IRQn          = 44;
    constexpr static uint32_t UP_IRQn           = 44;
    constexpr static uint32_t TRG_COM_IRQn      = 44;
    constexpr static uint32_t CC_IRQn           = 44;
};
template<> struct tim_t<14>
{
    constexpr static uint32_t TIM_BASE = 0x40002000;
    static void INLINE clockEnable(const bool en) { Rcc::clockTim14(en); }
    constexpr static uint32_t BRK_IRQn          = 45;
    constexpr static uint32_t UP_IRQn           = 45;
    constexpr static uint32_t TRG_COM_IRQn      = 45;
    constexpr static uint32_t CC_IRQn           = 45;
};


//namespace timspace {

    struct CR1_1825t {
        uint32_t    CEN:1;
        uint32_t    UDIS:1;
        uint32_t    URS:1;
        uint32_t    OPM:1;
        uint32_t    DIR:1;
        uint32_t    CMS:2;
        uint32_t    ARPE:1;
        uint32_t    CKD:2;
    };
    struct CR1_9121014t {
        uint32_t    CEN:1;
        uint32_t    UDIS:1;
        uint32_t    URS:1;
        uint32_t    RESERVED1:4;
        uint32_t    ARPE:1;
        uint32_t    CKD:2;
    };
    struct CR1_67t {
        uint32_t    CEN:1;
        uint32_t    UDIS:1;
        uint32_t    URS:1;
        uint32_t    OPM:1;
        uint32_t    RESERVED1:3;
        uint32_t    ARPE:1;
    };
    //+++
    struct CR2_18t {
        uint32_t    CCPC:1;
        uint32_t    RESERVED1:1;
        uint32_t    CCUC:1;
        uint32_t    CCDS:1;
        uint32_t    MMS:3;
        uint32_t    TI1S:1;
        uint32_t    OIIS1:1;
        uint32_t    OIIS1N:1;
        uint32_t    OIIS2:1;
        uint32_t    OIIS2N:1;
        uint32_t    OIIS3:1;
        uint32_t    OIIS3N:1;
        uint32_t    OIIS4:1;
    };
    struct CR2_25t {
        uint32_t    RESERVED1:3;
        uint32_t    CCDS:1;
        uint32_t    MMS:3;
        uint32_t    TI1S:1;
    };
    struct CR2_67t {
        uint32_t    RESERVED1:4;
        uint32_t    MMS:3;
    };
    //+++
    struct SMCR_1825t {
        uint32_t    SMS:3;
        uint32_t    RESERVED1:1;
        uint32_t    TS:3;
        uint32_t    MSM:1;
        uint32_t    ETF:4;
        uint32_t    ETPS:2;
        uint32_t    ECE:1;
        uint32_t    ETP:1;
    };
    struct SMCR_912t {
        uint32_t    SMS:3;
        uint32_t    RESERVED1:1;
        uint32_t    TS:3;
        uint32_t    MSM:1;
    };

    //+++
    struct DIER_18t {
        uint32_t    UIE:1;
        uint32_t    CC1IE:1;
        uint32_t    CC2IE:1;
        uint32_t    CC3IE:1;
        uint32_t    CC4IE:1;
        uint32_t    COMIE:1;
        uint32_t    TIE:1;
        uint32_t    BIE:1;
        uint32_t    UDE:1;
        uint32_t    CC1DE:1;
        uint32_t    CC2DE:1;
        uint32_t    CC3DE:1;
        uint32_t    CC4DE:1;
        uint32_t    RESERVED3:1;
        uint32_t    TDE:1;
    };
    struct DIER_25t {
        uint32_t    UIE:1;
        uint32_t    CC1IE:1;
        uint32_t    CC2IE:1;
        uint32_t    CC3IE:1;
        uint32_t    CC4IE:1;
        uint32_t    RESERVED1:1;
        uint32_t    TIE:1;
        uint32_t    RESERVED2:1;
        uint32_t    UDE:1;
        uint32_t    CC1DE:1;
        uint32_t    CC2DE:1;
        uint32_t    CC3DE:1;
        uint32_t    CC4DE:1;
        uint32_t    RESERVED3:1;
        uint32_t    TDE:1;
    };
    struct DIER_67t {
        uint32_t    UIE:1;
        uint32_t    RESERVED1:7;
        uint32_t    UDE:1;
    };
    struct DIER_912t {
        uint32_t    UIE:1;
        uint32_t    CC1IE:1;
        uint32_t    CC2IE:1;
        uint32_t    RESERVED1:3;
        uint32_t    TIE:1;
    };
    struct DIER_1014t {
        uint32_t    UIE:1;
        uint32_t    CC1IE:1;
    };

    //+++
    struct SR_18t {
        uint32_t    UIF:1;
        uint32_t    CC1F:1;
        uint32_t    CC2F:1;
        uint32_t    CC3F:1;
        uint32_t    CC4F:1;
        uint32_t    COMIF:1;
        uint32_t    TIF:1;
        uint32_t    BIF:1;
        uint32_t    RESERVED2:1;
        uint32_t    CC1OF:1;
        uint32_t    CC2OF:1;
        uint32_t    CC3OF:1;
        uint32_t    CC4OF:1;
    };
    struct SR_25t {
        uint32_t    UIF:1;
        uint32_t    CC1F:1;
        uint32_t    CC2F:1;
        uint32_t    CC3F:1;
        uint32_t    CC4F:1;
        uint32_t    RESERVED1:1;
        uint32_t    TIF:1;
        uint32_t    RESERVED2:2;
        uint32_t    CC1OF:1;
        uint32_t    CC2OF:1;
        uint32_t    CC3OF:1;
        uint32_t    CC4OF:1;
    };
    struct SR_67t {
        uint32_t    UIF:1;
    };
    struct SR_912t {
        uint32_t    UIF:1;
        uint32_t    CC1F:1;
        uint32_t    CC2F:1;
        uint32_t    RESERVED1:3;
        uint32_t    TIF:1;
        uint32_t    RESERVED2:2;
        uint32_t    CC1OF:1;
        uint32_t    CC2OF:1;
    };
    struct SR_1014t {
        uint32_t    UIF:1;
        uint32_t    CC1F:1;
        uint32_t    RESERVED1:7;
        uint32_t    CC1OF:1;
    };

    //+++
    struct EGR_18t {
        uint32_t    UG:1;
        uint32_t    CC1G:1;
        uint32_t    CC2G:1;
        uint32_t    CC3G:1;
        uint32_t    CC4G:1;
        uint32_t    COMG:1;
        uint32_t    TG:1;
        uint32_t    BG:1;
    };
    struct EGR_25t {
        uint32_t    UG:1;
        uint32_t    CC1G:1;
        uint32_t    CC2G:1;
        uint32_t    CC3G:1;
        uint32_t    CC4G:1;
        uint32_t    RESERVED1:1;
        uint32_t    TG:1;
    };
    struct EGR_67t {
        uint32_t    UG:1;
    };
    struct EGR_912t {
        uint32_t    UG:1;
        uint32_t    CC1G:1;
        uint32_t    CC2G:1;
        uint32_t    RESERVED1:3;
        uint32_t    TG:1;
    };
    struct EGR_1014t {
        uint32_t    UG:1;
        uint32_t    CC1G:1;
    };

    //+++
    struct CNT_t {
        uint32_t    CNTK:16;
    };
    struct CNT32_t {
        uint32_t    CNTK:32;
    };


    //+++
    struct PSC_t {
        uint32_t    PSC:16;
    };

    //+++
    struct ARR_t {
        uint32_t    ARR:16;
    };
    struct ARR32_t {
        uint32_t    ARR:32;
    };

    //+++
    struct RCR_t {
        uint32_t    REP:8;
    };

    //+++
    struct CCR_t {
        uint32_t    CCR:16;
        uint32_t    RESERVED:16;
    };

    struct CCR32_t {
        uint32_t    CCR:32;
    };

    //+++
    struct BDTR_t {
        uint32_t    DTG:8;
        uint32_t    LOCK:2;
        uint32_t    OSSI:1;
        uint32_t    OSSR:1;
        uint32_t    BKE:1;
        uint32_t    BKP:1;
        uint32_t    AOE:1;
        uint32_t    MOE:1;
    };

    //+++
    struct DCR_t {
        uint32_t    DBA:5;
        uint32_t    RESERVED1:3;
        uint32_t    DBL:5;
    };

    //+++
    struct DMAR_t {
        uint32_t    DMAB:16;
    };

    struct OR_2t {
        uint32_t    RESERVED1:10;
        uint32_t    ITR1_RMP:2;
    };
    struct OR_5t {
        uint32_t    RESERVED1:6;
        uint32_t    IT4_RMP:2;
    };

    template<int tm> struct TimerRegs;
    template<> struct TimerRegs<1> {
        CR1_1825t       CR1;
        CR2_18t         CR2;
        SMCR_1825t      SMCR;
        DIER_18t        DIER;
        SR_18t          SR;
        EGR_18t         EGR;
        uint32_t        CCMR[2];
        uint32_t        CCER;
        CNT_t           CNT;
        PSC_t           PSC;
        ARR_t           ARR;
        RCR_t           RCR;
        CCR_t           CCR[4];
        BDTR_t          BDTR;
        DCR_t           DCR;
        DMAR_t          DMA;
    };
    template<> struct TimerRegs<2> {
        CR1_1825t       CR1;
        CR2_25t         CR2;
        SMCR_1825t      SMCR;
        DIER_25t        DIER;
        SR_25t          SR;
        EGR_25t         EGR;
        uint32_t        CCMR[2];
        uint32_t        CCER;
        CNT32_t         CNT;
        PSC_t           PSC;
        ARR32_t         ARR;
        uint32_t        reserved1;
        CCR32_t         CCR[4];
        uint32_t        reserved2;
        DCR_t           DCR;
        DMAR_t          DMA;
        OR_2t           OR;
    };
    template<> struct TimerRegs<3> {
        CR1_1825t       CR1;
        CR2_25t         CR2;
        SMCR_1825t      SMCR;
        DIER_25t        DIER;
        SR_25t          SR;
        EGR_25t         EGR;
        uint32_t        CCMR[2];
        uint32_t        CCER;
        CNT_t           CNT;
        PSC_t           PSC;
        ARR_t           ARR;
        uint32_t        reserved1;
        CCR_t           CCR[4];
        BDTR_t          BDTR;
        DCR_t           DCR;
        DMAR_t          DMA;
        OR_5t           OR;
    };
    template<> struct TimerRegs<4> {
        CR1_1825t       CR1;
        CR2_25t         CR2;
        SMCR_1825t      SMCR;
        DIER_25t        DIER;
        SR_25t          SR;
        EGR_25t         EGR;
        uint32_t        CCMR[2];
        uint32_t        CCER;
        CNT_t           CNT;
        PSC_t           PSC;
        ARR_t           ARR;
        uint32_t        reserved1;
        CCR_t           CCR[4];
        uint32_t        reserved2;
        DCR_t           DCR;
        DMAR_t          DMA;
    };
    template<> struct TimerRegs<5> {
        CR1_1825t       CR1;
        CR2_25t         CR2;
        SMCR_1825t      SMCR;
        DIER_25t        DIER;
        SR_25t          SR;
        EGR_25t         EGR;
        uint32_t        CCMR[2];
        uint32_t        CCER;
        CNT32_t         CNT;
        PSC_t           PSC;
        ARR32_t         ARR;
        uint32_t        reserved1;
        CCR32_t         CCR[4];
        uint32_t        reserved2;
        DCR_t           DCR;
        DMAR_t          DMA;
    };
    template<> struct TimerRegs<6> {
        CR1_67t         CR1;
        CR2_67t         CR2;
        uint32_t        reserved1;
        DIER_67t        DIER;
        SR_67t          SR;
        EGR_67t         EGR;
        uint32_t        reserved2;
        uint32_t        reserved3;
        uint32_t        reserved4;
        CNT_t           CNT;
        PSC_t           PSC;
        ARR_t           ARR;
    };
    template<> struct TimerRegs<7> {
        CR1_1825t       CR1;
        CR2_25t         CR2;
        uint32_t        reserved1;
        DIER_25t        DIER;
        SR_25t          SR;
        EGR_25t         EGR;
        uint32_t        reserved2;
        uint32_t        reserved3;
        uint32_t        reserved4;
        CNT_t           CNT;
        PSC_t           PSC;
        ARR_t           ARR;
    };
    template<> struct TimerRegs<8> {
        CR1_1825t       CR1;
        CR2_18t         CR2;
        SMCR_1825t      SMCR;
        DIER_18t        DIER;
        SR_18t          SR;
        EGR_18t         EGR;
        uint32_t        CCMR[2];
        uint32_t        CCER;
        CNT_t           CNT;
        PSC_t           PSC;
        ARR_t           ARR;
        RCR_t           RCR;
        CCR_t           CCR[4];
        BDTR_t          BDTR;
        DCR_t           DCR;
        DMAR_t          DMA;
    };
    template<> struct TimerRegs<9> {
        CR1_9121014t    CR1;
        uint32_t        reserved1;
        SMCR_912t       SMCR;
        DIER_912t       DIER;
        SR_912t         SR;
        EGR_912t        EGR;
        uint32_t        CCMR[1];
        uint32_t        reserved2;
        uint32_t        CCER;
        CNT_t           CNT;
        PSC_t           PSC;
        ARR_t           ARR;
        uint32_t        reserved3;
        CCR_t           CCR[2];
    };
    template<> struct TimerRegs<10> {
        CR1_9121014t    CR1;
        uint32_t        reserved1;
        uint32_t        reserved2;
        DIER_1014t      DIER;
        SR_1014t        SR;
        EGR_1014t       EGR;
        uint32_t        CCMR;
        uint32_t        reserved3;
        uint32_t        CCER;
        CNT_t           CNT;
        PSC_t           PSC;
        ARR_t           ARR;
        uint32_t        reserved4;
        CCR_t           CCR;
    };
    template<> struct TimerRegs<11> {
        CR1_9121014t    CR1;
        uint32_t        reserved1;
        uint32_t        reserved2;
        DIER_1014t      DIER;
        SR_1014t        SR;
        EGR_1014t       EGR;
        uint32_t        CCMR;
        uint32_t        reserved3;
        uint32_t        CCER;
        CNT_t           CNT;
        PSC_t           PSC;
        ARR_t           ARR;
        uint32_t        reserved4;
        CCR_t           CCR;
    };
    template<> struct TimerRegs<12> {
        CR1_9121014t    CR1;
        uint32_t        reserved1;
        SMCR_912t       SMCR;
        DIER_912t       DIER;
        SR_912t         SR;
        EGR_912t        EGR;
        uint32_t        CCMR;
        uint32_t        reserved2;
        uint32_t        CCER;
        CNT_t           CNT;
        PSC_t           PSC;
        ARR_t           ARR;
        uint32_t        reserved3;
        CCR_t           CCR[2];
    };
    template<> struct TimerRegs<13> {
        CR1_9121014t    CR1;
        uint32_t        reserved1;
        uint32_t        reserved2;
        DIER_1014t      DIER;
        SR_1014t        SR;
        EGR_1014t       EGR;
        uint32_t        CCMR;
        uint32_t        reserved3;
        uint32_t        CCER;
        CNT_t           CNT;
        PSC_t           PSC;
        ARR_t           ARR;
        uint32_t        reserved4;
        CCR_t           CCR;
    };
    template<> struct TimerRegs<14> {
        CR1_9121014t    CR1;
        uint32_t        reserved1;
        uint32_t        reserved2;
        DIER_1014t      DIER;
        SR_1014t        SR;
        EGR_1014t       EGR;
        uint32_t        CCMR;
        uint32_t        reserved3;
        uint32_t        CCER;
        CNT_t           CNT;
        PSC_t           PSC;
        ARR_t           ARR;
        uint32_t        reserved4;
        CCR_t           CCR;
    };


//}
struct Timer {
    enum Trgo {
        tReset = 0,
        tEnable = 1,
        tUpdate = 2,
        tComparePulse = 3,
        tCompareOC1REF = 4,
        tCompareOC2REF = 5,
        tCompareOC3REF = 6,
        tCompareOC4REF = 7
    };

    enum PwmMode {
        pmFrozen = 0b000,
        pmActiveLevel = 0b001,
        pmInactiveLevel = 0b010,
        pmToggle = 0b011,
        pmForceInactive = 0b100,
        pmForceActive = 0b101,
        pmPwm1 = 0b110,
        pmPwm2 = 0b111
    };

    enum CcMode {
        ccmOutput = 0b00,
        cc1InputTi1 = 0b01,
        cc1InputTi2 = 0b10,
        cc2InputTi2 = 0b01,
        cc2InputTi1 = 0b10,
        cc3InputTi3 = 0b01,
        cc3InputTi4 = 0b10,
        cc4InputTi4 = 0b01,
        cc4InputTi3 = 0b10,
        ccInputTrc = 0b11
    };

    enum CcPolarity {
        ccpActiveHigh = 0,
        ccpActiveLow = 1
    };

    enum Ti1Selection {
        t1sChannel1 = 0,
        t1sChannel123Xor = 1
    };

    enum SlaveMode {
        smDisabled = 0b000,
        smEncoder1 = 0b001,
        smEncoder2 = 0b010,
        smEncoder3 = 0b011,
        smReset = 0b100,
        smGated = 0b101,
        smTrigger = 0b110,
        smExternalClock = 0b111
    };

    enum TriggerSelection {
        tsTrigger0 = 0b000,
        tsTrigger1 = 0b001,
        tsTrigger2 = 0b010,
        tsTrigger3 = 0b011,
        tsTi1Edge = 0b100,
        tsFilteredTimerInput1 = 0b101,
        tsFilteredTimerInput2 = 0b110,
        tsExternalTriggerInput = 0b111
    };

    enum InputCaptureFilter {
        icfNoFlilter = 0b0000,
        icfFckIntN2 = 0b0001,
        icfFckIntN4 = 0b0010,
        icfFckIntN8 = 0b0011,
        icfFdts2N6 = 0b0100,
        icfFdts2N8 = 0b0101,
        icfFdts4N6 = 0b0110,
        icfFdts4N8 = 0b0111,
        icfFdts8N6 = 0b1000,
        icfFdts8N8 = 0b1001,
        icfFdts16N5 = 0b1010,
        icfFdts16N6 = 0b1011,
        icfFdts16N8 = 0b1100,
        icfFdts32N5 = 0b1101,
        icfFdts32N6 = 0b1110,
        icfFdts32N8 = 0b1111,
    };

};

template<int num>
struct Tim {

#ifdef DEBUG
    volatile TimerRegs<num>* volatile debug = reinterpret_cast<TimerRegs<num>*volatile>(tim_t<num>::TIM_BASE);
#endif



    ///---------------------------------------------------------------------
    ///
    /// \brief Включение тактирования
    ///
    INLINE static void clockEnable(const bool en)
    {
        tim_t<num>::clockEnable(en);
    }


    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    INLINE static volatile TimerRegs<num>* rg()
    {
        return reinterpret_cast<volatile TimerRegs<num> * volatile>(tim_t<num>::TIM_BASE);
    }



    INLINE static void enable(bool en) { rg()->CR1.CEN = en; }

    INLINE static void setTRGO(Timer::Trgo trgo) { rg()->CR2.MMS = trgo; }

    INLINE static void setCounter(uint16_t counter) { rg()->CNT.CNTK = counter;  }
    INLINE static void setArr(uint16_t arr) { rg()->ARR.ARR = arr;  }
	INLINE static void setUpdateRequestSource(bool urs)
	{
		rg()->CR1.URS = urs;

	}

	INLINE static void updateGeneration(bool ug = true)
	{
		rg()->EGR.UG = ug;
	}

    INLINE static void presetForUpdate(uint16_t prescaler, uint32_t  arr)
    {
//        rg()->CR1.ARPE = 1;          // ARR is buffered
        rg()->PSC.PSC = prescaler;
        rg()->ARR.ARR = arr;
    }

    INLINE static void setUpdateInterrupt(uint32_t priorityGroup,
                               uint32_t preemptPriority,
                               uint32_t subPriority)
    {
        Rcc::clockSyscfg(true);

        Nvic::setPriority(static_cast<Nvic::IrqType>(tim_t<num>::UP_IRQn), preemptPriority);  //TODO:
        Nvic::enableIrq(static_cast<Nvic::IrqType>(tim_t<num>::UP_IRQn));


    }

    INLINE static void enableUpdateInterrupt(bool en) { rg()->DIER.UIE = en; }
    INLINE static void enableUpdateDma(bool en) { rg()->DIER.UDE = en; }
    INLINE static void clearUpdateInterruptFlag() { rg()->SR.UIF = 0; }
    INLINE static bool updateInterruptFlag() { return (rg()->SR.UIF == 1); }


    INLINE static void enableMainOutput(UNUSED const bool en)
    {
        switch (num) {

        if constexpr ((num == 1) &&
                      (num == 8)
                      ) {rg()->BDTR.MOE = en;}

        }
    } //TODO add specialization


    INLINE static void selectTi1(Timer::Ti1Selection selection) { rg()->CR2.TI1S = selection; }

    INLINE static void selectSlaveMode(Timer::SlaveMode mode) 
	{ 
		rg()->SMCR.SMS = mode; 
	}
    INLINE static void selectSlaveTrigger(Timer::TriggerSelection selection) { rg()->SMCR.TS = selection; }

    INLINE static uint32_t getCounter() { return rg()->CNT.CNTK; }


    ///------------------------------------------------------------------------
    INLINE static void setCcMode(uint8_t channel, Timer::CcMode mode)
    {
        uint32_t index = ((channel - 1) >> 1) & 0b01;
        uint32_t pos = (channel - 1)  & 0b01;
        uint32_t mask = 3U << (pos * 8);
        uint32_t value = static_cast<uint32_t>(mode) << (pos * 8);

        rg()->CCMR[index] = (rg()->CCMR[index] & (~mask)) | value;

    }

    ///------------------------------------------------------------------------
    INLINE static void setCcInputFilter(uint8_t channel, Timer::InputCaptureFilter filter)
    {
        uint32_t index = ((channel - 1) >> 1) & 0b01;
        uint32_t pos = (channel - 1)  & 0b01;
        uint32_t mask = 15U << (pos * 8);
        uint32_t value = static_cast<uint32_t>(filter) << (pos * 8 + 4);

        rg()->CCMR[index] = (rg()->CCMR[index] & (~mask)) | value;

    }


    ///------------------------------------------------------------------------
    INLINE static void setOutputCompareMode(uint8_t channel, Timer::PwmMode mode)
    {
        uint32_t index = ((channel - 1) >> 1) & 0b01;
        uint32_t pos = (channel - 1)  & 0b01;
        uint32_t mask = 7U << (pos * 8 + 4);
        uint32_t value = static_cast<uint32_t>(mode) << (pos * 8 + 4);

        rg()->CCMR[index] = (rg()->CCMR[index] & (~mask)) | value;

    }
    ///------------------------------------------------------------------------
    INLINE static void setCcPolarity(uint8_t channel, Timer::CcPolarity polarity)
    {
        uint32_t mask = 1U << ((channel - 1) * 4 + 1);
        uint32_t value = static_cast<uint32_t>(polarity) << ((channel - 1) * 4 + 1);

        rg()->CCER = (rg()->CCER & (~mask)) | value;
    }

    ///------------------------------------------------------------------------
    INLINE static void setCcPolarityN(uint8_t channel, Timer::CcPolarity polarity)
    {
        uint32_t mask = 1U << ((channel - 1) * 4 + 3);
        uint32_t value = static_cast<uint32_t>(polarity) << ((channel - 1) * 4 + 3);

        rg()->CCER = (rg()->CCER & (~mask)) | value;
    }

    ///------------------------------------------------------------------------
    INLINE static void enableCcOutput(uint8_t channel, bool en)
    {
        uint32_t mask = 1U << ((channel - 1) * 4);
        uint32_t value = static_cast<uint32_t>(en) << ((channel - 1) * 4);

        rg()->CCER = (rg()->CCER & (~mask)) | value;
    }

    ///------------------------------------------------------------------------
    INLINE static void enableCcOutputN(uint8_t channel, bool en)
    {
        uint32_t mask = 1U << ((channel - 1) * 4 + 2);
        uint32_t value = static_cast<uint32_t>(en) << ((channel - 1) * 4 + 2);

        rg()->CCER = (rg()->CCER & (~mask)) | value;
    }

    ///------------------------------------------------------------------------
    INLINE static void setCcValue(uint8_t channel, uint32_t value)
    {
       rg()->CCR[(channel - 1)].CCR = value;
    }

    ///------------------------------------------------------------------------
    INLINE static uint8_t getIrqnUp()
    {
       return tim_t<num>::UP_IRQn;
    }



};





#endif // TIM_H
