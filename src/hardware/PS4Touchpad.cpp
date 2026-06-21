#include "PS4Touchpad.h"

void PS4Touchpad::read() {
    Wire.beginTransmission(TOUCHPAD_ADDR);
    Wire.requestFrom(TOUCHPAD_ADDR, 32);

    byte data[32];
    int i = 0;
    while (Wire.available() && i < 32) {
        data[i++] = Wire.read();
    }

    firstTouchPressed = false;
    secondTouchPressed = false;

    if (data[3] < 128) {
        int x1 = ((data[5] << 8) | data[4]) - 61440;
        int y1 = ((data[7] << 8) | data[6]) - 49152;

        firstTouchX = x1;
        firstTouchY = y1;
        firstTouchPressed = true;
    }

    if (data[9] < 128) {
        int x2 = ((data[11] << 8) | data[10]) - 61440;
        int y2 = ((data[13] << 8) | data[12]) - 49152;

        secondTouchX = x2;
        secondTouchY = y2;
        secondTouchPressed = true;
    }
}

void PS4Touchpad::setAddress(uint8_t addr) {
    TOUCHPAD_ADDR = addr;
}

void PS4Touchpad::setMaxX(int max) {
    MAX_X = max;
}

void PS4Touchpad::setMaxY(int max) {
    MAX_Y = max;
}

uint8_t PS4Touchpad::getAddress() {
    return TOUCHPAD_ADDR;
}

int PS4Touchpad::getMaxX() {
    return MAX_X;
}

int PS4Touchpad::getMaxY() {
    return MAX_Y;
}

bool PS4Touchpad::isFirstPressed() {
    return firstTouchPressed;
}

int PS4Touchpad::getFirstX() {
    return firstTouchX;
}

int PS4Touchpad::getFirstY() {
    return firstTouchY;
}

bool PS4Touchpad::isSecondPressed() {
    return secondTouchPressed;
}

int PS4Touchpad::getSecondX() {
    return secondTouchX;
}

int PS4Touchpad::getSecondY() {
    return secondTouchY;
}

double PS4Touchpad::getFirstXLimited() {
    return map(getFirstX(), 0.0, MAX_X, 0.0, 100.0);
}

double PS4Touchpad::getFirstYLimited() {
    return map(getFirstY(), 0.0, MAX_Y, 0.0, 100.0);
}

double PS4Touchpad::getSecondXLimited() {
    return map(getSecondX(), 0.0, MAX_X, 0.0, 100);
}

double PS4Touchpad::getSecondYLimited() {
    return map(getSecondY(), 0.0, MAX_Y, 0.0, 100.0);
}