#pragma once

#include "../../SettingsEntry.h"

class TouchpadInertiaSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void use() override;
};