#pragma once

class Settings {
  private:
    bool usbMode = true;

    bool touchpadScroll = false;
    bool leftMouseLock = false;
    bool rightMouseLock = false;

  public:
    void setUSBMode(bool value) {
      usbMode = value;
    }

    void setTouchpadScroll(bool value) {
      touchpadScroll = value;
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

    bool isTouchpadScroll() {
      return touchpadScroll;
    }

    bool isLeftMouseLock() {
      return leftMouseLock;
    }

    bool isRightMouseLock() {
      return rightMouseLock;
    }
};