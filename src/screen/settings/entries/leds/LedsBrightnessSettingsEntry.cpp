#include "LedsBrightnessSettingsEntry.h"

String LedsBrightnessSettingsEntry::getName() {
    return "Brightness: " + String(getSettings().getLedBrightness()) + "%";
}

void LedsBrightnessSettingsEntry::left() {
    int value = getSettings().getLedBrightness();
    if (value - 5 >= 0) {
        value -= 5;
        getSettings().setLedBrightness(value);
        playToneSettings();
    }
}

void LedsBrightnessSettingsEntry::right() {
    int value = getSettings().getLedBrightness();
    if (value + 5 <= 100) {
        value += 5;
        getSettings().setLedBrightness(value);
        playToneSettings();
    }
}