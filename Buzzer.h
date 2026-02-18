#pragma once

class Buzzer {
  private:
    Settings* settings;

  public:
    void playTone(unsigned int frequency, unsigned int duration) {
      tone(BUZZER_PIN, frequency, duration);
    }

    void playTone(unsigned int frequency) {
      tone(BUZZER_PIN, frequency);
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