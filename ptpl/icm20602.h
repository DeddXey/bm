#ifndef ICM20602_H
#define ICM20602_H

#include <cstdint>


struct XgOffsTcH {
	constexpr static uint8_t number = 4;
	constexpr static uint8_t offsTcH[]{ 0, 2 }; 	//<
	constexpr static uint8_t lp[]{ 2, 6 };			//<
};

struct XgOffsTcL {
	constexpr static uint8_t number = 5;
	constexpr static uint8_t offsTcL[]{ 0, 8 }; 	//<
};


struct YgOffsTcH {
	constexpr static uint8_t number = 7;
	constexpr static uint8_t offsTcH[]{ 0, 2 }; 	//<
	constexpr static uint8_t lp[]{ 2, 6 };			//<
};

struct YgOffsTcL {
	constexpr static uint8_t number = 8;
	constexpr static uint8_t offsTcL[]{ 0, 8 }; 	//<
};

struct ZgOffsTcH {
	constexpr static uint8_t number = 10;
	constexpr static uint8_t offsTcH[]{ 0, 2 }; 	//<
	constexpr static uint8_t lp[]{ 2, 6 };			//<
};

struct ZgOffsTcL {
	constexpr static uint8_t number = 11;
	constexpr static uint8_t offsTcL[]{ 0, 8 }; 	//<
};

struct SelfTestXAccel {
	constexpr static uint8_t number = 11;
};

#endif // ICM20602_H
