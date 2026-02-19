#pragma once

class Buzzer {
  private:
    Settings* settings;

  public:
    void playTone(unsigned int frequency, unsigned int duration) {
      if (getSettings.isSound()) tone(BUZZER_PIN, frequency, duration);
    }

    void playTone(unsigned int frequency) {
      if (getSettings.isSound()) tone(BUZZER_PIN, frequency);
    }

    void playNoTone() {
      noTone(BUZZER_PIN);
    }

    void setSettings(Settings* settings) {
      this->settings = settings;
    }

    Settings& getSettings() {
      return *this->settings;
    }
};