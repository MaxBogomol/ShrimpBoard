#pragma once

#include "../defines/Defines.h"
#include "../keyboard/Settings.h"

class Battery {
    private:
        Settings* settings;

    public:
        int getPercentage();
        double getRawVoltage();
        double getVoltage();

        void setSettings(Settings* settings);
        Settings& getSettings();
};