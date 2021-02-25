#ifndef RTC_H
#define RTC_H


#include <stdint.h>
#include "rcc.h"
//#include "mcu.h"


struct Rtc {

    struct TR_t {
        uint32_t        SU:4;
        uint32_t        ST:3;
        uint32_t        RESERVED1:1;
        uint32_t        MNU:4;
        uint32_t        MNT:3;
        uint32_t        RESERVED2:1;
        uint32_t        HU:4;
        uint32_t        HT:2;
        uint32_t        PM:1;
    };

    struct DR_t {
            uint32_t        DU:4;
            uint32_t        DT:2;
            uint32_t        RESERVED1:2;
            uint32_t        MU:4;
            uint32_t        MT:1;
            uint32_t        WDU:3;
            uint32_t        YU:4;
            uint32_t        YT:4;
            uint32_t        RESERVED2:1;
    };

    struct CR_t {
            uint32_t        WCKSEL:3;
            uint32_t        TSEDGE:1;
            uint32_t        REFCKON:1;
            uint32_t        BYPSHAD:1;
            uint32_t        FMT:1;
            uint32_t        DCE:1;
            uint32_t        ALRAE:1;
            uint32_t        ALRBE:1;
            uint32_t        WUTE:1;
            uint32_t        TSE:1;
            uint32_t        ALRAIE:1;
            uint32_t        ALRBIE:1;
            uint32_t        WUTIE:1;
            uint32_t        TSIE:1;
            uint32_t        ADD1H:1;
            uint32_t        SUB1H:1;
            uint32_t        BKP:1;
            uint32_t        COSEL:1;
            uint32_t        POL:1;
            uint32_t        OSEL:2;
            uint32_t        COE:1;
            uint32_t        RESERVED:1;
    };

    struct ISR_t {
            uint32_t        ALRAWF:1;
            uint32_t        ALRBWF:1;
            uint32_t        WUTWF:1;
            uint32_t        SHPF:1;
            uint32_t        INITS:1;
            uint32_t        RSF:1;
            uint32_t        INITF:1;
            uint32_t        INIT:1;
            uint32_t        ALRAF:1;
            uint32_t        ALRBF:1;
            uint32_t        WUTF:1;
            uint32_t        TSF:1;
            uint32_t        TSOVF:1;
            uint32_t        TAMP1F:1;
            uint32_t        TAMP2F:1;
            uint32_t        RESERVED:16;
    };

    struct PRER_t {
            uint32_t        PREDIV_S:15;
            uint32_t        RESERVED1:1;
            uint32_t        PREDIV_A:7;
            uint32_t        RESERVED2:1;
    };

    struct WUTR_t {
            uint32_t        WUT:16;
            uint32_t        RESERVED1:16;
    };

    struct CALIBR_t {
            uint32_t        DC:5;
            uint32_t        RESERVED1:2;
            uint32_t        DCS:1;
            uint32_t        RESERVED2:1;
    };

    struct ALRMR_t {
            uint32_t        SU:4;
            uint32_t        ST:3;
            uint32_t        MSK1:1;
            uint32_t        MNU:4;
            uint32_t        MNT:3;
            uint32_t        MSK2:1;
            uint32_t        HU:4;
            uint32_t        HT:2;
            uint32_t        PM:1;
            uint32_t        MSK3:1;
            uint32_t        DU:4;
            uint32_t        DT:2;
            uint32_t        WDSEL:1;
            uint32_t        MSK4:1;
    };

    struct WPR_t {
            uint32_t        KEY:8;
            uint32_t        RESERVED1:16;
    };

    struct SSR_t {
            uint32_t        SS:16;
            uint32_t        RESERVED1:16;
    };

    struct SHIFTR_t {
            uint32_t        SUBFS:15;
            uint32_t        RESERVED:16;
            uint32_t        ADD1S:1;
    };

    struct TSTR_t {
            uint32_t        SU:4;
            uint32_t        ST:3;
            uint32_t        RESERVED1:1;
            uint32_t        MNU:4;
            uint32_t        MNT:3;
            uint32_t        RESERVED2:1;
            uint32_t        HU:4;
            uint32_t        HT:2;
            uint32_t        PM:1;
            uint32_t        RESERVED3:1;
    };

    struct TSSSR_t {
            uint32_t        SS:16;
            uint32_t        RESERVED1:16;
    };
    struct CALR_t {
            uint32_t        CALM:9;
            uint32_t        RESERVED1:4;
            uint32_t        CALW16:1;
            uint32_t        CALW8:1;
            uint32_t        CALP:1;
            uint32_t        RESERVED:16;
    };

