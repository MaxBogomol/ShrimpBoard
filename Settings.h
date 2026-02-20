#pragma once

class Settings {
  private:
    bool usbMode = true;
    bool screenFocus = false;
    bool showLoadingScreen = false;
    unsigned long activeMillis = 0;

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
    int touchpadInertiaStresshold = 50;
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
    void reset() {
      debounce = true;
      debounceTime = 5;
      buttonScroll = true;
      buttonScrollDelay = 500;
      buttonScrollTime = 100;

      mouseSpeed = 1;
      touchpadScroll = true;
      mouseLockScroll = false;
      leftMouseLockScroll = false;
      rightMouseLockScroll = false;
      mouseScrollSpeed = 1;
      mouseButtonScrollTime = 10;
      touchpadRounded = true;
      touchpadRoundLimit = 5;
      touchpadInertia = true;
      touchpadInertiaRounded = true;
      touchpadInertiaStresshold = 50;
      touchpadInertiaStep = 5;

      displayUpdateDelay = 25;
      loadingScreen = 0;
      loadingScreenType = 0;
      loadingScreenSpeed = 2;

      leds = true;
      ledBrightness = 100;

      inactive = true;
      inactiveTime = 5;

      sound = true;
      pressSound = false;
      pressSoundFrequency = 1000;
      pressSoundDuration = 50;
    }

    void copy(Settings* otherSettings) {
      debounce = otherSettings->isDebounce();
      debounceTime = otherSettings->getDebounceTime();
      buttonScroll = otherSettings->isButtonScroll();
      buttonScrollDelay = otherSettings->getButtonScrollDelay();
      buttonScrollTime = otherSettings->getButtonScrollTime();

      mouseSpeed = otherSettings->getMouseSpeed();
      touchpadScroll = otherSettings->isTouchpadScroll();
      mouseLockScroll = otherSettings->isMouseLockScroll();
      leftMouseLockScroll = otherSettings->isLeftMouseLockScroll();
      rightMouseLockScroll = otherSettings->isRightMouseLockScroll();
      mouseScrollSpeed = otherSettings->getMouseScrollSpeed();
      mouseButtonScrollTime = otherSettings->getButtonScrollTime();
      touchpadRounded = otherSettings->isTouchpadRounded();
      touchpadRoundLimit = otherSettings->getTouchpadRoundLimit();
      touchpadInertia = otherSettings->isTouchpadInertia();
      touchpadInertiaRounded = otherSettings->isTouchpadInertiaRounded();
      touchpadInertiaStresshold = otherSettings->getTouchpadInertiaStresshold();
      touchpadInertiaStep = otherSettings->getTouchpadInertiaStep();

      displayUpdateDelay = otherSettings->getDisplayUpdateDelay();
      loadingScreen = otherSettings->getLoadingScreen();
      loadingScreenType = otherSettings->getLoadingScreenType();
      loadingScreenSpeed = otherSettings->getLoadingScreenSpeed();

      leds = otherSettings->isLeds();
      ledBrightness = otherSettings->getLedBrightness();

      inactive = otherSettings->isInactive();
      inactiveTime = otherSettings->getInactiveTime();

      sound = otherSettings->isSound();
      pressSound = otherSettings->isPressSound();
      pressSoundFrequency = otherSettings->getPressSoundFrequency();
      pressSoundDuration = otherSettings->getPressSoundDuration();
    }

    void setUSBMode(bool value) {
      usbMode = value;
    }

    void setScreenFocus(bool value) {
      screenFocus = value;
    }

    void setShowLoadingScreen(bool value) {
      showLoadingScreen = value;
    }

    void setActiveMillis(unsigned long value) {
      activeMillis = value;
    }

    void setNumLockUSB(bool value) {
      numLockUSB = value;
    }

    void setCapsLockUSB(bool value) {
      capsLockUSB = value;
    }

    void setScrollLockUSB(bool value) {
      scrollLockUSB = value;
    }

    void setNumLockBLE(bool value) {
      numLockBLE = value;
    }

    void setCapsLockBLE(bool value) {
      capsLockBLE = value;
    }

    void setScrollLockBLE(bool value) {
      scrollLockBLE = value;
    }

    void setLeftMouseLock(bool value) {
      leftMouseLock = value;
    }

    void setRightMouseLock(bool value) {
      rightMouseLock = value;
    }

    void setDebounce(bool value) {
      debounce = value;
    }

    void setDebounceTime(int value) {
      if (value < 1) value = 1;
      if (value > 100) value = 100;
      debounceTime = value;
    }

    void setButtonScroll(bool value) {
      buttonScroll = value;
    }

    void setButtonScrollDelay(int value) {
      if (value < 100) value = 100;
      if (value > 1000) value = 1000;
      buttonScrollDelay = value;
    }

    void setButtonScrollTime(int value) {
      if (value < 10) value = 10;
      if (value > 1000) value = 1000;
      buttonScrollTime = value;
    }

    void setMouseSpeed(float value) {
      if (value < 0.1) value = 0.1;
      if (value > 3) value = 3;
      mouseSpeed = value;
    }

    void setTouchpadScroll(bool value) {
      touchpadScroll = value;
    }

    void setMouseLockScroll(bool value) {
      mouseLockScroll = value;
    }

    void setLeftMouseLockScroll(bool value) {
      leftMouseLockScroll = value;
    }

    void setRightMouseLockScroll(bool value) {
      rightMouseLockScroll = value;
    }

    void setMouseScrollSpeed(float value) {
      if (value < 0.1) value = 0.1;
      if (value > 2) value = 2;
      mouseScrollSpeed = value;
    }

