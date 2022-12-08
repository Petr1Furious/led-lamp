#pragma once

#define DEBUG_MODE

// Lamp class
constexpr uint8_t EFFECTS_COUNT = 3;
#define EB_STEP 10

// Serial
constexpr int BAUD_RATE = 9600;

// Led settings
constexpr uint8_t LED_PIN = 10;
constexpr size_t LED_STRIP_LENGTH = 11;
constexpr size_t LED_STRIPS_COUNT = 4;
constexpr uint8_t MIN_BRIGHTNESS = 3;
constexpr uint8_t MAX_BRIGHTNESS = 255;

// Power settings
constexpr uint16_t POWER_LIMIT = 2000;

// Other
constexpr uint8_t BUTTON_PIN = 13;
