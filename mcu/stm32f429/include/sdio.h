#ifndef SDIO_H
#define SDIO_H

#include <stdint.h>

#include "rcc.h"
#include "boarddriver.h"

extern Ostream<ConsoleCfg, USE_SD_DEBUG> dbgSd;

struct Sdio {

    struct POWER_t {
        uint32_t        PWRCTRL:2;
        uint32_t        RESERVED:30;
    };

    struct CLKCR_t {
        uint32_t        CLKDIV:8;
        uint32_t        CLKEN:1;
        uint32_t        PWRSAV:1;
        uint32_t        BYPASS:1;
        uint32_t        WIDBUS:2;
        uint32_t        NEGEDGE:1;
        uint32_t        HWFC_EN:1;
        uint32_t        RESERVED:17;
    };

    struct CMD_t {
        uint32_t        CMDINDEX:6;
        uint32_t        WAITRESP:2;
        uint32_t        WAITINT:1;
        uint32_t        WAITPEND:1;
        uint32_t        CPSMEN:1;
        uint32_t        SDIOSUSPEND:1;
        uint32_t        ENCMDCOMPL:1;
        uint32_t        NIEN:1;
        uint32_t        CE_ATACMD:1;
        uint32_t        RESERVED:17;
    };

    struct RESPCMD_t {
        uint32_t        RESPCMD:6;
        uint32_t        RESERVED:1;
    };

    struct DLEN_t {
        uint32_t        DATALENGTH:25;
        uint32_t        RESERVED:1;
    };

    struct DCTRL_t {
        uint32_t        DTEN:1;
        uint32_t        DTDIR:1;
        uint32_t        DTMODE:1;
        uint32_t        DMAEN:1;
        uint32_t        DBLOCKSIZE:4;
        uint32_t        RWSTART:1;
        uint32_t        RWSTOP:1;
        uint32_t        RWMOD:1;
        uint32_t        SDIOEN:1;
        uint32_t        RESERVED:20;
    };

    struct DCOUNT_t {
        uint32_t        DATACOUNT:25;
        uint32_t        RESERVED:1;
    };

    struct STA_t {
        uint32_t        CCRCFAIL:1;
        uint32_t        DCRCFAIL:1;
        uint32_t        CTIMEOUT:1;
        uint32_t        DTIMEOUT:1;
        uint32_t        TXUNDERR:1;
        uint32_t        RXOVERR:1;
        uint32_t        CMDREND:1;
        uint32_t        CMDSENT:1;
        uint32_t        DATAEND:1;
        uint32_t        STBITERR:1;
        uint32_t        DBCKEND:1;
        uint32_t        CMDACT:1;
        uint32_t        TXACT:1;
        uint32_t        RXACT:1;
        uint32_t        TXFIFOHE:1;
        uint32_t        RXFIFOHF:1;
        uint32_t        TXFIFOF:1;
        uint32_t        RXFIFOF:1;
        uint32_t        TXFIFOE:1;
        uint32_t        RXFIFOE:1;
        uint32_t        TXDAVL:1;
        uint32_t        RXDAVL:1;
        uint32_t        SDIOIT:1;
        uint32_t        CEATAEND:1;
        uint32_t        RESERVED:1;
    };

    struct ICR_t {
        uint32_t        CCRCFAILC:1;
        uint32_t        DCRCFAILC:1;
        uint32_t        CTIMEOUTC:1;
        uint32_t        DTIMEOUTC:1;
        uint32_t        TXUNDERRC:1;
        uint32_t        RXOVERRC:1;
        uint32_t        CMDRENDC:1;
        uint32_t        CMDSENTC:1;
        uint32_t        DATAENDC:1;
        uint32_t        STBITERRC:1;
        uint32_t        DBCKENDC:1;
        uint32_t        RESERVED1:11;
        uint32_t        SDIOITC:1;
        uint32_t        CEATAENDC:1;
        uint32_t        RESERVED2:1;
    };

