#ifndef I2C_H
#define I2C_H
#include "nvic.h"
#include "rcc.h"
#include "terminal.h"
#include "utility"

#include <cstdint>

template<int num>
struct i2c_t;

template<>
struct i2c_t<1>
{
  constexpr static uint32_t      base = 0x40005400;
  constexpr static Nvic::IrqType event_irq =
    Nvic::itI2c1Ev; ///< I2C1 event global interrupt
  constexpr static Nvic::IrqType error_irq =
    Nvic::itI2c1Er; ///< I2C1 error global interrupt

  static void enable_clock(const bool en)
  {
    Rcc::clockI2c1(en);
  }

  static void reset(const bool en)
  {
    Rcc::resetI2c1(en);
  }
};

template<>
struct i2c_t<2>
{
  constexpr static uint32_t      base = 0x40005800;
  constexpr static Nvic::IrqType event_irq =
    Nvic::itI2c2Ev; ///< I2C1 event global interrupt
  constexpr static Nvic::IrqType error_irq =
    Nvic::itI2c2Er; ///< I2C1 error global interrupt

  static void enable_clock(const bool en)
  {
    Rcc::clockI2c2(en);
  }
  static void reset(const bool en)
  {
    Rcc::resetI2c2(en);
  }
};

struct i2c_common
{

  struct regs
  {
    uint32_t CR1;   //< 0x0 Control register 1
    uint32_t CR2;   //< 0x4 Control register 2
    uint32_t OAR1;  //< 0x8 Own address register 1
    uint32_t OAR2;  //< 0xC Own address register 2
    uint32_t DR;    //< 0x10 Data register
    uint32_t SR1;   //< 0x14 Status register 1
    uint32_t SR2;   //< 0x18 Status register 2
    uint32_t CCR;   //< 0x1C Clock control register
    uint32_t TRISE; //< 0x20 TRISE register
  };

  struct CR1
  {
    constexpr static uint8_t SWRST[]{ 15, 1 }; //< Software reset
    constexpr static uint8_t ALERT[]{ 13, 1 }; //< SMBus alert
    constexpr static uint8_t PEC[]{ 12, 1 };   //< Packet error checking
    constexpr static uint8_t POS[]{
      11,
      1
    }; //< Acknowledge/PEC Position (for data reception)
    constexpr static uint8_t ACK[]{ 10, 1 };  //< Acknowledge enable
    constexpr static uint8_t STOP[]{ 9, 1 };  //< Stop generation
    constexpr static uint8_t START[]{ 8, 1 }; //< Start generation
    constexpr static uint8_t NOSTRETCH[]{
      7,
      1
    }; //< Clock stretching disable (Slave mode)
    constexpr static uint8_t ENGC[]{ 6, 1 };    //< General call enable
    constexpr static uint8_t ENPEC[]{ 5, 1 };   //< PEC enable
    constexpr static uint8_t ENARP[]{ 4, 1 };   //< ARP enable
    constexpr static uint8_t SMBTYPE[]{ 3, 1 }; //< SMBus type
    constexpr static uint8_t SMBUS[]{ 1, 1 };   //< SMBus mode
    constexpr static uint8_t PE[]{ 0, 1 };      //< Peripheral enable
  };

  struct CR2
  {
    constexpr static uint8_t LAST[]{ 12, 1 };    //< DMA last transfer
    constexpr static uint8_t DMAEN[]{ 11, 1 };   //< DMA requests enable
    constexpr static uint8_t ITBUFEN[]{ 10, 1 }; //< Buffer interrupt enable
    constexpr static uint8_t ITEVTEN[]{ 9, 1 };  //< Event interrupt enable
    constexpr static uint8_t ITERREN[]{ 8, 1 };  //< Error interrupt enable
    constexpr static uint8_t FREQ[]{ 0, 6 };     //< Peripheral clock frequency
  };

  struct OAR1
  {
    constexpr static uint8_t ADDMODE[]{ 15,
                                        +1 }; //< Addressing mode (slave mode)
    constexpr static uint8_t ADD10[]{ 8, 2 }; //< Interface address
    constexpr static uint8_t ADD7[]{ 1, 7 };  //< Interface address
    constexpr static uint8_t ADD0[]{ 0, 1 };  //< Interface address
  };

  struct OAR2
  {
    constexpr static uint8_t ADD2[]{ 1, 7 };   //< Interface address
    constexpr static uint8_t ENDUAL[]{ 0, 1 }; //< Dual addressing mode enable
  };

