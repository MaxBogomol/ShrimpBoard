#include "NameLoadingScreen.h"

void NameLoadingScreen::begin() {
    Screen::begin();
    previousMillis = millis();
    next = false;
    step = 0;
}

void NameLoadingScreen::loop() {
    unsigned long currentMillis = millis();
    int type = getSettings().getLoadingScreenType();

    if (step < 288) {
        if (currentMillis - previousMillis >= getSettings().getDisplayUpdateDelay()) {
            int x = step - 144;
            if (type == 1) x = 144 - step;

            getDisplay().clear();
            getDisplay().textReset();
            getDisplay().setTextSize(2);
            getDisplay().setTextPos(x, 8);
            getDisplay().setTextWrap(false);
            getDisplay().setTextColor(getDisplay().white());
            getDisplay().drawText(text);
            getDisplay().update();

            previousMillis = currentMillis;
            step += getSettings().getLoadingScreenSpeed();
        }
    } else {
        next = true;
    }
    if (getKeyboard().isFNPress() || getKeyboard().isEscPress() || getKeyboard().isEnterPress() || getKeyboard().isSpacePress()) next = true;
}

bool NameLoadingScreen::hasNextScreen() {
    return next;
}