#ifndef SETTINGS_H
#define SETTINGS_H

// Lamp class
constexpr uint8_t button_pin = 13;
constexpr uint8_t led_pin = 10;
constexpr int16_t led_size = 11;
constexpr int16_t strips_size = 4;

// Serial
constexpr int baud_rate = 9600;

// Led settings
constexpr uint8_t min_brightness = 3;
constexpr uint8_t max_brightness = 191;
constexpr int8_t modes_size = 2;

// Power settings
constexpr int16_t power_limit = 2000;

// Добавить настройки

#endif