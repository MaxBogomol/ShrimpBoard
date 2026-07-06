#include "SettingsIndexScreen.h"

void SettingsIndexScreen::begin() {
    Screen::begin();
    previousMillis = millis();
    next = false;
    select = false;
    selectedIndex = 0;
    selectedOffset = 0;
    getSettings().setScreenFocus(true);
}

void SettingsIndexScreen::loop() {
    unsigned long currentMillis = millis();
    bool scroll = getSettings().isButtonScroll();
    int scrollDelay = getSettings().getButtonScrollDelay();
    int scrollTime = getSettings().getButtonScrollTime();

    SettingsEntry* entry = getSettingsEntries()[0];
    int max = getSettingsEntries().size();

    if (currentMillis - previousMillis >= getSettings().getDisplayUpdateDelay()) {
        getDisplay().clear();
        getDisplay().textReset();
        getDisplay().setTextWrap(false);
        /*
        i = 0;
        while (true) {
            SettingsEntry* index = &node->getData();

            int offset = i - selectedOffset;
            String s = index->getName();
            if (i == selectedIndex) s = ">" + s;
            if (offset >= 0 && offset <= 3) {
                int x = 0;
                int l = s.length() * 6;
                float speed = 10;
                if (l > 128) {
                    double t = (double) fmod((currentMillis / (l / 128.0)) * (1 / speed), 360);
                    double xOffset = sin(t * (PI / 180.0));
                    x = (int) (xOffset * (l - 128 + 2));
                    x = -abs(x);
                }

                getDisplay().setTextPos(x, offset * 8);
                getDisplay().drawText(s);
            }

            if (!node->hasNext()) break;
            node = &(node->getNextNode());
            i++;
        }*/
        getDisplay().update();

        previousMillis = currentMillis;
    }

    bool left = false;
    bool right = false;
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
    if (getKeyboard().isRightPress() || getKeyboard().isDPress() || getKeyboard().isEnterPress() || getKeyboard().isSpacePress()) {
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
/*
    node = settingsEntries;
    i = 0;
    while (true) {
        if (i == selectedIndex) {
            SettingsEntry* index = &node->getData();
            if (left) index->left();
            if (right) index->right();
            if (left || right) select = index->hasNextScreen();
        }

        if (!node->hasNext()) break;
        node = &(node->getNextNode());
        i++;
    }*/

    bool up = false;
    bool down = false;
    bool sound = false;
    if (getKeyboard().isUpPress() || getKeyboard().isWPress()) {
        up = true;
        upPressMillis = millis();
        upPress = false;
    }
    if (scroll && (getKeyboard().isUpPressed() || getKeyboard().isWPressed())) {
        if (!upPress && currentMillis - upPressMillis >= scrollDelay) {
            up = true;
            upPressMillis = millis();
            upPress = true;
        }
        if (upPress && currentMillis - upPressMillis >= scrollTime) {
            up = true;
            upPressMillis = millis();
        }
    }
    if (getKeyboard().isDownPress() || getKeyboard().isSPress()) {
        down = true;
        downPressMillis = millis();
        downPress = false;
    }
    if (scroll && (getKeyboard().isDownPressed() || getKeyboard().isSPressed())) {
        if (!downPress && currentMillis - downPressMillis >= scrollDelay) {
            down = true;
            downPressMillis = millis();
            downPress = true;
        }
        if (downPress && currentMillis - downPressMillis >= scrollTime) {
            down = true;
            downPressMillis = millis();
        }
    }

    if (up) {
        if (selectedIndex - 1 >= 0) {
            selectedIndex--;
            sound = true;
        }
        if (selectedOffset - 1 >= 0 && selectedIndex - selectedOffset < 1) selectedOffset--;
    }
    if (down) {
        if (selectedIndex + 1 < max) {
            selectedIndex++;
            sound = true;
        }
        if (selectedOffset + 4 < max && selectedIndex - selectedOffset > 2) selectedOffset++;
    }
    if (sound && getSettings().isPressSound()) {
        int frequency = getSettings().getPressSoundFrequency();
        int duration = getSettings().getPressSoundDuration();
        getBuzzer().playTone(frequency, duration);
    }

    if (getKeyboard().isEscPress()) {
        next = true;
        if (getSettings().isPressSound()) {
            int frequency = getSettings().getPressSoundFrequency();
            int duration = getSettings().getPressSoundDuration();
            getBuzzer().playTone(frequency / 2, duration);
        }
    }
}

bool SettingsIndexScreen::hasNextScreen() {
    return next || select;
}

Screen& SettingsIndexScreen::getNextScreen() {
    if (select) {
        SettingsEntry* entry = getSettingsEntries()[selectedIndex];
        if (entry->hasNextScreen()) {
            return entry->getNextScreen();
        }
    }
    return Screen::getNextScreen();
}

void SettingsIndexScreen::addSettingsEntry(SettingsEntry* settingsEntry) {
    getSettingsEntries().push_back(settingsEntry);
}

vector<SettingsEntry*>& SettingsIndexScreen::getSettingsEntries() {
    return this->settingsEntries;
}