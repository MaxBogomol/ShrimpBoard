#pragma once

#include "../../SettingsEntry.h"

class ShowLoadingScreenSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void use() override;
};