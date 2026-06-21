#pragma once

#include <Arduino.h>
#include <BleCompositeHID.h>

#include "../defines/Images.h"
#include "../keyboard/Settings.h"
#include "../hardware/ButtonMatrix.h"
#include "../hardware/Battery.h"
#include "../hardware/Leds.h"
#include "../hardware/Buzzer.h"
#include "../hardware/Touchpad.h"
#include "../hardware/Display.h"
#include "../hardware/EPROM.h"
#include "Screen.h"
#include "LoadingScreens.h"
#include "MainScreens.h"
#include "SettingsScreens.h"
#include "../games/BadApple.h"

class Interface {
    private:
        Settings* settings;

        BleCompositeHID* compositeHID;

        ButtonMatrix* buttonMatrix;
        Battery* battery;
        Leds* leds;
        Buzzer* buzzer;
        Touchpad* touchpad;
        Display* display;
        EPROM* eprom;

        Screen* screen;

        LoadingLinesScreen loadingLinesScreen;
        LoadingShrimpBoardScreen loadingShrimpBoardScreen;

        MainScreen mainScreen;

        SettingsScreen settingsScreen;

        SettingsIndexScreen mainSettingsIndexScreen;
        SettingsIndexScreen keyboardSettingsIndexScreen;
        SettingsIndexScreen mouseSettingsIndexScreen;
        SettingsIndexScreen screenSettingsIndexScreen;
        SettingsIndexScreen batterySettingsIndexScreen;
        SettingsIndexScreen ledsSettingsIndexScreen;
        SettingsIndexScreen buzzerSettingsIndexScreen;
        SettingsScreen gamesSettingsIndexScreen;

        ModeSettingsEntry modeSettingsEntry;
        USBStatusSettingsEntry usbStatusSettingsEntry;
        BLEStatusSettingsEntry bleStatusSettingsEntry;
        SaveSettingsEntry saveSettingsEntry;
        ResetSettingsEntry resetSettingsEntry;
        ResetEPROMSettingsEntry resetEPROMSettingsEntry;

        DebounceSettingsEntry debounceSettingsEntry;
        DebounceTimeSettingsEntry debounceTimeSettingsEntry;
        ButtonScrollSettingsEntry buttonScrollSettingsEntry;
        ButtonScrollDelaySettingsEntry buttonScrollDelaySettingsEntry;
        ButtonScrollTimeSettingsEntry buttonScrollTimeSettingsEntry;

        MouseSpeedSettingsEntry mouseSpeedSettingsEntry;
        TouchpadScrollSettingsEntry touchpadScrollSettingsEntry;
        MouseLockScrollSettingsEntry mouseLockScrollSettingsEntry;
        LeftMouseLockScrollSettingsEntry leftMouseLockScrollSettingsEntry;
        RightMouseLockScrollSettingsEntry rightMouseLockScrollSettingsEntry;
        MouseScrollSpeedSettingsEntry mouseScrollSpeedSettingsEntry;
        MouseButtonScrollTimeSettingsEntry mouseButtonScrollTimeSettingsEntry;
        TouchpadRoundedSettingsEntry touchpadRoundedSettingsEntry;
        TouchpadRoundLimitSettingsEntry touchpadRoundLimitSettingsEntry;
        TouchpadInertiaSettingsEntry touchpadInertiaSettingsEntry;
        TouchpadInertiaRoundedSettingsEntry touchpadInertiaRoundedSettingsEntry;
        TouchpadInertiaThresholdSettingsEntry touchpadInertiaThresholdSettingsEntry;
        TouchpadInertiaStepSettingsEntry touchpadInertiaStepSettingsEntry;

        DisplayUpdateDelaySettingsEntry displayUpdateDelaySettingsEntry;
        LoadingScreenSettingsEntry loadingScreenSettingsEntry;
        LoadingScreenTypeSettingsEntry loadingScreenTypeSettingsEntry;
        LoadingScreenSpeedSettingsEntry loadingScreenSpeedSettingsEntry;
        ShowLoadingScreenSettingsEntry showLoadingScreenSettingsEntry;

        InactiveSettingsEntry inactiveSettingsEntry;
        InactiveTimeSettingsEntry inactiveTimeSettingsEntry;
        ShowSleepSettingsEntry showSleepSettingsEntry;
        ReloadSettingsEntry reloadSettingsEntry;

        LedsSettingsEntry ledsSettingsEntry;
        LedsBrightnessSettingsEntry ledsBrightnessSettingsEntry;

        SoundSettingsEntry soundSettingsEntry;
        PressSoundSettingsEntry pressSoundSettingsEntry;
        PressSoundFrequencySettingsEntry pressSoundFrequencySettingsEntry;
        PressSoundDurationSettingsEntry pressSoundDurationSettingsEntry;

        BadAppleScreen badAppleScreen;

    public:
        void setupScreens();

        void setupScreensParameters();

        void setupScreensNexts();

        void loop();

        void setSettings(Settings* settings);

        void setCompositeHID(BleCompositeHID* compositeHID);

        void setButtonMatrix(ButtonMatrix* buttonMatrix);

        void setBattery(Battery* battery);

        void setLeds(Leds* leds);

        void setBuzzer(Buzzer* buzzer);

        void setTouchpad(Touchpad* touchpad);

        void setDisplay(Display* display);

        void setEPROM(EPROM* eprom);

        void setScreen(Screen* screen);

        Settings& getSettings();

        BleCompositeHID& getCompositeHID();

        ButtonMatrix& getButtonMatrix();

        Battery& getBattery();

        Leds& getLeds();

        Buzzer& getBuzzer();

        Touchpad& getTouchpad();

        Display& getDisplay();

        EPROM& getEPROM();

        Screen& getScreen();

        void setScreenParameters(Screen* screen);

        void setSettingsEntryParameters(SettingsEntry* entry);

        void addSettingsIndexNode(SettingsIndexNode* indexNode, Screen* data, const uint8_t BMP[]);

        void setSettingsIndexNode(SettingsIndexNode* indexNode, Screen* data, const uint8_t BMP[]);

        void addSettingsEntryNode(SettingsEntryNode* entryNode, SettingsEntry* data);

        void setSettingsEntryNode(SettingsEntryNode* entryNode, SettingsEntry* data);

        Screen& getLoadingScreen();
};