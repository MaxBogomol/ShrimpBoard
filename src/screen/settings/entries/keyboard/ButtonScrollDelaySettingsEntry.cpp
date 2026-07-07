#include "ButtonScrollDelaySettingsEntry.h"

String ButtonScrollDelaySettingsEntry::getName() {
    return "Scroll delay: " + String(getSettings().getButtonScrollDelay()) + " ms";
}

void ButtonScrollDelaySettingsEntry::left() {
    int value = getSettings().getButtonScrollDelay();
    if (value - 10 >= 100) {
        value -=10;
        getSettings().setButtonScrollDelay(value);
        playToneSettings();
    }
}

void ButtonScrollDelaySettingsEntry::right() {
    int value = getSettings().getButtonScrollDelay();
    if (value + 10 <= 1000) {
        value += 10;
        getSettings().setButtonScrollDelay(value);
        playToneSettings();
    }
}