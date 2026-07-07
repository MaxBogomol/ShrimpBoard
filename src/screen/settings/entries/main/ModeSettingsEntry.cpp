#include "ModeSettingsEntry.h"

String ModeSettingsEntry::getName() {
    String name = "Mode: ";
    if (getSettings().isUSBMode()) {
        name = name + "USB";
    } else {
        name = name + "BLE";
    }
    return name;
}

void ModeSettingsEntry::use() {
    getSettings().setUSBMode(!getSettings().isUSBMode());
    playToneSettings();
}