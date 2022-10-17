#ifndef TICK_SERVICE_H
#define TICK_SERVICE_H

template<typename I>
class TickService
{
  uint32_t system_ticks = 0;

public:
  void init()
  {
    I::init();
  }

  void irq_handler()
  {
    ++system_ticks;
  }

  void delay_ms(uint32_t ms)
  {
    const uint32_t prev = get_ticks();
    while ((get_ticks() - prev) < ms) {}
  }

  uint32_t get_ticks()
  {
    return system_ticks;
  }
};

template<typename Tick>
class DelayTimer
{

  Tick    &tick_;
  uint32_t start_ticks;
  uint32_t delay;
  bool     in_progress = false;

public:
  DelayTimer(Tick &tick) : tick_(tick) {}

  void start(uint32_t ms) noexcept
  {
    start_ticks = tick_.get_ticks();
    delay       = ms;
    in_progress = true;
  }

  bool is_expired()
  {
    if (in_progress) {
      if ((tick_.get_ticks() - start_ticks) >= delay) {
        in_progress = false;
//        con.debug() << "DelayTimerExpired\n";
        return true;
      }
    }
    return false;
  }
};

template<typename T>
DelayTimer<T> make_delay_timer(T& tick_service)
{
  return DelayTimer<T>(tick_service);
}

#endif // TICK_SERVICE_H
