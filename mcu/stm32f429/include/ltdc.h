#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "rcc.h"
#include "utility.h"



enum class PixelFormat: uint8_t {

	argb8888  = 0b000,
	rgb888    = 0b001,
	rgb565    = 0b010,
	argb1555  = 0b011,
	argb4444  = 0b100,
	l8        = 0b101,
	al44      = 0b110,
	al88      = 0b111
};


template<int num>
struct layer_t;

template<>struct layer_t<1> {
	constexpr static uint32_t base = 0x40016884; //CHECK:
};

template<>struct layer_t<2> {
	constexpr static uint32_t base = 0x40016904; //CHECK:
};

struct Ltdc {

	struct SSCR {
		constexpr static uint8_t HSW[]{ 16, 10 }; 	//< Horizontal Synchronization Width (in units of pixel clock period)
		constexpr static uint8_t VSH[]{ 0, 11 }; 	//< Vertical Synchronization Height (in units of horizontal scan line)
	};

	struct BPCR {
		constexpr static uint8_t AHBP[]{ 16, 10 }; 	//< Accumulated Horizontal back porch (in units of pixel clock period)
		constexpr static uint8_t AVBP[]{ 0, 11 }; 	//< Accumulated Vertical back porch (in units of horizontal scan line)
	};

	struct AWCR {
		constexpr static uint8_t AAV[]{ 16, 10 }; 	//< AAV
		constexpr static uint8_t AAH[]{ 0, 11 }; 	//< Accumulated Active Height (in units of horizontal scan line)
	};

	struct TWCR {
		constexpr static uint8_t TOTALW[]{ 16, 10 }; 	//< Total Width (in units of pixel clock period)
		constexpr static uint8_t TOTALH[]{ 0, 11 }; 	//< Total Height (in units of horizontal scan line)
	};

	struct GCR {
		constexpr static uint8_t HSPOL[]{ 31, 1 }; 	//< Horizontal Synchronization Polarity
		constexpr static uint8_t VSPOL[]{ 30, 1 }; 	//< Vertical Synchronization Polarity
		constexpr static uint8_t DEPOL[]{ 29, 1 }; 	//< Data Enable Polarity
		constexpr static uint8_t PCPOL[]{ 28, 1 }; 	//< Pixel Clock Polarity
		constexpr static uint8_t DEN[]{ 16, 1 }; 	//< Dither Enable
		constexpr static uint8_t DRW[]{ 12, 3 }; 	//< Dither Red Width
		constexpr static uint8_t DGW[]{ 8, 3 }; 	//< Dither Green Width
		constexpr static uint8_t DBW[]{ 4, 3 }; 	//< Dither Blue Width
		constexpr static uint8_t LTDCEN[]{ 0, 1 }; 	//< LCD-TFT controller enable bit
	};

	struct SRCR {
		constexpr static uint8_t VBR[]{ 1, 1 }; 	//< Vertical Blanking Reload
		constexpr static uint8_t IMR[]{ 0, 1 }; 	//< Immediate Reload
	};

	struct BCCR {
		constexpr static uint8_t BCBLUE[]{ 0, 8 }; 	//< Background Color Red value
		constexpr static uint8_t BCGREEN[]{ 8, 8 }; 	//< Background Color Red value
		constexpr static uint8_t BCRED[]{ 16, 8 }; 	//< Background Color Red value
	};

	struct IER {
		constexpr static uint8_t RRIE[]{ 3, 1 }; 	//< Register Reload interrupt enable
		constexpr static uint8_t TERRIE[]{ 2, 1 }; 	//< Transfer Error Interrupt Enable
		constexpr static uint8_t FUIE[]{ 1, 1 }; 	//< FIFO Underrun Interrupt Enable
		constexpr static uint8_t LIE[]{ 0, 1 }; 	//< Line Interrupt Enable
	};

	struct ISR {
		constexpr static uint8_t RRIF[]{ 3, 1 }; 	//< Register Reload Interrupt Flag
		constexpr static uint8_t TERRIF[]{ 2, 1 }; 	//< Transfer Error interrupt flag
		constexpr static uint8_t FUIF[]{ 1, 1 }; 	//< FIFO Underrun Interrupt flag
		constexpr static uint8_t LIF[]{ 0, 1 }; 	//< Line Interrupt flag
	};

	struct ICR {
		constexpr static uint8_t CRRIF[]{ 3, 1 }; 	//< Clears Register Reload Interrupt Flag
		constexpr static uint8_t CTERRIF[]{ 2, 1 }; 	//< Clears the Transfer Error Interrupt Flag
		constexpr static uint8_t CFUIF[]{ 1, 1 }; 	//< Clears the FIFO Underrun Interrupt flag
		constexpr static uint8_t CLIF[]{ 0, 1 }; 	//< Clears the Line Interrupt Flag
	};

	struct LIPCR {
		constexpr static uint8_t LIPOS[]{ 0, 11 }; 	//< Line Interrupt Position
	};

