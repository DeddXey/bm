#ifndef DMA2D_H
#define DMA2D_H


#include "rcc.h"
#include "ltdc.h"

struct Dma2D {
  
    enum Mode {
        mMemToMem           = 0b00,
        mMemToMemPfc        = 0b01,
        mMemToMemBlending   = 0b10,
        mRegisterToMem      = 0b11

    };




//    struct CR_t {
//        uint32_t    START:1;
//        uint32_t    SUSP:1;
//        uint32_t    ABORT:1;
//        uint32_t    RESERVED:5;
//        uint32_t    TEIE:1;
//        uint32_t    TCIE:1;
//        uint32_t    TWIE:1;
//        uint32_t    CAEIE:1;
//        uint32_t    CTCIE:1;
//        uint32_t    CEIE:1;
//        uint32_t    RESERVED2:2;
//        uint32_t    MODE:2;
//    };

//    struct ISR_t {
//        uint32_t    TEIF:1;
//        uint32_t    TCIF:1;
//        uint32_t    TWIF:1;
//        uint32_t    CAEIF:1;
//        uint32_t    CTCIF:1;
//        uint32_t    CEIF:1;
//    };

//    struct IFCR_t {
//        uint32_t    CTEIF:1;
//        uint32_t    CTCIF:1;
//        uint32_t    CTWIF:1;
//        uint32_t    CCAEIF:1;
//        uint32_t    CCTCIF:1;
//        uint32_t    CCEIF:1;
//    };

//    struct GOR_t {
//        uint32_t    LO:14;
//    };



//    struct GPFCCR_t {
//        uint32_t    CM:4;
//        uint32_t    CCM:1;
//        uint32_t    START:1;
//        uint32_t    RESERVED1:2;
//        uint32_t    CS:8;
//        uint32_t    AM:2;
//        uint32_t    RESERVED2:6;
//        uint32_t    ALPHA:8;
//    };

//    struct GCOLR_t {
//        uint32_t    BLUE:8;
//        uint32_t    GREEN:8;
//        uint32_t    RED:8;
//    };

//    struct OPFCCR_t {
//        uint32_t    CM:3;
//    };
    
//    struct NLR_t {
//        uint32_t    NL:16;
//        uint32_t    PL:14;
//    };

//    struct LWR_t {
//        uint32_t    LW:16;
//    };
    
//    struct AMTCR_t {
//        uint32_t    EN:1;
//        uint32_t    RESERVED1:7;
//        uint32_t    DT:8;
//    };

	struct CR {
		constexpr static uint8_t MODE[]{ 16, 2 }; 	//< DMA2D mode
		constexpr static uint8_t CEIE[]{ 13, 1 }; 	//< Configuration Error Interrupt Enable
		constexpr static uint8_t CTCIE[]{ 12, 1 }; 	//< CLUT transfer complete interrupt enable
		constexpr static uint8_t CAEIE[]{ 11, 1 }; 	//< CLUT access error interrupt enable
		constexpr static uint8_t TWIE[]{ 10, 1 }; 	//< Transfer watermark interrupt enable
		constexpr static uint8_t TCIE[]{ 9, 1 }; 	//< Transfer complete interrupt enable
		constexpr static uint8_t TEIE[]{ 8, 1 }; 	//< Transfer error interrupt enable
		constexpr static uint8_t ABORT[]{ 2, 1 }; 	//< Abort
		constexpr static uint8_t SUSP[]{ 1, 1 }; 	//< Suspend
		constexpr static uint8_t START[]{ 0, 1 }; 	//< Start
	};

	struct ISR {
		constexpr static uint8_t CEIF[]{ 5, 1 }; 	//< Configuration error interrupt flag
		constexpr static uint8_t CTCIF[]{ 4, 1 }; 	//< CLUT transfer complete interrupt flag
		constexpr static uint8_t CAEIF[]{ 3, 1 }; 	//< CLUT access error interrupt flag
		constexpr static uint8_t TWIF[]{ 2, 1 }; 	//< Transfer watermark interrupt flag
		constexpr static uint8_t TCIF[]{ 1, 1 }; 	//< Transfer complete interrupt flag
		constexpr static uint8_t TEIF[]{ 0, 1 }; 	//< Transfer error interrupt flag
	};

	struct IFCR {
		constexpr static uint8_t CCEIF[]{ 5, 1 }; 	//< Clear configuration error interrupt flag
		constexpr static uint8_t CCTCIF[]{ 4, 1 }; 	//< Clear CLUT transfer complete interrupt flag
		constexpr static uint8_t CAECIF[]{ 3, 1 }; 	//< Clear CLUT access error interrupt flag
		constexpr static uint8_t CTWIF[]{ 2, 1 }; 	//< Clear transfer watermark interrupt flag
		constexpr static uint8_t CTCIF[]{ 1, 1 }; 	//< Clear transfer complete interrupt flag
		constexpr static uint8_t CTEIF[]{ 0, 1 }; 	//< Clear Transfer error interrupt flag
	};