  struct DR
  {
    constexpr static uint8_t DR_[]{ 0, 8 }; //< 8-bit data register
  };

  struct SR1
  {
    constexpr static uint8_t SMBALERT[]{ 15, 1 }; //< SMBus alert
    constexpr static uint8_t TIMEOUT[]{ 14, 1 };  //< Timeout or Tlow error
    constexpr static uint8_t PECERR[]{ 12, 1 };   //< PEC Error in reception
    constexpr static uint8_t OVR[]{ 11, 1 };      //< Overrun/Underrun
    constexpr static uint8_t AF[]{ 10, 1 };       //< Acknowledge failure
    constexpr static uint8_t ARLO[]{ 9, 1 }; //< Arbitration lost (master mode)
    constexpr static uint8_t BERR[]{ 8, 1 }; //< Bus error
    constexpr static uint8_t TxE[]{ 7,
                                    1 }; //< Data register empty (transmitters)
    constexpr static uint8_t RxNE[]{
      6,
      1
    }; //< Data register not empty (receivers)
    constexpr static uint8_t STOPF[]{ 4, 1 }; //< Stop detection (slave mode)
    constexpr static uint8_t ADD10[]{ 3,
                                      1 };  //< 10-bit header sent (Master mode)
    constexpr static uint8_t BTF[]{ 2, 1 }; //< Byte transfer finished
    constexpr static uint8_t ADDR[]{
      1,
      1
    }; //< Address sent (master mode)/matched (slave mode)
    constexpr static uint8_t SB[]{ 0, 1 }; //< Start bit (Master mode)
  };

  struct SR2
  {
    constexpr static uint8_t PEC[]{ 8, 8 };   //< acket error checking register
    constexpr static uint8_t DUALF[]{ 7, 1 }; //< Dual flag (Slave mode)
    constexpr static uint8_t SMBHOST[]{ 6,
                                        1 }; //< SMBus host header (Slave mode)
    constexpr static uint8_t SMBDEFAULT[]{
      5,
      1
    }; //< SMBus device default address (Slave mode)
    constexpr static uint8_t GENCALL[]{
      4,
      1
    }; //< General call address (Slave mode)
    constexpr static uint8_t TRA[]{ 2, 1 };  //< Transmitter/receiver
    constexpr static uint8_t BUSY[]{ 1, 1 }; //< Bus busy
    constexpr static uint8_t MSL[]{ 0, 1 };  //< Master/slave
  };

  struct CCR
  {
    constexpr static uint8_t F_S[]{ 15, 1 };  //< I2C master mode selection
    constexpr static uint8_t DUTY[]{ 14, 1 }; //< Fast mode duty cycle
    constexpr static uint8_t CCR_[]{
      0,
      12
    }; //< Clock control register in Fast/Standard mode (Master mode)
  };

  struct TRISE
  {
    constexpr static uint8_t TRISE_[]{
      0,
      6
    }; //< Maximum rise time in Fast/Standard mode (Master mode)
  };
};

template<int num>
struct i2c_ll
{

  /// \brief Получение указателя на регистры
  /// \return указатель на регистры
  static volatile i2c_common::regs *rg()
  {
    return reinterpret_cast<volatile i2c_common::regs *volatile>(
      i2c_t<num>::base);
  }

  static void enable_clock(const bool val)
  {
    i2c_t<num>::enable_clock(val);
  }

  static void reset(const bool val)
  {
    i2c_t<num>::reset(val);
  }

  static void set_stop(bool val)
  {
    tl::setRegister(rg()->CR1, i2c_common::CR1::STOP, val);
  }

  static void set_start(bool val)
  {
    tl::setRegister(rg()->CR1, i2c_common::CR1::START, val);
  }

  static void set_ack(bool val)
  {
    tl::setRegister(rg()->CR1, i2c_common::CR1::ACK, val);
  }

  static void set_buffer_interrupt(bool val)
  {
    tl::setRegister(rg()->CR2, i2c_common::CR2::ITBUFEN, val);
  }

  static void set_event_interrupt(bool val)
  {
    tl::setRegister(rg()->CR2, i2c_common::CR2::ITEVTEN, val);
  }

  static void set_error_interrupt(bool val)
  {
    tl::setRegister(rg()->CR2, i2c_common::CR2::ITERREN, val);
  }

  static void set_fast_mode(bool val)
  {
    tl::setRegister(rg()->CCR, i2c_common::CCR::F_S, val);
  }

