#include "ShowSleepSettingsEntry.h"

String ShowSleepSettingsEntry::getName() {
    return "Sleep";
}

void ShowSleepSettingsEntry::use() {
    getSettings().setShowSleep(true);
}