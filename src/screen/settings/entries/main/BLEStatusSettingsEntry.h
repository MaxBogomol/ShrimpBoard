#pragma once

#include "../../SettingsEntry.h"

class BLEStatusSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;
};