#include "../../SettingsEntry.h"
#include "TouchpadScrollSettingsEntry.h"

String TouchpadScrollSettingsEntry::getName() {
    return getBoolName("Touchpad scroll: ", getSettings().isTouchpadScroll());
}

void TouchpadScrollSettingsEntry::use() {
    getSettings().setTouchpadScroll(!getSettings().isTouchpadScroll());
    playToneSettings();
}