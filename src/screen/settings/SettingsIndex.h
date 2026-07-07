#pragma once

#include <Arduino.h>

#include "../../defines/Images.h"
#include "../Screen.h"

class SettingsIndex {
    private:
        Screen* screen;
        const uint8_t* BMP = SETTINGS_BMP;

    public:
        void setScreen(Screen* screen);
        Screen& getScreen();

        void setBitmap(const uint8_t BMP[]);
        const uint8_t (*getBitmap());
};