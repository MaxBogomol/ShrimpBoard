#include "Buzzer.h"

void Buzzer::playTone(unsigned int frequency, unsigned int duration) {
    if (getSettings().isSound()) tone(BUZZER_PIN, frequency, duration);
}

void Buzzer::playTone(unsigned int frequency) {
    if (getSettings().isSound()) tone(BUZZER_PIN, frequency);
}

void Buzzer::playNoTone() {
    noTone(BUZZER_PIN);
}

void Buzzer::setSettings(Settings* settings) {
    this->settings = settings;
}

Settings& Buzzer::getSettings() {
    return *this->settings;
}