#pragma once

class EPROM {
  private:
    AT24C256* eprom;
    Settings* settings;
    Settings* settingsSaved;

  public:
    void setup() {
        this->eprom = new AT24C256(EPROM_ADDRESS);
        this->settings = new Settings();
        this->settingsSaved = new Settings();
    }

    AT24C256& getEPROM() {
      return *this->eprom;
    }

    Settings& getSettings() {
      return *this->settings;
    }

    Settings& getSettingsSaved() {
      return *this->settingsSaved;
    }
};