#ifndef SPI_SERVICE_H
#define SPI_SERVICE_H

#include "sync.h"
#include <cstdint>
#include <iterator>

struct SpiDevice
{
  uint8_t  cs_port;
  uint8_t  cs_pin;
  uint32_t baudrate;
};

template<typename I>
class SpiService
{
protected:
  tl::spinlock_mutex mtx;

public:
  void init()
  {
    static_cast<I *>(this)->init();
  }

  template<typename T>
  bool transaction_sync_int(T &input, T &out, uint32_t timeout_ms = 100)
  {
    auto     in_ptr   = std::begin(input);
    auto     out_ptr  = std::begin(out);
    bool     flag_in  = false;
    bool     flag_out = false;
    uint32_t prev     = T::systick_service;
    // TODO: @alex add timeout


    for (;;) {

      if (I::If::is_tx_empty()) {

        if (in_ptr != std::end(input)) {
          I::If::set_dr(*in_ptr++);
        }
        else {
          flag_in = true;
        }
      }
      if (I::If::is_rx_not_empty()) {

        if (out_ptr != std::end(out)) {
          *in_ptr++ = I::If::get_dr();
        }
        else {
          flag_out = true;
        }
      }
      if (flag_in && flag_out)
        return true;



    }
  }
};

#endif // SPI_SERVICE_H
