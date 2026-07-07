#include "TouchpadInertiaSettingsEntry.h"

String TouchpadInertiaSettingsEntry::getName() {
    return getBoolName("Inertia: ", getSettings().isTouchpadInertia());
}

void TouchpadInertiaSettingsEntry::use() {
    getSettings().setTouchpadInertia(!getSettings().isTouchpadInertia());
    playToneSettings();
}