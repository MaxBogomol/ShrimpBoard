#pragma once

#include "../keyboard/Settings.h"
#include "../hardware/ButtonMatrix.h"
#include "../hardware/Battery.h"
#include "../hardware/Leds.h"
#include "../hardware/Buzzer.h"
#include "../hardware/Keyboard.h"
#include "../hardware/Touchpad.h"
#include "../hardware/Display.h"
#include "../hardware/EPROM.h"

class ShrimpBoard;

class Screen {
    private:
        ShrimpBoard* shrimpBoard;

        Screen* nextScreen;

    public:
        virtual void begin();
        virtual void loop() {};
        virtual void end() {};

        void setShrimpBoard(ShrimpBoard* shrimpBoard);

        ShrimpBoard& getShrimpBoard();

        virtual bool hasNextScreen();
        virtual void setNextScreen(Screen* nextScreen);
        virtual Screen& getNextScreen();

        virtual bool isScreenFocus();

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