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

#endif // TICK_SERVICE_H
