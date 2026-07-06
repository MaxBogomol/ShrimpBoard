#include "../../SettingsEntry.h"
#include "USBStatusSettingsEntry.h"

String USBStatusSettingsEntry::getName() {
    return getBoolName("USB: ", getSettings().isUSB());
}