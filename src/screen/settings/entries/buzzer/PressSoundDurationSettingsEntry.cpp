#include "../../SettingsEntry.h"
#include "PressSoundDurationSettingsEntry.h"

String PressSoundDurationSettingsEntry::getName() {
    return "Duration: " + String(getSettings().getPressSoundDuration()) + " ms";
}

void PressSoundDurationSettingsEntry::left() {
    int value = getSettings().getPressSoundDuration();
    if (value - 10 >= 10) {
        value -= 10;
        getSettings().setPressSoundDuration(value);
        playToneSettings();
    }
}

void PressSoundDurationSettingsEntry::right() {
    int value = getSettings().getPressSoundDuration();
    if (value + 10 <= 250) {
        value += 10;
        getSettings().setPressSoundDuration(value);
        playToneSettings();
    }
}