#include "Battery.h"

#include <Arduino.h>

void Battery::read() {
    for (int i = 0; i < getRoundLimit() - 1; i++) {
        voltageRound[i] = voltageRound[i + 1];
    }
    float voltage = getRawVoltage();
    if (filteredVoltage < 0) {
        filteredVoltage = voltage;
    }
    voltage = (voltage * emaAlpha) + (filteredVoltage * (1.0 - emaAlpha));
    voltageRound[getRoundLimit() - 1] = voltage;
}

int Battery::getPercentage(float x) {
    float percentage = (x - 680.0) * (x - 548.694) * 0.000730968;
    return constrain(round(percentage), 0, 100);
}

int Battery::getPercentage() {
    float x = getRawVoltage() / 4.0;
    return getPercentage(x);
}

int Battery::getPercentageRounded() {
    return getPercentage((float) getVoltageRounded() / 4.0);
}

double Battery::getRawVoltage() {
    return analogRead(BATTERY_PIN);
}

double Battery::getVoltage() {
    return (getRawVoltage() * 3.3) / MAX_ANALOG_VALUE;
}

double Battery::getVoltageRounded() {
    double voltage = 0;
    for (int i = 0; i < getRoundLimit(); i++) {
        voltage += voltageRound[i];
    }
    return voltage / getRoundLimit();
}

int Battery::getRoundLimit() {
    return roundLimit;
}

void Battery::setSettings(Settings* settings) {
    this->settings = settings;
}

Settings& Battery::getSettings() {
    return *this->settings;
}