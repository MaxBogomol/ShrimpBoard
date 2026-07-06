#include "LinesLoadingScreen.h"

void LinesLoadingScreen::begin() {
    Screen::begin();
    previousMillis = millis();
    next = false;
    line = 0;
}

void LinesLoadingScreen::loop() {
    unsigned long currentMillis = millis();
    int step = getSettings().getLoadingScreenSpeed();
    int type = getSettings().getLoadingScreenType();

    if (line < 80) {
        if (currentMillis - previousMillis >= getSettings().getDisplayUpdateDelay()) {
            for (int i = 0; i < step; i++) {
                int x1 = -32;
                int x2 = 0;
                if (type == 2 || type == 3) {
                    x1 = 0;
                    x2 = -32;
                }
                x1 = x1 + ((line + i) * 2);
                x2 = x2 + ((line + i) * 2);
                if (type == 1 || type == 3) {
                    x1 = 128 - x1;
                    x2 = 128 - x2;
                }
                getDisplay().drawLine(x1, 32, x2, 0, getDisplay().white());
            }
            getDisplay().update();

            previousMillis = currentMillis;
            line += step;
        }
    } else {
        next = true;
    }
    if (getKeyboard().isFNPress() || getKeyboard().isEscPress() || getKeyboard().isEnterPress() || getKeyboard().isSpacePress()) next = true;
}

bool LinesLoadingScreen::hasNextScreen() {
    return next;
}