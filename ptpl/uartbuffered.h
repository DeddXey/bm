#pragma once

#include "fifo_atomic.h"
#include "usart.h"
#include "sync.h"

template<typename Port, int sizeTx = 255, int sizeRx = 255>
class UartBuffered
{

  tl::fifo_atomic<uint8_t, sizeTx> txBuffer;
  tl::fifo_atomic<uint8_t, sizeRx> rxBuffer;
  bool txIdle = true;  ///< Флаг опустошения очереди.
  bool rxIdle = false; ///< Флаг опустошения очереди.
  bool ovr    = false;

public:
  using UPort = Port;

  void init()
  {
    Port::init();
  }

  //    tl::fifo_atomic<uint8_t, sizeRx>& getRxFifo()
  auto getRxFifo() -> decltype(rxBuffer) &
  {
    return rxBuffer;
  }

  [[nodiscard]] bool overrun() const
  {
    return ovr;
  }

  void clearRxQueue()
  {
    rxBuffer.clear();
    Port::setRxNotEmptyIt(true);
  }

  void clearTxQueue()
  {
    txBuffer.clear();
  }

  void clearOverrun()
  {
    ovr = false;
  }

  [[nodiscard]] bool empty() const
  {
    return rxBuffer.empty();
  }

  //    tl::fifo_atomic<uint8_t, sizeTx>& getTxFifo()
  auto getTxFifo() -> decltype(txBuffer) &
  {
    return txBuffer;
  }

  bool &getTxIdle()
  {
    return txIdle;
  }

  bool &getRxIdle()
  {
    return txIdle;
  }

  void putChar(const uint8_t ch)
  {
    tl::critical_section cs;
    if (txIdle) {
      txIdle = false;
      Port::putDr(ch);
      Port::setTxEmptyIt(true);
    }
    else {
      while (!txBuffer.push(ch))
        ;
      //            getTxFifo().push(ch);
    }
  }

  bool getChar(uint8_t &out)
  {
    //      tl::critical_section cs;
//    if (rxBuffer.empty())
//      return false;
    auto const out_o = rxBuffer.getOut();
    if (out_o) {
      Port::setRxNotEmptyIt(true);
      out = out_o.value();
      rxBuffer.pop();
      return true;
    }
    return false;
  }

  int getTxFifoCapacity()
  {
    return txBuffer.size();
  }

  void irqHandler()
  {
    if (Port::isOverrun()) {
      ovr = true;
    }

    if (Port::isTxEmpty()) {

      auto out = txBuffer.getOut();
      if (out) {
        Port::putDr(out.value());
        txBuffer.pop();
      }
      else {
        txIdle = true;
        Port::setTxEmptyIt(false);
      }
    }

    if (Port::isRxNotEmpty()) {
      if (getRxFifo().full()) {
        Port::setRxNotEmptyIt(false);
      }
      //            else {
      uint8_t d = Port::getDr();
      getRxFifo().push(d);
      //            }
    }
  }
};


