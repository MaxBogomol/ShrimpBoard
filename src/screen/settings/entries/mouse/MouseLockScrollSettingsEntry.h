#pragma once

#include "../../SettingsEntry.h"

class MouseLockScrollSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void use() override;
};