  static void set_apb_freq(uint8_t freq)
  {
    tl::setRegister(rg()->CR2, i2c_common::CR2::FREQ, freq);
  }

  static void set_clock_control(uint16_t val)
  {
    tl::setRegister(rg()->CCR, i2c_common::CCR::CCR_, val);
  }

  static void set_duty(bool val)
  {
    tl::setRegister(rg()->CCR, i2c_common::CCR::DUTY, val);
  }

  static void set_maximum_rise_time(uint16_t val)
  {
    tl::setRegister(rg()->TRISE, i2c_common::TRISE::TRISE_, val);
  }

  static void enable(bool val)
  {
    tl::setRegister(rg()->CR1, i2c_common::CR1::PE, val);
  }

  static uint8_t read_data_register()
  {
    uint8_t value = rg()->DR;
    con.debug() << Fg::green << "i2c write: " << Use::hex << Use::w2 << value
                << "\n"
                << Attr::reset;
    return value;
  }

  static void write_data_register(uint8_t value)
  {
    con.debug() << Fg::green << "i2c write: " << Use::hex << Use::w2 << value
                << "\n"
                << Attr::reset;
    rg()->DR = value;
  }

  static bool is_busy()
  {
    return tl::getRegField(rg()->SR2, i2c_common::SR2::BUSY);
  }

  static uint32_t get_status1()
  {
    return rg()->SR1;
  }

  static uint32_t get_status2()
  {
    return rg()->SR2;
  }

  static void clear_status1()
  {
    rg()->SR1 = 0;
  }

  static void clear_status2()
  {
    rg()->SR1 = 0;
  }
  static bool is_overrun(uint32_t sr1)
  {
    return tl::getRegField(sr1, i2c_common::SR1::OVR);
  }

  static bool is_overrun()
  {
    return tl::getRegField(rg()->SR1, i2c_common::SR1::OVR);
  }

  static bool is_ask_failed(uint32_t sr1)
  {
    return tl::getRegField(sr1, i2c_common::SR1::AF);
  }

  static bool is_ask_failed()
  {
    return tl::getRegField(rg()->SR1, i2c_common::SR1::AF);
  }

  static bool is_arbitration_lost(uint32_t sr1)
  {
    return tl::getRegField(sr1, i2c_common::SR1::ARLO);
  }

  static bool is_arbitration_lost()
  {
    return tl::getRegField(rg()->SR1, i2c_common::SR1::ARLO);
  }

  static bool is_bus_error(uint32_t sr1)
  {
    return tl::getRegField(sr1, i2c_common::SR1::BERR);
  }

  static bool is_bus_error()
  {
    return tl::getRegField(rg()->SR1, i2c_common::SR1::BERR);
  }

  static bool is_start(uint32_t sr1)
  {
    return tl::getRegField(sr1, i2c_common::SR1::SB);
  }

  static bool is_start()
  {
    return tl::getRegField(rg()->SR1, i2c_common::SR1::SB);
  }

  static bool is_enable()
  {
    return tl::getRegField(rg()->CR1, i2c_common::CR1::PE);
  }

  static bool is_address_sent(uint32_t sr1)
  {
    return tl::getRegField(sr1, i2c_common::SR1::ADDR);
  }

  static bool is_address_sent()
  {
    return tl::getRegField(rg()->SR1, i2c_common::SR1::ADDR);
  }

  static bool is_receive_register_not_empty(uint32_t sr1)
  {
    return tl::getRegField(sr1, i2c_common::SR1::RxNE);
  }

  static bool is_receive_register_not_empty()
  {
    return tl::getRegField(rg()->SR1, i2c_common::SR1::RxNE);
  }

  static bool is_transmit_register_empty(uint32_t sr1)
  {
    return tl::getRegField(sr1, i2c_common::SR1::TxE);
  }

  static bool is_transmit_register_empty()
  {
    return tl::getRegField(rg()->SR1, i2c_common::SR1::TxE);
  }
  static bool is_byte_transfer_finished(uint32_t sr1)
  {
    return tl::getRegField(sr1, i2c_common::SR1::RxNE);
  }

  static bool is_byte_transfer_finished()
  {
    return tl::getRegField(rg()->SR1, i2c_common::SR1::RxNE);
  }
  static void set_next_byte_ask()
  {
    tl::setRegister(rg()->CR1, i2c_common::CR1::POS, 1);
  }

  static Nvic::IrqType get_irq_event_number()
  {
    return i2c_t<num>::event_irq;
  }

  static Nvic::IrqType get_irq_error_number()
  {
    return i2c_t<num>::error_irq;
  }
};

