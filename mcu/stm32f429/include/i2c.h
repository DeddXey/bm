#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#include "bufferdescriptor.h"
#include "dbg.h_"
#include "nvic.h"
#include "utility.h"

template<int num> struct i2c_t;

template<> struct i2c_t<1>
{
	constexpr static uint32_t I2C_BASE = 0x40005400;
	static void INLINE clockEnable(const bool en) { Rcc::clockI2c1(en); }
	constexpr static Nvic::IrqType EV_IRQn                = Nvic::itI2c1Ev;     ///< I2C1 event global interrupt
	constexpr static Nvic::IrqType ER_IRQn                = Nvic::itI2c1Er;     ///< I2C1 error global interrupt
};

template<> struct i2c_t<2>
{
	constexpr static uint32_t I2C_BASE = 0x40005800;
	static void INLINE clockEnable(const bool en) { Rcc::clockI2c2(en); }
	constexpr static Nvic::IrqType EV_IRQn                = Nvic::itI2c2Ev;     ///< I2C1 event global interrupt
	constexpr static Nvic::IrqType ER_IRQn                = Nvic::itI2c2Er;     ///< I2C1 error global interrupt
};

template<> struct i2c_t<3>
{
	constexpr static uint32_t I2C_BASE = 0x40005C00;
	static void INLINE clockEnable(const bool en) { Rcc::clockI2c3(en); }
	constexpr static Nvic::IrqType EV_IRQn                = Nvic::itI2c3Ev;     ///< I2C1 event global interrupt
	constexpr static Nvic::IrqType ER_IRQn                = Nvic::itI2c3Er;     ///< I2C1 error global interrupt
};





template<int num>
struct I2c {

	struct Flags {
		uint8_t read:1;
		uint8_t slave:1;
		uint8_t ready:1;
		uint8_t error:1;

	};



	struct I2cHandler {
		uint8_t     devAddress;
		uint8_t     regAddress;
		Flags       flags;
		uint8_t     *writeBuffer;
		uint16_t    bytesToWrite;
		uint8_t     *readBuffer;
		uint16_t    bytesToRead;

		uint16_t    writeIndex;
		uint16_t    readIndex;

	};



	constexpr static uint8_t flagRead = 0x01;
	constexpr static uint8_t flagSlave = 0x02;

	constexpr static uint8_t flagReady = 0x10;
	constexpr static uint8_t flagError = 0x20;
	//    constexpr static uint8_t flagDebug = 0x40;


	struct CR1_t {
		uint32_t  PE:1;
		uint32_t  SMBUS:1;
		uint32_t  RESERVED1:1;
		uint32_t  SMBTYPE:1;
		uint32_t  ENARP:1;
		uint32_t  ENPEC:1;
		uint32_t  ENGC:1;
		uint32_t  NOSTRETCH:1;
		uint32_t  START:1;
		uint32_t  STOP:1;
		uint32_t  ACK:1;
		uint32_t  POS:1;
		uint32_t  PEC:1;
		uint32_t  ALERT:1;
		uint32_t  RESERVED2:1;
		uint32_t  SWRST:1;
	};

	struct CR2_t {
		uint32_t  FREQ:6;
		uint32_t  RESERVED1:2;
		uint32_t  ITERREN:1;
		uint32_t  ITEVEN:1;
		uint32_t  ITBUFEN:1;
		uint32_t  DMAEN:1;
		uint32_t  LAST:1;

	};

	struct OAR1_t {
		uint32_t  ADD0:1;
		uint32_t  ADD:7;
		uint32_t  ADD98:2;
		uint32_t  RESERVED1:5;
		uint32_t  ADDMODE:1;

	};

	struct OAR2_t {
		uint32_t  ENDUAL:1;
		uint32_t  ADD2:7;
	};

	struct DR_t {
		uint32_t  DR:8;
	};

	union SR1_u {
		uint32_t whole;
		struct {
			uint32_t  SB:1;
			uint32_t  ADDR:1;
			uint32_t  BTF:1;
			uint32_t  ADD10:1;
			uint32_t  STOPF:1;
			uint32_t  RESERVED1:1;
			uint32_t  RxNE:1;
			uint32_t  TxE:1;
			uint32_t  BERR:1;
			uint32_t  ARLO:1;
			uint32_t  AF:1;
			uint32_t  OVR:1;
			uint32_t  PECERR:1;
			uint32_t  RESERVED2:1;
			uint32_t  TIMEOUT:1;
			uint32_t  SMBALERT:1;
		} b;
	};

	union SR2_u {
		uint32_t whole;
		struct {
			uint32_t  MSL:1;
			uint32_t  BUSY:1;
			uint32_t  TRA:1;
			uint32_t  RESERVED1:1;
			uint32_t  GENCALL:1;
			uint32_t  SMBDEFAULT:1;
			uint32_t  SMBHOST:1;
			uint32_t  DUALF:1;
		} b;
	};

