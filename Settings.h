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
    
    bool touchpadScroll = true;

  public:
    void reset() {
      
    }

    void setUSBMode(bool value) {
      usbMode = value;
    }

    void setScreenFocus(bool value) {
      screenFocus = value;
    }

    void setTouchpadScroll(bool value) {
      touchpadScroll = value;
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

    bool isUSBMode() {
      return usbMode;
    }

    bool isScreenFocus() {
      return screenFocus;
    }

    bool isTouchpadScroll() {
      return touchpadScroll;
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
};