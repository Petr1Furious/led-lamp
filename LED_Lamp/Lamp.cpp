#include "Lamp.h"
#include <EEPROM.h>

Lamp::Lamp() {
}

void Lamp::init() {
#ifdef DEBUG_MODE
  Serial.begin(baud_rate);
#endif
  LEDS.addLeds<WS2811, led_pin, GRB>(leds, led_size).setCorrection(TypicalLEDStrip);
  if (power_limit)
    LEDS.setMaxPowerInVoltsAndMilliamps(5, power_limit / strips_size);
  pinMode(button_pin, INPUT);
  EEPROM.write(0, constrain(EEPROM.read(0), min_brightness, max_brightness));
  EEPROM.write(1, constrain(EEPROM.read(1), 0, modes_size - 1));
  EEPROM.write(2, constrain(EEPROM.read(2), 0, 1));
  EEPROM.write(3, constrain(EEPROM.read(3), 0, 255));
  EEPROM.write(4, constrain(EEPROM.read(4), 1, 10));
  EEPROM.write(5, constrain(EEPROM.read(5), 0, 255));
  EEPROM.write(6, constrain(EEPROM.read(6), 0, 255));

  m_brightness = EEPROM.read(0);
  m_current_mode = EEPROM.read(1);
  m_white_mode = EEPROM.read(2);
  m_warm_level = EEPROM.read(3);
  m_overflowing_colors_step = EEPROM.read(4);
  m_static_color_counter = ((int32_t)EEPROM.read(5) << 8) + (int32_t)EEPROM.read(6);
  m_overflowing_colors_counter = 768 - m_overflowing_colors_step;
  LEDS.setBrightness(0);
  if (m_white_mode) {
    set_color_leds(calc_color(255, 255, 255 - m_warm_level));
  } else {
    apply_mode();
  }
  LEDS.show();
}

int32_t Lamp::calc_color(int32_t red, int32_t green, int32_t blue) {
  return (red << 16) + (green << 8) + blue;
}

void Lamp::set_color_led(uint8_t idx, int32_t color) {
  leds[idx] = color;
}

void Lamp::set_color_leds(int32_t color) {
  for (int16_t i = 0; i < m_led_size; ++i) {
    leds[i] = color;
  }
}
void Lamp::set_colors_leds(int32_t* colors) {
  for (int16_t i = 0; i < m_led_size; ++i) {
    leds[i] = colors[i];
  }
}

void Lamp::apply_mode() {
  switch (m_current_mode) {
    case 1:
      return; // Режим 1
      break;
    case 2:
      return;
      break; // Режим 2
    default:
      #ifdef DEBUG_MODE
        Serial.println("ERROR");
      #endif
      break;
  }
}

void Lamp::run() {
  // Тут то, что нужно в loop файла скечта
}
