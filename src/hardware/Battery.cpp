#include "Battery.h"

#include <Arduino.h>

int Battery::getPercentage() {
    return 100;
}

double Battery::getRawVoltage() {
    int rawValue = analogRead(BATTERY_PIN);
    return (rawValue * 3.3) / MAX_ANALOG_VALUE;
}

double Battery::getVoltage() {
    return getRawVoltage();
}

void Battery::setSettings(Settings* settings) {
    this->settings = settings;
}

Settings& Battery::getSettings() {
    return *this->settings;
}