template<typename I>
class i2c
{
  uint8_t dev_address;
  //  uint8_t  reg_address;
  uint8_t *write_buffer;
  uint16_t bytes_to_write;
  uint8_t *read_buffer;
  uint16_t bytes_to_read;
  uint16_t write_index;
  uint16_t read_index;
  //  bool     read;
  //  bool     slave;
  bool ready;
  bool error;

  using device = typename I::device;

public:
  void init()
  {
    I::init();
    device::enable_clock(false);
    device::enable_clock(true);

    device::reset(true);
    device::reset(false);

    set_timing(I::t_hi_100ns, I::t_lo_100ns);

    if constexpr (I::use_interrupt) {
      //      device::set_error_interrupt(true);
      //      device::set_event_interrupt(true);

      Nvic::setPriority(device::get_irq_event_number(), I::interrupt_priority);
      Nvic::setPriority(device::get_irq_error_number(), I::interrupt_priority);
      Nvic::enableIrq(device::get_irq_event_number());
      Nvic::enableIrq(device::get_irq_error_number());
    }
  }

  /// \brief Set timing for i2c signals
  /// \param t_hi_100ns hi timing in 100ns intervals
  /// \param t_lo_100ns low timing in 100ns intervals
  void set_timing(uint32_t t_hi_100ns, uint32_t t_lo_100ns)
  {
    bool fast_mode = false;
    bool duty      = false;

    device::enable(false);

    if ((t_hi_100ns < 10) | (t_lo_100ns < 10)) {
      fast_mode = true;
    }

    const uint32_t freq_khz = Rcc::apb1Clk() / 1000;

    device::set_apb_freq(freq_khz / 1000);
    device::set_fast_mode(fast_mode);

    uint32_t ccr_hi = (freq_khz * t_hi_100ns) / 10000;
    uint32_t ccr_lo = (freq_khz * t_lo_100ns) / 10000;

    if (fast_mode) {
      const int32_t ratio = abs((t_hi_100ns * 2 * 100) / t_lo_100ns - 100);
      const int32_t ratio_duty =
        abs((t_hi_100ns * 16 * 100) / (t_lo_100ns * 9) - 100);

      if (ratio > ratio_duty) {
        duty = true;
      }
      if (duty) {
        ccr_hi = (freq_khz * t_hi_100ns) / 90000;
        ccr_lo = (freq_khz * t_lo_100ns) / 160000;
      }
      else {
        ccr_hi = (freq_khz * t_hi_100ns) / 10000;
        ccr_lo = (freq_khz * t_lo_100ns) / 20000;
      }
    }
    uint32_t ccr = std::max(ccr_hi, ccr_lo);
    device::set_duty(duty);
    device::set_clock_control(ccr);

    uint32_t trise = (freq_khz * t_hi_100ns) / 100000 + 1;
    device::set_maximum_rise_time(trise);

    //    device::enable(true);
  }

  bool is_write_complete()
  {
    return (bytes_to_write == write_index);
  }

  bool is_read_complete()
  {
    return (bytes_to_read == read_index);
  }

  bool is_request_complete()
  {
    return ready;
  }

  bool is_request_error()
  {
    return error;
  }

  bool request(const uint8_t  dev_addr,
               const uint8_t *wr_buffer,
               const uint16_t bytes_to_write,
               uint8_t       *rd_buffer,
               const uint16_t bytes_to_read)
  {
    this->dev_address    = dev_addr;
    this->write_buffer   = const_cast<uint8_t *>(wr_buffer);
    this->bytes_to_write = bytes_to_write;
    this->read_buffer    = rd_buffer;
    this->bytes_to_read  = bytes_to_read;
    this->read_index     = 0;
    this->write_index    = 0;

    this->ready = false;
    this->error = false;

    device::set_stop(false);

    uint32_t counter = 0xfffff;

    while (counter) {

      --counter;
      if (!(device::is_busy())) {

        if (!device::is_enable())
          device::enable(true);

        device::set_ack(true);
        device::set_event_interrupt(true);
        device::set_error_interrupt(true);

        //        device::clear_status1();
        //        device::clear_status2();

        device::set_start(true);

        return true;
      }
    }
    return false;
  }

