#include "TouchpadInertiaThresholdSettingsEntry.h"

String TouchpadInertiaThresholdSettingsEntry::getName() {
    return "Inertia threshold: " + String(getSettings().getTouchpadInertiaThreshold());
}

void TouchpadInertiaThresholdSettingsEntry::left() {
    int value = getSettings().getTouchpadInertiaThreshold();
    if (value - 5 >= 5) {
        value -= 5;
        getSettings().setTouchpadInertiaThreshold(value);
        playToneSettings();
    }
}

void TouchpadInertiaThresholdSettingsEntry::right() {
    int value = getSettings().getTouchpadInertiaThreshold();
    if (value + 5 <= 300) {
        value += 5;
        getSettings().setTouchpadInertiaThreshold(value);
        playToneSettings();
    }
}