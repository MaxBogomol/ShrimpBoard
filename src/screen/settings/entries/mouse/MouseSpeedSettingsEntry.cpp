#include "../../SettingsEntry.h"
#include "MouseSpeedSettingsEntry.h"

String MouseSpeedSettingsEntry::getName() {
    return "Mouse speed: " + String(getSettings().getMouseSpeed());
}

void MouseSpeedSettingsEntry::left() {
    float value = getSettings().getMouseSpeed();
    if (value - 0.1 >= 0.09) {
        value -= 0.1;
        getSettings().setMouseSpeed(value);
        playToneSettings();
    }
}

void MouseSpeedSettingsEntry::right() {
    float value = getSettings().getMouseSpeed();
    if (value + 0.1 <= 3.01) {
        value += 0.1;
        getSettings().setMouseSpeed(value);
        playToneSettings();
    }
}