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
  uint8_t m_speed;
  uint8_t m_red;
  uint8_t m_green;
  uint8_t m_blue;
};
