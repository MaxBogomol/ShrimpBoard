#include "../../SettingsEntry.h"
#include "ResetEPROMSettingsEntry.h"

String ResetEPROMSettingsEntry::getName() {
    return "Reset EPROM";
}

void ResetEPROMSettingsEntry::use() {
    if (getSettings().isPressSound()) getBuzzer().playTone(3000, 1000);
    getEPROM().reset();
}