	struct CPSR {
		constexpr static uint8_t CXPOS[]{ 16, 16 }; 	//< Current X Position
		constexpr static uint8_t CYPOS[]{ 0, 16 }; 	//< Current Y Position
	};

	struct CDSR {
		constexpr static uint8_t HSYNCS[]{ 3, 1 }; 	//< Horizontal Synchronization display Status
		constexpr static uint8_t VSYNCS[]{ 2, 1 }; 	//< Vertical Synchronization display Status
		constexpr static uint8_t HDES[]{ 1, 1 }; 	//< Horizontal Data Enable display Status
		constexpr static uint8_t VDES[]{ 0, 1 }; 	//< Vertical Data Enable display Status
	};


	struct Regs {
		uint32_t    SSCR;
		uint32_t    BPCR;
		uint32_t    AWCR;
		uint32_t    TWCR;
		uint32_t    GCR;
		uint32_t    RESERVED1[2];  /*!< Reserved, 0x1C-0x20                                                       */
		uint32_t    SRCR;
		uint32_t    RESERVED2[1];  /*!< Reserved, 0x28                                                            */
		uint32_t    BCCR;
		uint32_t    RESERVED3[1];  /*!< Reserved, 0x30                                                            */
		uint32_t    IERt;
		uint32_t    ISR;
		uint32_t    ICR;
		uint32_t    LIPCR;
		uint32_t    CPSR;
		uint32_t    CDSR;
	};

	constexpr static uint32_t base = 0x40016808;

	///---------------------------------------------------------------------
	///
	/// \brief Получение указателя на регистры
	/// \return указатель на регистры
	///
	INLINE static volatile Regs* rg()
	{
		return reinterpret_cast<volatile Regs* volatile>(base);
	}

	///---------------------------------------------------------------------
	///
	/// \brief Включение тактирования
	///
	INLINE static void clockEnable(const bool en)
	{
		Rcc::clockLtdc(en);
	}

	INLINE static void enable(const bool en)
	{
		::setRegister(rg()->GCR,
		                     GCR::LTDCEN, en);
	}
	INLINE static void setSynchronizationSize(const uint16_t horizontalSynchronizationWidth,
	                                          const uint16_t verticalSynchronizationHeight)
	{
		::setRegister(rg()->SSCR,
		                     SSCR::HSW, horizontalSynchronizationWidth,
		                     SSCR::VSH, verticalSynchronizationHeight);
	}

	INLINE static void setBackporch(const uint16_t accumulatedHorizontalBackPorch,
	                                const uint16_t accumulatedVerticalBackPorch)
	{
		::setRegister(rg()->BPCR,
		                     BPCR::AHBP, accumulatedHorizontalBackPorch,
		                     BPCR::AVBP, accumulatedVerticalBackPorch);
	}

	INLINE static void setActiveSize(const uint16_t accumulatedActiveWidth,
	                                 const uint16_t accumulatedActiveHeight)
	{
		::setRegister(rg()->AWCR,
		                     AWCR::AAV, accumulatedActiveWidth,
		                     AWCR::AAH, accumulatedActiveHeight);
	}

	INLINE static void setTotalSize(const uint16_t totalWidth,
	                                const uint16_t totalHeight)
	{
		::setRegister(rg()->TWCR,
		                     TWCR::TOTALW, totalWidth,
		                     TWCR::TOTALH, totalHeight);
	}

	INLINE static void setBgColor(const uint8_t red,
	                              const uint8_t green,
	                              const uint8_t blue)
	{
		::setRegister(rg()->BCCR,
		                     BCCR::BCRED, red,
		                     BCCR::BCGREEN, green,
		                     BCCR::BCBLUE, blue);
	}

	INLINE static void setShadowReloadCfg(const bool immediateReload,
	                                      const bool verticalBlankingReload)
	{
		::setRegister(rg()->SRCR,
		                     SRCR::VBR, verticalBlankingReload,
		                     SRCR::IMR, immediateReload);
	}
};

//##############################################################################
template<int num>
struct LtdcLayer {


	struct CR {
		constexpr static uint8_t CLUTEN[]{ 4, 1 }; 	//< Color Look-Up Table Enable
		constexpr static uint8_t COLKEN[]{ 1, 1 }; 	//< Color Keying Enable
		constexpr static uint8_t LEN[]{ 0, 1 }; 	//< Layer Enable
	};

	struct WHPCR {
		constexpr static uint8_t WHSPPOS[]{ 16, 12 }; 	//< Window Horizontal Stop Position
		constexpr static uint8_t WHSTPOS[]{ 0, 12 }; 	//< Window Horizontal Start Position
	};

	struct WVPCR {
		constexpr static uint8_t WVSPPOS[]{ 16, 11 }; 	//< Window Vertical Stop Position
		constexpr static uint8_t WVSTPOS[]{ 0, 11 }; 	//< Window Vertical Start Position
	};

