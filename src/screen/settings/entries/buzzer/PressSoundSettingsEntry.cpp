#include "../../SettingsEntry.h"
#include "PressSoundSettingsEntry.h"

String PressSoundSettingsEntry::getName() {
    return getBoolName("Press sound: ", getSettings().isPressSound());
}

void PressSoundSettingsEntry::use() {
    getSettings().setPressSound(!getSettings().isPressSound());
    playToneSettings();
}