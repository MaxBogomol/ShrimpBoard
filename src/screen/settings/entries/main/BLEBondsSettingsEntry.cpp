#include "BLEBondsSettingsEntry.h"

#include <NimBLEDevice.h>

String BLEBondsSettingsEntry::getName() {
    return "Bonds: " + String(NimBLEDevice::getNumBonds());
}