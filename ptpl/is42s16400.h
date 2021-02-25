#ifndef IS42S16400_H
#define IS42S16400_H

#include "fmc.h"


template <typename I>
class Is42S16400 {

public:
	static bool init();
};


template<typename I>
bool Is42S16400<I>::init()
{
	I::preInit();

	FmcSdram::clockEnable(true);

	FmcSdram::configControl(1,
	                        Fmc::cab8,
	                        Fmc::rab12,
	                        Fmc::bw16,
	                        Fmc::nbFour,
	                        3,
	                        false,
	                        Fmc::cc2Periods,
	                        false,
	                        Fmc::rpOneClock);



	FmcSdram::setTiming(1, 2, 7, 4, 7, 2, 2, 2);

	if (!FmcSdram::sendCommand(false, true, Fmc::mClockConfigurationEnable))
		return false;

	::simpleDelay(168000); // 100uS ну или как-то так :)

	if (!FmcSdram::sendCommand(false, true, Fmc::mPall))
		return false;

	if (!FmcSdram::sendCommand(false, true, Fmc::mAutoRefresh, 4))
		return false;

	if (!FmcSdram::sendCommand(false, true, Fmc::mLoadModeRegister, 1,
	                           I::moderegBurstLength2 |
	                           I::moderegBurstTypeSequential |
	                           I::moderegCasLatency3 |
	                           I::moderegOperatingModeStandard |
	                           I::moderegWriteburstModeSingle))
		return false;

	FmcSdram::setRefreshCount(I::refreshCount);

	return true;
}


#endif //IS42S16400_H