    struct MASK_t {
        uint32_t        CCRCFAILIE:1;
        uint32_t        DCRCFAILIE:1;
        uint32_t        CTIMEOUTIE:1;
        uint32_t        DTIMEOUTIE:1;
        uint32_t        TXUNDERRIE:1;
        uint32_t        RXOVERRIE:1;
        uint32_t        CMDRENDIE:1;
        uint32_t        CMDSENTIE:1;
        uint32_t        DATAENDIE:1;
        uint32_t        STBITERRIE:1;
        uint32_t        DBCKENDIE:1;
        uint32_t        CMDACTIE:1;
        uint32_t        TXACTIE:1;
        uint32_t        RXACTIE:1;
        uint32_t        TXFIFOHEIE:1;
        uint32_t        RXFIFOHFIE:1;
        uint32_t        TXFIFOFIE:1;
        uint32_t        RXFIFOFIE:1;
        uint32_t        TXFIFOEIE:1;
        uint32_t        RXFIFOEIE:1;
        uint32_t        TXDAVLIE:1;
        uint32_t        RXDAVLIE:1;
        uint32_t        SDIOITIE:1;
        uint32_t        CEATAENDIE:1;
        uint32_t        RESERVED:1;
    };

    struct FIFOCNT_t {
        uint32_t        FIFOCOUNT:24;
        uint32_t        RESERVED:1;
    };

    struct Regs {
        POWER_t     POWER;
        CLKCR_t     CLKCR;
        uint32_t    ARG;
        CMD_t       CMD;
        RESPCMD_t   RESPCMD;
        uint32_t    RESP[4];
        uint32_t    DTIMER;
        DLEN_t      DLEN;
        DCTRL_t     DCTRL;
        DCOUNT_t    DCOUNT;
        STA_t       STA;
        ICR_t       ICR;
        MASK_t      MASK;
        uint32_t    RESERVED1[2];
        FIFOCNT_t   FIFOCNT;
        uint32_t    RESERVED2[13];
        uint32_t    FIFO;
    };

    //*********************************************************************
    struct STA_c {
        constexpr static uint8_t CCRCFAIL[]   {0 , 1};
        constexpr static uint8_t DCRCFAIL[]   {1 , 1};
        constexpr static uint8_t CTIMEOUT[]   {2 , 1};
        constexpr static uint8_t DTIMEOUT[]   {3 , 1};
        constexpr static uint8_t TXUNDERR[]   {4 , 1};
        constexpr static uint8_t RXOVERR[]   {5 , 1};
        constexpr static uint8_t CMDREND[]   {6 , 1};
        constexpr static uint8_t CMDSENT[]   {7 , 1};
        constexpr static uint8_t DATAEND[]   {8 , 1};
        constexpr static uint8_t STBITERR[]   {9 , 1};
        constexpr static uint8_t DBCKEND[]   {10 , 1};
        constexpr static uint8_t CMDACT[]   {11 , 1};
        constexpr static uint8_t TXACT[]   {12 , 1};
        constexpr static uint8_t RXACT[]   {13 , 1};
        constexpr static uint8_t TXFIFOHE[]   {14 , 1};
        constexpr static uint8_t RXFIFOHF[]   {15 , 1};
        constexpr static uint8_t TXFIFOF[]   {16 , 1};
        constexpr static uint8_t RXFIFOF[]   {17 , 1};
        constexpr static uint8_t TXFIFOE[]   {18 , 1};
        constexpr static uint8_t RXFIFOE[]   {19 , 1};
        constexpr static uint8_t TXDAVL[]   {20 , 1};
        constexpr static uint8_t RXDAVL[]   {21 , 1};
        constexpr static uint8_t SDIOIT[]   {22 , 1};
        constexpr static uint8_t CEATAEND[]   {23 , 1};
        constexpr static uint8_t RESERVED[]   {24 , 1};
    };



