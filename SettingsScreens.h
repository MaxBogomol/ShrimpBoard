#pragma once

class SettingsScreen : public Screen {
  private:
    unsigned long previousMillis = 0;
    bool next = false;

  public:
    virtual void begin() override {
      Screen::begin();
      previousMillis = millis();
      next = false;
      getSettings().setScreenFocus(true);
    }

    virtual void loop() override {
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis > 25) {
        getDisplay().clear();
        getDisplay().drawRoundRectangle(6, 6, 20, 20, 3, getDisplay().white());
        getDisplay().drawBitmap(SETTINGS_BMP, 8, 8, 16, 16, getDisplay().white());
        getDisplay().update();

        previousMillis = millis();
      }

      if (isScreenFocus()) next = true;
    }

    virtual bool hasNextScreen() override {
      return next;
    }
};