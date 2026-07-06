#include "../../SettingsEntry.h"
#include "InactiveTimeSettingsEntry.h"

String InactiveTimeSettingsEntry::getName() {
    return "Inactive time: " + String(getSettings().getInactiveTime()) + " min";
}

void InactiveTimeSettingsEntry::left() {
    int value = getSettings().getInactiveTime();
    if (value - 1 >= 1) {
        value--;
        getSettings().setInactiveTime(value);
        playToneSettings();
    }
}

void InactiveTimeSettingsEntry::right() {
    int value = getSettings().getInactiveTime();
    if (value + 1 <= 60) {
        value++;
        getSettings().setInactiveTime(value);
        playToneSettings();
    }
}