
#ifndef FMC_H
#define FMC_H

#include <stdint.h>
#include "rcc.h"

#include<utility.h>

namespace Fmc {

enum ReadPipe {
    rpNoClock = 0b00,
    rpOneClock = 0b01,
    rpTwoClock = 0b10,

};

enum ClockConfig {
    ccDisable = 0b00,
    cc2Periods = 0b10,
    cc3Periods = 0b11
};

enum NumBanks {
    nbTwo = 0,
    nbFour = 1
};

enum Mode {
    mNormal = 0,
    mClockConfigurationEnable = 0b001,
    mPall = 0b010,
    mAutoRefresh = 0b011,
    mLoadModeRegister = 0b100,
    mSelfRefresh = 0b101,
    mPowerDown = 0b110
};

enum BusWidth {
    bw8 = 0b00,
    bw16 = 0b01,
    bw32 = 0b10
};

enum RowAddressBits {
    rab11 = 0b00,
    rab12 = 0b01,
    rab13 = 0b10
};
enum ColumnAddressBits {
    cab8 = 0b00,
    cab9 = 0b01,
    cab10 = 0b10,
    cab11 = 0b11
};

};



struct FmcSdram {

	struct SDCR {
		constexpr static uint8_t NC[]{ 0, 2 }; 	//< Number of column address bits
		constexpr static uint8_t NR[]{ 2, 2 }; 	//< Number of row address bits
		constexpr static uint8_t MWID[]{ 4, 2 }; 	//< Memory data bus width
		constexpr static uint8_t NB[]{ 6, 1 }; 	//< Number of internal banks
		constexpr static uint8_t CAS[]{ 7, 2 }; 	//< CAS latency
		constexpr static uint8_t WP[]{ 9, 1 }; 	//< Write protection
		constexpr static uint8_t SDCLK[]{ 10, 2 }; 	//< SDRAM clock configuration
		constexpr static uint8_t RBURST[]{ 12, 1 }; 	//< Burst read
		constexpr static uint8_t RPIPE[]{ 13, 2 }; 	//< Read pipe
	};


	struct SDTR {
		constexpr static uint8_t TMRD[]{ 0, 4 }; 	//< Load Mode Register to Active
		constexpr static uint8_t TXSR[]{ 4, 4 }; 	//< Exit self-refresh delay
		constexpr static uint8_t TRAS[]{ 8, 4 }; 	//< Self refresh time
		constexpr static uint8_t TRC[]{ 12, 4 }; 	//< Row cycle delay
		constexpr static uint8_t TWR[]{ 16, 4 }; 	//< Recovery delay
		constexpr static uint8_t TRP[]{ 20, 4 }; 	//< Row precharge delay
		constexpr static uint8_t TRCD[]{ 24, 4 }; 	//< Row to column delay
	};


	struct SDCMR {
		constexpr static uint8_t MODE[]{ 0, 3 }; 	//< Command mode
		constexpr static uint8_t CTB2[]{ 3, 1 }; 	//< Command target bank 2
		constexpr static uint8_t CTB1[]{ 4, 1 }; 	//< Command target bank 1
		constexpr static uint8_t NRFS[]{ 5, 4 }; 	//< Number of Auto-refresh
		constexpr static uint8_t MRD[]{ 9, 13 }; 	//< Mode Register definition
	};

	struct SDRTR {
		constexpr static uint8_t CRE[]{ 0, 1 }; 	//< Clear Refresh error flag
		constexpr static uint8_t COUNT[]{ 1, 13 }; 	//< Refresh Timer Count
		constexpr static uint8_t REIE[]{ 14, 1 }; 	//< RES Interrupt Enable
	};

	struct SDSR {
		constexpr static uint8_t RE[]{ 0, 1 }; 	//< Refresh error flag
		constexpr static uint8_t MODES1[]{ 1, 2 }; 	//< Status Mode for Bank 1
		constexpr static uint8_t MODES2[]{ 3, 2 }; 	//< Status Mode for Bank 2
		constexpr static uint8_t BUSY[]{ 5, 1 }; 	//< Busy status
	};


    struct Regs {

        uint32_t    SDCR[2];
        uint32_t    SDTR[2];
        uint32_t    SDCMR;
        uint32_t    SDRTR;
		uint32_t	SDSR;
    };

	constexpr static uint32_t base = 0xA0000000 + 0x140;


    //    constexpr static volatile Regs* const rcc = /*reinterpret_cast<Regs*>*/(Regs*)(BASE);

    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    INLINE static volatile Regs* rg()
    {
		return reinterpret_cast<volatile Regs*volatile>(base);
    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Включение тактирования
    ///
    INLINE static void clockEnable(const bool en)
    {
        Rcc::clockFmc(en);
    }

	INLINE static void configControl(const uint8_t bank,
	                                 const Fmc::ColumnAddressBits columnAddressBits,
	                                 const Fmc::RowAddressBits rowAddressBits,
	                                 const Fmc::BusWidth busWidth,
	                                 const Fmc::NumBanks numBanks,
	                                 const uint8_t casLatency,
	                                 const bool writeProtection,
	                                 const Fmc::ClockConfig clockConfig,
	                                 const bool burstRead,
	                                 const Fmc::ReadPipe readPipe)
    {
		::setRegister(rg()->SDCR[bank],
		                     SDCR::NC, columnAddressBits,
		                     SDCR::NR, rowAddressBits,
		                     SDCR::MWID, busWidth,
		                     SDCR::NB, numBanks,
		                     SDCR::CAS, casLatency,
		                     SDCR::WP, writeProtection,
		                     SDCR::SDCLK, clockConfig,
		                     SDCR::RBURST, burstRead,
		                     SDCR::RPIPE, readPipe);


        if (bank == 1) {
			::setRegister(rg()->SDCR[0],
			                     SDCR::SDCLK, clockConfig,
			                     SDCR::RBURST, burstRead,
			                     SDCR::RPIPE, readPipe);
        }
    }


	INLINE static void setTiming(const uint8_t bank,
	                             const uint8_t loadModeRegisterActive,
	                             const uint8_t exitSelfRefreshDelay,
	                             const uint8_t selfRefreshTime,
	                             const uint8_t rowCycleDelay,
	                             const uint8_t recoveryDelay,
	                             const uint8_t rowPrechargeDelay,
	                             const uint8_t rowToColumnDelay)
    {
		::setRegister(rg()->SDTR[bank],
		                     SDTR::TMRD, loadModeRegisterActive - 1,
		                     SDTR::TXSR, exitSelfRefreshDelay - 1,
		                     SDTR::TRAS, selfRefreshTime - 1,
		                     SDTR::TRC, rowCycleDelay - 1,
		                     SDTR::TWR, recoveryDelay - 1,
		                     SDTR::TRP, rowPrechargeDelay - 1,
		                     SDTR::TRCD, rowToColumnDelay - 1);

        if (bank == 1) {
			::setRegister(rg()->SDTR[0],
			                     SDTR::TRC, rowCycleDelay - 1,
			                     SDTR::TRP, rowPrechargeDelay - 1);
        }
    }

	static bool sendCommand(const bool bank1,
	                               const bool bank2,
	                               const Fmc::Mode mode,
	                               const uint8_t numberOfAutorefresh = 1,
	                               const uint16_t modeRegister = 0);

	INLINE static void setRefreshCount(const uint16_t refreshCount)
    {
		::setRegister(rg()->SDRTR,
		                     SDRTR::COUNT, refreshCount);
    }

};








#endif // FMC_H
