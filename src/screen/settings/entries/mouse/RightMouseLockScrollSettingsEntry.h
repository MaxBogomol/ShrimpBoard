#pragma once

#include "../../SettingsEntry.h"

class RightMouseLockScrollSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void use() override;
};