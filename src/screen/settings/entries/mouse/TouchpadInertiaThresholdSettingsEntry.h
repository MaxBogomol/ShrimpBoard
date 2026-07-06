#pragma once

#include "../../SettingsEntry.h"

class TouchpadInertiaThresholdSettingsEntry : public SettingsEntry {
    public:
        virtual String getName() override;

        virtual void left() override;
        virtual void right() override;
};