    //**********************************************************************

    constexpr static uint32_t base = 0x40012C00;
    ///---------------------------------------------------------------------
    ///
    /// \brief Получение указателя на регистры
    /// \return указатель на регистры
    ///
    INLINE static volatile Regs* rg()
    {
        return reinterpret_cast<volatile Regs * volatile>(base);
    }

    enum WaitResponce {
        wrNo = 0b00,
        wrShort = 0b01,
        wrLong = 0b11,
    };

    enum BusWide {
        bw1 = 0b00,
        bw4 = 0b01,
        bw8 = 0b10,
    };

    enum DataBlockSize {
        dbs1 =      0b0000,
        dbs2 =      0b0001,
        dbs4 =      0b0010,
        dbs8 =      0b0011,
        dbs16 =     0b0100,
        dbs32 =     0b0101,
        dbs64 =     0b0110,
        dbs128 =    0b0111,
        dbs256 =    0b1000,
        dbs512 =    0b1001,
        dbs1024 =   0b1010,
        dbs2048 =   0b1011,
        dbs4096 =   0b1100,
        dbs8192 =   0b1101,
        dbs16384 =  0b1110,
    };

    enum ReadWaitMode {
        rwmStopD2 = 0,
        rwmCK = 1
    };

    ///
    /// \brief SDIO card status
    ///
    struct CardStatus {
        uint32_t        reserved1:2;
        uint32_t        reserved2:1;
        uint32_t        akeSeqError:1;
        uint32_t        reserved3:1; //4
        uint32_t        appCmd:1;
        uint32_t        reserved4:1;
        uint32_t        switchError:1;
        uint32_t        readyForData:1;
        uint32_t        currentState:4; //9
        uint32_t        eraseReset:1;
        uint32_t        cardEccDisabled:1; //14
        uint32_t        wpEraseSkip:1;
        uint32_t        cidCsdOverwrite:1;
        uint32_t        streamWriteOverrun:1;
        uint32_t        streamReadUnderrun:1;
        uint32_t        error:1;
        uint32_t        ccError:1; //20
        uint32_t        cardEccFailed:1;
        uint32_t        illegalCommand:1;
        uint32_t        comCrcError:1;
        uint32_t        lockUnlockFailed:1;
        uint32_t        cardIsLocked:1; //25
        uint32_t        wpViolation:1;
        uint32_t        eraseParam:1;
        uint32_t        eraseSeqError:1;
        uint32_t        blockLenError:1;
        uint32_t        addressMisalign:1; //30
        uint32_t        addressOutOfRange:1;
    };