	struct FGMAR {
		constexpr static uint8_t MA[]{ 0, 32 }; 	//< Memory address
	};

	struct FGOR {
		constexpr static uint8_t LO[]{ 0, 14 }; 	//< Line offset
	};

	struct BGMAR {
		constexpr static uint8_t MA[]{ 0, 32 }; 	//< Memory address
	};

	struct BGOR {
		constexpr static uint8_t LO[]{ 0, 14 }; 	//< Line offset
	};

	struct FGPFCCR {
		constexpr static uint8_t ALPHA[]{ 24, 8 }; 	//< Alpha value
		constexpr static uint8_t AM[]{ 16, 2 }; 	//< Alpha mode
		constexpr static uint8_t CS[]{ 8, 8 }; 	//< CLUT size
		constexpr static uint8_t START[]{ 5, 1 }; 	//< Start
		constexpr static uint8_t CCM[]{ 4, 1 }; 	//< CLUT color mode
		constexpr static uint8_t CM[]{ 0, 4 }; 	//< Color mode
	};

	struct FGCOLR {
		constexpr static uint8_t RED[]{ 16, 8 }; 	//< Red Value
		constexpr static uint8_t GREEN[]{ 8, 8 }; 	//< Green Value
		constexpr static uint8_t BLUE[]{ 0, 8 }; 	//< Blue Value
	};

	struct BGPFCCR {
		constexpr static uint8_t ALPHA[]{ 24, 8 }; 	//< Alpha value
		constexpr static uint8_t AM[]{ 16, 2 }; 	//< Alpha mode
		constexpr static uint8_t CS[]{ 8, 8 }; 	//< CLUT size
		constexpr static uint8_t START[]{ 5, 1 }; 	//< Start
		constexpr static uint8_t CCM[]{ 4, 1 }; 	//< CLUT Color mode
		constexpr static uint8_t CM[]{ 0, 4 }; 	//< Color mode
	};

	struct BGCOLR {
		constexpr static uint8_t RED[]{ 16, 8 }; 	//< Red Value
		constexpr static uint8_t GREEN[]{ 8, 8 }; 	//< Green Value
		constexpr static uint8_t BLUE[]{ 0, 8 }; 	//< Blue Value
	};

	struct FGCMAR {
		constexpr static uint8_t MA[]{ 0, 32 }; 	//< Memory Address
	};

	struct BGCMAR {
		constexpr static uint8_t MA[]{ 0, 32 }; 	//< Memory address
	};

	struct OPFCCR {
		constexpr static uint8_t CM[]{ 0, 3 }; 	//< Color mode
	};

	struct OCOLR {
		constexpr static uint8_t APLHA[]{ 24, 8 }; 	//< Alpha Channel Value
		constexpr static uint8_t RED[]{ 16, 8 }; 	//< Red Value
		constexpr static uint8_t GREEN[]{ 8, 8 }; 	//< Green Value
		constexpr static uint8_t BLUE[]{ 0, 8 }; 	//< Blue Value
	};

	struct OMAR {
		constexpr static uint8_t MA[]{ 0, 32 }; 	//< Memory Address
	};

	struct OOR {
		constexpr static uint8_t LO[]{ 0, 14 }; 	//< Line Offset
	};

	struct NLR {
		constexpr static uint8_t PL[]{ 16, 14 }; 	//< Pixel per lines
		constexpr static uint8_t NL[]{ 0, 16 }; 	//< Number of lines
	};

	struct LWR {
		constexpr static uint8_t LW[]{ 0, 16 }; 	//< Line watermark
	};

	struct AMTCR {
		constexpr static uint8_t DT[]{ 8, 8 }; 	//< Dead Time
		constexpr static uint8_t EN[]{ 0, 1 }; 	//< Enable
	};

	struct FGCLUT {
		constexpr static uint8_t APLHA[]{ 24, 8 }; 	//< APLHA
		constexpr static uint8_t RED[]{ 16, 8 }; 	//< RED
		constexpr static uint8_t GREEN[]{ 8, 8 }; 	//< GREEN
		constexpr static uint8_t BLUE[]{ 0, 8 }; 	//< BLUE
	};

	struct BGCLUT {
		constexpr static uint8_t APLHA[]{ 24, 8 }; 	//< APLHA
		constexpr static uint8_t RED[]{ 16, 8 }; 	//< RED
		constexpr static uint8_t GREEN[]{ 8, 8 }; 	//< GREEN
		constexpr static uint8_t BLUE[]{ 0, 8 }; 	//< BLUE
	};



