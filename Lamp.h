#ifndef LAMP_H
#define LAMP_H

#include <FastLED.h>
#include "settings.h"

class Lamp {
public:
  Lamp();
  void init();
  void run();
private:
  int32_t calc_color(int32_t red, int32_t green, int32_t blue);
  void set_color_led(uint8_t idx, int32_t color);
  void set_color_leds(int32_t color);
  void set_colors_leds(int32_t* colors);
  void apply_mode();
  // Тут еще дополнительные методы

  uint8_t m_button_pin = button_pin;
  uint8_t m_led_pin = led_pin;
  int16_t m_led_size = led_size;
  int16_t m_strips_size = strips_size;
  uint8_t m_brightness;
  uint8_t m_current_mode;
  uint8_t m_warm_level;
  int32_t m_overflowing_colors_step;
  int32_t m_overflowing_colors_counter;
  int32_t m_static_color_counter;
  bool m_white_mode = false;
  CRGB leds[led_size];
};

#endif