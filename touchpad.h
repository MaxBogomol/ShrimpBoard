#pragma once

class Touchpad {
  private:
    PS4Touchpad* touchpad;

    bool firstTouch = false;
    int firstTouchX = 0;
    int firstTouchY = 0;
    bool secondTouch = false;
    int secondTouchX = 0;
    int secondTouchY = 0;

    bool firstTouchOld = false;
    int firstTouchXOld = 0;
    int firstTouchYOld = 0;
    bool secondTouchOld = false;
    int secondTouchXOld = 0;
    int secondTouchYOld = 0;

    int firstTouchNormalized = 0;
    int secondTouchNormalized = 0;

  public:
    void setup() {
      this->touchpad = new PS4Touchpad();
      touchpad->setAddress(TOUCHPAD_ADDRESS);
    }

    void read() {
      touchpad->read();

      firstTouchXOld = firstTouchX;
      firstTouchYOld = firstTouchY;
      secondTouchXOld = secondTouchX;
      secondTouchYOld = secondTouchY;

      firstTouchOld = firstTouch;
      secondTouchOld = secondTouch;

      firstTouchX = touchpad->getFirstY();
      firstTouchY = touchpad->getMaxX() - touchpad->getFirstX();
      secondTouchX = touchpad->getSecondY();
      secondTouchY = touchpad->getMaxX() - touchpad->getSecondX();

      firstTouch = touchpad->isFirstPressed();
      secondTouch = touchpad->isSecondPressed();

      firstTouchNormalized = normalizeValue(firstTouch, firstTouchOld);
      secondTouchNormalized = normalizeValue(secondTouch, secondTouchOld);
    }

    PS4Touchpad& getTouchpad() {
      return *this->touchpad;
    }

    int getMaxX() {
      return touchpad->getMaxY();
    }

    int getMaxY() {
      return touchpad->getMaxX();
    }

    int normalizeValue(bool button, bool buttonOld) {
      int value = 0;
      if (button && !buttonOld) value = 1;
      if (button && buttonOld) value = 2;
      if (!button && buttonOld) value = 3;
      return value;
    }

    int getFirstX() {
      return firstTouchX;
    }

    int getFirstY() {
      return firstTouchY;
    }

    int getSecondX() {
      return secondTouchX;
    }

    int getSecondY() {
      return secondTouchY;
    }

    int getFirstXOld() {
      return firstTouchXOld;
    }

    int getFirstYOld() {
      return firstTouchYOld;
    }

    int getSecondXOld() {
      return secondTouchXOld;
    }

    int getSecondYOld() {
      return secondTouchYOld;
    }
    
    int getFirstTocuhValue() {
      return firstTouchNormalized;
    }

    bool isFirstTocuhPress() {
      return getFirstTocuhValue() == 1;
    }

    bool isFirstTocuhPressed() {
      return getFirstTocuhValue() == 2;
    }

    bool isFirstTocuhRelease() {
      return getFirstTocuhValue() == 3;
    }

    int getSecondTocuhValue() {
      return secondTouchNormalized;
    }

    bool isSecondTocuhPress() {
      return getSecondTocuhValue() == 1;
    }

    bool isSecondTocuhPressed() {
      return getSecondTocuhValue() == 2;
    }

    bool isSecondTocuhRelease() {
      return getSecondTocuhValue() == 3;
    }
};