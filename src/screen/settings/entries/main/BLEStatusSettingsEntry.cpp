#include "../../SettingsEntry.h"
#include "BLEStatusSettingsEntry.h"

#include "../../../../keyboard/ShrimpBoard.h"

String BLEStatusSettingsEntry::getName() {
    return getBoolName("BLE: ", getShrimpBoard().isBLEConnected());
}