    struct TAFCR_t {
            uint32_t        TAMP1E:1;
            uint32_t        TAMP1ETRG:1;
            uint32_t        TAMPIE:1;
            uint32_t        TAMP2E:1;
            uint32_t        TAMP2TRG:1;
            uint32_t        RESERVED1:2;
            uint32_t        TAMPTS:1;
            uint32_t        TAMPFREQ:3;
            uint32_t        TAMPFLT:2;
            uint32_t        TAMPPRCH:2;
            uint32_t        TAMPPUDIS:1;
            uint32_t        TAMP1INSEL:1;
            uint32_t        TSINSEL:1;
            uint32_t        ALARMOUTTYPE:1;
            uint32_t        RESERVED:1;
    };

    struct ALRMSSR_t {
            uint32_t        SS:15;
            uint32_t        RESERVED1:9;
            uint32_t        MASKSS:4;
            uint32_t        RESERVED:4;
    };

    struct Regs {
        TR_t        TR;
        DR_t        DR;
        CR_t        CR;
        ISR_t       ISR;
        PRER_t      PRER;
        WUTR_t      WUTR;
        CALIBR_t    CALIBR;
        ALRMR_t     ALRMAR;
        ALRMR_t     ALRMBR;
        WPR_t       WPR;
        SSR_t       SSR;
        SHIFTR_t    SHIFTR;
        TSTR_t      TSTR;
        TSSSR_t     TSSSR;
        CALR_t      CALR;
        TAFCR_t     TAFCR;
        ALRMSSR_t   ALRMASSR;
        ALRMSSR_t   ALRMBSSR;
        uint32_t    BKPR[20];
    };

    constexpr static uint32_t base = 0x40002800;
    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    INLINE static volatile Regs* rg()
    {
        return reinterpret_cast<volatile Regs * volatile>(base);
    }

    //---------------------------------------------------------------------
//    ///
//    /// \brief Включение тактирования
//    ///
//    INLINE static void clockEnable(bool en)
//    {
//        Rcc::rg()->APB1ENR. = en;
//    }

    INLINE static void writeProtectionDisable()
    {
        rg()->WPR.KEY = 0xCAU;
        rg()->WPR.KEY = 0x53U;
    }

    INLINE static void writeProtectionEnable()
    {
        rg()->WPR.KEY = 0xFFU;
    }

    /*inline */static void set( uint8_t day,
                            uint8_t month,
                            uint8_t year,
                            uint8_t hour,
                            uint8_t minute,
                            uint8_t sec,
                            uint16_t predivS = 255,
                            uint8_t predivA = 127)
    {
        writeProtectionDisable();
        rg()->ISR.INIT = 1;

        while (rg()->ISR.INITF != 1) {::simpleDelay(1); }

        rg()->CR.BYPSHAD = 1;

        rg()->PRER.PREDIV_A = predivA;
        rg()->PRER.PREDIV_S = predivS;
        rg()->DR.DT = day / 10;
        rg()->DR.DU = day - (rg()->DR.DT * 10);
        rg()->DR.MT = month / 10;
        rg()->DR.MU = month - (rg()->DR.MT * 10);
        rg()->DR.YT = year / 10;
        rg()->DR.YU = year - (rg()->DR.YT * 10);

        rg()->TR.HT = hour / 10;
        rg()->TR.HU = hour - (rg()->TR.HT * 10);
        rg()->TR.MNT = minute / 10;
        rg()->TR.MNU = minute - (rg()->TR.MNT * 10);
        rg()->TR.ST = sec / 10;
        rg()->TR.SU = sec - (rg()->TR.ST * 10);

        rg()->CR.FMT = 0;
        rg()->ISR.INIT = 0;

        writeProtectionEnable();

    }

    INLINE static uint8_t getHour() { return rg()->TR.HT * 10 + rg()->TR.HU; }
    INLINE static uint8_t getMinutes() { return rg()->TR.MNT * 10 + rg()->TR.MNU; }
    INLINE static uint8_t getSeconds() { return rg()->TR.ST * 10 + rg()->TR.SU; }

    INLINE static uint8_t getDay() { return rg()->DR.DT * 10 + rg()->DR.DU; }
    INLINE static uint8_t getMonth() { return rg()->DR.MT * 10 + rg()->DR.MU; }
    INLINE static uint8_t getYear() { return rg()->DR.YT * 10 + rg()->DR.YU; }


};

#endif // RTC_H
