#include "ComplexEffects.h"
#include "Lamp.h"
#include <EEPROM.h>

void RainbowEffect::init(size_t led_count) {
  // То, что закоммментированно ниже - это данные, если мы будем запоминат положение цветов. Скорее всего, это нам ненужно
  // uint32_t data;
  // // EEPROM.get(4, colors); укажи нужный индекс
  // // 0-7: blue
  // // 8-15: green
  // // 16-23: red
  // // 24-32: speed
  // m_speed = (data & (((2 << 31) - 1) - ((2 << 23) - 1))) >> 24;
  // m_red = (data & (((2 << 23) - 1) - ((2 << 15) - 1))) >> 16;
  // m_green = (data & (((2 << 15) - 1) - ((2 << 7) - 1))) >> 8;
  // m_blue = data & ((2 << 7) - 1);
  EEPROM.get(9, m_speed); // Укажи нудный адерс. И ниже тоже
  m_red = 255;
  m_green = 0;
  m_blue = 0;
}

void RainbowEffect::tick() {
  if (m_red == 255 && m_green < 255) {
    m_green = constrain(m_green + m_speed, 0, 255);
  } else if (m_green == 255 && m_red > 0) {
    m_red = constrain(m_red - m_speed, 0, 255);
  } else if (m_green == 255 && m_blue < 255) {
    m_blue = constrain(m_blue + m_speed, 0, 255);
  } else if (m_blue == 255 && m_green > 0) {
    m_green = constrain(m_green - m_speed, 0, 255);
  } else if (m_blue == 255 && m_red < 255) {
    m_red = constrain(m_red + m_speed, 0, 255);
  } else if (m_red == 255 && m_blue > 0) {
    m_blue = constrain(m_blue - m_speed, 0, 255);
  }
  // uinti32_t data = (m_speed << 24) + (m_red << 16) + (m_green << 8) + m_blue;
  // EEPROM(9, data);
  m_lamp->set_color_leds(Lamp::calc_color(m_red, m_green, m_blue));
}

void RainbowEffect::action_tick(bool reverse) {
  m_speed += reverse ? -(int16_t)STEP_TIMEOUT / 3 : STEP_TIMEOUT / 3;
  EEPROM.put(9, m_speed);
}
