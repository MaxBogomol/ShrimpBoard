#include "MouseLockScrollSettingsEntry.h"

String MouseLockScrollSettingsEntry::getName() {
    return getBoolName("M lock scroll: ", getSettings().isMouseLockScroll());
}

void MouseLockScrollSettingsEntry::use() {
    getSettings().setMouseLockScroll(!getSettings().isMouseLockScroll());
    playToneSettings();
}