    constexpr static uint32_t errNone                  = 0x00000000U;   /*!< No error                                                      */
    constexpr static uint32_t errCmdCrcFail            = 0x00000001U;   /*!< Command response received (but CRC check failed)              */
    constexpr static uint32_t errDataCrcFail           = 0x00000002U;   /*!< Data block sent/received (CRC check failed)                   */
    constexpr static uint32_t errCmdRspTimeout         = 0x00000004U;   /*!< Command response timeout                                      */
    constexpr static uint32_t errDataTimeout           = 0x00000008U;   /*!< Data timeout                                                  */
    constexpr static uint32_t errTxUnderrun            = 0x00000010U;   /*!< Transmit FIFO underrun                                        */
    constexpr static uint32_t errRxOverrun             = 0x00000020U;   /*!< Receive FIFO overrun                                          */
    constexpr static uint32_t errAddrMisaligned        = 0x00000040U;   /*!< Misaligned address                                            */
    constexpr static uint32_t errBlockLenErr           = 0x00000080U;   /*!< Transferred block length is not allowed for the card or the
                                                     number of transferred bytes does not match the block length   */
    constexpr static uint32_t errEraseSeqErr           = 0x00000100U;   /*!< An error in the sequence of erase command occurs              */
    constexpr static uint32_t errBadEraseParam         = 0x00000200U;   /*!< An invalid selection for erase groups                         */
    constexpr static uint32_t errWriteProtViolation    = 0x00000400U;   /*!< Attempt to program a write protect block                      */
    constexpr static uint32_t errLockUnlockFailed      = 0x00000800U;   /*!< Sequence or password error has been detected in unlock
                                                    command or if there was an attempt to access a locked card    */
    constexpr static uint32_t errComCrcFailed          = 0x00001000U;   /*!< CRC check of the previous command failed                      */
    constexpr static uint32_t errIllegalCmd            = 0x00002000U;   /*!< Command is not legal for the card state                       */
    constexpr static uint32_t errCardEccFailed         = 0x00004000U;   /*!< Card internal ECC was applied but failed to correct the data  */
    constexpr static uint32_t errCcErr                 = 0x00008000U;   /*!< Internal card controller error                                */
    constexpr static uint32_t errGeneralUnknownErr     = 0x00010000U;   /*!< General or unknown error                                      */
    constexpr static uint32_t errStreamReadUnderrun    = 0x00020000U;   /*!< The card could not sustain data reading in stream rmode       */
    constexpr static uint32_t errStreamWriteOverrun    = 0x00040000U;   /*!< The card could not sustain data programming in stream mode    */
    constexpr static uint32_t errCidCsdOverwrite       = 0x00080000U;   /*!< CID/CSD overwrite error                                       */
    constexpr static uint32_t errWpEraseSkip           = 0x00100000U;   /*!< Only partial address space was erased                         */
    constexpr static uint32_t errCardEccDisabled       = 0x00200000U;   /*!< Command has been executed without using internal ECC          */
    constexpr static uint32_t errEraseReset            = 0x00400000U;   /*!< Erase sequence was cleared before executing because an out
                                                    of erase sequence command was received                        */
    constexpr static uint32_t errAkeSeqErr             = 0x00800000U;   /*!< Error in sequence of authentication                           */
    constexpr static uint32_t errInvalidVoltrange      = 0x01000000U;   /*!< Error in case of invalid voltage range                        */
    constexpr static uint32_t errAddrOutOfRange        = 0x02000000U;   /*!< Error when addressed block is out of range                    */
    constexpr static uint32_t errRequestNotApplicable  = 0x04000000U;   /*!< Error when command request is not applicable                  */
    constexpr static uint32_t errInvalidParameter      = 0x08000000U;   /*!< the used parameter is not valid                               */
    constexpr static uint32_t errUnsupportedFeature    = 0x10000000U;   /*!< Error when feature is not insupported                         */
    constexpr static uint32_t errBusy                  = 0x20000000U;   /*!< Error when transfer process is busy                           */
    constexpr static uint32_t errDma                   = 0x40000000U;   /*!< Error while DMA transfer                                      */
    constexpr static uint32_t errTimeout               = 0x80000000U;   /*!< Timeout error                                                 */


    constexpr static uint32_t cmdTimeout               = 5000U;
    constexpr static uint32_t datatimeout              = 0xFFFFFFFFU;


    constexpr static uint32_t r6GeneralUnknownError    =  0x00002000U;
    constexpr static uint32_t r6IllegalCmd             =  0x00004000U;
    constexpr static uint32_t r6ComCrcFailed           =  0x00008000U;

    constexpr static uint32_t checkPattern             = 0x000001AAU;
    constexpr static uint32_t voltageWindowSd          = 0x80100000U;

    constexpr static uint32_t allzero                 =  0x00000000U;

    constexpr static uint32_t wideBusSupport         =   0x00040000U;
    constexpr static uint32_t singleBusSupport      =    0x00010000U;
    constexpr static uint32_t cardLocked               = 0x02000000U;


    //---------------------------------------------------------------------
    ///
    /// \brief Включение тактирования
    ///
    INLINE static void clockEnable(const bool en)
    {
        Rcc::clockSdio(en);
    }

