#ifndef SCB_H
#define SCB_H

#include "utility.h"
#include <cstdint>
#include "rcc.h"

struct Scb {

    constexpr static uint32_t base = 0xE000ED00;

    enum PriorityGrouping {
        pg16_0  = 0b000,
        pg8_2 = 0b100,
        pg4_4 = 0b101,
        pg2_8 = 0b110,
        pg0_16 = 0b111
    };

    struct Regs {
         uint32_t CPUID; 	//< 0x0 CPUID base register
         uint32_t ICSR; 	//< 0x4 Interrupt control and state register
         uint32_t VTOR; 	//< 0x8 Vector table offset register
         uint32_t AIRCR; 	//< 0xC Application interrupt and reset control register
         uint32_t SCR; 	//< 0x10 System control register
         uint32_t CCR; 	//< 0x14 Configuration and control register
         uint32_t SHPR[3]; 	//< 0x18 System handler priority registers
         uint32_t SHCSR; 	//< 0x24 System handler control and state register
         uint32_t CFSR_UFSR_BFSR_MMFSR; 	//< 0x28 Configurable fault status register
         uint32_t HFSR; 	//< 0x2C Hard fault status register
         uint32_t reserved0; 	//< reserved
         uint32_t MMFAR; 	//< 0x34 Memory management fault address register
         uint32_t BFAR; 	//< 0x38 Bus fault address register
         uint32_t AFSR; 	//< 0x3C Auxiliary fault status register
    };

    struct CPUID {
        constexpr static uint8_t Revision[]{ 0, 4 }; 	//< Revision number
        constexpr static uint8_t PartNo[]{ 4, 12 }; 	//< Part number of the processor
        constexpr static uint8_t Constant[]{ 16, 4 }; 	//< Reads as 0xF
        constexpr static uint8_t Variant[]{ 20, 4 }; 	//< Variant number
        constexpr static uint8_t Implementer[]{ 24, 8 }; 	//< Implementer code
    };

    struct ICSR {
        constexpr static uint8_t VECTACTIVE[]{ 0, 9 }; 	//< Active vector
        constexpr static uint8_t RETTOBASE[]{ 11, 1 }; 	//< Return to base level
        constexpr static uint8_t VECTPENDING[]{ 12, 7 }; 	//< Pending vector
        constexpr static uint8_t ISRPENDING[]{ 22, 1 }; 	//< Interrupt pending flag
        constexpr static uint8_t PENDSTCLR[]{ 25, 1 }; 	//< SysTick exception clear-pending bit
        constexpr static uint8_t PENDSTSET[]{ 26, 1 }; 	//< SysTick exception set-pending bit
        constexpr static uint8_t PENDSVCLR[]{ 27, 1 }; 	//< PendSV clear-pending bit
        constexpr static uint8_t PENDSVSET[]{ 28, 1 }; 	//< PendSV set-pending bit
        constexpr static uint8_t NMIPENDSET[]{ 31, 1 }; 	//< NMI set-pending bit.
    };

    struct VTOR {
        constexpr static uint8_t TBLOFF[]{ 9, 21 }; 	//< Vector table base offset field
    };

    struct AIRCR {
        constexpr static uint8_t VECTRESET[]{ 0, 1 }; 	//< VECTRESET
        constexpr static uint8_t VECTCLRACTIVE[]{ 1, 1 }; 	//< VECTCLRACTIVE
        constexpr static uint8_t SYSRESETREQ[]{ 2, 1 }; 	//< SYSRESETREQ
        constexpr static uint8_t PRIGROUP[]{ 8, 3 }; 	//< PRIGROUP
        constexpr static uint8_t ENDIANESS[]{ 15, 1 }; 	//< ENDIANESS
        constexpr static uint8_t VECTKEYSTAT[]{ 16, 16 }; 	//< Register key
    };

    struct SCR {
        constexpr static uint8_t SLEEPONEXIT[]{ 1, 1 }; 	//< SLEEPONEXIT
        constexpr static uint8_t SLEEPDEEP[]{ 2, 1 }; 	//< SLEEPDEEP
        constexpr static uint8_t SEVEONPEND[]{ 4, 1 }; 	//< Send Event on Pending bit
    };

    struct CCR {
        constexpr static uint8_t NONBASETHRDENA[]{ 0, 1 }; 	//< Configures how the processor enters Thread mode
        constexpr static uint8_t USERSETMPEND[]{ 1, 1 }; 	//< USERSETMPEND
        constexpr static uint8_t UNALIGN__TRP[]{ 3, 1 }; 	//< UNALIGN_ TRP
        constexpr static uint8_t DIV_0_TRP[]{ 4, 1 }; 	//< DIV_0_TRP
        constexpr static uint8_t BFHFNMIGN[]{ 8, 1 }; 	//< BFHFNMIGN
        constexpr static uint8_t STKALIGN[]{ 9, 1 }; 	//< STKALIGN
    };

