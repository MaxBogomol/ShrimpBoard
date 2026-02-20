#pragma once

class Leds {
  private:
    Settings* settings;

  public:
    void setNumLockBrightness(int brightness) {
      setLedBrightness(LED_NUM_LOCK_PIN, brightness);
    }

    void setCapsLockBrightness(int brightness) {
      setLedBrightness(LED_CAPS_LOCK_PIN, brightness);
    }

    void setScrollLockBrightness(int brightness) {
      setLedBrightness(LED_SCROLL_LOCK_PIN, brightness);
    }

    void setLeftMouseLockBrightness(int brightness) {
      setLedBrightness(LED_LEFT_MOUSE_LOCK_PIN, brightness);
    }

    void setRightMouseLockBrightness(int brightness) {
      setLedBrightness(LED_RIGHT_MOUSE_LOCK_PIN, brightness);
    }

    void setSpecialBrightness(int brightness) {
      setLedBrightness(LED_SPECIAL_PIN, brightness);
    }

    void disableAll() {
      setNumLockBrightness(0);
      setCapsLockBrightness(0);
      setScrollLockBrightness(0);
      setLeftMouseLockBrightness(0);
      setRightMouseLockBrightness(0);
      setSpecialBrightness(0);
    }

    void setLedBrightness(int pin, int brightness) {
      setLedWrite(pin, (int) (MAX_ANALOG_VALUE * (brightness / 100.0)));
    }

    void setLedBrightnessRaw(int pin, int brightness) {
      setLedWriteRaw(pin, (int) (MAX_ANALOG_VALUE * (brightness / 100.0)));
    }

    void setLedWrite(int pin, int value) {
      int brightness = getSettings().getLedBrightness();
      setLedWriteRaw(pin, (int) (value * (brightness / 100.0)));
    }
  
    void setLedWriteRaw(int pin, int value) {
      if (!getSettings().isLeds()) value = 0;
      analogWrite(pin, value);
    }
  
    void setSettings(Settings* settings) {
      this->settings = settings;
    }

    Settings& getSettings() {
      return *this->settings;
    }
};