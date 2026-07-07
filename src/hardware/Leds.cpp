#include "Leds.h"

#include <Arduino.h>

void Leds::setNumLockBrightness(int brightness) {
    setLedBrightness(LED_NUM_LOCK_PIN, brightness);
}

void Leds::setCapsLockBrightness(int brightness) {
    setLedBrightness(LED_CAPS_LOCK_PIN, brightness);
}

void Leds::setScrollLockBrightness(int brightness) {
    setLedBrightness(LED_SCROLL_LOCK_PIN, brightness);
}

void Leds::setLeftMouseLockBrightness(int brightness) {
    setLedBrightness(LED_LEFT_MOUSE_LOCK_PIN, brightness);
}

void Leds::setRightMouseLockBrightness(int brightness) {
    setLedBrightness(LED_RIGHT_MOUSE_LOCK_PIN, brightness);
}

void Leds::setSpecialBrightness(int brightness) {
    setLedBrightness(LED_SPECIAL_PIN, brightness);
}

void Leds::setLedBrightness(int pin, int brightness) {
    setLedWrite(pin, (int) (MAX_ANALOG_VALUE * (brightness / 100.0)));
}

void Leds::setLedBrightnessRaw(int pin, int brightness) {
    setLedWriteRaw(pin, (int) (MAX_ANALOG_VALUE * (brightness / 100.0)));
}

void Leds::setLedWrite(int pin, int value) {
    int brightness = getSettings().getLedBrightness();
    setLedWriteRaw(pin, (int) (value * (brightness / 100.0)));
}

void Leds::setLedWriteRaw(int pin, int value) {
    if (!getSettings().isLeds()) value = 0;
    analogWrite(pin, value);
}

void Leds::disableAll() {
    setNumLockBrightness(0);
    setCapsLockBrightness(0);
    setScrollLockBrightness(0);
    setLeftMouseLockBrightness(0);
    setRightMouseLockBrightness(0);
    setSpecialBrightness(0);
}

void Leds::setSettings(Settings* settings) {
    this->settings = settings;
}

Settings& Leds::getSettings() {
    return *this->settings;
}