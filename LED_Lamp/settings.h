#pragma once

// #define DEBUG_MODE

// Lamp class
constexpr uint8_t EFFECTS_COUNT = 6;
constexpr uint16_t HOLD_TIMEOUT = 500;
constexpr uint16_t STEP_TIMEOUT = 10;
#define VB_DEB 20

// Serial
constexpr int BAUD_RATE = 9600;

// Led settings
constexpr uint8_t LED_PIN = 10;
constexpr size_t LED_STRIP_LENGTH = 11;
constexpr size_t LED_STRIPS_COUNT = 4;
constexpr uint8_t MIN_BRIGHTNESS = 2;
constexpr uint8_t MAX_BRIGHTNESS = 255;

// Power settings
#ifndef DEBUG_MODE
constexpr uint16_t POWER_LIMIT = 2000;
#else
constexpr uint16_t POWER_LIMIT = 500;
#endif

// Other
constexpr uint8_t BUTTON_PIN = 13;
constexpr uint16_t SMOOTH_TRANSITION_PERIOD = 500;
