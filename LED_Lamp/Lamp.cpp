#include <EEPROM.h>

#include "SimpleEffects.h"
#include "Lamp.h"

Lamp::Lamp() {
}

void Lamp::init() {
#ifdef DEBUG_MODE
  Serial.begin(BAUD_RATE);
#endif
  LEDS.addLeds<WS2811, LED_PIN, GRB>(leds, LED_STRIP_LENGTH).setCorrection(TypicalLEDStrip);
  if (POWER_LIMIT) {
    LEDS.setMaxPowerInVoltsAndMilliamps(5, POWER_LIMIT / LED_STRIPS_COUNT);
  }

  pinMode(BUTTON_PIN, INPUT);

  m_on = EEPROM.read(0);
  m_current_effect = constrain(EEPROM.read(1), 0, EFFECTS_COUNT - 1);
  m_brightness = constrain(EEPROM.read(2), MIN_BRIGHTNESS, MAX_BRIGHTNESS);
  m_brightness_change_direction = EEPROM.read(3);

  LEDS.setBrightness(m_brightness);

  m_effects[0] = new StaticColorEffect(this);
  m_effects[1] = new FlowingColorEffect(this);
  m_effects[2] = new WarmWhiteEffect(this);

  for (size_t i = 0; i < EFFECTS_COUNT; i++) {
    m_effects[i]->init(LED_STRIP_LENGTH);
  }

  button.setHoldTimeout(HOLD_TIMEOUT);
  button.setStepTimeout(STEP_TIMEOUT);
}

uint32_t Lamp::calc_color(uint8_t red, uint8_t green, uint8_t blue) {
  return ((uint32_t)red << 16) + ((uint32_t)green << 8) + (uint32_t)blue;
}

uint32_t Lamp::get_hue(uint16_t counter) {
  if (counter < (1 << 8)) {
    return 0xFF0000 + ((uint32_t)counter << 8);
  } else if (counter < (2 << 8)) {
    return 0x00FF00 + ((uint32_t)((2 << 8) - counter - 1) << 16);
  } else if (counter < (3 << 8)) {
    return 0x00FF00 + (uint32_t)(counter - (2 << 8));
  } else if (counter < (4 << 8)) {
    return 0x0000FF + ((uint32_t)((4 << 8) - counter - 1) << 8);
  } else if (counter < (5 << 8)) {
    return 0x0000FF + ((uint32_t)(counter - (4 << 8)) << 16);
  } else {
    return 0xFF0000 + (uint32_t)((6 << 8) - counter - 1);
  }
}

void Lamp::set_color_led(size_t idx, uint32_t color) {
  leds[idx] = color;
}

void Lamp::set_color_leds(uint32_t color) {
  for (size_t i = 0; i < LED_STRIP_LENGTH; ++i) {
    leds[i] = color;
  }
}

void Lamp::set_colors_leds(uint32_t* colors) {
  for (size_t i = 0; i < LED_STRIP_LENGTH; ++i) {
    leds[i] = colors[i];
  }
}

void Lamp::run() {
  button.poll(digitalRead(BUTTON_PIN));

  if (button.hasClicks(1)) {
    m_on = !m_on;
    if (m_on) {
      LEDS.setBrightness(m_brightness);
    } else {
      LEDS.setBrightness(0);
    }

    EEPROM.write(0, m_on);
  }

  if (m_on) {
    if (button.hasClicks(2)) {
      m_current_effect++;
      if (m_current_effect == EFFECTS_COUNT) {
        m_current_effect = 0;
      }

      EEPROM.write(1, m_current_effect);
    }
    if (button.hasClicks(3)) {
      if (m_current_effect == 0) {
        m_current_effect = EFFECTS_COUNT;
      }
      m_current_effect--;

      EEPROM.write(1, m_current_effect);
    }

    if (button.step(0)) {
      m_brightness = constrain(m_brightness + (m_brightness_change_direction ? 1 : -1), MIN_BRIGHTNESS, MAX_BRIGHTNESS);
      LEDS.setBrightness(m_brightness);
      LEDS.show();

      EEPROM.write(2, m_brightness);
    }
    if (button.releaseStep(0)) {
      m_brightness_change_direction = !m_brightness_change_direction;

      EEPROM.write(3, m_brightness_change_direction);
    }

    if (button.step(1)) {
      m_effects[m_current_effect]->action_tick(false);
    }
    if (button.step(2)) {
      m_effects[m_current_effect]->action_tick(true);
    }
    m_effects[m_current_effect]->tick();
  }

  LEDS.show();
}