	struct CCR_t {
		uint32_t  CCR:12;
		uint32_t  RESERVED1:2;
		uint32_t  DUTY:1;
		uint32_t  FS:1;
	};

	struct TRISE_t {
		uint32_t  TRISE:6;

	};

	struct FLTR_t {
		uint32_t  DNF:4;
		uint32_t  ANOFF:1;
	};



	struct Regs {
		CR1_t     CR1;
		CR2_t     CR2;
		OAR1_t    OAR1;
		OAR2_t    OAR2;
		DR_t      DR;
		SR1_u     SR1;
		SR2_u     SR2;
		CCR_t     CCR;
		TRISE_t   TRISE;
		FLTR_t    FLTR;
	};



#ifdef DEBUG
	volatile Regs* const debug = reinterpret_cast<Regs*>(i2c_t<num>::I2C_BASE);
#endif
	//    constexpr static volatile Regs* const i2c = /*reinterpret_cast<Regs*>*/(Regs*)(I2C_BASE);


	///---------------------------------------------------------------------
	///
	/// \brief Включение тактирования
	///
	INLINE static void clockEnable(const bool en)
	{
		i2c_t<num>::clockEnable(en);
	}


	///---------------------------------------------------------------------
	///
	/// \brief Получение указателя на регистры
	/// \return указатель на регистры
	///
	INLINE static volatile Regs* rg()
	{
		return reinterpret_cast<volatile Regs* volatile >(i2c_t<num>::I2C_BASE);
	}


	///
	/// \brief Получение дескриптора устройства
	/// \return ссылка на дескриптор
	///
	INLINE static I2cHandler& getHandler()
	{
		static I2cHandler handler;
		return handler;
	}


	static void setStop(bool val)
	{
		rg()->CR1.STOP = val;
		//		dbg << Fg::green << "Stop" << val << Use::endl << Attr::reset;
	}

	static void setStart()
	{
		rg()->CR1.START = 1;
		//		dbg << Fg::green << "Start\n"<< Attr::reset;

	}
	INLINE static void setAck(bool val) { rg()->CR1.ACK = val; }
	INLINE static void setItbufen(bool val) { rg()->CR2.ITBUFEN = val; }
	INLINE static void setItEvEnable(bool val) { rg()->CR2.ITEVEN = val; }
	INLINE static void setItErEnable(bool val) { rg()->CR2.ITERREN = val; }
	INLINE static void setFastMode(bool val) { rg()->CCR.FS = val; }
	INLINE static void setFreq(uint8_t freq) {rg()->CR2.FREQ = freq; }
	INLINE static void setCcr(uint16_t ccr) {rg()->CCR.CCR = ccr; }
	INLINE static void setTrise(uint8_t value) {rg()->TRISE.TRISE = value; }


	INLINE static void enable() { rg()->CR1.PE = 1; }
	INLINE static void disable() { rg()->CR1.PE = 0; }
	static uint8_t readDr()
	{
		uint8_t dr = rg()->DR.DR;
		//		dbg << Fg::green << "Read DR: " << Use::w2 << dr << Use::endl << Attr::reset;
		return dr;
	}
	static void  writeDr(uint8_t val)
	{
		rg()->DR.DR = val;
		//		dbg << Fg::green << "Write DR: " << Use::w2 << val << Use::endl << Attr::reset;
	}
	INLINE static bool isBusy() { return (rg()->SR2.b.BUSY); }

	INLINE static bool isWriteComplete() { return (getHandler().bytesToWrite == getHandler().writeIndex); }
	INLINE static bool isReadComplete() { return (getHandler().bytesToRead == getHandler().readIndex); }

	INLINE static bool isRequestComplete() { return (getHandler().flags.ready); }
	INLINE static bool isRequestError() { return (getHandler().flags.error); }




	///-----------------------------------------------------------------------------
	INLINE static bool request(const uint8_t devAddr,
	                           const uint8_t *writeBuffer,
	                           const uint16_t bytesToWrite,
	                           uint8_t *readBuffer,
	                           const uint16_t bytesToRead)
	{
		getHandler().devAddress = devAddr;
		getHandler().writeBuffer = const_cast<uint8_t*>(writeBuffer);
		getHandler().bytesToWrite = bytesToWrite;
		getHandler().readBuffer = readBuffer;
		getHandler().bytesToRead = bytesToRead;
		getHandler().readIndex = 0;
		getHandler().writeIndex = 0;

		getHandler().flags.ready = 0;
		getHandler().flags.error = 0;

		setStop(false);
		uint32_t counter = 0xffffff;

		while (counter) {

			--counter;
			if(!(isBusy()))    {

				//            setCcr(0xd2);
				setFreq(42); //TODO
				setCcr(50);
				setFastMode(true);
				setTrise(0x2b);
				// setTrise(0x2);
				enable();
				setAck(true);
				setItEvEnable(true);
				setItErEnable(true);


				setStart();

				return true;
			}
		}
		return false;
	}

