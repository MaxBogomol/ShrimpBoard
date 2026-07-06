#include "../../SettingsEntry.h"
#include "LeftMouseLockScrollSettingsEntry.h"

String LeftMouseLockScrollSettingsEntry::getName() {
    return getBoolName("L M lock scroll: ", getSettings().isLeftMouseLockScroll());
}

void LeftMouseLockScrollSettingsEntry::use() {
    getSettings().setLeftMouseLockScroll(!getSettings().isLeftMouseLockScroll());
    playToneSettings();
}