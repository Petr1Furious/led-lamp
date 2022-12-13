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
  int16_t m_flowing_colors_counter;
  uint16_t m_last_save;

  uint8_t m_speed;

  const int8_t MAX_BUFFER_SIZE = 400 / STEP_TIMEOUT;
  int8_t m_buffer = 0;
};

class WarmWhiteEffect : public Effect {
public:
  WarmWhiteEffect(Lamp* lamp)
    : Effect(lamp) {}

  void init(size_t led_count) override;

  void tick() override;

  void action_tick(bool reverse) override;

private:
  int8_t m_color_temperature;

  const int8_t MAX_BUFFER_SIZE = 30 / STEP_TIMEOUT;
  int8_t m_buffer = 0;
};
