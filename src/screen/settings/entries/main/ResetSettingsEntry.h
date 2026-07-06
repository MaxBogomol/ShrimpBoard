#pragma once

#include "../../SettingsEntry.h"

class ResetSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void use() override;
};