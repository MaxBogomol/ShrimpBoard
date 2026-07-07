#pragma once

#include <Arduino.h>

#include "Screen.h"
#include "loading/LinesLoadingScreen.h"
#include "loading/NameLoadingScreen.h"
#include "main/MainScreen.h"
#include "settings/SettingsScreen.h"
#include "settings/SettingsIndexScreen.h"

#include "settings/SettingsIndex.h"
#include "settings/SettingsEntry.h"

#include "settings/entries/main/ModeSettingsEntry.h"
#include "settings/entries/main/USBStatusSettingsEntry.h"
#include "settings/entries/main/BLEStatusSettingsEntry.h"
#include "settings/entries/main/SaveSettingsEntry.h"
#include "settings/entries/main/ResetSettingsEntry.h"
#include "settings/entries/main/ResetEPROMSettingsEntry.h"

#include "settings/entries/keyboard/DebounceSettingsEntry.h"
#include "settings/entries/keyboard/DebounceTimeSettingsEntry.h"
#include "settings/entries/keyboard/ButtonScrollSettingsEntry.h"
#include "settings/entries/keyboard/ButtonScrollDelaySettingsEntry.h"
#include "settings/entries/keyboard/ButtonScrollTimeSettingsEntry.h"

#include "settings/entries/mouse/MouseSpeedSettingsEntry.h"
#include "settings/entries/mouse/TouchpadScrollSettingsEntry.h"
#include "settings/entries/mouse/MouseLockScrollSettingsEntry.h"
#include "settings/entries/mouse/LeftMouseLockScrollSettingsEntry.h"
#include "settings/entries/mouse/RightMouseLockScrollSettingsEntry.h"
#include "settings/entries/mouse/MouseScrollSpeedSettingsEntry.h"
#include "settings/entries/mouse/MouseButtonScrollTimeSettingsEntry.h"
#include "settings/entries/mouse/TouchpadRoundedSettingsEntry.h"
#include "settings/entries/mouse/TouchpadRoundLimitSettingsEntry.h"
#include "settings/entries/mouse/TouchpadInertiaSettingsEntry.h"
#include "settings/entries/mouse/TouchpadInertiaRoundedSettingsEntry.h"
#include "settings/entries/mouse/TouchpadInertiaThresholdSettingsEntry.h"
#include "settings/entries/mouse/TouchpadInertiaStepSettingsEntry.h"

#include "settings/entries/screen/DisplayUpdateDelaySettingsEntry.h"
#include "settings/entries/screen/LoadingScreenSettingsEntry.h"
#include "settings/entries/screen/LoadingScreenTypeSettingsEntry.h"
#include "settings/entries/screen/LoadingScreenSpeedSettingsEntry.h"
#include "settings/entries/screen/ShowLoadingScreenSettingsEntry.h"

#include "settings/entries/battery/InactiveSettingsEntry.h"
#include "settings/entries/battery/InactiveTimeSettingsEntry.h"
#include "settings/entries/battery/ShowSleepSettingsEntry.h"
#include "settings/entries/battery/ReloadSettingsEntry.h"

#include "settings/entries/leds/LedsSettingsEntry.h"
#include "settings/entries/leds/LedsBrightnessSettingsEntry.h"

#include "settings/entries/buzzer/SoundSettingsEntry.h"
#include "settings/entries/buzzer/PressSoundSettingsEntry.h"
#include "settings/entries/buzzer/PressSoundFrequencySettingsEntry.h"
#include "settings/entries/buzzer/PressSoundDurationSettingsEntry.h"

#include "../games/BadApple.h"

class ShrimpBoard;

class Interface {
    private:
        ShrimpBoard* shrimpBoard;

        Screen* screen;

        LinesLoadingScreen linesLoadingScreen;
        NameLoadingScreen nameLoadingScreen;

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

        void setShrimpBoard(ShrimpBoard* shrimpBoard);
        void setScreen(Screen* screen);

        ShrimpBoard& getShrimpBoard();
        Screen& getScreen();

        Screen& setScreenParameters(Screen* screen);
        SettingsEntry& setSettingsEntryParameters(SettingsEntry* entry);
        SettingsIndex& getSettingsIndex(Screen* screen, const uint8_t BMP[]);
        SettingsIndex& getSettingsIndex(Screen* screen);

        Screen& getLoadingScreen();

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