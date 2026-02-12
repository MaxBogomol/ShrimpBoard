#pragma once

class Screen {
  private:
    Settings* settings;
    
    ButtonMatrix* buttonMatrix;
    Touchpad* touchpad;
    Display* display;
    EPROM* eprom;

  public:
    virtual void loop() {

    }

    void setSettings(Settings* settings) {
      this->settings = settings;
    }

    void setButtonMatrix(ButtonMatrix* buttonMatrix) {
      this->buttonMatrix = buttonMatrix;
    }

    void setTouchpad(Touchpad* touchpad) {
      this->touchpad = touchpad;
    }

    void setDisplay(Display* display) {
      this->display = display;
    }

    void setEPROM(EPROM* eprom) {
      this->eprom = eprom;
    }

    Settings& getSettings() {
      return *this->settings;
    }

    ButtonMatrix& getButtonMatrix() {
      return *this->buttonMatrix;
    }

    Touchpad& getTouchpad() {
      return *this->touchpad;
    }

    Display& getDisplay() {
      return *this->display;
    }

    EPROM& getEPROM() {
      return *this->eprom;
    }
};