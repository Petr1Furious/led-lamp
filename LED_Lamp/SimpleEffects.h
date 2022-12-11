#pragma once

#include "Effect.h"

class StaticColorEffect : public Effect {
public:
  StaticColorEffect(Lamp* lamp)
    : Effect(lamp){};

  void init(size_t led_count) override;

  void tick() override;

  void action_tick(bool reverse) override;

private:
  int16_t m_hue_counter;
};

class FlowingColorEffect : public Effect {
public:
  FlowingColorEffect(Lamp* lamp)
    : Effect(lamp) {}

  void init(size_t led_count) override;

  void tick() override;

  void action_tick(bool reverse) override;

private:
  int16_t m_overflowing_colors_counter;
  int16_t m_speed;
  // uint8_t m_red;
  // uint8_t m_green;
  // uint8_t m_blue;
};

class WarmWhiteEffect : public Effect {
public:
  WarmWhiteEffect(Lamp* lamp)
    : Effect(lamp) {}

  void init(size_t led_count) override;

  void tick() override;

  void action_tick(bool reverse) override;

private:
  int16_t m_warm_level;
};
