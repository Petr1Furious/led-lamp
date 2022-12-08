#include "SimpleEffects.h"
#include "Lamp.h"
#include <EEPROM.h>

void StaticColorEffect::init(size_t led_count) {
  m_static_color_counter = constrain(((uint16_t)EEPROM.read(4) << 8) + (uint16_t)EEPROM.read(5), 0, (3 << 8) - 1);
}

void StaticColorEffect::tick() {
  // TODO
  // for demonstration purposes:
  m_lamp->set_color_led(0, Lamp::calc_color(255, 0, 0));
}

void StaticColorEffect::action_tick(bool reverse) {
  // TODO
}

void FlowingColorEffect::init(size_t led_count) {
  m_overflowing_colors_counter = constrain(((uint16_t)EEPROM.read(6) << 8) + (uint16_t)EEPROM.read(7), 0, (3 << 8) - 1);
}

void FlowingColorEffect::tick() {
  // TODO
  // for demonstration purposes:
  m_lamp->set_color_led(0, Lamp::calc_color(0, 255, 0));
}

void FlowingColorEffect::action_tick(bool reverse) {
  // TODO
}

void WarmWhiteEffect::init(size_t led_count) {
  m_warm_level = constrain(EEPROM.read(8), 0, 255);
}

void WarmWhiteEffect::tick() {
  // TODO
  // for demonstration purposes:
  m_lamp->set_color_led(0, Lamp::calc_color(0, 0, 255));
}

void WarmWhiteEffect::action_tick(bool reverse) {
  // TODO
}
