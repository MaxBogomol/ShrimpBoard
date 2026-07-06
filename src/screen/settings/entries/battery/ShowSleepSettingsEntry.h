#pragma once

#include "../../SettingsEntry.h"

class ShowSleepSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void use() override;
};