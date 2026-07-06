#include "SettingsEntry.h"

#include "../../keyboard/ShrimpBoard.h"

String SettingsEntry::getName() {
    return "Entry";
}

void SettingsEntry::setShrimpBoard(ShrimpBoard* shrimpBoard) {
    this->shrimpBoard = shrimpBoard;
}

ShrimpBoard& SettingsEntry::getShrimpBoard() {
    return *this->shrimpBoard;
}

bool SettingsEntry::hasNextScreen() {
    return false;
}

void SettingsEntry::setNextScreen(Screen* nextScreen) {
    this->nextScreen = nextScreen;
}

Screen& SettingsEntry::getNextScreen() {
    return *this->nextScreen;
}

String SettingsEntry::getBoolName(String name, bool value) {
    if (value) {
        name = name + "+";
    } else {
        name = name + "-";
    }
    return name;
}

void SettingsEntry::playTone() {
    int frequency = getSettings().getPressSoundFrequency();
    int duration = getSettings().getPressSoundDuration();
    getBuzzer().playNoTone();
    getBuzzer().playTone(frequency, duration);
}

void SettingsEntry::playToneSettings() {
    if (getSettings().isPressSound()) playTone();
}

Settings& SettingsEntry::getSettings() {
    return getShrimpBoard().getSettings();
}

ButtonMatrix& SettingsEntry::getButtonMatrix() {
    return getShrimpBoard().getButtonMatrix();
}

Battery& SettingsEntry::getBattery() {
    return getShrimpBoard().getBattery();
}

Leds& SettingsEntry::getLeds() {
    return getShrimpBoard().getLeds();
}

Buzzer& SettingsEntry::getBuzzer() {
    return getShrimpBoard().getBuzzer();
}

Keyboard& SettingsEntry::getKeyboard() {
    return getShrimpBoard().getKeyboard();
}

Touchpad& SettingsEntry::getTouchpad() {
    return getShrimpBoard().getTouchpad();
}

Display& SettingsEntry::getDisplay() {
    return getShrimpBoard().getDisplay();
}

EPROM& SettingsEntry::getEPROM() {
    return getShrimpBoard().getEPROM();
}