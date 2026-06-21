#pragma once

#include <Arduino.h>
#include <Wire.h>

class PS4Touchpad {
    private:
        uint8_t TOUCHPAD_ADDR = 0x4B;
        int MAX_X = 1920;
        int MAX_Y = 940;

        bool firstTouchPressed = false;
        int firstTouchX = 0;
        int firstTouchY = 0;
        bool secondTouchPressed = false;
        int secondTouchX = 0;
        int secondTouchY = 0;

    public:
        void read();

        void setAddress(uint8_t addr);
        void setMaxX(int max);
        void setMaxY(int max);

        uint8_t getAddress();
        int getMaxX();
        int getMaxY();

        bool isFirstPressed();
        int getFirstX();
        int getFirstY();
        
        bool isSecondPressed();
        int getSecondX();
        int getSecondY();

        double getFirstXLimited();
        double getFirstYLimited();
        double getSecondXLimited();
        double getSecondYLimited();
};