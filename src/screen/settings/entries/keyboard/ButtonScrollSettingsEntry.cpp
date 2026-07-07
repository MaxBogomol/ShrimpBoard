#include "ButtonScrollSettingsEntry.h"

String ButtonScrollSettingsEntry::getName() {
    return getBoolName("Scroll: ", getSettings().isButtonScroll());
}

void ButtonScrollSettingsEntry::use() {
    getSettings().setButtonScroll(!getSettings().isButtonScroll());
    playToneSettings();
}