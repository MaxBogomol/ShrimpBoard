#include "LedsSettingsEntry.h"

String LedsSettingsEntry::getName() {
    return getBoolName("LEDs: ", getSettings().isLeds());
}

void LedsSettingsEntry::use() {
    getSettings().setLeds(!getSettings().isLeds());
    playToneSettings();
}