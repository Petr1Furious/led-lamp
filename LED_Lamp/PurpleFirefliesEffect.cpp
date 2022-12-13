#include "PurpleFirefliesEffect.h"
#include "Lamp.h"
#include "settings.h"
#include <EEPROM.h>

void PurpleFirefliesEffect::init(size_t led_count) {
  EEPROM.get(14, m_speed);
  m_speed = constrain(m_speed, 1, STEP_TIMEOUT);
}

void PurpleFirefliesEffect::tick() {
  m_buffer += m_speed;

  if (m_buffer >= MAX_BUFFER_SIZE) {
    m_buffer -= MAX_BUFFER_SIZE;
    m_fireflies_counter++;
    if (m_fireflies_counter == LED_STRIP_LENGTH - 1) {
      m_fireflies_counter = 0;
    }
  }

  m_lamp->clear_leds();

  if (m_fireflies_counter <= LED_STRIP_LENGTH / 2) {
    m_lamp->set_color_led(LED_STRIP_LENGTH / 2 - m_fireflies_counter, FIREFLY_COLOR);
    m_lamp->set_color_led(LED_STRIP_LENGTH / 2 + m_fireflies_counter, FIREFLY_COLOR);
  } else {
    m_lamp->set_color_led(m_fireflies_counter - LED_STRIP_LENGTH / 2, FIREFLY_COLOR);
    m_lamp->set_color_led(LED_STRIP_LENGTH - 1 - (m_fireflies_counter - LED_STRIP_LENGTH / 2), FIREFLY_COLOR);
  }
}

void PurpleFirefliesEffect::action_tick(bool reverse) {
  m_buffer_speed += reverse ? -1 : 1;

  if (m_buffer_speed == -1) {
    m_buffer_speed = MAX_BUFFER_SIZE_SPEED - 1;
    m_speed = max(1, m_speed - 1);
  }
  if (m_buffer_speed == MAX_BUFFER_SIZE_SPEED) {
    m_buffer_speed = 0;
    m_speed = min(STEP_TIMEOUT, m_speed + 1);
  }

  EEPROM.put(14, m_speed);
}
