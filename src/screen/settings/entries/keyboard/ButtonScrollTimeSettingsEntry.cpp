#include "ButtonScrollTimeSettingsEntry.h"

String ButtonScrollTimeSettingsEntry::getName() {
    return "Scroll time: " + String(getSettings().getButtonScrollTime()) + " ms";
}

void ButtonScrollTimeSettingsEntry::left() {
    int value = getSettings().getButtonScrollTime();
    if (value - 10 >= 10) {
        value -= 10;
        getSettings().setButtonScrollTime(value);
        playToneSettings();
    }
}

void ButtonScrollTimeSettingsEntry::right() {
    int value = getSettings().getButtonScrollTime();
    if (value + 10 <= 1000) {
        value += 10;
        getSettings().setButtonScrollTime(value);
        playToneSettings();
    }
}