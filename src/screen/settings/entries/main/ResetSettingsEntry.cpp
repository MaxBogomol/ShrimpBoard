#include "../../SettingsEntry.h"
#include "ResetSettingsEntry.h"

String ResetSettingsEntry::getName() {
    return "Reset settings";
}

void ResetSettingsEntry::use() {
    if (getSettings().isPressSound()) getBuzzer().playTone(3000, 500);
    getSettings().reset();
}