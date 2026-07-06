#pragma once

#include <Arduino.h>
#include "soc/rtc_cntl_reg.h"
#include <BleCompositeHID.h>
#include <KeyboardDevice.h>
#include <MouseDevice.h>
#include <USBHIDKeyboard.h>
#include <USBHIDMouse.h>
#include "USBHIDConsumerControl.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <at24c256.h>
#include "USB.h"
#include <Wire.h>
#include <SPI.h>

#include "../defines/Defines.h"
#include "../defines/ScanCodes.h"
#include "../defines/ScanMatrix.h"

#include "../keyboard/Settings.h"
#include "../hardware/ButtonMatrix.h"
#include "../hardware/Battery.h"
#include "../hardware/Leds.h"
#include "../hardware/Buzzer.h"
#include "../hardware/Keyboard.h"
#include "../hardware/Touchpad.h"
#include "../hardware/Display.h"
#include "../hardware/EPROM.h"
#include "../screen/Interface.h"

class ShrimpBoard {
    private:
        KeyboardDevice* keyboardBLE;
        MouseDevice* mouseBLE;
        BleCompositeHID* compositeHID;
        USBHIDKeyboard keyboardUSB;
        USBHIDMouse mouseUSB;
        USBHIDConsumerControl consumerControl;
        Settings* settings;
        ButtonMatrix buttonMatrix;
        Battery battery;
        Leds leds;
        Buzzer buzzer;
        Keyboard keyboard;
        Touchpad touchpad;
        Display display;
        EPROM eprom;
        Interface interface;

        int sleepCount = 0;
        int awakeCount = 0;

        bool screenFocus = false;
        bool mouseScroll = false;

        bool leftMouseUp = false;
        bool leftMouseDown = false;
        bool rightMouseUp = false;
        bool rightMouseDown = false;
        unsigned long leftMouseUpMillis = 0;
        unsigned long leftMouseDownMillis = 0;
        unsigned long rightMouseUpMillis = 0;
        unsigned long rightMouseDownMillis = 0;

    public:
        void setup();
        void setupPins();
        void setupBLE();
        void setupUSB();
        void setupButtonMatrix();
        void setupKeyboard();
        void setupTouchpad();
        void setupDisplay();
        void setupEPROM();
        void setupInterface();
        void setupSettings();
        void setupScreens();

        void loop();
        void loopSleep();
        void loopLeds();
        void loopKeyboard();
        void loopMouse();
        void loopInterface();

        bool isBLEConnected();
        bool isUSBMode();
        bool isUseUSB();
        bool isUseBLE();
        bool isMouseScroll();

        bool isModifierKey(uint8_t k);
        void keyboardPress(uint8_t k);
        void keyboardRelease(uint8_t k);
        void keyboardReleaseAll();
        void mousePress(uint8_t b);
        void mouseRelease(uint8_t b);
        void mouseReleaseAll();
        void mouseMove(int x, int y, int wheel, int pan);
        void mouseMove(int x, int y, int wheel);
        void mouseMove(int x, int y);
        void mediaPress(int row, int collumn);
        void mediaPressUSB(uint16_t c);
        void mediaPressBLE(uint32_t c);
        void mediaRelease(int row, int collumn);
        void mediaReleaseUSB();
        void mediaReleaseBLE(uint32_t c);

        Settings& getSettings();
        ButtonMatrix& getButtonMatrix();
        Battery& getBattery();
        Leds& getLeds();
        Buzzer& getBuzzer();
        Keyboard& getKeyboard();
        Touchpad& getTouchpad();
        Display& getDisplay();
        EPROM& getEPROM();
        Interface& getInterface();
};