    //---------------------------------------------------------------------
    INLINE static void init(uint8_t clkDiv,
                            bool clkEn,
                            bool powerSave,
                            bool clockBypass,
                            Sdio::BusWide busWide,
                            bool negEdge,
                            bool hwFlowControl)
    {
        CLKCR_t clkcr;
        ::asWord(clkcr) = 0;

        dbgSd << "Sdio::init\n";
        dbgSd << "  clkEn: " << clkEn << Use::endl;
        dbgSd << "  clkDiv: " << clkDiv << Use::endl;
        dbgSd << "  powerSave: " << powerSave << Use::endl;
        dbgSd << "  clockBypass: " << clockBypass << Use::endl;
        dbgSd << "  busWide: " << busWide << Use::endl;
        dbgSd << "  negEdge: " << negEdge << Use::endl;
        dbgSd << "  hwFlowControl: " << hwFlowControl << Use::endl;


        clkcr.CLKEN = clkEn;
        clkcr.CLKDIV = clkDiv;
        clkcr.PWRSAV = powerSave;
        clkcr.BYPASS = clockBypass;
        clkcr.WIDBUS = busWide;
        clkcr.NEGEDGE = negEdge;
        clkcr.HWFC_EN = hwFlowControl;

        ::asWord(rg()->CLKCR) = ::asWord(clkcr);
    }
    //---------------------------------------------------------------------
    INLINE static bool isCmdResponceReady() { return rg()->STA.CMDREND; }
    INLINE static bool isCmdSent() { return rg()->STA.CMDSENT; }
    INLINE static bool isDataBlockSR() { return rg()->STA.DBCKEND; }
    INLINE static bool isCommandTimeout() { return rg()->STA.CTIMEOUT; }
    INLINE static bool isDataTimeout() { return rg()->STA.DTIMEOUT; }
    INLINE static bool isCommandCrcFail() { return rg()->STA.CCRCFAIL; }
    INLINE static bool isDataCrcFail() { return rg()->STA.DCRCFAIL; }
    INLINE static bool isRxOverrun() { return rg()->STA.RXOVERR; }
    INLINE static bool isRxNotEmpty() { return rg()->STA.RXDAVL; }
    INLINE static bool isRx8NotEmpty() { return rg()->STA.RXFIFOHF; }
    INLINE static bool isTx8NotEmpty() { return rg()->STA.TXFIFOHE; }
    INLINE static bool isTxNotEmpty() { return rg()->STA.TXDAVL; }
    INLINE static bool isDataEnd() { return rg()->STA.DATAEND; }
    INLINE static bool isWriting() { return rg()->STA.TXACT; }
    INLINE static bool isBusy() { return (rg()->STA.TXACT | rg()->STA.RXACT); }
    INLINE static bool isTxFifoFull() { return rg()->STA.TXFIFOF; }



    //---------------------------------------------------------------------
    INLINE static void clearCmdResponceReady() { rg()->ICR.CMDRENDC = 1; }
    INLINE static void clearCmdSent() { rg()->ICR.CMDSENTC = 1; }
    INLINE static void clearDataBlockSR() { rg()->ICR.DBCKENDC = 1; }
    INLINE static void clearCommandTimeout() { rg()->ICR.CTIMEOUTC = 1; }
    INLINE static void clearDataTimeout() { rg()->ICR.DTIMEOUTC = 1; }
    INLINE static void clearDataCrcFail() { rg()->ICR.DCRCFAILC = 1; }
    INLINE static void clearCommandCrcFail() { rg()->ICR.CCRCFAILC = 1; }
    INLINE static void clearRxOverrun() { rg()->ICR.RXOVERRC = 1; }
    INLINE static void clearDataEnd() { rg()->ICR.DATAENDC = 1; }

