#pragma once

class MainScreen : public Screen {
  private:
    unsigned long previousMillis = 0;
    bool next = false;

  public:
    virtual void begin() override {
      Screen::begin();
      previousMillis = millis();
      next = false;
      getSettings().setScreenFocus(false);
    }

    virtual void loop() override {
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= getSettings().getDisplayUpdateDelay()) {
        getDisplay().clear();
        getDisplay().textReset();
        drawStats(74, 0);
        drawKeyboard(0, 0);
        getDisplay().update();

        previousMillis = currentMillis;
      }

      if (isScreenFocus()) next = true;
    }

    virtual bool hasNextScreen() override {
      return next;
    }

    void drawStats(int x, int y) {
      getDisplay().setTextPos(x, y + isUSBMode() ? 4 : 20);
      getDisplay().drawText(">");
      getDisplay().drawBitmap(USB_BMP, x + 8, y, 16, 16, getDisplay().white());
      getDisplay().drawBitmap(isBLEConnected() ? BLE_BMP : NO_BLE_BMP, x + 8, y + 16, 16, 16, getDisplay().white());
      getDisplay().drawBitmap(BATTERY_10_BMP, x + 24, y, 16, 16, getDisplay().white());
      getDisplay().setTextPos(x + 24, y + 20);
      getDisplay().drawText("100%");
    }

    void drawKeyboard(int x, int y) {
      getDisplay().drawRectangle(x + 2, y + 4, 70, 24, getDisplay().white());
      getDisplay().drawRectangle(x + 58, y + 6, 9, 17, getDisplay().white());

      getDisplay().drawRectangle(x + 7, y + 24, 41, 2, getDisplay().white());
      getDisplay().drawRectangle(x + 58, y + 24, 9, 2, getDisplay().white());

      bool numLock = ((isUseUSB() && getSettings().isNumLockUSB()) || (isUseBLE() && getSettings().isNumLockBLE()));
      bool capsLock = ((isUseUSB() && getSettings().isCapsLockUSB()) || (isUseBLE() && getSettings().isCapsSLockBLE()));
      bool scrollLock = ((isUseUSB() && getSettings().isScrollLockUSB()) || (isUseBLE() && getSettings().isScrollLockBLE()));
      if (numLock) getDisplay().drawRectangle(x + 49, y + 24, 2, 2, getDisplay().white());
      if (capsLock) getDisplay().drawRectangle(x + 52, y + 24, 2, 2, getDisplay().white());
      if (scrollLock) getDisplay().drawRectangle(x + 55, y + 24, 2, 2, getDisplay().white());
      if (getSettings().isLeftMouseLock()) getDisplay().drawRectangle(x + 4, y + 24, 2, 2, getDisplay().white());
      if (getSettings().isRightMouseLock()) getDisplay().drawRectangle(x + 68, y + 24, 2, 2, getDisplay().white());

      if (getTouchpad().isFirstTouchPressed()) {
        int tx = map(getTouchpad().getFirstX(), 0, getTouchpad().getMaxX(), 0, 7);
        int ty = map(getTouchpad().getFirstY(), 0, getTouchpad().getMaxY(), 0, 15);
        getDisplay().drawPixel(x + 59 + tx, y + 7 + ty, getDisplay().white());
      }

      if (getTouchpad().isSecondTouchPressed()) {
        int tx = map(getTouchpad().getSecondX(), 0, getTouchpad().getMaxX(), 0, 7);
        int ty = map(getTouchpad().getSecondY(), 0, getTouchpad().getMaxY(), 0, 15);
        getDisplay().drawPixel(x + 59 + tx, y + 7 + ty, getDisplay().white());
      }

      for (int i = 0; i < 6; i++) {
        if (getButtonMatrix().isPressed(i, 0)) {
          getDisplay().drawRectangle(x + 4, y + 6 + (i * 3), 2, 2, getDisplay().white());
        }
      }
      for (int j = 0; j < 15; j++) {
        if (getButtonMatrix().isPressed(0, j + 2)) {
          getDisplay().drawRectangle(x + 13 + (j * 3), y + 6, 2, 2, getDisplay().white());
        }
      }
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 16; j++) {
          if (getButtonMatrix().isPressed(i + 1, j + 1)) {
            getDisplay().drawRectangle(x + 7 + (j * 3), y + 9 + (i * 3), 2, 2, getDisplay().white());
          }
        }
      }
      for (int j = 0; j < 12; j++) {
        if (getButtonMatrix().isPressed(3, j + 1)) {
          getDisplay().drawRectangle(x + 7 + (j * 3), y + 15, 2, 2, getDisplay().white());
        }
      }
      for (int j = 0; j < 10; j++) {
        if (getButtonMatrix().isPressed(4, j + 2)) {
          getDisplay().drawRectangle(x + 13 + (j * 3), y + 18, 2, 2, getDisplay().white());
        }
      }
      for (int j = 0; j < 3; j++) {
        if (getButtonMatrix().isPressed(5, j + 1)) {
          getDisplay().drawRectangle(x + 7 + (j * 3), y + 21, 2, 2, getDisplay().white());
        }
      }
      for (int j = 0; j < 7; j++) {
        if (getButtonMatrix().isPressed(5, j + 6)) {
          getDisplay().drawRectangle(x + 37 + (j * 3), y + 21, 2, 2, getDisplay().white());
        }
      }

      if (getButtonMatrix().isPressed(0, 1)) getDisplay().drawRectangle(x + 7, y + 6, 5, 2, getDisplay().white());
      if (getButtonMatrix().isPressed(4, 1)) getDisplay().drawRectangle(x + 7, y + 18, 5, 2, getDisplay().white());
      if (getButtonMatrix().isPressed(3, 13)) getDisplay().drawRectangle(x + 43, y + 15, 5, 2, getDisplay().white());
      if (getButtonMatrix().isPressed(4, 12)) getDisplay().drawRectangle(x + 43, y + 18, 5, 2, getDisplay().white());
      if (isTwoLinkedButtonPressed(5, 4, 5, 5)) getDisplay().drawRectangle(x + 16, y + 21, 20, 2, getDisplay().white());
      if (getButtonMatrix().isPressed(4, 13)) getDisplay().drawRectangle(x + 52, y + 18, 2, 2, getDisplay().white());
      if (getButtonMatrix().isPressed(3, 16)) getDisplay().drawRectangle(x + 55, y + 9, 2, 2, getDisplay().white());
      if (getButtonMatrix().isPressed(4, 16)) getDisplay().drawRectangle(x + 55, y + 12, 2, 2, getDisplay().white());
      if (getButtonMatrix().isPressed(4, 14))  getDisplay().drawRectangle(x + 68, y + 6, 2, 2, getDisplay().white());
      if (getButtonMatrix().isPressed(4, 15)) getDisplay().drawRectangle(x + 68, y + 9, 2, 2, getDisplay().white());
      if (getButtonMatrix().isPressed(5, 13)) getDisplay().drawRectangle(x + 68, y + 12, 2, 2, getDisplay().white());
      if (getButtonMatrix().isPressed(5, 14)) getDisplay().drawRectangle(x + 68, y + 15, 2, 2, getDisplay().white());
      if (getButtonMatrix().isPressed(5, 15)) getDisplay().drawRectangle(x + 68, y + 18, 2, 2, getDisplay().white());
      if (getButtonMatrix().isPressed(5, 16)) getDisplay().drawRectangle(x + 68, y + 21, 2, 2, getDisplay().white());
    }
};