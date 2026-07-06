#pragma once

class Settings {
    private:
        bool usbMode = true;
        bool usb = false;
        bool screenFocus = false;
        bool showLoadingScreen = false;
        unsigned long activeMillis = 0;
        bool showSleep = false;

        bool numLockUSB = false;
        bool capsLockUSB = false;
        bool scrollLockUSB = false;
        bool numLockBLE = false;
        bool capsLockBLE = false;
        bool scrollLockBLE = false;
        bool leftMouseLock = false;
        bool rightMouseLock = false;

        bool debounce = true;
        int debounceTime = 5;
        bool buttonScroll = true;
        int buttonScrollDelay = 500;
        int buttonScrollTime = 100;
        
        float mouseSpeed = 1;
        bool touchpadScroll = true;
        bool mouseLockScroll = false;
        bool leftMouseLockScroll = false;
        bool rightMouseLockScroll = false;
        float mouseScrollSpeed = 1;
        int mouseButtonScrollTime = 10;
        bool touchpadRounded = true;
        int touchpadRoundLimit = 5;
        bool touchpadInertia = true;
        bool touchpadInertiaRounded = true;
        int touchpadInertiaThreshold = 50;
        int touchpadInertiaStep = 5;

        int displayUpdateDelay = 25;
        int loadingScreen = 0;
        int loadingScreenType = 0;
        int loadingScreenSpeed = 2;

        bool inactive = true;
        int inactiveTime = 5;

        bool leds = true;
        int ledBrightness = 100;

        bool sound = true;
        bool pressSound = false;
        int pressSoundFrequency = 1000;
        int pressSoundDuration = 50;

    public:
        void reset();
        void copy(Settings* otherSettings);

        void setUSBMode(bool value);
        void setUSB(bool value);
        void setScreenFocus(bool value);
        void setShowLoadingScreen(bool value);
        void setActiveMillis(unsigned long value);
        void setShowSleep(bool value);
        void setNumLockUSB(bool value);
        void setCapsLockUSB(bool value);
        void setScrollLockUSB(bool value);
        void setNumLockBLE(bool value);
        void setCapsLockBLE(bool value);
        void setScrollLockBLE(bool value);
        void setLeftMouseLock(bool value);
        void setRightMouseLock(bool value);
        void setDebounce(bool value);
        void setDebounceTime(int value);
        void setButtonScroll(bool value);
        void setButtonScrollDelay(int value);
        void setButtonScrollTime(int value);
        void setMouseSpeed(float value);
        void setTouchpadScroll(bool value);
        void setMouseLockScroll(bool value);
        void setLeftMouseLockScroll(bool value);
        void setRightMouseLockScroll(bool value);
        void setMouseScrollSpeed(float value);
        void setMouseButtonScrollTime(int value);
        void setTouchpadRounded(bool value);
        void setTouchpadRoundLimit(int value);
        void setTouchpadInertia(bool value);
        void setTouchpadInertiaRounded(bool value);
        void setTouchpadInertiaThreshold(int value);
        void setTouchpadInertiaStep(int value);
        void setDisplayUpdateDelay(int value);
        void setLoadingScreen(int value);
        void setLoadingScreenType(int value);
        void setLoadingScreenSpeed(int value);
        void setInactive(bool value);
        void setInactiveTime(int value);
        void setLeds(bool value);
        void setLedBrightness(int value);
        void setSound(bool value);
        void setPressSound(bool value);
        void setPressSoundFrequency(int value);
        void setPressSoundDuration(int value);

        bool isUSBMode();
        bool isUSB();
        bool isScreenFocus();
        bool isShowLoadingScreen();
        unsigned long getActiveMillis();
        bool isShowSleep();
        bool isNumLockUSB();
        bool isCapsLockUSB();
        bool isScrollLockUSB();
        bool isNumLockBLE();
        bool isCapsLockBLE();
        bool isScrollLockBLE();
        bool isLeftMouseLock();
        bool isRightMouseLock();
        bool isDebounce();
        int getDebounceTime();
        bool isButtonScroll();
        int getButtonScrollDelay();
        int getButtonScrollTime();
        float getMouseSpeed();
        bool isTouchpadScroll();
        bool isMouseLockScroll();
        bool isLeftMouseLockScroll();
        bool isRightMouseLockScroll();
        float getMouseScrollSpeed();
        int getMouseButtonScrollTime();
        bool isTouchpadRounded();
        int getTouchpadRoundLimit();
        bool isTouchpadInertia();
        bool isTouchpadInertiaRounded();
        int getTouchpadInertiaThreshold();
        int getTouchpadInertiaStep();
        int getDisplayUpdateDelay();
        int getLoadingScreen();
        int getLoadingScreenType();
        int getLoadingScreenSpeed();
        bool isInactive();
        int getInactiveTime();
        bool isLeds();
        int getLedBrightness();
        bool isSound();
        bool isPressSound();
        int getPressSoundFrequency();
        int getPressSoundDuration();

        bool isMouseLock();
};