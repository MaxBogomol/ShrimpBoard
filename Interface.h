#pragma once

#include <Screen.h>
#include <LoadingScreen.h>

class Interface {
  private:
    Settings* settings;

    ButtonMatrix* buttonMatrix;
    Touchpad* touchpad;
    Display* display;
    EPROM* eprom;

    Screen* screen;

    LoadingScreenLines loadingScreenLines;

  public:
    void setupScreens() {
      setScreenParameters(&loadingScreenLines);
    }

    void loop() {
      setScreen(&loadingScreenLines);
      getScreen().loop();
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

    void setScreen(Screen* screen) {
      this->screen = screen;
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

    Screen& getScreen() {
      return *this->screen;
    }

    void setScreenParameters(Screen* screen) {
      screen->setSettings(settings);
      screen->setButtonMatrix(buttonMatrix);
      screen->setTouchpad(touchpad);
      screen->setDisplay(display);
      screen->setEPROM(eprom);
    }

    Screen& getLoadingScreen() {
      Screen* screen = &loadingScreenLines;
      return *screen;
    }
};