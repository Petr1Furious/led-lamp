#pragma once

#include "Effect.h"

class FireEffect : public Effect {
public:
  FireEffect(Lamp* lamp)
    : Effect(lamp) {}

  void init(size_t led_count) override;

  void tick() override;

  void action_tick(bool reverse) override;

private:
  const uint8_t RED_GRADIENT = 230;
  const uint8_t GREEN_GRADIENT = 24;
  const int8_t GRADIENT_RANGE = 10;
  const uint8_t MAX_GREEN_INCREASE = 150;
  const uint8_t FIRE_SOURCE_SIZE = LED_STRIP_LENGTH / 3 + 1;
  const uint16_t MAX_FIRE_DELAY = 500;

  uint8_t m_target_fire_height = 0;
  uint8_t m_cur_fire_height = 0;
  uint32_t m_next_burst = 0;

  const uint16_t MAX_ASCENDING_BUFFER_SIZE = 30 / STEP_TIMEOUT;
  uint8_t m_ascending_buffer = 0;
  const uint16_t MAX_DESCENDING_BUFFER_SIZE = 10 / STEP_TIMEOUT;
  uint8_t m_descending_buffer = 0;
};
