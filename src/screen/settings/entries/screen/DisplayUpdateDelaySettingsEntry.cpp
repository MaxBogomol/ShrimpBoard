#include "DisplayUpdateDelaySettingsEntry.h"

String DisplayUpdateDelaySettingsEntry::getName() {
    return "Update delay: " + String(getSettings().getDisplayUpdateDelay()) + " ms";
}

void DisplayUpdateDelaySettingsEntry::left() {
    int value = getSettings().getDisplayUpdateDelay();
    if (value - 5 >= 0) {
        value -=5;
        getSettings().setDisplayUpdateDelay(value);
        playToneSettings();
    }
}

void DisplayUpdateDelaySettingsEntry::right() {
    int value = getSettings().getDisplayUpdateDelay();
    if (value + 5 <= 100) {
        value += 5;
        getSettings().setDisplayUpdateDelay(value);
        playToneSettings();
    }
}