#pragma once

#include "Effect.h"

class PurpleFirefliesEffect : public Effect {
public:
  PurpleFirefliesEffect(Lamp* lamp)
    : Effect(lamp) {}

  void init(size_t led_count) override;

  void tick() override;

  void action_tick(bool reverse) override;

private:
  uint8_t m_fireflies_counter = 0;

  const int8_t MAX_BUFFER_SIZE = 400 / STEP_TIMEOUT;
  int8_t m_buffer = 0;

  uint8_t m_speed;

  const int8_t MAX_BUFFER_SIZE_SPEED = 250 / STEP_TIMEOUT;
  int8_t m_buffer_speed = 0;

  const uint32_t FIREFLY_COLOR = Lamp::calc_color(100, 20, 140);
};
