#include "MouseScrollSpeedSettingsEntry.h"

String MouseScrollSpeedSettingsEntry::getName() {
    return "Scroll speed: " + String(getSettings().getMouseScrollSpeed());
}

void MouseScrollSpeedSettingsEntry::left() {
    float value = getSettings().getMouseScrollSpeed();
    if (value - 0.1 >= 0.09) {
        value -= 0.1;
        getSettings().setMouseScrollSpeed(value);
        playToneSettings();
    }
}

void MouseScrollSpeedSettingsEntry::right() {
    float value = getSettings().getMouseScrollSpeed();
    if (value + 0.1 <= 2.01) {
        value += 0.1;
        getSettings().setMouseScrollSpeed(value);
        playToneSettings();
    }
}