    //---------------------------------------------------------------------
    INLINE static void setCmdResponceReady(const bool en) { rg()->MASK.CMDRENDIE = en; }
    INLINE static void setCmdSent(const bool en) { rg()->MASK.CMDSENTIE = en; }
    INLINE static void setDataBlockSR(const bool en) { rg()->MASK.DBCKENDIE = en; }
    INLINE static void setCommandTimeout(const bool en) { rg()->MASK.CTIMEOUTIE = en; }
    INLINE static void setDataTimeout(const bool en) { rg()->MASK.DTIMEOUTIE = en; }
    INLINE static void setDataCrcFail(const bool en) { rg()->MASK.DCRCFAILIE = en; }
    INLINE static void setCommandCrcFail(const bool en) { rg()->MASK.CCRCFAILIE = en; }
    INLINE static void setRxOverrun(const bool en) { rg()->MASK.RXOVERRIE = en; }
    INLINE static void setRxNotEmpty(const bool en) { rg()->MASK.RXDAVLIE = en; }
    INLINE static void setRx8NotEmpty(const bool en) { rg()->MASK.RXFIFOHFIE = en; }
    INLINE static void setTx8NotEmpty(const bool en) { rg()->MASK.TXFIFOHEIE = en; }
    INLINE static void setTxNotEmpty(const bool en) { rg()->MASK.TXDAVLIE = en; }
    INLINE static void setDataEnd(const bool en) { rg()->MASK.DATAENDIE = en; }
    INLINE static void setTxFifoFull(const bool en) { rg()->MASK.TXFIFOFIE = en; }


    //---------------------------------------------------------------------
    INLINE static bool getPowerState() { return rg()->POWER.PWRCTRL; }
    INLINE static void setPowerState(bool en) { rg()->POWER.PWRCTRL = en?0xb11:0; }
    INLINE static volatile uint32_t& getFifo() { return rg()->FIFO; }
    INLINE static uint32_t getFifoCnt() { return rg()->FIFOCNT.FIFOCOUNT; }
    INLINE static uint32_t readFifo() { return rg()->FIFO; }
    INLINE static void writeFifo(uint32_t* data) { rg()->FIFO = *data; }
    INLINE static uint32_t setReadWaitMode(Sdio::ReadWaitMode rwm) { return rg()->DCTRL.RWMOD = rwm; }
    INLINE static uint32_t getDataCounter() { return rg()->DCOUNT.DATACOUNT; }
    INLINE static uint32_t getFifoCount() { return rg()->FIFOCNT.FIFOCOUNT; }
    INLINE static uint32_t getResponse(uint8_t responce) { return rg()->RESP[responce - 1]; }
    INLINE static void clearStaticFlags() { ::asWord(rg()->ICR) = 0xc007ff; }
    INLINE static void clearDctrl() { ::asWord(rg()->DCTRL) = 0; }
    INLINE static void setDma(const bool en) { rg()->DCTRL.DMAEN = en; }

    //---------------------------------------------------------------------
    INLINE static uint8_t getCommandResponce() { return rg()->RESPCMD.RESPCMD; }
    INLINE static void sendCommand(uint8_t index,
                                   Sdio::WaitResponce wr,
                                   bool waitForInterrupt,
                                   bool cpsmEnable,
                                   uint32_t argument)
    {
        rg()->ARG = argument;

        CMD_t   cmd;
        ::asWord(cmd) = 0;
        cmd.CMDINDEX = index;
        cmd.WAITRESP = wr;
        cmd.WAITINT = waitForInterrupt;
        cmd.CPSMEN = cpsmEnable;


        ::asWord(rg()->CMD) = ::asWord(cmd);
    }

