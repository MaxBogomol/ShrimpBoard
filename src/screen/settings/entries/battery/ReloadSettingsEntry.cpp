#include "../../SettingsEntry.h"
#include "ReloadSettingsEntry.h"

String ReloadSettingsEntry::getName() {
    return "Reload";
}

void ReloadSettingsEntry::use() {
    ESP.restart();
}