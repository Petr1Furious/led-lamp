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
  int16_t m_speed;
};
