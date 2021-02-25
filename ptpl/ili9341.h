#ifndef ILI9341_H
#define ILI9341_H

#include <stdint.h>

#include "gpio.h"
#include "utility.h"
#include <utility>

template<typename I>
class Ili9341
{
    enum Registers {
        rgSleepOut          =  0x11,   /* Sleep out register */
        rgGamma             =  0x26,   /* Gamma register */
        rgDisplayOff        =  0x28,   /* Display off register */
        rgDisplayOn         =  0x29,   /* Display on register */
        rgColumnAddr        =  0x2A,   /* Colomn address register */
        rgPageAddr          =  0x2B,   /* Page address register */
        rgGram              =  0x2C,   /* GRAM register */
        rgMac               =  0x36,   /* Memory Access Control register*/
        rgPixelFormat       =  0x3A,   /* Pixel Format register */
        rgWdb               =  0x51,   /* Write Brightness Display register */
        rgWcd               =  0x53,   /* Write Control Display register*/
        rgRgbInterface      =  0xB0,   /* RGB Interface Signal Control */
        rgFrc               =  0xB1,   /* Frame Rate Control register */
        rgBpc               =  0xB5,   /* Blanking Porch Control register*/
        rgDfc               =  0xB6,   /* Display Function Control register*/
        rgPower1            =  0xC0,   /* Power Control 1 register */
        rgPower2            =  0xC1,   /* Power Control 2 register */
        rgVcom1             =  0xC5,   /* VCOM Control 1 register */
        rgVcom2             =  0xC7,   /* VCOM Control 2 register */
        rgPowera            =  0xCB,   /* Power control A register */
        rgPowerb            =  0xCF,   /* Power control B register */
        rgPgamma            =  0xE0,   /* Positive Gamma Correction register*/
        rgNgamma            =  0xE1,   /* Negative Gamma Correction register*/
        rgDtca              =  0xE8,   /* Driver timing control A */
        rgDtcb              =  0xEA,   /* Driver timing control B */
        rgPowerSeq          =  0xED,   /* Power on sequence register */
        rg3gammaEn          =  0xF2,   /* 3 Gamma enable register */
        rgInterface         =  0xF6,   /* Interface control register */
        rgPrc               =  0xF7,   /* Pump ratio control register */
    };

	enum class Cd {
		none = 0,
		cmd = 1,
		data = 2
	};

