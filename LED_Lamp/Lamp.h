#pragma once

#include <VirtualButton.h>
#include <FastLED.h>

class Effect;

#include "Effect.h"
#include "settings.h"

class Lamp {
public:
  Lamp();

  void init();

  void run();

  static uint32_t calc_color(uint8_t red, uint8_t green, uint8_t blue);

  static uint32_t get_hue(uint16_t counter);

  void set_color_led(size_t idx, uint32_t color);

  void set_color_leds(uint32_t color);

  void set_colors_leds(uint32_t* colors);

private:
  CRGB leds[LED_STRIP_LENGTH];

  VButton button;

  uint8_t m_brightness;

  bool m_brightness_change_direction;

  bool m_on;

  Effect* m_effects[EFFECTS_COUNT];

  uint8_t m_current_effect;

  uint32_t m_last_tick;
};

// 
