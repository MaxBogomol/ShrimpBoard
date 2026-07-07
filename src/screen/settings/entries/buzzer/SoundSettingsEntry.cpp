#include "SoundSettingsEntry.h"

String SoundSettingsEntry::getName() {
    return getBoolName("Sound: ", getSettings().isSound());
}

void SoundSettingsEntry::use() {
    getSettings().setSound(!getSettings().isSound());
    playToneSettings();
}