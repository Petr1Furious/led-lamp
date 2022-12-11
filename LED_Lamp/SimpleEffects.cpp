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
  // EEPROM.get(6, m_overflowing_colors_counter);
  m_overflowing_colors_counter = constrain(m_overflowing_colors_counter, 0, (3 << 8) - 1);
  EEPROM.get(9, m_speed);
  // m_red = 255;
  // m_green = 0;
  // m_blue = 0;
}

void FlowingColorEffect::tick() {
  // if (m_red == 255 && m_green < 255) {
  //   m_green = constrain(m_green + m_speed, 0, 255);
  // } else if (m_green == 255 && m_red > 0) {
  //   m_red = constrain(m_red - m_speed, 0, 255);
  // } else if (m_green == 255 && m_blue < 255) {
  //   m_blue = constrain(m_blue + m_speed, 0, 255);
  // } else if (m_blue == 255 && m_green > 0) {
  //   m_green = constrain(m_green - m_speed, 0, 255);
  // } else if (m_blue == 255 && m_red < 255) {
  //   m_red = constrain(m_red + m_speed, 0, 255);
  // } else if (m_red == 255 && m_blue > 0) {
  //   m_blue = constrain(m_blue - m_speed, 0, 255);
  // }
  m_overflowing_colors_counter += STEP_TIMEOUT / 3;
  if (m_hue_counter >= (6 << 8)) {
    m_hue_counter -= 6 << 8;
  }
  if (m_hue_counter < 0) {
    m_hue_counter += (6 << 8);
  }
  m_lamp->set_color_leds(Lamp::get_hue(m_overflowing_colors_counter));
}

void FlowingColorEffect::action_tick(bool reverse) {
  m_speed += reverse ? -(int16_t)STEP_TIMEOUT / 3 : STEP_TIMEOUT / 3;
  EEPROM.put(9, m_speed);
}

void WarmWhiteEffect::init(size_t led_count) {
  m_warm_level = EEPROM.read(8);
}

void WarmWhiteEffect::tick() {
  m_lamp->set_color_leds(Lamp::calc_color(255, m_warm_level, m_warm_level));
}

void WarmWhiteEffect::action_tick(bool reverse) {
  m_warm_level += reverse ? -(int16_t)STEP_TIMEOUT / 3 : STEP_TIMEOUT / 3;
  m_warm_level = constrain(m_warm_level, 0, 255);
  EEPROM.put(8, m_warm_level);
}
