#pragma once

class PS4Touchpad {
  private:
    uint8_t TOUCHPAD_ADDR = 0x4B;
    int MAX_X = 1920;
    int MAX_Y = 940;

    bool firstTouchPressed = false;
    int firstTouchX = 0;
    int firstTouchY = 0;
    bool secondTouchPressed = false;
    int secondTouchX = 0;
    int secondTouchY = 0;

  public:
    void read() {
      Wire.beginTransmission(TOUCHPAD_ADDR);
      Wire.requestFrom(TOUCHPAD_ADDR, 32);

      byte data[32];
      int i = 0;
      while (Wire.available() && i < 32) {
        data[i++] = Wire.read();
      }

      firstTouchPressed = false;
      secondTouchPressed = false;

      if (data[3] < 128) {
        int x1 = ((data[5] << 8) | data[4]) - 61440;
        int y1 = ((data[7] << 8) | data[6]) - 49152;

        firstTouchX = x1;
        firstTouchY = y1;
        firstTouchPressed = true;
      }

      if (data[9] < 128) {
        int x2 = ((data[11] << 8) | data[10]) - 61440;
        int y2 = ((data[13] << 8) | data[12]) - 49152;

        secondTouchX = x2;
        secondTouchY = y2;
        secondTouchPressed = true;
      }
    }

    void setAddress(uint8_t addr) {
      TOUCHPAD_ADDR = addr;
    }

    void setMaxX(int max) {
      MAX_X = max;
    }

    void setMaxY(int max) {
      MAX_Y = max;
    }

    uint8_t getAddress() {
      return TOUCHPAD_ADDR;
    }

    int getMaxX() {
      return MAX_X;
    }

    int getMaxY() {
      return MAX_Y;
    }

    bool isFirstPressed() {
      return firstTouchPressed;
    }

    int getFirstX() {
      return firstTouchX;
    }

    int getFirstY() {
      return firstTouchY;
    }

    bool isSecondPressed() {
      return secondTouchPressed;
    }

    int getSecondX() {
      return secondTouchX;
    }

    int getSecondY() {
      return secondTouchY;
    }

    double getFirstXLimited() {
      return map(getFirstX(), 0.0, MAX_X, 0.0, 100.0);
    }

    double getFirstYLimited() {
      return map(getFirstY(), 0.0, MAX_Y, 0.0, 100.0);
    }

    double getSecondXLimited() {
      return map(getSecondX(), 0.0, MAX_X, 0.0, 100);
    }

    double getSecondYLimited() {
      return map(getSecondY(), 0.0, MAX_Y, 0.0, 100.0);
    }
};