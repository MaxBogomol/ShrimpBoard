#pragma once

class Leds {
  private:
    Settings* settings;

  public:
  
    void setSettings(Settings* settings) {
      this->settings = settings;
    }

    Settings& getSettings() {
      return *this->settings;
    }
};