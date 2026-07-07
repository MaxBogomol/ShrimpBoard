#include "ShowLoadingScreenSettingsEntry.h"

String ShowLoadingScreenSettingsEntry::getName() {
    return "Show loading";
}

void ShowLoadingScreenSettingsEntry::use() {
    getSettings().setShowLoadingScreen(true);
    playToneSettings();
}