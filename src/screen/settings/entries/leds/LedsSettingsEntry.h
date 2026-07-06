#pragma once

#include "../../SettingsEntry.h"

class LedsSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void use() override;
};