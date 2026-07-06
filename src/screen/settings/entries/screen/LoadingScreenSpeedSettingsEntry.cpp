#include "../../SettingsEntry.h"
#include "LoadingScreenSpeedSettingsEntry.h"

String LoadingScreenSpeedSettingsEntry::getName() {
    return "Loading speed: " + String(getSettings().getLoadingScreenSpeed());
}

void LoadingScreenSpeedSettingsEntry::left() {
    int value = getSettings().getLoadingScreenSpeed();
    if (value - 1 >= 1) {
        value--;
        getSettings().setLoadingScreenSpeed(value);
        playToneSettings();
    }
}

void LoadingScreenSpeedSettingsEntry::right() {
    int value = getSettings().getLoadingScreenSpeed();
    if (value + 1 <= 10) {
        value++;
        getSettings().setLoadingScreenSpeed(value);
        playToneSettings();
    }
}