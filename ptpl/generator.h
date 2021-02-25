#ifndef GENERATOR_H
#define GENERATOR_H

#include "dac.h"
#include "dbg.h_"
#include "dma.h"
#include "table.h"
#include "tim.h"
#include <cstdint>
#include <math.h>

//TODO: вытащить в отдельный  модуль
/// Вспомогательный класс для задания правильного размера пересылки в
/// контроллере DMA
template <int a>
struct DmaDataSize {

};

template<>
struct DmaDataSize<2> {
	constexpr static auto value = Dma::dsHalfWord;
};

template<>
struct DmaDataSize<4> {
	constexpr static auto value = Dma::dsWord;
};

/// ШИМ генератор по таблице синуса с DMA
template <typename I, typename T= int16_t>
class GeneratorPwmSin
{

	constexpr static double pi = 3.14159265358979323846;
	///
	/// \brief Функция заполнения первого квадранта периода синуса
	/// \param idx индекс значения
	/// \return целочисленный синус
	///
	static constexpr T sin16( unsigned idx )
	{
		return sin(pi * 2.0 * idx / I::tableSize) * I::max + I::max;
	}

	static const T* getTable()
	{
		static constexpr Table<T, I::tableSize> sinTable = tableGenerator<T, I::tableSize>(sin16);

		return sinTable.values;
	}

	//    static constexpr Table<T, Initializer::tableSize> sinTable = tableGenerator<int16_t, Initializer::tableSize>(sin16);

public:
	static void init()
	{
		I::preInit();

		I::Timer::clockEnable(true);
		I::Timer::presetForUpdate(I::presc, I::arr);
		I::Timer::setCcMode(I::timerChannelOut, Timer::ccmOutput);
		I::Timer::setOutputCompareMode(I::timerChannelOut, Timer::pmPwm1);
		I::Timer::enableUpdateDma(true);
		I::Timer::enableMainOutput(true);


		I::TableDmaStream::clockEnable(true);
		I::TableDmaStream::setChannel(I::dmaChannel);
		I::TableDmaStream::setMemoryDataSize(DmaDataSize<sizeof(T)>::value);
		I::TableDmaStream::setPeripheralDataSize(DmaDataSize<sizeof(T)>::value);
		I::TableDmaStream::memoryIncrement(true);
		I::TableDmaStream::peripheralIncrement(false);
		//        Initializer::TableDmaStream::setMemoryBurst(Dma::bSingle);
		//        Initializer::TableDmaStream::setPeripheralBurst(Dma::bSingle);

		I::TableDmaStream::circularMode(true);
		I::TableDmaStream::setDmaDirection(Dma::ddMemoryToPeripheral);
		// TODO: move into timer
		I::TableDmaStream::setPeripheralAddress(reinterpret_cast<uint32_t>(&(I::Timer::rg()->CCR[I::timerChannelOut -1])));
		I::TableDmaStream::setMemoryAddress0(reinterpret_cast<uint32_t>(getTable()));
	}

	static void on(const bool val)
	{
		if (val) {
			I::TableDmaStream::setTransferSize(I::tableSize);
			I::Timer::setCounter(0);
		}
		I::TableDmaStream::enable(val);
		I::Timer::enableCcOutput(I::timerChannelOut, val);
		I::Timer::enable(val);
	}

};

template <typename I, typename T= int16_t>
class GeneratorSlaveSimpleMeanderTi1 {

public:
	//------------------------------------------------------------------------
	static void init()
	{
		I::preInit();
		Tim<I::timer>::clockEnable(true);
		Tim<I::timer>::presetForUpdate(I::prescaler, I::timerPeriod);
		Tim<I::timer>::setCcMode(I::timerChannel, Timer::ccmOutput);
		Tim<I::timer>::setOutputCompareMode(I::timerChannel, Timer::pmPwm1);
		Tim<I::timer>::setCcPolarity(I::timerChannel, Timer::ccpActiveHigh);
		Tim<I::timer>::setCcValue(I::timerChannel, I::timerPulse);
		Tim<I::timer>::enableMainOutput(true);

		Tim<I::timer>::selectTi1(Timer::t1sChannel123Xor);
		Tim<I::timer>::setUpdateRequestSource(true);
		// WARN: Check for cc mode all channels
		Tim<I::timer>::setCcMode(I::timerChannelIn, Timer::cc1InputTi1);
		Tim<I::timer>::selectSlaveMode(Timer::smExternalClock);
		Tim<I::timer>::selectSlaveTrigger(Timer::tsFilteredTimerInput1);

		Tim<I::timer>::enable(true);
	}

