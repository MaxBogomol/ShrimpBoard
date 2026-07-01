#include "Settings.h"

void Settings::reset() {
    debounce = true;
    debounceTime = 5;
    buttonScroll = true;
    buttonScrollDelay = 500;
    buttonScrollTime = 100;

    mouseSpeed = 1;
    touchpadScroll = true;
    mouseLockScroll = false;
    leftMouseLockScroll = false;
    rightMouseLockScroll = false;
    mouseScrollSpeed = 1;
    mouseButtonScrollTime = 10;
    touchpadRounded = true;
    touchpadRoundLimit = 5;
    touchpadInertia = true;
    touchpadInertiaRounded = true;
    touchpadInertiaThreshold = 50;
    touchpadInertiaStep = 5;

    displayUpdateDelay = 25;
    loadingScreen = 0;
    loadingScreenType = 0;
    loadingScreenSpeed = 2;

    leds = true;
    ledBrightness = 100;

    inactive = true;
    inactiveTime = 5;

    sound = true;
    pressSound = false;
    pressSoundFrequency = 1000;
    pressSoundDuration = 50;
}

void Settings::copy(Settings* otherSettings) {
    debounce = otherSettings->isDebounce();
    debounceTime = otherSettings->getDebounceTime();
    buttonScroll = otherSettings->isButtonScroll();
    buttonScrollDelay = otherSettings->getButtonScrollDelay();
    buttonScrollTime = otherSettings->getButtonScrollTime();

    mouseSpeed = otherSettings->getMouseSpeed();
    touchpadScroll = otherSettings->isTouchpadScroll();
    mouseLockScroll = otherSettings->isMouseLockScroll();
    leftMouseLockScroll = otherSettings->isLeftMouseLockScroll();
    rightMouseLockScroll = otherSettings->isRightMouseLockScroll();
    mouseScrollSpeed = otherSettings->getMouseScrollSpeed();
    mouseButtonScrollTime = otherSettings->getButtonScrollTime();
    touchpadRounded = otherSettings->isTouchpadRounded();
    touchpadRoundLimit = otherSettings->getTouchpadRoundLimit();
    touchpadInertia = otherSettings->isTouchpadInertia();
    touchpadInertiaRounded = otherSettings->isTouchpadInertiaRounded();
    touchpadInertiaThreshold = otherSettings->getTouchpadInertiaThreshold();
    touchpadInertiaStep = otherSettings->getTouchpadInertiaStep();

    displayUpdateDelay = otherSettings->getDisplayUpdateDelay();
    loadingScreen = otherSettings->getLoadingScreen();
    loadingScreenType = otherSettings->getLoadingScreenType();
    loadingScreenSpeed = otherSettings->getLoadingScreenSpeed();

    leds = otherSettings->isLeds();
    ledBrightness = otherSettings->getLedBrightness();

    inactive = otherSettings->isInactive();
    inactiveTime = otherSettings->getInactiveTime();

    sound = otherSettings->isSound();
    pressSound = otherSettings->isPressSound();
    pressSoundFrequency = otherSettings->getPressSoundFrequency();
    pressSoundDuration = otherSettings->getPressSoundDuration();
}

void Settings::setUSBMode(bool value) {
    usbMode = value;
}

void Settings::setUSB(bool value) {
    usb = value;
}

void Settings::setScreenFocus(bool value) {
    screenFocus = value;
}

void Settings::setShowLoadingScreen(bool value) {
    showLoadingScreen = value;
}

void Settings::setActiveMillis(unsigned long value) {
    activeMillis = value;
}

void Settings::setShowSleep(bool value) {
    showSleep = value;
}

void Settings::setNumLockUSB(bool value) {
    numLockUSB = value;
}

void Settings::setCapsLockUSB(bool value) {
    capsLockUSB = value;
}

void Settings::setScrollLockUSB(bool value) {
    scrollLockUSB = value;
}

