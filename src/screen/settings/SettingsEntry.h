#pragma once

#include "../Screen.h"

#include "../../keyboard/Settings.h"
#include "../../hardware/ButtonMatrix.h"
#include "../../hardware/Battery.h"
#include "../../hardware/Leds.h"
#include "../../hardware/Buzzer.h"
#include "../../hardware/Keyboard.h"
#include "../../hardware/Touchpad.h"
#include "../../hardware/Display.h"
#include "../../hardware/EPROM.h"

class ShrimpBoard;

class SettingsEntry {
    private:
        ShrimpBoard* shrimpBoard;

        Screen* nextScreen;

    public:
        virtual String getName();

        virtual void use() {};
        virtual void left() {};
        virtual void right() {};

        void setShrimpBoard(ShrimpBoard* shrimpBoard);

        ShrimpBoard& getShrimpBoard();

        virtual bool hasNextScreen();
        virtual void setNextScreen(Screen* nextScreen);
        virtual Screen& getNextScreen();

        String getBoolName(String name, bool value);
        void playTone();
        void playToneSettings();

        Settings& getSettings();
        ButtonMatrix& getButtonMatrix();
        Battery& getBattery();
        Leds& getLeds();
        Buzzer& getBuzzer();
        Keyboard& getKeyboard();
        Touchpad& getTouchpad();
        Display& getDisplay();
        EPROM& getEPROM();
};