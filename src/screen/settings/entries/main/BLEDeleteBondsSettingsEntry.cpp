#include "BLEDeleteBondsSettingsEntry.h"

#include <NimBLEDevice.h>

String BLEDeleteBondsSettingsEntry::getName() {
    return "Delete bonds";
}

void BLEDeleteBondsSettingsEntry::use() {
    if (getSettings().isPressSound()) getBuzzer().playTone(3000, 500);
    NimBLEDevice::deleteAllBonds();
}