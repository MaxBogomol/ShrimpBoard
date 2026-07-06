#pragma once

#include "../../SettingsEntry.h"

class ReloadSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void use() override;
};