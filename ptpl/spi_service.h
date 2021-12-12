#ifndef SPI_SERVICE_H
#define SPI_SERVICE_H

#include <cstdint>
#include <iterator>
#include "sync.h"

template<typename I>
class SpiService
{
  tl::spinlock_mutex mtx;
public:
  void init()
  {
    I::init();
  }

  template<typename T>
  bool
  transaction_sync(typename I::Cs cs, T &in, T &out, uint32_t timeout_ms = 100)
  {
    auto     in_ptr   = std::begin(in);
    auto     out_ptr  = std::begin(out);
    bool     flag_in  = false;
    bool     flag_out = false;
    uint32_t prev     = T::systick_service;

    mtx.lock();
    I::cs_select(cs);

    for (;;) {

      if (I::If::is_tx_empty()) {

        if (in_ptr != std::end(in)) {
          I::If::set_dr(*in_ptr++);
        }
        else {
          flag_in = true;
        }
      }
      if (I::If::is_rx_notempty()) {

        if (out_ptr != std::end(out)) {
          *in_ptr++ = I::If::get_dr();
        }
        else {
          flag_out = true;
        }
      }
      if (flag_in && flag_out)
        break;
    }
    cs_select(I::Cs::none);
    mtx.unlock();
  }
};

#endif // SPI_SERVICE_H
