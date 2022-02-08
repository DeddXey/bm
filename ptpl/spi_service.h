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

  template<typename T, typename S>
  bool transaction_sync_int(T &input, S &out, uint32_t timeout_ms = 100)
  {
    auto in_ptr   = std::begin(input);
    auto out_ptr  = std::begin(out);
    bool flag_in  = false;
    bool flag_out = false;
    //    uint32_t prev     = T::systick_service;
    // TODO: @alex add timeout


    I::If::enable(true);

    for (;;) {

      if (in_ptr != std::end(input)) {
        if (I::If::is_tx_empty()) {
//          con.debug() << "DR <- " << *in_ptr << Use::endl;
          I::If::set_dr(*in_ptr++);
        }
      }
      else {
        flag_in = true;
      }

      if (out_ptr != std::end(out)) {
        if (I::If::is_rx_not_empty()) {

          *out_ptr = I::If::get_dr();
//          con.debug() << "DR -> " << *out_ptr << Use::endl;
          out_ptr++;
        }
        if (flag_in) {
          if (I::If::is_tx_empty()) {
//            con.debug() << "DR <- (0)" << Use::endl;
            I::If::set_dr(0);
          }
        }
      }
      else {
        flag_out = true;
      }
      if (flag_in && flag_out)
        break;
    }

    while (I::If::is_busy()) {}

    I::If::enable(false);

    return true;
  }
};

#endif // SPI_SERVICE_H