	//------------------------------------------------------------------------
	INLINE static void on(const bool val)
	{
		I::on(val); // Manage enable/disable pin

		Tim<I::timer>::enableCcOutput(I::timerChannel, val);
		Tim<I::timer>::setCounter(0);
		Tim<I::timer>::updateGeneration();
	}

	//------------------------------------------------------------------------
	static void setFreq(const uint32_t freq)
	{
		constexpr uint32_t maxPresc = 32767;

		const uint32_t	prescaler = ((I::inFreq / freq) +
		                             maxPresc - 1) / maxPresc;


		const uint16_t	timerPeriod = (I::inFreq /
		                               (prescaler) /
		                               freq) - 1;
		const uint16_t	timerPulse = timerPeriod /  I::pulseWidthDivider;
//		const uint16_t	timerPulse = 16;
		Tim<I::timer>::presetForUpdate(prescaler - 1, timerPeriod);
		Tim<I::timer>::setCcValue(I::timerChannel, timerPulse);

	}
};

template <typename I, typename T= int16_t>
class GeneratorSlaveSimpleMeanderTi2 {

public:
	//------------------------------------------------------------------------
	static void init()
	{
		I::preInit();
		Tim<I::timer>::clockEnable(true);
		Tim<I::timer>::presetForUpdate(I::prescaler, I::timerPeriod);
		Tim<I::timer>::setCcMode(I::timerChannel, Timer::ccmOutput);
		Tim<I::timer>::setOutputCompareMode(I::timerChannel, Timer::pmPwm1);
		Tim<I::timer>::setCcPolarity(I::timerChannel, Timer::ccpActiveHigh);
		Tim<I::timer>::setCcValue(I::timerChannel, I::timerPulse);

		Tim<I::timer>::setUpdateRequestSource(true);
		// WARN: Check for cc mode all channels
		Tim<I::timer>::setCcMode(I::timerChannelIn, Timer::cc2InputTi2);
		Tim<I::timer>::selectSlaveMode(Timer::smExternalClock);
		Tim<I::timer>::selectSlaveTrigger(Timer::tsFilteredTimerInput2);

		Tim<I::timer>::enable(true);
	}

	//------------------------------------------------------------------------
	INLINE static void on(const bool val)
	{
		I::on(val); // Manage enable/disable pin

		Tim<I::timer>::enableCcOutput(I::timerChannel, val);
		Tim<I::timer>::setCounter(0);
		Tim<I::timer>::updateGeneration();
	}

	//------------------------------------------------------------------------
	static void setFreq(const uint32_t freq)
	{
		constexpr uint32_t maxPresc = 32767;

		const uint32_t	prescaler = ((I::inFreq / freq) +
		                             maxPresc - 1) / maxPresc;


		const uint16_t	timerPeriod = (I::inFreq /
		                               (prescaler) /
		                               freq) - 1;
		const uint16_t	timerPulse = timerPeriod / I::pulseWidthDivider;
//		const uint16_t	timerPulse = 1;
		Tim<I::timer>::presetForUpdate(prescaler - 1, timerPeriod);
		Tim<I::timer>::setCcValue(I::timerChannel, timerPulse);

	}
};


