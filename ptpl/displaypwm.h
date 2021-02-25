#ifndef DISPLAYPWM_H
#define DISPLAYPWM_H

#include "tim.h"



template <typename I>
class DisplayPwmTimer {

	constexpr static uint16_t period = 42000 / I::pwmFreq;

public:
	static void init()
	{
		I::preInit();

		const uint16_t pulse = (50 * (period + 1)) / 100;



		Tim<I::pwmTimer>::clockEnable(true);
		Tim<I::pwmTimer>::presetForUpdate(1999, period);
		Tim<I::pwmTimer>::enable(true);
		Tim<I::pwmTimer>::setCcMode(I::pwmTimerChannel, Timer::ccmOutput);
		Tim<I::pwmTimer>::setOutputCompareMode(I::pwmTimerChannel, Timer::pmPwm1);
		Tim<I::pwmTimer>::setCcPolarity(I::pwmTimerChannel, Timer::ccpActiveHigh);
		Tim<I::pwmTimer>::setCcValue(I::pwmTimerChannel, pulse);
		Tim<I::pwmTimer>::enableCcOutput(I::pwmTimerChannel, true);
		Tim<I::pwmTimer>::enableMainOutput(true);

	}

	static void setDuty(const uint8_t duty)
	{
		const uint16_t pulse = (duty * (period + 1)) / 100;
		Tim<I::pwmTimer>::setCcValue(I::pwmTimerChannel, pulse);
	}
};



#endif // DISPLAYPWM_H
