#pragma once

class Battery {
  private:
    Settings* settings;

  public:

    int getPercentage() {
      return 100;
    }

    double getRawVoltage() {
      int rawValue = analogRead(BATTERY_PIN);
      return (rawValue * 3.3) / MAX_ANALOG_VALUE;
    }

    double getVoltage() {
      return getRawVoltage();
    }

    void setSettings(Settings* settings) {
      this->settings = settings;
    }

    Settings& getSettings() {
      return *this->settings;
    }
};