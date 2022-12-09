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
  uint32_t m_overflowing_colors_counter;
};

class WarmWhiteEffect : public Effect {
public:
  WarmWhiteEffect(Lamp* lamp)
    : Effect(lamp) {}

  void init(size_t led_count) override;

  void tick() override;

  void action_tick(bool reverse) override;

private:
  uint8_t m_warm_level;
};
