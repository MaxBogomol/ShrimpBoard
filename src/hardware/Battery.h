#pragma once

#include "../defines/Defines.h"
#include "../keyboard/Settings.h"

class Battery {
    private:
        Settings* settings;

        float emaAlpha = 0.05;
        double filteredVoltage = -1;
        int roundLimit = 64;
        double voltageRound[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    public:
        void read();

        int getPercentage(float x);
        int getPercentage();
        int getPercentageRounded();
        double getRawVoltage();
        double getVoltage();
        double getVoltageRounded();

        int getRoundLimit();

        void setSettings(Settings* settings);
        Settings& getSettings();
};