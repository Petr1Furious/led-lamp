#include "FireEffect.h"
#include "Lamp.h"
#include "settings.h"

void FireEffect::init(size_t led_count) {
}

void FireEffect::tick() {
  if (millis() >= m_next_burst) {
    if (m_cur_fire_height == m_target_fire_height) {
      if (m_cur_fire_height == 0) {
        m_target_fire_height = Lamp::rand_int(1, LED_STRIP_LENGTH - 1);
        m_next_burst = millis() + (uint32_t)Lamp::rand_int(100, MAX_FIRE_DELAY);
      } else {
        m_target_fire_height = 0;
      }
    } else if (m_cur_fire_height < m_target_fire_height) {
      m_ascending_buffer++;
      if (m_ascending_buffer == MAX_ASCENDING_BUFFER_SIZE) {
        m_ascending_buffer = 0;
        m_cur_fire_height++;
      }
    } else {
      m_descending_buffer++;
      if (m_descending_buffer == MAX_DESCENDING_BUFFER_SIZE) {
        m_descending_buffer = 0;
        m_cur_fire_height--;
      }
    }
  }

  m_lamp->clear_leds();
  for (uint8_t i = 0; i < FIRE_SOURCE_SIZE; i++) {
    m_lamp->set_color_led(i, Lamp::calc_color(
      RED_GRADIENT + Lamp::rand_int(-GRADIENT_RANGE, GRADIENT_RANGE),
      GREEN_GRADIENT + Lamp::rand_int(-GRADIENT_RANGE, GRADIENT_RANGE), 0));
  }

  for (uint8_t i = 0; i < m_cur_fire_height; i++) {
    m_lamp->set_color_led(i, Lamp::calc_color(
      RED_GRADIENT + Lamp::rand_int(-GRADIENT_RANGE, GRADIENT_RANGE),
      map(i, 0, m_cur_fire_height - 1, GREEN_GRADIENT, GREEN_GRADIENT + MAX_GREEN_INCREASE) +
      Lamp::rand_int(-GRADIENT_RANGE, GRADIENT_RANGE),
      0));
  }
  
  m_lamp->set_color_led(m_cur_fire_height, Lamp::calc_color(RED_GRADIENT + Lamp::rand_int(-GRADIENT_RANGE, GRADIENT_RANGE),
  GREEN_GRADIENT + MAX_GREEN_INCREASE / 2 + Lamp::rand_int(-GRADIENT_RANGE, GRADIENT_RANGE), 0));
}

void FireEffect::action_tick(bool reverse) {
}