void Settings::setNumLockBLE(bool value) {
    numLockBLE = value;
}

void Settings::setCapsLockBLE(bool value) {
    capsLockBLE = value;
}

void Settings::setScrollLockBLE(bool value) {
    scrollLockBLE = value;
}

void Settings::setLeftMouseLock(bool value) {
    leftMouseLock = value;
}

void Settings::setRightMouseLock(bool value) {
    rightMouseLock = value;
}

void Settings::setDebounce(bool value) {
    debounce = value;
}

void Settings::setDebounceTime(int value) {
    if (value < 1) value = 1;
    if (value > 100) value = 100;
    debounceTime = value;
}

void Settings::setButtonScroll(bool value) {
    buttonScroll = value;
}

void Settings::setButtonScrollDelay(int value) {
    if (value < 100) value = 100;
    if (value > 1000) value = 1000;
    buttonScrollDelay = value;
}

void Settings::setButtonScrollTime(int value) {
    if (value < 10) value = 10;
    if (value > 1000) value = 1000;
    buttonScrollTime = value;
}

void Settings::setMouseSpeed(float value) {
    if (value < 0.1) value = 0.1;
    if (value > 3) value = 3;
    mouseSpeed = value;
}

void Settings::setTouchpadScroll(bool value) {
    touchpadScroll = value;
}

void Settings::setMouseLockScroll(bool value) {
    mouseLockScroll = value;
}

void Settings::setLeftMouseLockScroll(bool value) {
    leftMouseLockScroll = value;
}

void Settings::setRightMouseLockScroll(bool value) {
    rightMouseLockScroll = value;
}

void Settings::setMouseScrollSpeed(float value) {
    if (value < 0.1) value = 0.1;
    if (value > 2) value = 2;
    mouseScrollSpeed = value;
}

void Settings::setMouseButtonScrollTime(int value) {
    if (value < 1) value = 1;
    if (value > 100) value = 100;
    mouseButtonScrollTime = value;
}

void Settings::setTouchpadRounded(bool value) {
    touchpadRounded = value;
}

void Settings::setTouchpadRoundLimit(int value) {
    if (value < 2) value = 2;
    if (value > 10) value = 10;
    touchpadRoundLimit = value;
}

void Settings::setTouchpadInertia(bool value) {
    touchpadInertia = value;
}

void Settings::setTouchpadInertiaRounded(bool value) {
    touchpadInertiaRounded = value;
}

void Settings::setTouchpadInertiaThreshold(int value) {
    if (value < 5) value = 5;
    if (value > 300) value = 300;
    touchpadInertiaThreshold = value;
}

void Settings::setTouchpadInertiaStep(int value) {
    if (value < 1) value = 1;
    if (value > 50) value = 50;
    touchpadInertiaStep = value;
}

void Settings::setDisplayUpdateDelay(int value) {
    if (value < 0) value = 0;
    if (value > 100) value = 100;
    displayUpdateDelay = value;
}

void Settings::setLoadingScreen(int value) {
    if (value < 0) value = 0;
    if (value > 1) value = 1;
    loadingScreen = value;
}

void Settings::setLoadingScreenType(int value) {
    if (value < 0) value = 0;
    if (value > 3 && loadingScreen == 0) value = 3;
    if (value > 1 && loadingScreen == 1) value = 1;
    loadingScreenType = value;
}

void Settings::setLoadingScreenSpeed(int value) {
    if (value < 1) value = 1;
    if (value > 10) value = 10;
    loadingScreenSpeed = value;
}

void Settings::setInactive(bool value) {
    inactive = value;
}

void Settings::setInactiveTime(int value) {
    if (value < 1) value = 1;
    if (value > 60) value = 60;
    inactiveTime = value;
}

void Settings::setLeds(bool value) {
    leds = value;
}

void Settings::setLedBrightness(int value) {
    if (value < 0) value = 0;
    if (value > 100) value = 100;
    ledBrightness = value;
}

