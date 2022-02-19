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
  tl::spinlock_mutex    mtx;
  constexpr static bool with_print = true;

public:
  void init()
  {
    static_cast<I *>(this)->init();
  }

  template<typename T, typename S>
  bool transaction_sync_int(T                        &input,
                            S                        &out,
                            [[maybe_unused]] uint32_t timeout_ms = 100)
  {
    auto in_ptr      = std::begin(input);
    auto out_ptr     = std::begin(out);
    bool in_complete = false;
    //    uint32_t prev     = T::systick_service;
    // TODO: @alex add timeout

    I::If::enable(true);

    if (in_ptr != std::end(input)) {
      if constexpr (with_print) {
        con.debug() << "@DR <- " << Use::w2 << Use::hex << *in_ptr << Use::endl;
      }
      I::If::set_dr(*in_ptr++);
    }

    int32_t pushed = 1;
    for (;;) {

      if ((out_ptr == std::end(out)) && in_complete) {
        if constexpr (with_print) {
          con.debug() << "End\n";
        }
        break;
      }

      if (I::If::is_rx_not_empty()) {

        if ((out_ptr != std::end(out))) {
          if (I::If::is_overrun()) {
            con.debug() << "OVR!\n";
          }
          *out_ptr = I::If::get_dr();
          if constexpr (with_print) {
            con.debug() << "     DR -> " << Use::w2 << Use::hex << *out_ptr
                        << Use::endl;
          }
          pushed--;
          out_ptr++;
        }
        if (I::If::is_tx_empty()) {

          if (in_ptr != std::end(input)) {
            if constexpr (with_print) {
              con.debug() << " DR <- " << Use::w2 << Use::hex << *in_ptr
                          << Use::endl;
            }
            I::If::set_dr(*in_ptr++);
            pushed++;
          }
          else {
            in_complete = true;
            if constexpr (with_print) {
              con.debug() << "In complete" << Use::endl;
            }
            if ((out_ptr != std::end(out))) {
              if constexpr (with_print) {
                con.debug() << " DR <- (0)" << Use::endl;
              }
              I::If::set_dr(0);
              pushed++;
            }
          }
        }
      }
    }

    while (!I::If::is_tx_empty()) {}
    while (I::If::is_busy()) {}

    I::If::enable(false);

    con.debug() << Use::dec;
    return true;
  }
};

#endif // SPI_SERVICE_H
