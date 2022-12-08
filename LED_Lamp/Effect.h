#pragma once

class Lamp;

#include "Lamp.h"

#include <FastLED.h>

class Effect {
public:
  Effect(Lamp* lamp)
    : m_lamp(lamp) {}

  virtual void init(size_t led_count) = 0;

  // is called each EB_STEP milliseconds after action_click
  virtual void tick() = 0;

  // is called each EB_STEP milliseconds if the effect is begin changed
  // the effect is being changed if there has been a single click (or double click for reverse), and the button is being held afterwards
  // you should not change LED state here
  virtual void action_tick(bool reverse) = 0;

protected:
  Lamp* m_lamp;
};
