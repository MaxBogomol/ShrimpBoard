#include "VoltageSettingsEntry.h"

String VoltageSettingsEntry::getName() {
    return "Voltage: " + String(getBattery().getVoltageRounded());
}