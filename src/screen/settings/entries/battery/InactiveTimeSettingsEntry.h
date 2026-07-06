#pragma once

#include "../../SettingsEntry.h"

class InactiveTimeSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void left() override;
        virtual void right() override;
};