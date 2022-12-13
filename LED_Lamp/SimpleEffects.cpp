#include "SimpleEffects.h"
#include "Lamp.h"
#include "TemperatureToColor.h"
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
  EEPROM.get(6, m_flowing_colors_counter);
  m_flowing_colors_counter = constrain(m_flowing_colors_counter, 0, (6 << 8) - 1);
  m_last_save = millis();

  EEPROM.get(8, m_speed);
  m_speed = constrain(m_speed, 1, STEP_TIMEOUT);
}

void FlowingColorEffect::tick() {
  m_flowing_colors_counter += m_speed;
  if (m_flowing_colors_counter >= (6 << 8)) {
    m_flowing_colors_counter -= 6 << 8;
  }
  m_lamp->set_color_leds(Lamp::get_hue(m_flowing_colors_counter));

  if (millis() - m_last_save >= 250) {
    m_last_save = millis();
    EEPROM.put(6, m_flowing_colors_counter);
  }
}

void FlowingColorEffect::action_tick(bool reverse) {
  m_buffer += reverse ? -1 : 1;

  if (m_buffer == -1) {
    m_buffer = MAX_BUFFER_SIZE - 1;
    m_speed = max(1, m_speed - 1);
  }
  if (m_buffer == MAX_BUFFER_SIZE) {
    m_buffer = 0;
    m_speed = min(STEP_TIMEOUT / 2, m_speed + 1);
  }

  EEPROM.put(8, m_speed);
}

void WarmWhiteEffect::init(size_t led_count) {
  m_color_temperature = EEPROM.read(9);
}

void WarmWhiteEffect::tick() {
  m_lamp->set_color_leds(temperature_to_color[m_color_temperature]);
}

void WarmWhiteEffect::action_tick(bool reverse) {
  m_buffer += reverse ? -1 : 1;

  if (m_buffer == -1) {
    m_buffer = MAX_BUFFER_SIZE - 1;
    m_color_temperature = max(0, m_color_temperature - 1);
  }
  if (m_buffer == MAX_BUFFER_SIZE) {
    m_buffer = 0;
    m_color_temperature = min((int8_t)TEMPERATURE_COLORS - 1, m_color_temperature + 1);
  }
  
  EEPROM.put(9, m_color_temperature);
}
