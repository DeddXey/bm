#ifndef PROFILER_H
#define PROFILER_H

#include <cstdint>
#include "dwt.h"
#include "rcc.h"


class Profiler
{
    uint32_t counter;
public:
    Profiler()
    {
		Dwt::enableTrace(true);
		Dwt::enableCounter(true);
		resetCycles();
    }

    INLINE void resetCycles()
    {
		counter = 0;
		Dwt::resetCounter();
    }

    INLINE uint32_t getCycles()
    {
		return (Dwt::getCounter() - counter);
    }

	INLINE float getSeconds()
	{
		return getCycles() / Rcc::systemCoreClock();
	}

	INLINE uint32_t getMicroSeconds()
	{
		return (getCycles() * static_cast<uint64_t>(1000000)) / Rcc::systemCoreClock();
	}

};

#endif // PROFILER_H
