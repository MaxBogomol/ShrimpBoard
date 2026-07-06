#pragma once

#include "../../SettingsEntry.h"

class TouchpadInertiaRoundedSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void use() override;
};