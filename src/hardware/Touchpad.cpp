#include "Touchpad.h"

void Touchpad::setup() {
    this->touchpad = new PS4Touchpad();
    touchpad->setAddress(TOUCHPAD_ADDRESS);
}

void Touchpad::read() {
    touchpad->read();

    firstTouchXOld = firstTouchX;
    firstTouchYOld = firstTouchY;
    secondTouchXOld = secondTouchX;
    secondTouchYOld = secondTouchY;

    firstTouchOld = firstTouch;
    secondTouchOld = secondTouch;

    firstTouchX = touchpad->getFirstY();
    firstTouchY = touchpad->getMaxX() - touchpad->getFirstX();
    secondTouchX = touchpad->getSecondY();
    secondTouchY = touchpad->getMaxX() - touchpad->getSecondX();

    firstTouch = touchpad->isFirstPressed();
    secondTouch = touchpad->isSecondPressed();

    firstTouchNormalized = normalizeValue(firstTouch, firstTouchOld);
    secondTouchNormalized = normalizeValue(secondTouch, secondTouchOld);

    firstTouchXMoved = firstTouchX - firstTouchXOld;
    firstTouchYMoved = firstTouchY - firstTouchYOld;
    secondTouchXMoved = secondTouchX - secondTouchXOld;
    secondTouchYMoved = secondTouchY - secondTouchYOld;

    if (isFirstTouchPress()) {
        firstTouchXMoved = 0;
        firstTouchYMoved = 0;
        for (int i = 0; i < 10; i++) {
            firstRound[i][0] = firstTouchXMoved;
            firstRound[i][1] = firstTouchYMoved;
        }
    }
    if (isSecondTouchPress()) {
        secondTouchXMoved = 0;
        secondTouchYMoved = 0;
        for (int i = 0; i < 10; i++) {
            secondRound[i][0] = secondTouchXMoved;
            secondRound[i][1] = secondTouchYMoved;
        }
    }

    int roundLimit = getRoundLimit();

    for (int i = 0; i < roundLimit - 1; i++) {
        firstRound[i][0] = firstRound[i + 1][0];
        firstRound[i][1] = firstRound[i + 1][1];
        secondRound[i][0] = secondRound[i + 1][0];
        secondRound[i][1] = secondRound[i + 1][1];
    }
    firstRound[roundLimit - 1][0] = firstTouchXMoved;
    firstRound[roundLimit - 1][1] = firstTouchYMoved;
    secondRound[roundLimit - 1][0] = secondTouchXMoved;
    secondRound[roundLimit - 1][1] = secondTouchYMoved;

    firstTouchXRounded = 0;
    firstTouchYRounded = 0;
    secondTouchXRounded = 0;
    secondTouchYRounded = 0;
    for (int i = 0; i < roundLimit; i++) {
        firstTouchXRounded += firstRound[i][0];
        firstTouchYRounded += firstRound[i][1];
        secondTouchXRounded += secondRound[i][0];
        secondTouchYRounded += secondRound[i][1];
    }
    firstTouchXRounded = firstTouchXRounded / roundLimit;
    firstTouchYRounded = firstTouchYRounded / roundLimit;
    secondTouchXRounded = secondTouchXRounded / roundLimit;
    secondTouchYRounded = secondTouchYRounded / roundLimit;

    int inertiaThreshold = getInertiaThreshold();
    int inertiaStep = getInertiaStep();

    if (getSettings().isTouchpadInertiaRounded()) {
        if (firstTouchXRounded <= -inertiaThreshold || firstTouchXRounded >= inertiaThreshold ||
                firstTouchYRounded <= -inertiaThreshold || firstTouchYRounded >= inertiaThreshold) {
            firstTouchXInertial = firstTouchXRounded;
            firstTouchYInertial = firstTouchYRounded;
        }
        if (secondTouchXRounded <= -inertiaThreshold || secondTouchXRounded >= inertiaThreshold ||
                secondTouchYRounded <= -inertiaThreshold || secondTouchYRounded >= inertiaThreshold) {
            firstTouchXInertial = firstTouchXRounded;
            firstTouchYInertial = secondTouchYRounded;
        }
    } else {
        if (firstTouchXMoved <= -inertiaThreshold || firstTouchXMoved >= inertiaThreshold ||
                firstTouchYMoved <= -inertiaThreshold || firstTouchYMoved >= inertiaThreshold) {
            firstTouchXInertial = firstTouchXMoved;
            firstTouchYInertial = firstTouchYMoved;
        }
        if (secondTouchXMoved <= -inertiaThreshold || secondTouchXMoved >= inertiaThreshold ||
                secondTouchYMoved <= -inertiaThreshold || secondTouchYMoved >= inertiaThreshold) {
            firstTouchXInertial = firstTouchXMoved;
            firstTouchYInertial = secondTouchYMoved;
        }
    }

    firstTouchXInertial = inertiaValue(firstTouchXInertial, inertiaStep);
    firstTouchYInertial = inertiaValue(firstTouchYInertial, inertiaStep);
    secondTouchXInertial = inertiaValue(secondTouchXInertial, inertiaStep);
    secondTouchYInertial = inertiaValue(secondTouchYInertial, inertiaStep);
}