    struct SHPR1 {
        constexpr static uint8_t PRI_4[]{ 0, 8 }; 	//< Priority of system handler 4
        constexpr static uint8_t PRI_5[]{ 8, 8 }; 	//< Priority of system handler 5
        constexpr static uint8_t PRI_6[]{ 16, 8 }; 	//< Priority of system handler 6
    };

    struct SHPR2 {
        constexpr static uint8_t PRI_11[]{ 24, 8 }; 	//< Priority of system handler 11
    };

    struct SHPR3 {
        constexpr static uint8_t PRI_14[]{ 16, 8 }; 	//< Priority of system handler 14
        constexpr static uint8_t PRI_15[]{ 24, 8 }; 	//< Priority of system handler 15
    };

    struct SHCSR {
        constexpr static uint8_t MEMFAULTACT[]{ 0, 1 }; 	//< Memory management fault exception active bit
        constexpr static uint8_t BUSFAULTACT[]{ 1, 1 }; 	//< Bus fault exception active bit
        constexpr static uint8_t USGFAULTACT[]{ 3, 1 }; 	//< Usage fault exception active bit
        constexpr static uint8_t SVCALLACT[]{ 7, 1 }; 	//< SVC call active bit
        constexpr static uint8_t MONITORACT[]{ 8, 1 }; 	//< Debug monitor active bit
        constexpr static uint8_t PENDSVACT[]{ 10, 1 }; 	//< PendSV exception active bit
        constexpr static uint8_t SYSTICKACT[]{ 11, 1 }; 	//< SysTick exception active bit
        constexpr static uint8_t USGFAULTPENDED[]{ 12, 1 }; 	//< Usage fault exception pending bit
        constexpr static uint8_t MEMFAULTPENDED[]{ 13, 1 }; 	//< Memory management fault exception pending bit
        constexpr static uint8_t BUSFAULTPENDED[]{ 14, 1 }; 	//< Bus fault exception pending bit
        constexpr static uint8_t SVCALLPENDED[]{ 15, 1 }; 	//< SVC call pending bit
        constexpr static uint8_t MEMFAULTENA[]{ 16, 1 }; 	//< Memory management fault enable bit
        constexpr static uint8_t BUSFAULTENA[]{ 17, 1 }; 	//< Bus fault enable bit
        constexpr static uint8_t USGFAULTENA[]{ 18, 1 }; 	//< Usage fault enable bit
    };

    struct CFSR_UFSR_BFSR_MMFSR {
        constexpr static uint8_t IACCVIOL[]{ 0, 1 }; 	//< Instruction access violation flag
        constexpr static uint8_t DACCVIOL[]{ 1, 1 }; 	//< Instruction access violation flag
        constexpr static uint8_t MUNSTKERR[]{ 3, 1 }; 	//< Memory manager fault on unstacking for a return from exception
        constexpr static uint8_t MSTKERR[]{ 4, 1 }; 	//< Memory manager fault on stacking for exception entry.
        constexpr static uint8_t MLSPERR[]{ 5, 1 }; 	//< MLSPERR
        constexpr static uint8_t MMARVALID[]{ 7, 1 }; 	//< Memory Management Fault Address Register (MMAR) valid flag
        constexpr static uint8_t IBUSERR[]{ 8, 1 }; 	//< Instruction bus error
        constexpr static uint8_t PRECISERR[]{ 9, 1 }; 	//< Precise data bus error
        constexpr static uint8_t IMPRECISERR[]{ 10, 1 }; 	//< Imprecise data bus error
        constexpr static uint8_t UNSTKERR[]{ 11, 1 }; 	//< Bus fault on unstacking for a return from exception
        constexpr static uint8_t STKERR[]{ 12, 1 }; 	//< Bus fault on stacking for exception entry
        constexpr static uint8_t LSPERR[]{ 13, 1 }; 	//< Bus fault on floating-point lazy state preservation
        constexpr static uint8_t BFARVALID[]{ 15, 1 }; 	//< Bus Fault Address Register (BFAR) valid flag
        constexpr static uint8_t UNDEFINSTR[]{ 16, 1 }; 	//< Undefined instruction usage fault
        constexpr static uint8_t INVSTATE[]{ 17, 1 }; 	//< Invalid state usage fault
        constexpr static uint8_t INVPC[]{ 18, 1 }; 	//< Invalid PC load usage fault
        constexpr static uint8_t NOCP[]{ 19, 1 }; 	//< No coprocessor usage fault.
        constexpr static uint8_t UNALIGNED[]{ 24, 1 }; 	//< Unaligned access usage fault
        constexpr static uint8_t DIVBYZERO[]{ 25, 1 }; 	//< Divide by zero usage fault
    };

