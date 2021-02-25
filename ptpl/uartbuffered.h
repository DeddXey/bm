#ifndef UARTBUFFERED_H
#define UARTBUFFERED_H


#include "usart.h"
#include "fifo.h"

template <typename Port,
          int sizeTx = 255,
          int sizeRx = 255>
class UartBuffered {

    Fifo<uint8_t, sizeTx> txBuffer;
    Fifo<uint8_t, sizeRx> rxBuffer;
    bool txIdle = true; ///< Флаг опустошения очереди.
    bool rxIdle = false; ///< Флаг опустошения очереди.
    bool ovr = false;


public:
    using UPort = Port;

    //------------------------------------------------------------------------
    Fifo<uint8_t, sizeRx>& getRxFifo()
    {
        return rxBuffer;
    }

    //------------------------------------------------------------------------
    bool overrun() const
    {
        return ovr;
    }

    //------------------------------------------------------------------------
    void clearRxQueue()
    {
        rxBuffer.clear();
    }

    //------------------------------------------------------------------------
    void clearTxQueue()
    {
        txBuffer.clear();
    }

    //------------------------------------------------------------------------
    void clearOverrun()
    {
        ovr = false;
    }

    //------------------------------------------------------------------------
    bool empty() const
    {
        return getRxFifo().empty();
    }

    //------------------------------------------------------------------------
    Fifo<uint8_t, sizeTx>& getTxFifo()
    {
        return txBuffer;
    }

    //------------------------------------------------------------------------
    bool& getTxIdle()
    {
        return txIdle;
    }

    //------------------------------------------------------------------------
    bool& getRxIdle()
    {
        return txIdle;
    }

    //------------------------------------------------------------------------
    void putChar(const uint8_t ch)
    {
        if (getTxIdle()) {
            getTxIdle() = false;
            Port::putDr(ch);
            Port::setTxEmptyIt(true);
        }
        else {
            while(!getTxFifo().push(ch));
        }
    }

    //------------------------------------------------------------------------
    bool getChar(uint8_t & out)
    {
        if (getRxFifo().empty())
            return false;

        Port::setRxNotEmptyIt(true);

        out = getRxFifo().getOut();
        getRxFifo().pop();
        return true;

    }

    //------------------------------------------------------------------------
    int getTxFifoCapacity()
    {
        return getTxFifo().size();
    }

    //------------------------------------------------------------------------
    void irqHandler()
    {
        if (Port::isOverrun()) {
            ovr = true;
        }


        if (Port::isTxEmpty()) {

            if (getTxFifo().empty()) {
                getTxIdle() = true;
                Port::setTxEmptyIt(false);
            }
            else {
                Port::putDr(getTxFifo().getOut());
                getTxFifo().pop();
            }
        }

        if (Port::isRxNotEmpty()) {
            if (getRxFifo().full()) {
                Port::setRxNotEmptyIt(false);
            }
            //            else {
            volatile uint8_t d = Port::getDr();
            getRxFifo().push(d);
            //            }
        }
    }
};




#endif // UARTBUFFERED_H
