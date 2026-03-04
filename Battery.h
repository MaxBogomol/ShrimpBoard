#pragma once

class Battery {
  private:
    Settings* settings;

  public:
    void reset() {
      digitalWrite(RESET_PIN, HIGH);
    }

    void setSettings(Settings* settings) {
      this->settings = settings;
    }

    Settings& getSettings() {
      return *this->settings;
    }
};