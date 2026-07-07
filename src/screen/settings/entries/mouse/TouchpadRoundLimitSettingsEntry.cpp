#include "TouchpadRoundLimitSettingsEntry.h"

String TouchpadRoundLimitSettingsEntry::getName() {
    return "Round limit: " + String(getSettings().getTouchpadRoundLimit());
}

void TouchpadRoundLimitSettingsEntry::left() {
    int value = getSettings().getTouchpadRoundLimit();
    if (value - 1 >= 2) {
        value--;
        getSettings().setTouchpadRoundLimit(value);
        playToneSettings();
    }
}

void TouchpadRoundLimitSettingsEntry::right() {
    int value = getSettings().getTouchpadRoundLimit();
    if (value + 1 <= 10) {
        value++;
        getSettings().setTouchpadRoundLimit(value);
        playToneSettings();
    }
}