    //---------------------------------------------------------------------
    INLINE static void configData(uint32_t timer,
                                  uint32_t length,
                                  bool dpsmEnable,
                                  bool fromCard,
                                  bool streamMode,
                                  Sdio::DataBlockSize blockSize,
                                  bool dmaEn = false)
    {
        rg()->DTIMER = timer;
        rg()->DLEN.DATALENGTH = length;

        DCTRL_t dctrl;
        ::asWord(dctrl) = 0;

        dctrl.DTEN = dpsmEnable;
        dctrl.DTDIR = fromCard;
        dctrl.DTMODE = streamMode;
        dctrl.DBLOCKSIZE = blockSize;
        dctrl.DMAEN = dmaEn;
        ::asWord(rg()->DCTRL) = ::asWord(dctrl);
    }

    //---------------------------------------------------------------------
    static uint32_t getCmdErr()
    {
        volatile uint32_t scc = Rcc::systemCoreClock();
//        uint32_t count = cmdTimeout * (Rcc::systemCoreClock() / 8U / 1000U);
        uint32_t count = cmdTimeout * (scc / 8U / 1000U);


        // Check for timeout
        do {
            if (!(--count))
                return errTimeout;
        } while (!(rg()->STA.CMDSENT));

        clearStaticFlags();

        return errNone;
    }

//    //---------------------------------------------------------------------
//    static uint32_t getCmdResp7()
//    {
//        uint32_t count = cmdTimeout * (Rcc::systemCoreClock() / 8U / 1000U);

//        // Check for timeout
//        do {
//            if (!(--count))
//                return errTimeout;
//        } while (!((rg()->STA.CCRCFAIL) |
//                   rg()->STA.CMDREND |
//                   rg()->STA.CTIMEOUT));

//        if (rg()->STA.CTIMEOUT) {
//            rg()->ICR.CTIMEOUTC = 1;
//            return errCmdRspTimeout;
//        }
//        else if (rg()->STA.CMDREND) {
//            rg()->ICR.CMDRENDC = 1;    //Проверить сие непотребство
//         }

//        return errNone;
//    }


//    //---------------------------------------------------------------------
//    static uint32_t getCmdResp6(uint8_t cmd, uint16_t *pRca)
//    {
//        uint32_t count = cmdTimeout * (Rcc::systemCoreClock() / 8U / 1000U);

//        // Check for timeout
//        do {
//            if (!(--count))
//                return errTimeout;
//        } while (!((rg()->STA.CCRCFAIL) |
//                   rg()->STA.CMDREND |
//                   rg()->STA.CTIMEOUT));

//        if (rg()->STA.CTIMEOUT) {
//            rg()->ICR.CTIMEOUTC = 1;
//            return errCmdRspTimeout;
//        }
//        else if (rg()->STA.CCRCFAIL) {
//            rg()->ICR.CCRCFAILC = 1;
//            return errCmdCrcFail;
//        }

//        // Check response received is of desired command
//        if (getCommandResponce() != cmd) {
//            return errCmdCrcFail;
//        }

//        clearStaticFlags();

//        uint32_t responceR6;
//        responceR6 = getResponse(1);

//        if (responceR6 & r6IllegalCmd) {
//            return errIllegalCmd;
//        }
//        else if (responceR6 & r6ComCrcFailed) {
//            return errComCrcFailed;
//        }
//        else if (responceR6 & r6GeneralUnknownError) {
//            return errGeneralUnknownErr;
//        }

//        *pRca = static_cast<uint16_t>(responceR6 >> 16);

//        return errNone;
//    }




    //---------------------------------------------------------------------
//    static uint32_t getCmdResp3()
//    {
//        uint32_t count = cmdTimeout * (Rcc::systemCoreClock() / 8U / 1000U);

//        // Check for timeout
//        do {
//            if (!(--count))
//                return errTimeout;
//        } while (!((rg()->STA.CCRCFAIL) |
//                   rg()->STA.CMDREND |
//                   rg()->STA.CTIMEOUT));

//        if (rg()->STA.CTIMEOUT) {
//            rg()->ICR.CTIMEOUTC = 1;
//            return errCmdRspTimeout;
//        }

//        clearStaticFlags();
//        return errNone;
//    }

