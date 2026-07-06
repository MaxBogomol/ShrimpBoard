#include "../../SettingsEntry.h"
#include "RightMouseLockScrollSettingsEntry.h"

String RightMouseLockScrollSettingsEntry::getName() {
    return getBoolName("R M lock scroll: ", getSettings().isRightMouseLockScroll());
}

void RightMouseLockScrollSettingsEntry::use() {
    getSettings().setRightMouseLockScroll(!getSettings().isRightMouseLockScroll());
    playToneSettings();
}