	INLINE static bool requestBlock(const uint8_t devAddr,
	                                const uint8_t *writeBuffer,
	                                const uint16_t bytesToWrite,
	                                uint8_t *readBuffer,
	                                const uint16_t bytesToRead)
	{

		if (!request(devAddr, writeBuffer, bytesToWrite, readBuffer, bytesToRead)){
			dbg<< "requestBlockError 1\n";
			return false;
		}


		while (!isRequestComplete()) {::simpleDelay(200);};

		if (isRequestError()) {
			dbg<< "requestBlockError 2\n";
			return false;
		}

//		BufferDescriptor bd{readBuffer, bytesToRead};
//		bd.print(dbg);

		return true;
	}


#define I2C_DEBUG 0

	///-----------------------------------------------------------------------------
	INLINE static void errorHandler()
	{
		SR1_u  status1;
		SR1_u  status2;
		(void)status2;
		status1.whole = rg()->SR1.whole;
		status2.whole = rg()->SR2.whole;


		dbg << Fg::red << "I2C Error\n";
		dbg << Use::hex << status1.whole << status2.whole << Use::endl;

		if (status1.b.OVR) {
			dbg << Fg::red << "OVR\n" << Attr::reset;
		}
		if (status1.b.AF) {
			dbg << Fg::red << "NOASK\n" << Attr::reset;
		}
		if (status1.b.ARLO) {
			dbg << Fg::red << "ARLO\n" << Attr::reset;
		}
		if (status1.b.BERR) {
			dbg << Fg::red << "BERR\n" << Attr::reset;
		}


		getHandler().flags.error = 1;
		rg()->SR1.whole = 0;
		disable();
	}

	///-----------------------------------------------------------------------------
	INLINE static void eventHandler()
	{
		SR1_u status1;
		status1.whole = rg()->SR1.whole;


		//-------------------------------------------------------------
		// Ev5
		if (status1.b.SB) {

			setItbufen(false);

			if (!isWriteComplete()) {
				writeDr(getHandler().devAddress);
			}
			else {

				if ((getHandler().bytesToRead == 2) ) {
					rg()->CR1.POS = 1;
				}
				writeDr(getHandler().devAddress | 1);

			}
			return;
		}

		//-------------------------------------------------------------
		// Ev6
		volatile SR2_u status2;
		if (status1.b.ADDR) {
			// Write data
			if (!isWriteComplete()) {
				status2.whole = rg()->SR2.whole;
				status2;
				writeDr(getHandler().writeBuffer[getHandler().writeIndex++]);

				if (isWriteComplete()) {

					if (isReadComplete()) {
						setStop(true);
						getHandler().flags.ready = 1;
					}
					else {
						setStart();
					}
				}
			}
			else {

				//Read
				switch(getHandler().bytesToRead) {

				case 1:
					setAck(false);
					status2.whole = rg()->SR2.whole;
					setStop(true);
					setItbufen(true);
					break;

				case 2:
					status2.whole = rg()->SR2.whole;
					setAck(false);
					break;

				default:
					status2.whole = rg()->SR2.whole;
				}

			}
			return;
		}

		//TODO: add slave

		//-------------------------------------------------------------
		// Ev7
		if (status1.b.RxNE) {

			switch (getHandler().bytesToRead - getHandler().readIndex) {
			default:
				if (status1.b.BTF){
					getHandler().readBuffer[getHandler().readIndex++] = rg()->DR.DR;
				}
				break;
			case 3:
				if (status1.b.BTF){
					setAck(false);
					getHandler().readBuffer[getHandler().readIndex++] = rg()->DR.DR;
				}
				break;

			case 2:
				if (status1.b.BTF){
					setStop(true);
					setAck(false);
					getHandler().readBuffer[getHandler().readIndex++] = rg()->DR.DR;
					getHandler().readBuffer[getHandler().readIndex++] = rg()->DR.DR;
					getHandler().flags.ready = 1;
					//disable();
				}
				break;
			case 1:
				getHandler().readBuffer[getHandler().readIndex++] = rg()->DR.DR;
				//setStop();
				getHandler().flags.ready = 1;
				//disable();
				break;
			}
			//return;
		}

		//-------------------------------------------------------------
		//Ev8 Tx is empty
		if (status1.b.TxE) {

			if (isWriteComplete())  {

				if (isReadComplete()) {
					setStop(true);
					getHandler().flags.ready = 1;
				}
				else {
					setStart();
				}
			}
			else {
				writeDr(getHandler().writeBuffer[getHandler().writeIndex++]);
			}

			return;
		}
	}

	INLINE static Nvic::IrqType getIrqEvN()
	{
		return i2c_t<num>::EV_IRQn;
	}

	INLINE static Nvic::IrqType getIrqErN()
	{
		return i2c_t<num>::ER_IRQn;
	}
};





#endif // I2C_H
