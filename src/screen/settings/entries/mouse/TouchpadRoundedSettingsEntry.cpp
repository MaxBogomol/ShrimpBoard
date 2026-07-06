#include "../../SettingsEntry.h"
#include "TouchpadRoundedSettingsEntry.h"

String TouchpadRoundedSettingsEntry::getName() {
    return getBoolName("Rounded: ", getSettings().isTouchpadRounded());
}

void TouchpadRoundedSettingsEntry::use() {
    getSettings().setTouchpadRounded(!getSettings().isTouchpadRounded());
    playToneSettings();
}