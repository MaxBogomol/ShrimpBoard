#pragma once

class Settings {
  private:
    bool usbMode = true;
    bool leftMouseLock = false;
    bool rightMouseLock = false;

  public:
    void setUSBMode(bool value) {
      usbMode = value;
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

    bool isLeftMouseLock() {
      return leftMouseLock;
    }

    bool isRightMouseLock() {
      return rightMouseLock;
    }
};