#include "SimpleEffects.h"
#include "Lamp.h"
#include <EEPROM.h>

void StaticColorEffect::init(size_t led_count) {
  EEPROM.get(4, m_hue_counter);
  m_hue_counter = constrain(m_hue_counter, 0, (6 << 8) - 1);
}

void StaticColorEffect::tick() {
  m_lamp->set_color_leds(Lamp::get_hue(m_hue_counter));
}

void StaticColorEffect::action_tick(bool reverse) {
  m_hue_counter += reverse ? -(int16_t)STEP_TIMEOUT / 3 : STEP_TIMEOUT / 3;
  EEPROM.put(4, m_hue_counter);

  if (m_hue_counter >= (6 << 8)) {
    m_hue_counter -= 6 << 8;
  }
  if (m_hue_counter < 0) {
    m_hue_counter += (6 << 8);
  }
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