    struct HFSR {
        constexpr static uint8_t VECTTBL[]{ 1, 1 }; 	//< Vector table hard fault
        constexpr static uint8_t FORCED[]{ 30, 1 }; 	//< Forced hard fault
        constexpr static uint8_t DEBUG_VT[]{ 31, 1 }; 	//< Reserved for Debug use
    };


    struct AFSR {
        constexpr static uint8_t IMPDEF[]{ 0, 32 }; 	//< Implementation defined
    };
    static constexpr uint8_t    aircrSysResetPos = 2;
    static constexpr uint8_t    aircrPriGroupPos = 8;
    static constexpr uint16_t   aircrKey = 0x5fa;

    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    INLINE static volatile Regs* rg()
    {
		return reinterpret_cast<volatile Regs*>(base);
    }

    INLINE static uint16_t getCpuidImplementer() { return ::getRegField(rg()->CPUID, CPUID::Implementer); }
    INLINE static uint16_t getCpuidVariant() { return ::getRegField(rg()->CPUID, CPUID::Variant); }
    INLINE static uint16_t getCpuidConstant() { return ::getRegField(rg()->CPUID, CPUID::Constant); }
    INLINE static uint16_t getCpuidPartNo() { return ::getRegField(rg()->CPUID, CPUID::PartNo); }
    INLINE static uint16_t getCpuidRevision() { return ::getRegField(rg()->CPUID, CPUID::Revision); }


    INLINE static uint16_t getUfDivByZero() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::DIVBYZERO); }
    INLINE static uint16_t getUfUnaligned() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::UNALIGNED); }
    INLINE static uint16_t getUfNoCoprocessor() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::NOCP); }
    INLINE static uint16_t getUfInvalidPc() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::INVPC); }
    INLINE static uint16_t getUfInvalidState() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::INVSTATE); }
    INLINE static uint16_t getUfUndefinedInstruction() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::UNDEFINSTR); }

    INLINE static uint16_t getBfValid() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::BFARVALID); }
    INLINE static uint16_t getBfFpLazyState() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::LSPERR); }
    INLINE static uint16_t getBfStacking() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::STKERR); }
    INLINE static uint16_t getBfUnStacking() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::UNSTKERR); }
    INLINE static uint16_t getBfImprecise() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::IMPRECISERR); }
    INLINE static uint16_t getBfPrecise() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::PRECISERR); }
    INLINE static uint16_t getBfInstruction() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::IBUSERR); }

    INLINE static uint16_t getMfValid() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::MMARVALID); }
    INLINE static uint16_t getMfFpLazyState() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::MLSPERR); }
    INLINE static uint16_t getMfStacking() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::MSTKERR); }
    INLINE static uint16_t getMfUnStacking() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::MUNSTKERR); }
    INLINE static uint16_t getMfDataAccess() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::DACCVIOL); }
    INLINE static uint16_t getMfInstructionAccess() { return ::getRegField(rg()->CFSR_UFSR_BFSR_MMFSR, CFSR_UFSR_BFSR_MMFSR::IACCVIOL); }

    INLINE static uint16_t getHfVectorTable() { return ::getRegField(rg()->HFSR, HFSR::VECTTBL); }
    INLINE static uint16_t getHfForsed() { return ::getRegField(rg()->HFSR, HFSR::FORCED); }
    INLINE static uint16_t getHfDebug() { return ::getRegField(rg()->HFSR, HFSR::DEBUG_VT); }



    INLINE static uint32_t getMemoryFaultAddress() { return (rg()->MMFAR); }
    INLINE static uint32_t getBusFaultAddress() { return (rg()->BFAR); }

    INLINE static void enableSeparatedFaults(const bool bus, const bool memory, const bool usage)
    {
        ::setRegister(rg()->SHCSR,
                             SHCSR::BUSFAULTENA, bus,
                             SHCSR::MEMFAULTENA, memory,
                             SHCSR::USGFAULTENA, usage);
    }

    INLINE static void enableTraps(const bool divByZero, const bool unaligned)
    {
        ::setRegister(rg()->CCR,
                             CCR::DIV_0_TRP, divByZero,
                             CCR::UNALIGN__TRP, unaligned);
    }



};


#endif // SCB_H
