#pragma once

class Settings {
  private:
    bool usbMode = true;
    bool screenFocus = false;

    bool numLockUSB = false;
    bool capsLockUSB = false;
    bool scrollLockUSB = false;
    bool numLockBLE = false;
    bool capsLockBLE = false;
    bool scrollLockBLE = false;
    bool leftMouseLock = false;
    bool rightMouseLock = false;
    
    float mouseSpeed = 1;
    bool touchpadScroll = true;
    bool mouseLockScroll = false;
    bool leftMouseLockScroll = false;
    bool rightMouseLockScroll = false;
    float mouseScrollSpeed = 1;
    bool touchpadRounded = true;
    int touchpadRoundLimit = 5;

    int displayUpdateDelay = 25;

  public:
    void reset() {
      mouseSpeed = 1;
      touchpadScroll = true;
      mouseLockScroll = false;
      leftMouseLockScroll = false;
      rightMouseLockScroll = false;
      mouseScrollSpeed = 1;
      touchpadRounded = true;
      touchpadRoundLimit = 5;

      displayUpdateDelay = 25;
    }

    void setUSBMode(bool value) {
      usbMode = value;
    }

    void setScreenFocus(bool value) {
      screenFocus = value;
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

    void setTouchpadRounded(bool value) {
      touchpadRounded = value;
    }

    void setTouchpadRoundLimit(int value) {
      if (value < 2) value = 2;
      if (value > 10) value = 10;
      touchpadRoundLimit = value;
    }

    void setDisplayUpdateDelay(int value) {
      if (value < 0) value = 0;
      if (value > 100) value = 100;
      displayUpdateDelay = value;
    }

    bool isUSBMode() {
      return usbMode;
    }

    bool isScreenFocus() {
      return screenFocus;
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

    bool isTouchpadRounded() {
      return touchpadRounded;
    }

    int getTouchpadRoundLimit() {
      return touchpadRoundLimit;
    }

    int getDisplayUpdateDelay() {
      return displayUpdateDelay;
    }
};