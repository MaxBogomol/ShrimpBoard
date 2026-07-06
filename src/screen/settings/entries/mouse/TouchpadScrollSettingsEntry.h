#pragma once

#include "../../SettingsEntry.h"

class TouchpadScrollSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void use() override;
};