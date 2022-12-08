#include "SimpleEffects.h"
#include "Lamp.h"
#include <EEPROM.h>

void StaticColorEffect::init(size_t led_count) {
  EEPROM.get(4, m_static_color_counter);
  m_static_color_counter = constrain(m_static_color_counter, 0, (3 << 8) - 1);
}

void StaticColorEffect::tick() {
  // TODO
  // for demonstration purposes:
  m_lamp->set_color_leds(Lamp::calc_color(255, just_for_testing, just_for_testing));
}

void StaticColorEffect::action_tick(bool reverse) {
  // TODO
  just_for_testing += reverse ? -1 : 1;
}

void FlowingColorEffect::init(size_t led_count) {
  EEPROM.get(6, m_overflowing_colors_counter);
  m_overflowing_colors_counter = constrain(m_overflowing_colors_counter, 0, (3 << 8) - 1);
}

void FlowingColorEffect::tick() {
  // TODO
  // for demonstration purposes:
  m_lamp->set_color_leds(0x00FF00);
}

void FlowingColorEffect::action_tick(bool reverse) {
  // TODO
}

void WarmWhiteEffect::init(size_t led_count) {
  m_warm_level = EEPROM.read(8);
}

void WarmWhiteEffect::tick() {
  // TODO
  // for demonstration purposes:
  m_lamp->set_color_leds(0x0000FF);
}

void WarmWhiteEffect::action_tick(bool reverse) {
  // TODO
}
