#include "../../SettingsEntry.h"
#include "DebounceSettingsEntry.h"

String DebounceSettingsEntry::getName() {
    return getBoolName("Debounce: ", getSettings().isDebounce());
}

void DebounceSettingsEntry::use() {
    getSettings().setDebounce(!getSettings().isDebounce());
    playToneSettings();
}
