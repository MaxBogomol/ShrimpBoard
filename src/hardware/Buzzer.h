#pragma once

#include "../defines/Defines.h"
#include "../keyboard/Settings.h"

class Buzzer {
    private:
        Settings* settings;

    public:
        void playTone(unsigned int frequency, unsigned int duration);
        void playTone(unsigned int frequency);
        void playNoTone();

        void setSettings(Settings* settings);
        Settings& getSettings();
};