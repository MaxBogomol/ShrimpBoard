#pragma once

#include "../defines/Defines.h"
#include "../keyboard/Settings.h"
#include "PS4Touchpad.h"

class Touchpad {
    private:
        PS4Touchpad* touchpad;

        Settings* settings;

        bool firstTouch = false;
        int firstTouchX = 0;
        int firstTouchY = 0;
        bool secondTouch = false;
        int secondTouchX = 0;
        int secondTouchY = 0;

        bool firstTouchOld = false;
        int firstTouchXOld = 0;
        int firstTouchYOld = 0;
        bool secondTouchOld = false;
        int secondTouchXOld = 0;
        int secondTouchYOld = 0;

        int firstTouchNormalized = 0;
        int secondTouchNormalized = 0;

        int firstTouchXMoved = 0;
        int firstTouchYMoved = 0;
        int secondTouchXMoved = 0;
        int secondTouchYMoved = 0;

        float firstTouchXRounded = 0;
        float firstTouchYRounded = 0;
        float secondTouchXRounded = 0;
        float secondTouchYRounded = 0;

        float firstTouchXInertial = 0;
        float firstTouchYInertial = 0;
        float secondTouchXInertial = 0;
        float secondTouchYInertial = 0;

        float firstRound[10][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
        float secondRound[10][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

    public:
        void setup();
        void read();

        PS4Touchpad& getTouchpad();
        void setSettings(Settings* settings);
        Settings& getSettings();

        int getMaxX();
        int getMaxY();
        int getRoundLimit();
        int getInertiaThreshold();
        int getInertiaStep();
        int normalizeValue(bool button, bool buttonOld);
        int inertiaValue(int value, int inertiaStep);
        int getFirstX();
        int getFirstY();
        int getSecondX();
        int getSecondY();
        int getFirstXOld();
        int getFirstYOld();
        int getSecondXOld();
        int getSecondYOld();
        int getFirstXMoved();
        int getFirstYMoved();
        int getSecondXMoved();
        int getSecondYMoved();
        float getFirstXRounded();
        float getFirstYRounded();
        float getSecondXRounded();
        float getSecondYRounded();
        float getFirstXInertial();
        float getFirstYInertial();
        float getSecondXInertial();
        float getSecondYInertial();
        int getFirstTouchValue();
        bool isFirstTouchPress();
        bool isFirstTouchPressed();
        bool isFirstTouchRelease();
        int getSecondTouchValue();
        bool isSecondTouchPress();
        bool isSecondTouchPressed();
        bool isSecondTouchRelease();
};