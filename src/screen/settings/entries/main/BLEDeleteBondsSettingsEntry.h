#pragma once

#include "../../SettingsEntry.h"

class BLEDeleteBondsSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void use() override;
};