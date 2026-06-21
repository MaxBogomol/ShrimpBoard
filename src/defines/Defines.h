#pragma once

//Pins
#define MAX_ANALOG_VALUE 4095

//Button matrix
#define BUTTON_COLUMN_PIN_SS 10
#define BUTTON_COLUMN_PIN_MOSI 11
#define BUTTON_COLUMN_PIN_SCK 12
#define BUTTON_COLUMN_PIN_OE 13
#define BUTTON_COLUMN_PIN_17 21

#define BUTTON_ROW_PIN_1 39
#define BUTTON_ROW_PIN_2 40
#define BUTTON_ROW_PIN_3 41
#define BUTTON_ROW_PIN_4 42
#define BUTTON_ROW_PIN_5 2
#define BUTTON_ROW_PIN_6 1

//Touch button
#define TOUCH_BUTTON_PIN 17
#define TOUCH_BUTTON_PIN_GPIO GPIO_NUM_17

//Battery
#define BATTERY_PIN 14

//Leds
#define LED_NUM_LOCK_PIN 6
#define LED_CAPS_LOCK_PIN 7
#define LED_SCROLL_LOCK_PIN 15
#define LED_LEFT_MOUSE_LOCK_PIN 4
#define LED_RIGHT_MOUSE_LOCK_PIN 16
#define LED_SPECIAL_PIN 5

//Buzzer
#define BUZZER_PIN 18

//Touchpad
#define TOUCHPAD_ADDRESS 0x64

//Screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

//EPROM
#define EPROM_ADDRESS 0x50

//Setings
#define DEVICE_NAME "ShrimpBoard"
#define DEVICE_MANUFACTURER "Pink Joke"
#define DEBUG true