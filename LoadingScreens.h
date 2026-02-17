#pragma once

class LoadingLinesScreen : public Screen {
  private:
    unsigned long previousMillis = 0;
    bool next = false;
    int line = 0;

  public:
    virtual void begin() override {
      Screen::begin();
      previousMillis = millis();
      next = false;
      line = 0;
    }

    virtual void loop() override {
      unsigned long currentMillis = millis();
      int step = getSettings().getLoadingScreenSpeed();
      int type = getSettings().getLoadingScreenType();

      if (line < 80) {
        if (currentMillis - previousMillis >= getSettings().getDisplayUpdateDelay()) {
          for (int i = 0; i < step; i++) {
            int x1 = -32;
            int x2 = 0;
            if (type == 2 || type == 3) {
              x1 = 0;
              x2 = -32;
            }
            x1 = x1 + ((line + i) * 2);
            x2 = x2 + ((line + i) * 2);
            if (type == 1 || type == 3) {
              x1 = 128 - x1;
              x2 = 128 - x2;
            }
            getDisplay().drawLine(x1, 32, x2, 0, getDisplay().white());
          }
          getDisplay().update();

          previousMillis = currentMillis;
          line += step;
        }
      } else {
        next = true;
      }
      if (isFNPress() ||isEscPress() || isEnterPress() || isSpacePress()) next = true;
    }

    virtual bool hasNextScreen() override {
      return next;
    }
};

class LoadingShrimpBoardScreen : public Screen {
  private:
    unsigned long previousMillis = 0;
    bool next = false;
    int step = 0;
    String text = "Shrimpboard";

  public:
    virtual void begin() override {
      Screen::begin();
      previousMillis = millis();
      next = false;
      step = 0;
    }

    virtual void loop() override {
      unsigned long currentMillis = millis();
      int type = getSettings().getLoadingScreenType();

      if (step < 288) {
        if (currentMillis - previousMillis >= getSettings().getDisplayUpdateDelay()) {
          int x = step - 144;
          if (type == 1) x = 144 - step;

          getDisplay().clear();
          getDisplay().textReset();
          getDisplay().setTextSize(2);
          getDisplay().setTextPos(x, 8);
          getDisplay().setTextWrap(false);
          getDisplay().setTextColor(getDisplay().white());
          getDisplay().drawText(text);
          getDisplay().update();

          previousMillis = currentMillis;
          step += getSettings().getLoadingScreenSpeed();
        }
      } else {
        next = true;
      }
      if (isFNPress() ||isEscPress() || isEnterPress() || isSpacePress()) next = true;
    }

    virtual bool hasNextScreen() override {
      return next;
    }
};