#include "RainbowEffect.h"
#include "Lamp.h"
#include "settings.h"
#include <EEPROM.h>

void RainbowEffect::init(size_t led_count) {
  EEPROM.get(11, m_rainbow_counter);
  m_rainbow_counter = constrain(m_rainbow_counter, 0, (6 << 8) - 1);
  m_last_save = millis();

  EEPROM.get(13, m_speed);
  m_speed = constrain(m_speed, 1, STEP_TIMEOUT);
}

void RainbowEffect::tick() {
  m_rainbow_counter += m_speed;
  if (m_rainbow_counter >= (6 << 8)) {
    m_rainbow_counter -= 6 << 8;
  }

  int16_t cur_counter = m_rainbow_counter;
  for (size_t i = 0; i < LED_STRIP_LENGTH; ++i) {
    m_lamp->set_color_led(i, Lamp::get_hue(cur_counter));
    cur_counter += 100;
    if (cur_counter >= (6 << 8)) {
      cur_counter -= 6 << 8;
    }
  }

  if (millis() - m_last_save > 250) {
    m_last_save = millis();
    EEPROM.put(11, m_rainbow_counter);
  }
}

void RainbowEffect::action_tick(bool reverse) {
  m_buffer += reverse ? -1 : 1;

  if (m_buffer == -1) {
    m_buffer = MAX_BUFFER_SIZE - 1;
    m_speed = max(1, m_speed - 1);
  }
  if (m_buffer == MAX_BUFFER_SIZE) {
    m_buffer = 0;
    m_speed = min(STEP_TIMEOUT, m_speed + 1);
  }

  EEPROM.put(13, m_speed);
}
