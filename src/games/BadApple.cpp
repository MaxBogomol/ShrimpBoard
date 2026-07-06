#include "BadApple.h"

void BadAppleScreen::begin() {
    Screen::begin();
    previousMillis = millis();
    next = false;
    frame = 0;
    note = 0;
    getSettings().setScreenFocus(true);
}

void BadAppleScreen::loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 200) {
        getDisplay().clear();
        getDisplay().drawBitmap(BAD_APPLE_ARRAY[frame], 43, 0, 42, 32, getDisplay().white());
        getDisplay().update();
        previousMillis = currentMillis;
        if (frame < BAD_APPLE_ARRAY_LEN) frame++;
    }

    if (frame == BAD_APPLE_ARRAY_LEN) next = true;

    if (getKeyboard().isEscPress()) next = true;

    if (currentMillis - previousMillisMusic >= pause) {
        int size = sizeof(BAD_APPLE_MELODY) / sizeof(int);
        int duration = 1000 / BAD_APPLE_DURATIONS[note];
        getBuzzer().playTone(BAD_APPLE_MELODY[note], duration);
        pause = duration * 1.30;
        previousMillisMusic = currentMillis;
        note++;
    }
}

bool BadAppleScreen::hasNextScreen() {
    return next;
}