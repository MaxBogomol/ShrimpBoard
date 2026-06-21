#pragma once

#include <Arduino.h>

#include "../defines/Defines.h"
#include "../keyboard/Settings.h"

class Leds {
    private:
        Settings* settings;

    public:
        void setNumLockBrightness(int brightness);
        void setCapsLockBrightness(int brightness);
        void setScrollLockBrightness(int brightness);
        void setLeftMouseLockBrightness(int brightness);
        void setRightMouseLockBrightness(int brightness);
        void setSpecialBrightness(int brightness);

        void setLedBrightness(int pin, int brightness);
        void setLedBrightnessRaw(int pin, int brightness);
        void setLedWrite(int pin, int value);
        void setLedWriteRaw(int pin, int value);

        void disableAll();

        void setSettings(Settings* settings);
        Settings& getSettings();
};