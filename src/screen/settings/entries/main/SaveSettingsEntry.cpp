#include "../../SettingsEntry.h"
#include "SaveSettingsEntry.h"

String SaveSettingsEntry::getName() {
    return "Save settings";
}

void SaveSettingsEntry::use() {
    if (getSettings().isPressSound()) getBuzzer().playTone(2000, 50);
    getEPROM().save();
}