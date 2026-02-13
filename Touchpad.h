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

    int firstTouchXMoved = 0;
    int firstTouchYMoved = 0;
    int secondTouchXMoved = 0;
    int secondTouchYMoved = 0;

    float firstTouchXRounded = 0;
    float firstTouchYRounded = 0;
    float secondTouchXRounded = 0;
    float secondTouchYRounded = 0;

    float firstRound[10][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    float secondRound[10][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

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

      firstTouchXMoved = firstTouchX - firstTouchXOld;
      firstTouchYMoved = firstTouchY - firstTouchYOld;
      secondTouchXMoved = secondTouchX - secondTouchXOld;
      secondTouchYMoved = secondTouchY - secondTouchYOld;

      if (isFirstTouchPress()) {
        firstTouchXMoved = 0;
        firstTouchYMoved = 0;
        for (int i = 0; i < 10; i++) {
          firstRound[i][0] = firstTouchXMoved;
          firstRound[i][1] = firstTouchYMoved;
        }
      }
      if (isSecondTouchPress()) {
        secondTouchXMoved = 0;
        secondTouchYMoved = 0;
        for (int i = 0; i < 10; i++) {
          secondRound[i][0] = secondTouchXMoved;
          secondRound[i][1] = secondTouchYMoved;
        }
      }

      int roundLimit = getRoundLimit();

      for (int i = 0; i < roundLimit - 1; i++) {
        firstRound[i][0] = firstRound[i + 1][0];
        firstRound[i][1] = firstRound[i + 1][1];
        secondRound[i][0] = secondRound[i + 1][0];
        secondRound[i][1] = secondRound[i + 1][1];
      }
      firstRound[roundLimit - 1][0] = firstTouchXMoved;
      firstRound[roundLimit - 1][1] = firstTouchYMoved;
      secondRound[roundLimit - 1][0] = secondTouchXMoved;
      secondRound[roundLimit - 1][1] = secondTouchYMoved;

      firstTouchXRounded = 0;
      firstTouchYRounded = 0;
      secondTouchXRounded = 0;
      secondTouchYRounded = 0;
      for (int i = 0; i < roundLimit; i++) {
        firstTouchXRounded += firstRound[i][0];
        firstTouchYRounded += firstRound[i][1];
        secondTouchXRounded += secondRound[i][0];
        secondTouchYRounded += secondRound[i][1];
      }
      firstTouchXRounded = firstTouchXRounded / roundLimit;
      firstTouchYRounded = firstTouchYRounded / roundLimit;
      secondTouchXRounded = secondTouchXRounded / roundLimit;
      secondTouchYRounded = secondTouchYRounded / roundLimit;
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

    int getRoundLimit() {
      return 5;
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

    int getFirstXMoved() {
      return firstTouchXMoved;
    }

    int getFirstYMoved() {
      return firstTouchYMoved;
    }

    int getSecondXMoved() {
      return secondTouchXMoved;
    }

    int getSecondYMoved() {
      return secondTouchYMoved;
    }

    float getFirstXRounded() {
      return firstTouchXRounded;
    }

    float getFirstYRounded() {
      return firstTouchYRounded;
    }

    float getSecondXRounded() {
      return secondTouchXRounded;
    }

    float getSecondYRounded() {
      return secondTouchYRounded;
    }
    
    int getFirstTouchValue() {
      return firstTouchNormalized;
    }

    bool isFirstTouchPress() {
      return getFirstTouchValue() == 1;
    }

    bool isFirstTouchPressed() {
      return getFirstTouchValue() == 2;
    }

    bool isFirstTouchRelease() {
      return getFirstTouchValue() == 3;
    }

    int getSecondTouchValue() {
      return secondTouchNormalized;
    }

    bool isSecondTouchPress() {
      return getSecondTouchValue() == 1;
    }

    bool isSecondTouchPressed() {
      return getSecondTouchValue() == 2;
    }

    bool isSecondTouchRelease() {
      return getSecondTouchValue() == 3;
    }
};