    struct Regs {
		uint32_t    CR;
		uint32_t    ISR;
		uint32_t    IFCR;
        uint32_t    FGMAR;
		uint32_t    FGOR;
        uint32_t    BGMAR;
		uint32_t    BGOR;
		uint32_t    FGPFCCR;
		uint32_t    FGCOLR;
		uint32_t    BGPFCCR;
		uint32_t    BGCOLR;
        uint32_t    FGCMAR;
        uint32_t    BGCMAR;
		uint32_t    OPFCCR;
        uint32_t    OCOLR;
        uint32_t    OMAR;
		uint32_t    OOR;
		uint32_t    NLR;
		uint32_t    LWR;
		uint32_t    AMTCR;
        uint32_t    RESERVED[236]; /*!< Reserved, 0x50-0x3FF */
        uint32_t    FGCLUT[256];   /*!< DMA2D Foreground CLUT,                          Address offset:400-7FF */
        uint32_t    BGCLUT[256];   /*!< DMA2D Background CLUT,                          Address offset:800-BFF */

    };


	constexpr static uint32_t base = 0x4002B000;
    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    INLINE static volatile Regs* rg()
    {
		return reinterpret_cast<volatile Regs * volatile>(base);
    }

    ///---------------------------------------------------------------------
    ///
    /// \brief Включение тактирования
    ///
    INLINE static void clockEnable(const bool en)
    {
        Rcc::clockDma2d(en);
    }

	INLINE static void start ()
	{
		::setRegister(rg()->CR,
		                     CR::START, 1);
	}

	INLINE static void setMode (Dma2D::Mode mode)
	{
		::setRegister(rg()->CR,
		                     CR::MODE, mode);
	}

	INLINE static void setPfcColorMode (PixelFormat fmt)
	{
		::setRegister(rg()->OPFCCR,
		                     OPFCCR::CM, static_cast<uint8_t>(fmt));
	}

	INLINE static void setForegroundColorMode (PixelFormat fmt)
	{
		::setRegister(rg()->FGPFCCR,
		                     FGPFCCR::CM, static_cast<uint8_t>(fmt));
	}

	INLINE static void setOutputColor (uint32_t color)
	{
		rg()->OCOLR = color;
	}

	INLINE static void setOutputOffset (uint16_t offset)
	{
		::setRegister(rg()->OOR,
		                     OOR::LO, offset);
	}

    INLINE static void setLines (uint16_t numberOfLines, uint16_t pixelPerLine)
    {
		::setRegister(rg()->NLR,
		                     NLR::NL, numberOfLines,
		                     NLR::PL, pixelPerLine);
    }

	INLINE static void setOutputMemoryAddress (uint32_t address)
	{
		rg()->OMAR = address;
	}

	INLINE static void setForegroundMemoryAddress (uint32_t address)
	{
		rg()->FGMAR = address;
	}

	INLINE static void setBackgroundMemoryAddress (uint32_t address)
	{
		rg()->BGMAR = address;
	}

	INLINE static void setForegroundOffset (uint16_t offset)
	{
		::setRegister(rg()->FGOR,
		                     FGOR::LO, offset);
	}

	INLINE static void setBackgroundOffset (uint16_t offset)
	{
		::setRegister(rg()->BGOR,
		                     BGOR::LO, offset);
	}

	INLINE static bool isTransferInProgress()
	{
		return ::getRegField(rg()->CR, CR::START);
	}

	INLINE static bool isTransferComplete()
	{
		return ::getRegField(rg()->ISR, ISR::TCIF);
	}

	INLINE static bool isTransferError()
	{
		return ::getRegField(rg()->ISR, ISR::TEIF);
	}

	INLINE static bool isTransferWatermark()
	{
		return ::getRegField(rg()->ISR, ISR::TWIF);
	}

	INLINE static bool isClutAccessError()
	{
		return ::getRegField(rg()->ISR, ISR::CAEIF);
	}

	INLINE static bool isClutTransferComplete()
	{
		return ::getRegField(rg()->ISR, ISR::CTCIF);
	}

	INLINE static bool isConfigurationError()
	{
		return ::getRegField(rg()->ISR, ISR::CEIF);
	}

	INLINE static void clearTransferComplete()
	{
		::setRegister(rg()->IFCR,
		                     IFCR::CTCIF, 1);
	}

	INLINE static void clearTransferError()
	{
		::setRegister(rg()->IFCR,
		                     IFCR::CTEIF, 1);
	}

	INLINE static void clearTransferWatermark()
	{
		::setRegister(rg()->IFCR,
		                     IFCR::CTWIF, 1);
	}

	INLINE static void clearClutAccessError()
	{
		::setRegister(rg()->IFCR,
		                     IFCR::CAECIF, 1);
	}

	INLINE static void clearClutTransferComplete()
	{
		::setRegister(rg()->IFCR,
		                     IFCR::CCTCIF, 1);
	}

	INLINE static void clearConfigurationError()
	{
		::setRegister(rg()->IFCR,
		                     IFCR::CCEIF, 1);
	}


};
        
        
        
        
#endif // DMA2D_H
