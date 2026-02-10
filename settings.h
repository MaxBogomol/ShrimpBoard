#pragma once

class Settings {
  private:
    bool usbMode = true;

  public:
    void setUSBMode(bool value) {
      usbMode = value;
    }

    bool isUSBMode() {
      return usbMode;
    }
};