void Settings::setSound(bool value) {
    sound = value;
}

void Settings::setPressSound(bool value) {
    pressSound = value;
}

void Settings::setPressSoundFrequency(int value) {
    if (value < 40) value = 40;
    if (value > 5000) value = 5000;
    pressSoundFrequency = value;
}

void Settings::setPressSoundDuration(int value) {
    if (value < 10) value = 10;
    if (value > 250) value = 250;
    pressSoundDuration = value;
}

bool Settings::isUSBMode() {
    return usbMode;
}

bool Settings::isUSB() {
    return usb;
}

bool Settings::isScreenFocus() {
    return screenFocus;
}

bool Settings::isShowLoadingScreen() {
    return showLoadingScreen;
}

unsigned long Settings::getActiveMillis() {
    return activeMillis;
}

bool Settings::isShowSleep() {
    return showSleep;
}

bool Settings::isNumLockUSB() {
    return numLockUSB;
}

bool Settings::isCapsLockUSB() {
    return capsLockUSB;
}

bool Settings::isScrollLockUSB() {
    return scrollLockUSB;
}

bool Settings::isNumLockBLE() {
    return numLockBLE;
}

bool Settings::isCapsLockBLE() {
    return capsLockBLE;
}

bool Settings::isScrollLockBLE() {
    return scrollLockBLE;
}

bool Settings::isLeftMouseLock() {
    return leftMouseLock;
}

bool Settings::isRightMouseLock() {
    return rightMouseLock;
}

bool Settings::isDebounce() {
    return debounce;
}

int Settings::getDebounceTime() {
    return debounceTime;
}

bool Settings::isButtonScroll() {
    return buttonScroll;
}

int Settings::getButtonScrollDelay() {
    return buttonScrollDelay;
}

int Settings::getButtonScrollTime() {
    return buttonScrollTime;
}

float Settings::getMouseSpeed() {
    return mouseSpeed;
}

bool Settings::isTouchpadScroll() {
    return touchpadScroll;
}

bool Settings::isMouseLockScroll() {
    return mouseLockScroll;
}

bool Settings::isLeftMouseLockScroll() {
    return leftMouseLockScroll;
}

bool Settings::isRightMouseLockScroll() {
    return rightMouseLockScroll;
}

float Settings::getMouseScrollSpeed() {
    return mouseScrollSpeed;
}

int Settings::getMouseButtonScrollTime() {
    return mouseButtonScrollTime;
}

bool Settings::isTouchpadRounded() {
    return touchpadRounded;
}

int Settings::getTouchpadRoundLimit() {
    return touchpadRoundLimit;
}

bool Settings::isTouchpadInertia() {
    return touchpadInertia;
}

bool Settings::isTouchpadInertiaRounded() {
    return touchpadInertiaRounded;
}

int Settings::getTouchpadInertiaThreshold() {
    return touchpadInertiaThreshold;
}

int Settings::getTouchpadInertiaStep() {
    return touchpadInertiaStep;
}

int Settings::getDisplayUpdateDelay() {
    return displayUpdateDelay;
}

int Settings::getLoadingScreen() {
    return loadingScreen;
}

int Settings::getLoadingScreenType() {
    return loadingScreenType;
}

int Settings::getLoadingScreenSpeed() {
    return loadingScreenSpeed;
}

bool Settings::isInactive() {
    return inactive;
}

int Settings::getInactiveTime() {
    return inactiveTime;
}

bool Settings::isLeds() {
    return leds;
}

int Settings::getLedBrightness() {
    return ledBrightness;
}

bool Settings::isSound() {
    return sound;
}

bool Settings::isPressSound() {
    return pressSound;
}

int Settings::getPressSoundFrequency() {
    return pressSoundFrequency;
}

int Settings::getPressSoundDuration() {
    return pressSoundDuration;
}