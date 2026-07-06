#include "../../SettingsEntry.h"
#include "InactiveSettingsEntry.h"

String InactiveSettingsEntry::getName() {
    return getBoolName("Inactive: ", getSettings().isInactive());
}

void InactiveSettingsEntry::use() {
    getSettings().setInactive(!getSettings().isInactive());
    playToneSettings();
}