  bool request_block(const uint8_t  dev_addr,
                     const uint8_t *wr_buffer,
                     const uint16_t bytes_to_write,
                     uint8_t       *rd_buffer,
                     const uint16_t bytes_to_read)
  {

    if (!request(dev_addr,
                 wr_buffer,
                 bytes_to_write,
                 rd_buffer,
                 bytes_to_read)) {
      con.debug() << "requestBlockError 1\n";
      return false;
    }

    while (!is_request_complete()) {
      tl::simpleDelay(200);
    };

    if (is_request_error()) {
      con.debug() << "requestBlockError 2\n";
      return false;
    }
    return true;
  }

  void error_handler()
  {
    uint32_t status1 = device::get_status1();
    uint32_t status2 = device::get_status2();

    con.error() << Fg::red << "I2C Error\n";
    con.error() << Use::hex << status1 << ":" << status2 << Use::endl;

    if (device::is_overrun(status1)) {
      con.error() << Fg::red << "OVERRUN ERROR\n" << Attr::reset;
    }
    if (device::is_ask_failed(status1)) {
      con.error() << Fg::red << "NO ASK ERROR\n" << Attr::reset;
    }
    if (device::is_arbitration_lost(status1)) {
      con.error() << Fg::red << "ARBITRATION LOST ERROR\n" << Attr::reset;
    }
    if (device::is_bus_error(status1)) {
      con.error() << Fg::red << "BUS ERROR\n" << Attr::reset;
    }

    error = true;
    device::clear_status1();
    device::clear_status2();
    device::enable(false);
  }

  void event_handler()
  {
    uint32_t status1 = device::get_status1();
    con.debug() << Fg::yellow << "i2c irq\n" << Attr::reset;

    //-------------------------------------------------------------
    // Ev5
    if (device::is_start(status1)) {
      con.debug() << Fg::green << "i2c start\n" << Attr::reset;
      device::set_buffer_interrupt(false);

      if (!is_write_complete()) {
        device::write_data_register(dev_address);
      }
      else {
        if ((bytes_to_read == 2)) {
          device::set_next_byte_ask();
        }
        device::write_data_register(dev_address | 1);
      }
      return;
    }

    //-------------------------------------------------------------
    // Ev6
    volatile uint32_t status2;
    if (device::is_address_sent(status1)) {
      con.debug() << Fg::green << "i2c address sent\n" << Attr::reset;

      // Write data
      if (!is_write_complete()) {
        status2 = device::get_status2();
        status2;
        device::write_data_register(write_buffer[write_index++]);

        if (is_write_complete()) {

          if (is_read_complete()) {
            device::set_stop(true);
            ready = true;
          }
          else {
            device::set_start(true);
          }
        }
      }
      else {

        // Read
        switch (bytes_to_read) {

        case 1:
          device::set_ack(false);
          status2 = device::get_status2();
          device::set_stop(true);
          device::set_buffer_interrupt(true);
          break;

        case 2:
          status2 = device::get_status2();
          device::set_ack(false);
          break;

        default:
          status2 = device::get_status2();
        }
      }
      return;
    }

    // TODO: add slave

    //-------------------------------------------------------------
    // Ev7
    if (device::is_receive_register_not_empty(status1)) {
      con.debug() << Fg::green << "i2c RxNE\n" << Attr::reset;

      switch (bytes_to_read - read_index) {
      default:
        if (device::is_byte_transfer_finished(status1)) {
          read_buffer[read_index++] = device::read_data_register();
        }
        break;
      case 3:
        if (device::is_byte_transfer_finished(status1)) {
          device::set_ack(false);
          read_buffer[read_index++] = device::read_data_register();
        }
        break;

      case 2:
        if (device::is_byte_transfer_finished(status1)) {
          device::set_stop(true);
          device::set_ack(false);
          read_buffer[read_index++] = device::read_data_register();
          read_buffer[read_index++] = device::read_data_register();
          ready                     = true;
        }
        break;
      case 1:
        read_buffer[read_index++] = device::read_data_register();
        ready                     = true;
        break;
      }
    }

    //-------------------------------------------------------------
    // Ev8 Tx is empty
    if (device::is_transmit_register_empty(status1)) {
      con.debug() << Fg::green << "i2c TxE\n" << Attr::reset;

      if (is_write_complete()) {

        if (is_read_complete()) {
          device::set_stop(true);
          ready = true;
        }
        else {
          device::set_start(true);
        }
      }
      else {
        device::write_data_register(write_buffer[write_index]);
        write_index++;
      }
      return;
    }
  }

  Nvic::IrqType get_irq_event_number()
  {
    return device::event_irq;
  }

  Nvic::IrqType get_irq_error_number()
  {
    return device::error_irq;
  }
};

#endif //  I2C_H
