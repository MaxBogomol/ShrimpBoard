#pragma once

class Screen {
  private:
    Settings* settings;

    BleCompositeHID* compositeHID;
    
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

    void setCompositeHID(BleCompositeHID* compositeHID) {
      this->compositeHID = compositeHID;
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

    BleCompositeHID& getCompositeHID() {
      return *this->compositeHID;
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

    bool isBLEConnected() {
      return getCompositeHID().isConnected();
    }

    bool isUSBMode() {
      return getSettings().isUSBMode();
    }

    bool isUseUSB() {
      return isUSBMode();
    }

    bool isUseBLE() {
      return !isUSBMode() && isBLEConnected();
    }

    bool isTwoLinkedButtonPress(int row1, int collumn1, int row2, int collumn2) {
      return ((getButtonMatrix().isPress(row1, collumn1) && !(getButtonMatrix().isPressed(row2, collumn2))) ||
              (getButtonMatrix().isPress(row2, collumn2) && !(getButtonMatrix().isPressed(row1, collumn1))));
    }

    bool isTwoLinkedButtonPressed(int row1, int collumn1, int row2, int collumn2) {
      return (getButtonMatrix().isPressed(row1, collumn1) || getButtonMatrix().isPressed(row2, collumn2));
    }

    bool isTwoLinkedButtonRelease(int row1, int collumn1, int row2, int collumn2) {
      return ((getButtonMatrix().isRelease(row1, collumn1) && !(getButtonMatrix().isPressed(row2, collumn2))) ||
              (getButtonMatrix().isRelease(row2, collumn2) && !(getButtonMatrix().isPressed(row1, collumn1))));
    }

    bool isEscPress() {
      return getButtonMatrix().isPress(0, 1);
    }

    bool isEnterPress() {
      return getButtonMatrix().isPress(3, 13);
    }

    bool isFNPress() {
      return getButtonMatrix().isPress(5, 8);
    }

    bool isFNPressed() {
      return getButtonMatrix().isPressed(5, 8);
    }

    bool isFNReleased() {
      return getButtonMatrix().isRelease(5, 8);
    }

    bool isScreenFocus() {
      return isFNPressed() && isEscPress();
    }
};