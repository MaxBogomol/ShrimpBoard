#pragma once

#include "../../SettingsEntry.h"

class ButtonScrollSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void use() override;
};