    //---------------------------------------------------------------------
//    static uint32_t getCmdResp2()
//    {
//        uint32_t count = cmdTimeout * (Rcc::systemCoreClock() / 8U / 1000U);

//        // Check for timeout
//        do {
//            if (!(--count))
//                return errTimeout;
//        } while (!((rg()->STA.CCRCFAIL) |
//                   rg()->STA.CMDREND |
//                   rg()->STA.CTIMEOUT));

//        if (rg()->STA.CTIMEOUT) {
//            rg()->ICR.CTIMEOUTC = 1;
//            return errCmdRspTimeout;
//        }
//        else if (rg()->STA.CCRCFAIL) {
//            rg()->ICR.CCRCFAILC = 1;
//            return errCmdCrcFail;
//        }

//        clearStaticFlags();
//        return errNone;
//    }

//    //---------------------------------------------------------------------
//    static uint32_t getCmdResp1(uint8_t cmd, uint32_t timeout)
//    {
//        uint32_t count = timeout * (Rcc::systemCoreClock() / 8U / 1000U);

//        // Check for timeout
//        do {
//            if (!(--count))
//                return errTimeout;
//        } while (!((rg()->STA.CCRCFAIL) |
//                   rg()->STA.CMDREND |
//                   rg()->STA.CTIMEOUT));

//        if (rg()->STA.CTIMEOUT) {
//            rg()->ICR.CTIMEOUTC = 1;
//            return errCmdRspTimeout;
//        }
//        else if (rg()->STA.CCRCFAIL) {
//            rg()->ICR.CCRCFAILC = 1;
//            return errCmdCrcFail;
//        }

//        // Check response received is of desired command
//        if (getCommandResponce() != cmd) {
//            return errCmdCrcFail;
//        }

//        clearStaticFlags();

//        CardStatus responceR1;
//        Utility::asWord(responceR1) = getResponse(1);

//        // No errors
//        if (!(Utility::asWord(responceR1) & cardStatusErrorBits)) {
//            return errNone;
//        }
//        else if (responceR1.addressOutOfRange) {
//            return errAddrOutOfRange;
//        }
//        else if (responceR1.addressMisalign) {
//            return errAddrMisaligned;
//        }
//        else if (responceR1.blockLenError) {
//            return errBlockLenErr;
//        }
//        else if (responceR1.eraseSeqError) {
//            return errEraseSeqErr;
//        }
//        else if (responceR1.eraseParam) {
//            return errBadEraseParam;
//        }
//        else if (responceR1.wpViolation) {
//            return errWriteProtViolation;
//        }
//        else if (responceR1.lockUnlockFailed) {
//            return errLockUnlockFailed;
//        }
//        else if (responceR1.comCrcError) {
//            return errComCrcFailed;
//        }
//        else if (responceR1.illegalCommand) {
//            return errIllegalCmd;
//        }
//        else if (responceR1.cardEccFailed) {
//            return errCardEccFailed;
//        }
//        else if (responceR1.ccError) {
//            return errCcErr;
//        }
//        else if (responceR1.streamReadUnderrun) {
//            return errStreamReadUnderrun;
//        }
//        else if (responceR1.streamWriteOverrun) {
//            return errStreamWriteOverrun;
//        }
//        else if (responceR1.cidCsdOverwrite) {
//            return errCidCsdOverwrite;
//        }
//        else if (responceR1.wpEraseSkip) {
//            return errWpEraseSkip;
//        }
//        else if (responceR1.cardEccDisabled) {
//            return errCardEccDisabled;
//        }
//        else if (responceR1.eraseReset) {
//            return errEraseReset;
//        }
//        else if (responceR1.akeSeqError) {
//            return errAkeSeqErr;
//        }
//        else {
//            return errGeneralUnknownErr;
//        }
//    }


};

#endif // SDIO_H
