#include "PressSoundFrequencySettingsEntry.h"

String PressSoundFrequencySettingsEntry::getName() {
    return "Frequency: " + String(getSettings().getPressSoundFrequency()) + " Hz";
}

void PressSoundFrequencySettingsEntry::left() {
    int value = getSettings().getPressSoundFrequency();
    if (value - 10 >= 40) {
        value -= 10;
        getSettings().setPressSoundFrequency(value);
        playToneSettings();
    }
}

void PressSoundFrequencySettingsEntry::right() {
    int value = getSettings().getPressSoundFrequency();
    if (value + 10 <= 5000) {
        value += 10;
        getSettings().setPressSoundFrequency(value);
        playToneSettings();
    }
}