template <typename I, typename T= int16_t>
class GeneratorSimpleMeander {

public:
	//------------------------------------------------------------------------
	static void init()
	{
		I::preInit();
		Tim<I::timer>::clockEnable(true);
		Tim<I::timer>::presetForUpdate(I::prescaler, I::timerPeriod);
		Tim<I::timer>::setCcMode(I::timerChannel, Timer::ccmOutput);
		Tim<I::timer>::setOutputCompareMode(I::timerChannel, Timer::pmPwm1);
		Tim<I::timer>::setCcPolarity(I::timerChannel, Timer::ccpActiveHigh);
		Tim<I::timer>::setCcValue(I::timerChannel, I::timerPulse);

		Tim<I::timer>::setUpdateRequestSource(true);
		// WARN: Check for cc mode all channels
//		Tim<I::timer>::setCcMode(I::timerChannelIn, Timer::cc2InputTi2);
//		Tim<I::timer>::selectSlaveMode(Timer::smExternalClock);
//		Tim<I::timer>::selectSlaveTrigger(Timer::tsFilteredTimerInput2);

		Tim<I::timer>::enable(true);
	}

	//------------------------------------------------------------------------
	/*INLINE */static void on(const bool val)
	{
		I::on(val); // Manage enable/disable pin

		Tim<I::timer>::enableCcOutput(I::timerChannel, val);
//		Tim<I::timer>::enableCcOutput(I::timerChannel, true);
		Tim<I::timer>::setCounter(0);
		Tim<I::timer>::updateGeneration();
	}

	//------------------------------------------------------------------------
	static void setFreq(const uint32_t freq)
	{
		constexpr uint32_t maxPresc = 32767;

		const uint32_t	prescaler = ((I::inFreq / freq) +
		                             maxPresc - 1) / maxPresc;


		const uint16_t	timerPeriod = (I::inFreq /
		                               (prescaler) /
		                               freq) - 1;
		const uint16_t	timerPulse = timerPeriod / I::pulseWidthDivider;
//		const uint16_t	timerPulse = 1;
		Tim<I::timer>::presetForUpdate(prescaler - 1, timerPeriod);
		Tim<I::timer>::setCcValue(I::timerChannel, timerPulse);

	}
};


/// ЦАП генератор по таблице синуса с DMA
template <typename I, typename T= uint16_t>
class GeneratorDacSin
{

	constexpr static double pi = 3.14159265358979323846;
	///
	/// \brief Функция заполнения таблицы синуса
	/// \param idx индекс значения
	/// \return целочисленный синус
	///
	static constexpr T sin16( unsigned idx )
	{
		return sin(pi * 2.0 * idx / I::tableSize) * I::max + I::max + 1;
	}

	static const T* getTable()
	{
		static constexpr Table<T, I::tableSize> sinTable = tableGenerator<T, I::tableSize>(sin16);

		return sinTable.values;
	}


public:
	static void init()
	{
		Dac::clockEnable(true);
		I::preInit();


		Tim<I::timer>::clockEnable(true);
		Tim<I::timer>::presetForUpdate(I::prescaler, I::timerPeriod);
		Tim<I::timer>::setTRGO(Timer::Trgo::tUpdate);


		I::TableDmaStream::clockEnable(true);
		I::TableDmaStream::setChannel(I::dmaChannel);
		I::TableDmaStream::setMemoryDataSize(DmaDataSize<sizeof(T)>::value);
		I::TableDmaStream::setPeripheralDataSize(DmaDataSize<sizeof(T)>::value);
		I::TableDmaStream::memoryIncrement(true);
		I::TableDmaStream::peripheralIncrement(false);

		I::TableDmaStream::circularMode(true);
		I::TableDmaStream::setDmaDirection(Dma::ddMemoryToPeripheral);
		I::TableDmaStream::setPeripheralAddress(I::loadRegister());
		I::TableDmaStream::setMemoryAddress0(reinterpret_cast<uint32_t>(getTable()));

		I::TableDmaStream::setTransferSize(I::tableSize);
		//I::TableDmaStream::enable(true);
		Tim<I::timer>::enable(true);
	}

	static void on(const bool val)
	{
//		I::TableDmaStream::setMemoryAddress0(reinterpret_cast<uint32_t>(getTable()));
//		dbg << val << Use::endl;
		I::TableDmaStream::setTransferSize(I::tableSize);
		I::TableDmaStream::enable(val);
		I::TableDma::clearAllFlags(I::dmaStream);
//		Tim<I::timer>::enable(val);
		I::on(val);

	}

};





#endif // GENERATOR_H
