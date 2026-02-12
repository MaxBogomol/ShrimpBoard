#pragma once

class Screen {
  private:
    Settings* settings;
    
    ButtonMatrix* buttonMatrix;
    Touchpad* touchpad;
    Display* display;
    EPROM* eprom;

    Screen* nextScreen;

  public:
    virtual void begin() {
      getDisplay().clear();
      getDisplay().update();
    }

    virtual void loop() {

    }

    virtual void end() {
      
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

    virtual bool hasNextScreen() {
      return false;
    }

    virtual void setNextScreen(Screen* nextScreen) {
      this->nextScreen = nextScreen;
    }

    virtual Screen& getNextScreen() {
      return *this->nextScreen;
    }
};