	struct CKCR {
		constexpr static uint8_t CKRED[]{ 16, 8 }; 	//< Color Key Red value
		constexpr static uint8_t CKGREEN[]{ 8, 8 }; 	//< Color Key Green value
		constexpr static uint8_t CKBLUE[]{ 0, 8 }; 	//< Color Key Blue value
	};

	struct PFCR {
		constexpr static uint8_t PF[]{ 0, 3 }; 	//< Pixel Format
	};

	struct CACR {
		constexpr static uint8_t CONSTA[]{ 0, 8 }; 	//< Constant Alpha
	};

	struct DCCR {
		constexpr static uint8_t DCALPHA[]{ 24, 8 }; 	//< Default Color Alpha
		constexpr static uint8_t DCRED[]{ 16, 8 }; 	//< Default Color Red
		constexpr static uint8_t DCGREEN[]{ 8, 8 }; 	//< Default Color Green
		constexpr static uint8_t DCBLUE[]{ 0, 8 }; 	//< Default Color Blue
	};

	struct BFCR {
		constexpr static uint8_t BF1[]{ 8, 3 }; 	//< Blending Factor 1
		constexpr static uint8_t BF2[]{ 0, 3 }; 	//< Blending Factor 2
	};

	struct CFBAR {
		constexpr static uint8_t CFBADD[]{ 0, 32 }; 	//< Color Frame Buffer Start Address
	};

	struct CFBLR {
		constexpr static uint8_t CFBP[]{ 16, 13 }; 	//< Color Frame Buffer Pitch in bytes
		constexpr static uint8_t CFBLL[]{ 0, 13 }; 	//< Color Frame Buffer Line Length
	};

	struct CFBLNR {
		constexpr static uint8_t CFBLNBR[]{ 0, 11 }; 	//< Frame Buffer Line Number
	};

	struct CLUTWR {
		constexpr static uint8_t CLUTADD[]{ 24, 8 }; 	//< CLUT Address
		constexpr static uint8_t RED[]{ 16, 8 }; 	//< Red value
		constexpr static uint8_t GREEN[]{ 8, 8 }; 	//< Green value
		constexpr static uint8_t BLUE[]{ 0, 8 }; 	//< Blue value
	};

	struct Regs {
		uint32_t    CR;
		uint32_t    WHPCR;
		uint32_t    WVPCR;
		uint32_t    CKCR;
		uint32_t    PFCR;
		uint32_t    CACR;
		uint32_t    DCCR;
		uint32_t    BFCR;
		uint32_t    RESERVED0[2];  /*!< Reserved                                                                           */
		uint32_t    CFBAR;
		uint32_t    CFBLR;
		uint32_t    CFBLNR;
		uint32_t    RESERVED1[3];  /*!< Reserved                                                                           */
		uint32_t    CLUTWR;
	};

#ifdef DEBUG
	volatile Regs* const debug = reinterpret_cast<Regs*>(layer_t<num>::LAYER_BASE);
#endif

	///---------------------------------------------------------------------
	///
	/// \brief Получение указателя на регистры
	/// \return указатель на регистры
	///
	INLINE static volatile Regs* rg()
	{
		return reinterpret_cast<volatile Regs* volatile>(layer_t<num>::base);
	}

	INLINE static void setPixelFormat(const PixelFormat pixelFormat)
	{
		::setRegister(rg()->PFCR,
		                     PFCR::PF, static_cast<uint8_t>(pixelFormat));
	}

	INLINE static void setFramebufferAddress(const uint32_t address)
	{
		rg()->CFBAR = address;
	}

	INLINE static void setFramebufferLength(const uint16_t lineLength,
	                                        const uint16_t pitch)
	{
		::setRegister(rg()->CFBLR,
		                     CFBLR::CFBP, pitch,
		                     CFBLR::CFBLL, lineLength);
	}

	INLINE static void setFramebufferLineNumber(const uint16_t lineNumber)
	{
		::setRegister(rg()->CFBLNR,
		                     CFBLNR::CFBLNBR, lineNumber);
	}

	INLINE static void setWindowHorizontalPosition(const uint16_t startPosition,
	                                               const uint16_t stopPosition)
	{
		rg()->WHPCR = startPosition |
		              (stopPosition << 16);

	}

	INLINE static void setWindowVerticalPosition(const uint16_t startPosition,
	                                             const uint16_t stopPosition)
	{
		::setRegister(rg()->WVPCR,
		                     WVPCR::WVSPPOS, stopPosition,
		                     WVPCR::WVSTPOS, startPosition);
	}

	INLINE static void setColor(const uint8_t red,
	                            const uint8_t green,
	                            const uint8_t blue,
	                            const uint8_t alpha = 0)
	{
		::setRegister(rg()->DCCR,
		                     DCCR::DCRED, red,
		                     DCCR::DCGREEN, green,
		                     DCCR::DCBLUE, blue,
		                     DCCR::DCALPHA, alpha);
	}

	INLINE static void enable(const bool en)
	{
		::setRegister(rg()->CR,
		                     CR::LEN, en);
	}


};


#endif // LCD_H