PS4Touchpad& Touchpad::getTouchpad() {
    return *this->touchpad;
}

void Touchpad::setSettings(Settings* settings) {
    this->settings = settings;
}

Settings& Touchpad::getSettings() {
    return *this->settings;
}

int Touchpad::getMaxX() {
    return touchpad->getMaxY();
}

int Touchpad::getMaxY() {
    return touchpad->getMaxX();
}

int Touchpad::getRoundLimit() {
    return settings->getTouchpadRoundLimit();
}

int Touchpad::getInertiaThreshold() {
    return settings->getTouchpadInertiaThreshold();
}

int Touchpad::getInertiaStep() {
    return settings->getTouchpadInertiaStep();
}

int Touchpad::normalizeValue(bool button, bool buttonOld) {
    int value = 0;
    if (button && !buttonOld) value = 1;
    if (button && buttonOld) value = 2;
    if (!button && buttonOld) value = 3;
    return value;
}

int Touchpad::inertiaValue(int value, int inertiaStep) {
    if (value > 0) {
        value -= inertiaStep;
        if (value < 0) value = 0;
    }
    if (value < 0) {
        value += inertiaStep;
        if (value > 0) value = 0;
    }
    return value;
}

int Touchpad::getFirstX() {
    return firstTouchX;
}

int Touchpad::getFirstY() {
    return firstTouchY;
}

int Touchpad::getSecondX() {
    return secondTouchX;
}

int Touchpad::getSecondY() {
    return secondTouchY;
}

int Touchpad::getFirstXOld() {
    return firstTouchXOld;
}

int Touchpad::getFirstYOld() {
    return firstTouchYOld;
}

int Touchpad::getSecondXOld() {
    return secondTouchXOld;
}

int Touchpad::getSecondYOld() {
    return secondTouchYOld;
}

int Touchpad::getFirstXMoved() {
    return firstTouchXMoved;
}

int Touchpad::getFirstYMoved() {
    return firstTouchYMoved;
}

int Touchpad::getSecondXMoved() {
    return secondTouchXMoved;
}

int Touchpad::getSecondYMoved() {
    return secondTouchYMoved;
}

float Touchpad::getFirstXRounded() {
    return firstTouchXRounded;
}

float Touchpad::getFirstYRounded() {
    return firstTouchYRounded;
}

float Touchpad::getSecondXRounded() {
    return secondTouchXRounded;
}

float Touchpad::getSecondYRounded() {
    return secondTouchYRounded;
}

float Touchpad::getFirstXInertial() {
    return firstTouchXInertial;
}

float Touchpad::getFirstYInertial() {
    return firstTouchYInertial;
}

float Touchpad::getSecondXInertial() {
    return secondTouchXInertial;
}

float Touchpad::getSecondYInertial() {
    return secondTouchYInertial;
}

int Touchpad::getFirstTouchValue() {
    return firstTouchNormalized;
}

bool Touchpad::isFirstTouchPress() {
    return getFirstTouchValue() == 1;
}

bool Touchpad::isFirstTouchPressed() {
    return getFirstTouchValue() == 2;
}

bool Touchpad::isFirstTouchRelease() {
    return getFirstTouchValue() == 3;
}

int Touchpad::getSecondTouchValue() {
    return secondTouchNormalized;
}

bool Touchpad::isSecondTouchPress() {
    return getSecondTouchValue() == 1;
}

bool Touchpad::isSecondTouchPressed() {
    return getSecondTouchValue() == 2;
}

bool Touchpad::isSecondTouchRelease() {
    return getSecondTouchValue() == 3;
}