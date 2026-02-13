#pragma once

class LoadingLinesScreen : public Screen {
  private:
    unsigned long previousMillis = 0;
    bool next = false;
    int line = 0;
    int step = 2;

  public:
    virtual void begin() override {
      Screen::begin();
      previousMillis = millis();
      next = false;
      line = 0;
      step = 2;
    }

    virtual void loop() override {
      unsigned long currentMillis = millis();

      if (line < 80) {
        if (currentMillis - previousMillis > 25) {
          for (int i = 0; i < step; i++) {
            getDisplay().drawLine(-32 + ((line + i) * 2), 32, ((line + i) * 2), 0, getDisplay().white());
          }
          getDisplay().update();

          previousMillis = millis();
          line += step;
        }
      } else {
        next = true;
      }
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

      if (step < 288) {
        if (currentMillis - previousMillis > 25) {
          getDisplay().clear();
          getDisplay().textReset();
          getDisplay().setTextSize(2);
          getDisplay().setTextPos(step - 144, 8);
          getDisplay().setTextWrap(false);
          getDisplay().setTextColor(getDisplay().white());
          getDisplay().drawText(text);
          getDisplay().update();

          previousMillis = millis();
          step += 2;
        }
      } else {
        next = true;
      }
    }

    virtual bool hasNextScreen() override {
      return next;
    }
};