#pragma once

class LoadingScreenLines : public Screen {
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

      if (line < 80) {
        if (currentMillis - previousMillis > 35) {
          getDisplay().drawLine(-32 + (line * 2), 32, (line * 2), 0, getDisplay().white());
          getDisplay().update();

          previousMillis = millis();
          line++;
        }
      } else {
        next = true;
      }
    }

    virtual bool hasNextScreen() override {
      return next;
    }
};

class LoadingScreenShrimpBoard : public Screen {
  private:
    unsigned long previousMillis = 0;
    bool next = false;
    int line = 0;
    String text = "Shrimpboard";

  public:
    virtual void begin() override {
      Screen::begin();
      previousMillis = millis();
      next = false;
      line = 0;
    }

    virtual void loop() override {
      unsigned long currentMillis = millis();

      if (line < 288) {
        if (currentMillis - previousMillis > 35) {
          getDisplay().clear();
          getDisplay().setTextSize(2);
          getDisplay().setTextPos(line - 144, 10);
          getDisplay().setTextWrap(false);
          getDisplay().setTextColor(getDisplay().white());
          getDisplay().drawText(text);
          getDisplay().update();

          previousMillis = millis();
          line++;
        }
      } else {
        
      }
    }

    virtual bool hasNextScreen() override {
      return next;
    }
};