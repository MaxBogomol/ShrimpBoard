#include "TouchpadInertiaStepSettingsEntry.h"

String TouchpadInertiaStepSettingsEntry::getName() {
    return "Inertia step: " + String(getSettings().getTouchpadInertiaStep());
}

void TouchpadInertiaStepSettingsEntry::left() {
    int value = getSettings().getTouchpadInertiaStep();
    if (value - 1 >= 1) {
        value--;
        getSettings().setTouchpadInertiaStep(value);
        playToneSettings();
    }
}

void TouchpadInertiaStepSettingsEntry::right() {
    int value = getSettings().getTouchpadInertiaStep();
    if (value + 1 <= 50) {
        value++;
        getSettings().setTouchpadInertiaStep(value);
        playToneSettings();
    }
}