    void setMouseButtonScrollTime(int value) {
      if (value < 1) value = 1;
      if (value > 100) value = 100;
      mouseButtonScrollTime = value;
    }

    void setTouchpadRounded(bool value) {
      touchpadRounded = value;
    }

    void setTouchpadRoundLimit(int value) {
      if (value < 2) value = 2;
      if (value > 10) value = 10;
      touchpadRoundLimit = value;
    }

    void setTouchpadInertia(bool value) {
      touchpadInertia = value;
    }

    void setTouchpadInertiaRounded(bool value) {
      touchpadInertiaRounded = value;
    }

    void setTouchpadInertiaStresshold(int value) {
      if (value < 5) value = 5;
      if (value > 300) value = 300;
      touchpadInertiaStresshold = value;
    }

    void setTouchpadInertiaStep(int value) {
      if (value < 1) value = 1;
      if (value > 50) value = 50;
      touchpadInertiaStep = value;
    }

    void setDisplayUpdateDelay(int value) {
      if (value < 0) value = 0;
      if (value > 100) value = 100;
      displayUpdateDelay = value;
    }

    void setLoadingScreen(int value) {
      if (value < 0) value = 0;
      if (value > 1) value = 1;
      loadingScreen = value;
    }

    void setLoadingScreenType(int value) {
      if (value < 0) value = 0;
      if (value > 3 && loadingScreen == 0) value = 3;
      if (value > 1 && loadingScreen == 1) value = 1;
      loadingScreenType = value;
    }

    void setLoadingScreenSpeed(int value) {
      if (value < 1) value = 1;
      if (value > 10) value = 10;
      loadingScreenSpeed = value;
    }

    void setInactive(bool value) {
      inactive = value;
    }

    void setInactiveTime(int value) {
      if (value < 1) value = 1;
      if (value > 60) value = 60;
      inactiveTime = value;
    }

    void setLeds(bool value) {
      leds = value;
    }

    void setLedBrightness(int value) {
      if (value < 0) value = 0;
      if (value > 100) value = 100;
      ledBrightness = value;
    }

    void setSound(bool value) {
      sound = value;
    }

    void setPressSound(bool value) {
      pressSound = value;
    }

    void setPressSoundFrequency(int value) {
      if (value < 10) value = 10;
      if (value > 5000) value = 5000;
      pressSoundFrequency = value;
    }

    void setPressSoundDuration(int value) {
      if (value < 10) value = 10;
      if (value > 250) value = 250;
      pressSoundDuration = value;
    }

    bool isUSBMode() {
      return usbMode;
    }

    bool isScreenFocus() {
      return screenFocus;
    }

    bool isShowLoadingScreen() {
      return showLoadingScreen;
    }

    unsigned long getActiveMillis() {
      return activeMillis;
    }

    bool isNumLockUSB() {
      return numLockUSB;
    }

    bool isCapsLockUSB() {
      return capsLockUSB;
    }

    bool isScrollLockUSB() {
      return scrollLockUSB;
    }

    bool isNumLockBLE() {
      return numLockBLE;
    }

    bool isCapsLockBLE() {
      return capsLockBLE;
    }

    bool isScrollLockBLE() {
      return scrollLockBLE;
    }

    bool isLeftMouseLock() {
      return leftMouseLock;
    }

    bool isRightMouseLock() {
      return rightMouseLock;
    }

    bool isDebounce() {
      return debounce;
    }

    int getDebounceTime() {
      return debounceTime;
    }

    bool isButtonScroll() {
      return buttonScroll;
    }

    int getButtonScrollDelay() {
      return buttonScrollDelay;
    }

    int getButtonScrollTime() {
      return buttonScrollTime;
    }

    float getMouseSpeed() {
      return mouseSpeed;
    }

    bool isTouchpadScroll() {
      return touchpadScroll;
    }

    bool isMouseLockScroll() {
      return mouseLockScroll;
    }

    bool isLeftMouseLockScroll() {
      return leftMouseLockScroll;
    }

    bool isRightMouseLockScroll() {
      return rightMouseLockScroll;
    }

    float getMouseScrollSpeed() {
      return mouseScrollSpeed;
    }

    int getMouseButtonScrollTime() {
      return mouseButtonScrollTime;
    }

    bool isTouchpadRounded() {
      return touchpadRounded;
    }

    int getTouchpadRoundLimit() {
      return touchpadRoundLimit;
    }

    bool isTouchpadInertia() {
      return touchpadInertia;
    }

    bool isTouchpadInertiaRounded() {
      return touchpadInertiaRounded;
    }

    int getTouchpadInertiaStresshold() {
      return touchpadInertiaStresshold;
    }

    int getTouchpadInertiaStep() {
      return touchpadInertiaStep;
    }

    int getDisplayUpdateDelay() {
      return displayUpdateDelay;
    }

    int getLoadingScreen() {
      return loadingScreen;
    }

    int getLoadingScreenType() {
      return loadingScreenType;
    }

    int getLoadingScreenSpeed() {
      return loadingScreenSpeed;
    }

    bool isInactive() {
      return inactive;
    }

    int getInactiveTime() {
      return inactiveTime;
    }

    bool isLeds() {
      return leds;
    }

    int getLedBrightness() {
      return ledBrightness;
    }

    bool isSound() {
      return sound;
    }

    bool isPressSound() {
      return pressSound;
    }

    int getPressSoundFrequency() {
      return pressSoundFrequency;
    }

    int getPressSoundDuration() {
      return pressSoundDuration;
    }
};