#include "SettingsScreen.h"

#include "../../keyboard/ShrimpBoard.h"

void SettingsScreen::begin() {
    Screen::begin();
    previousMillis = millis();
    next = false;
    select = false;
    getSettings().setScreenFocus(true);
}

void SettingsScreen::loop() {
    unsigned long currentMillis = millis();
    bool scroll = getSettings().isButtonScroll();
    int scrollDelay = getSettings().getButtonScrollDelay();
    int scrollTime = getSettings().getButtonScrollTime();

    int max = getSettingsIndices().size();

    if (currentMillis - previousMillis >= getSettings().getDisplayUpdateDelay()) {
        getDisplay().clear();
        //for (int i = 0; i < 6; i++) { 
        //    int offset = selectedOffset - i;
        //    if (offset >= -1 && offset <= 6) drawIndex(6 + (offset * 24), (i == selectedIndex) ? 2 : 6, node->getBitmap());
        //    i++;
        //}
        getDisplay().update();

        previousMillis = currentMillis;
    }

    bool left = false;
    bool right = false;
    bool sound = false;
    if (getKeyboard().isLeftPress() || getKeyboard().isAPress()) {
        left = true;
        leftPressMillis = millis();
        leftPress = false;
    }
    if (scroll && (getKeyboard().isLeftPressed() || getKeyboard().isAPressed())) {
        if (!leftPress && currentMillis - leftPressMillis >= scrollDelay) {
            left = true;
            leftPressMillis = millis();
            leftPress = true;
        }
        if (leftPress && currentMillis - leftPressMillis >= scrollTime) {
            left = true;
            leftPressMillis = millis();
        }
    }
    if (getKeyboard().isRightPress() || getKeyboard().isDPress()) {
        right = true;
        rightPressMillis = millis();
        rightPress = false;
    }
    if (scroll && (getKeyboard().isRightPressed() || getKeyboard().isDPressed())) {
        if (!rightPress && currentMillis - rightPressMillis >= scrollDelay) {
            right = true;
            rightPressMillis = millis();
            rightPress = true;
        }
        if (rightPress && currentMillis - rightPressMillis >= scrollTime) {
            right = true;
            rightPressMillis = millis();
        }
    }

    if (left) {
        if (selectedIndex - 1 >= 0) {
            selectedIndex--;
            sound = true;
        }
        if (selectedOffset - 1 >= 0 && selectedIndex - selectedOffset < 0) selectedOffset--;
    }
    if (right) {
        if (selectedIndex + 1 < max) {
            selectedIndex++;
            sound = true;
        }
        if (selectedOffset + 5 < max && selectedIndex - selectedOffset > 4) selectedOffset++;
    }

    if (getKeyboard().isEnterPress() || getKeyboard().isSpacePress()) {
        select = true;
        sound = true;
    }

    if (getKeyboard().isEscPress()) {
        next = true;
        sound = true;
    }

    if (sound && getSettings().isPressSound()) {
        int frequency = getSettings().getPressSoundFrequency();
        int duration = getSettings().getPressSoundDuration();
        getBuzzer().playTone(frequency / 2, duration);
    }
}

bool SettingsScreen::hasNextScreen() {
    return next || select;
}

Screen& SettingsScreen::getNextScreen() {
    if (select) {
        return getSettingsIndices()[selectedIndex]->getScreen();
    }
    return Screen::getNextScreen();
}

void SettingsScreen::addSettingsIndex(SettingsIndex* settingsIndex) {
    getSettingsIndices().push_back(settingsIndex);
}

vector<SettingsIndex*>& SettingsScreen::getSettingsIndices() {
    return this->settingsIndices;
}

void SettingsScreen::drawIndex(int x, int y, const uint8_t BMP[]) {
    getDisplay().drawRoundRectangle(x, y, 20, 20, 3, getDisplay().white());
    getDisplay().drawBitmap(BMP, x + 2, y + 2, 16, 16, getDisplay().white());
}