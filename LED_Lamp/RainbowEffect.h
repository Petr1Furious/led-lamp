#pragma once

#include "Effect.h"

class RainbowEffect : public Effect {
public:
  RainbowEffect(Lamp* lamp)
    : Effect(lamp) {}

  void init(size_t led_count) override;

  void tick() override;

  void action_tick(bool reverse) override;

private:
  int16_t m_rainbow_counter;
  uint16_t m_last_save;
  
  int8_t m_speed;

  const int8_t MAX_BUFFER_SIZE = 200 / STEP_TIMEOUT;
  int8_t m_buffer = 0;
};
