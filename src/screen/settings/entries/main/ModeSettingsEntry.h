#pragma once

#include "../../SettingsEntry.h"

class ModeSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void use() override;
};