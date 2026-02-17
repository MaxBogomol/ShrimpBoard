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

    bool isSpacePress() {
      return isTwoLinkedButtonPress(5, 4, 5, 5);
    }

    bool isLeftPress() {
      return getButtonMatrix().isPress(5, 10);
    }

    bool isRightPress() {
      return getButtonMatrix().isPress(5, 12);
    }

    bool isUpPress() {
      return getButtonMatrix().isPress(4, 13);
    }

    bool isDownPress() {
      return getButtonMatrix().isPress(5, 11);
    }

    bool isWPress() {
      return getButtonMatrix().isPress(2, 3);
    }

    bool isAPress() {
      return getButtonMatrix().isPress(3, 2);
    }

    bool isSPress() {
      return getButtonMatrix().isPress(3, 3);
    }

    bool isDPress() {
      return getButtonMatrix().isPress(3, 4);
    }

    bool isEscPressed() {
      return getButtonMatrix().isPressed(0, 1);
    }

    bool isEnterPressed() {
      return getButtonMatrix().isPressed(3, 13);
    }

    bool isSpacePressed() {
      return isTwoLinkedButtonPressed(5, 4, 5, 5);
    }

    bool isLeftPressed() {
      return getButtonMatrix().isPressed(5, 10);
    }

    bool isRightPressed() {
      return getButtonMatrix().isPressed(5, 12);
    }

    bool isUpPressed() {
      return getButtonMatrix().isPressed(4, 13);
    }

    bool isDownPressed() {
      return getButtonMatrix().isPressed(5, 11);
    }

    bool isWPressed() {
      return getButtonMatrix().isPressed(2, 3);
    }

    bool isAPressed() {
      return getButtonMatrix().isPressed(3, 2);
    }

    bool isSPressed() {
      return getButtonMatrix().isPressed(3, 3);
    }

    bool isDPressed() {
      return getButtonMatrix().isPressed(3, 4);
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