#include "SettingsIndex.h"

void SettingsIndex::setScreen(Screen* screen) {
    this->screen = screen;
}

Screen& SettingsIndex::getScreen() {
    return *this->screen;
}

void SettingsIndex::setBitmap(const uint8_t BMP[]) {
    this->BMP = BMP;
}

const uint8_t (*SettingsIndex::getBitmap()) {
    return BMP;
}