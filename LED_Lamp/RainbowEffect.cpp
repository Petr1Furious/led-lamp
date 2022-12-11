#include "RainbowEffect.h"
#include "Lamp.h"
#include "settings.h"
#include <EEPROM.h>

void RainbowEffect::init(size_t led_count) {
  EEPROM.get(9, m_speed);
}

void RainbowEffect::tick() {
  for (size_t i = 0; i < LED_STRIP_LENGTH; ++i) {
    m_lamp->set_color_led(Lamp::get_hue(m_rainbow_counter));
    m_rainbow_counter += m_speed;
    if (m_hue_counter >= (6 << 8)) {
      m_hue_counter -= 6 << 8;
    }
    if (m_hue_counter < 0) {
      m_hue_counter += (6 << 8);
    }
  }
}

void RainbowEffect::action_tick(bool reverse) {
  m_speed += reverse ? -(int16_t)STEP_TIMEOUT / 3 : STEP_TIMEOUT / 3;
  EEPROM.put(9, m_speed);
}