	static std::pair<Cd, uint8_t> getInitSequence1(uint8_t index)
	{
		static std::pair<Cd, uint8_t>  seq[] {
			{ Cd::cmd, 0xCA },
			{ Cd::data, 0xC3 },
			{ Cd::data, 0x08 },
			{ Cd::data, 0x50 },
			{ Cd::cmd, rgPowerb },
			{ Cd::data, 0x00 },
			{ Cd::data, 0xC1 },
			{ Cd::data, 0x30 },
			{ Cd::cmd, rgPowerSeq },
			{ Cd::data, 0x64 },
			{ Cd::data, 0x03 },
			{ Cd::data, 0x12 },
			{ Cd::data, 0x81 },
			{ Cd::cmd, rgDtca },
			{ Cd::data, 0x85 },
			{ Cd::data, 0x00 },
			{ Cd::data, 0x78 },
			{ Cd::cmd, rgPowera },
			{ Cd::data, 0x39 },
			{ Cd::data, 0x2C },
			{ Cd::data, 0x00 },
			{ Cd::data, 0x34 },
			{ Cd::data, 0x02 },
			{ Cd::cmd, rgPrc },
			{ Cd::data, 0x20 },
			{ Cd::cmd, rgDtcb },
			{ Cd::data, 0x00 },
			{ Cd::data, 0x00 },
			{ Cd::cmd, rgFrc },
			{ Cd::data, 0x00 },
			{ Cd::data, 0x1B },
			{ Cd::cmd, rgDfc },
			{ Cd::data, 0x0A },
			{ Cd::data, 0xA2 },
			{ Cd::cmd, rgPower1 },
			{ Cd::data, 0x10 },
			{ Cd::cmd, rgPower2 },
			{ Cd::data, 0x10 },
			{ Cd::cmd, rgVcom1 },
			{ Cd::data, 0x45 },
			{ Cd::data, 0x15 },
			{ Cd::cmd, rgVcom2 },
			{ Cd::data, 0x90 },
			{ Cd::cmd, rgMac },
			{ Cd::data, 0xC8 },
			{ Cd::cmd, rg3gammaEn },
			{ Cd::data, 0x00 },
			{ Cd::cmd, rgRgbInterface },
			{ Cd::data, 0xC2 },
			{ Cd::cmd, rgDfc },
			{ Cd::data, 0x0A },
			{ Cd::data, 0xA7 },
			{ Cd::data, 0x27 },
			{ Cd::data, 0x04 },
			{ Cd::cmd, rgColumnAddr },
			{ Cd::data, 0x00 },
			{ Cd::data, 0x00 },
			{ Cd::data, 0x00 },
			{ Cd::data, 0xEF },
			{ Cd::cmd, rgPageAddr },
			{ Cd::data, 0x00 },
			{ Cd::data, 0x00 },
			{ Cd::data, 0x01 },
			{ Cd::data, 0x3F },
			{ Cd::cmd, rgInterface },
			{ Cd::data, 0x01 },
			{ Cd::data, 0x00 },
			{ Cd::data, 0x06 },
			{ Cd::cmd, rgGram },
			{ Cd::none, 0 }
		};
		return seq[index];
	}

	static std::pair<Cd, uint8_t> getInitSequence2(uint8_t index)
	{
		static std::pair<Cd, uint8_t> seq[] {
			{ Cd::cmd, rgGamma },
			{ Cd::data, 0x01 },
			{ Cd::cmd, rgPgamma },
			{ Cd::data, 0x0F },
			{ Cd::data, 0x29 },
			{ Cd::data, 0x24 },
			{ Cd::data, 0x0C },
			{ Cd::data, 0x0E },
			{ Cd::data, 0x09 },
			{ Cd::data, 0x4E },
			{ Cd::data, 0x78 },
			{ Cd::data, 0x3C },
			{ Cd::data, 0x09 },
			{ Cd::data, 0x13 },
			{ Cd::data, 0x05 },
			{ Cd::data, 0x17 },
			{ Cd::data, 0x11 },
			{ Cd::data, 0x00 },
			{ Cd::cmd, rgNgamma },
			{ Cd::data, 0x00 },
			{ Cd::data, 0x16 },
			{ Cd::data, 0x1B },
			{ Cd::data, 0x04 },
			{ Cd::data, 0x11 },
			{ Cd::data, 0x07 },
			{ Cd::data, 0x31 },
			{ Cd::data, 0x33 },
			{ Cd::data, 0x42 },
			{ Cd::data, 0x05 },
			{ Cd::data, 0x0C },
			{ Cd::data, 0x0A },
			{ Cd::data, 0x28 },
			{ Cd::data, 0x2F },
			{ Cd::data, 0x0F },
			{ Cd::cmd, rgSleepOut },
			{ Cd::none, 0 }
		};

		return seq[index];
	}

	template<typename T>
	static void process(T fn)
	{
		uint16_t idx = 0;
		do {
			auto pr = fn(idx);
			switch(pr.first) {
			case Cd::cmd:
				I::cmd(pr.second);
				break;

			case Cd::data:
				I::data(pr.second);
				break;
			default:
				return;
			}
			++idx;
		}while(1);
	}


public:
    static void init()
    {
		I::preInit();

		process(getInitSequence1);

		simpleDelay(2000000);

		process(getInitSequence2);

		simpleDelay(2000000);
		I::cmd(rgDisplayOn);
		/* GRAM start writing */
		I::cmd(rgGram);
    }
};

#endif // ILI9341_H
