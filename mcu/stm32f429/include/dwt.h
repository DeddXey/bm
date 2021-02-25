#ifndef DWT_H
#define DWT_H


#include "utility.h"
#include <cstdint>
#include "instr.h"

struct Dwt {

	constexpr static uint32_t base = 0xE0001000;

	// if four comparators for watchpoints and triggers are present.
	constexpr static uint32_t reset1 = 0x40000000;
	// if four comparators for watchpoints only are present.
	constexpr static uint32_t reset2 = 0x4F000000;
	// if only one comparator is present.
	constexpr static uint32_t reset3 = 0x10000000;
	// if one comparator for watchpoints and not triggers is present.
	constexpr static uint32_t reset4 = 0x1F000000;
	// if DWT is not present.
	constexpr static uint32_t reset5 = 0x00000000;


	struct Bp {
		uint32_t	COMP;
		uint32_t	MASK;
		uint32_t	FUNCTION;
	};

	struct Regs {
		uint32_t	CTRL;
		uint32_t	CYCNT;
		uint32_t	CPICNT;
		uint32_t	EXCCNT;
		uint32_t	SLEEPCNT;
		uint32_t	LSUCNT;
		uint32_t	FOLDCNT;
		uint32_t	PCSR;
		Bp			BP[4];
	};

	struct PidCid {
		uint32_t	PID4;
		uint32_t	PID5;
		uint32_t	PID6;
		uint32_t	PID7;
		uint32_t	PID0;
		uint32_t	PID1;
		uint32_t	PID2;
		uint32_t	PID3;
		uint32_t	CID0;
		uint32_t	CID1;
		uint32_t	CID2;
		uint32_t	CID3;
	};

	struct CTRL {
		constexpr static uint8_t EN[]{ 0, 1 }; 	//
	};
	struct DEMCR {
		constexpr static uint8_t EN[]{ 24, 1 }; 	//
	};


	INLINE static volatile Regs* rg()
	{
		return reinterpret_cast<Regs*volatile>(base);
	}

	INLINE static volatile uint32_t* rgDemcr()
	{
		return reinterpret_cast<uint32_t*volatile>(0xE000EDFC);
	}

	INLINE static void enableTrace(const bool en)
	{
		return ::setRegister(*rgDemcr(),
		                            DEMCR::EN, en);
	}


	INLINE static void enableCounter(const bool en)
	{
		return ::setRegister(rg()->CTRL,
		                            CTRL::EN, en);
	}

	INLINE static uint16_t getCounter()
	{
		return __LDREXW(&rg()->CYCNT);
	}
	INLINE static uint16_t getControlRegister()
	{
		return rg()->CTRL;
	}

	INLINE static void resetCounter()
	{
		rg()->CYCNT = 0;
	}



};


#endif // DWT_H
