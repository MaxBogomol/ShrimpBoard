#include "DebounceTimeSettingsEntry.h"

String DebounceTimeSettingsEntry::getName() {
    return "Debounce time: " + String(getSettings().getDebounceTime()) + " ms";
}

void DebounceTimeSettingsEntry::left() {
    int value = getSettings().getDebounceTime();
    if (value - 1 >= 1) {
        value--;
        getSettings().setDebounceTime(value);
        playToneSettings();
    }
}

void DebounceTimeSettingsEntry::right() {
    int value = getSettings().getDebounceTime();
    if (value + 1 <= 100) {
        value++;
        getSettings().setDebounceTime(value);
        playToneSettings();
    }
}