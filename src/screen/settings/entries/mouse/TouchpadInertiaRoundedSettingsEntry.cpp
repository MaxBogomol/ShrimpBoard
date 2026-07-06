#include "../../SettingsEntry.h"
#include "TouchpadInertiaRoundedSettingsEntry.h"

String TouchpadInertiaRoundedSettingsEntry::getName() {
    return getBoolName("Inertia rounded: ", getSettings().isTouchpadInertiaRounded());
}

void TouchpadInertiaRoundedSettingsEntry::use() {
    getSettings().setTouchpadInertiaRounded(!getSettings().isTouchpadInertiaRounded());
    playToneSettings();
}