#include "Screen.h"

#include "../keyboard/ShrimpBoard.h"

void Screen::begin() {
    getDisplay().clear();
    getDisplay().update();
}

void Screen::setShrimpBoard(ShrimpBoard* shrimpBoard) {
    this->shrimpBoard = shrimpBoard;
}

ShrimpBoard& Screen::getShrimpBoard() {
    return *this->shrimpBoard;
}

bool Screen::hasNextScreen() {
    return false;
}

void Screen::setNextScreen(Screen* nextScreen) {
    this->nextScreen = nextScreen;
}

Screen& Screen::getNextScreen() {
    return *this->nextScreen;
}

bool Screen::isScreenFocus() {
    return getKeyboard().isFNPressed() && getKeyboard().isEscPress();
}

Settings& Screen::getSettings() {
    return getShrimpBoard().getSettings();
}

ButtonMatrix& Screen::getButtonMatrix() {
    return getShrimpBoard().getButtonMatrix();
}

Battery& Screen::getBattery() {
    return getShrimpBoard().getBattery();
}

Leds& Screen::getLeds() {
    return getShrimpBoard().getLeds();
}

Buzzer& Screen::getBuzzer() {
    return getShrimpBoard().getBuzzer();
}

Keyboard& Screen::getKeyboard() {
    return getShrimpBoard().getKeyboard();
}

Touchpad& Screen::getTouchpad() {
    return getShrimpBoard().getTouchpad();
}

Display& Screen::getDisplay() {
    return getShrimpBoard().getDisplay();
}

EPROM& Screen::getEPROM() {
    return getShrimpBoard().getEPROM();
}