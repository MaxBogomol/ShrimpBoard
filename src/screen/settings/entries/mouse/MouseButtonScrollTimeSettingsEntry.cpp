#include "../../SettingsEntry.h"
#include "MouseButtonScrollTimeSettingsEntry.h"

String MouseButtonScrollTimeSettingsEntry::getName() {
    return "Button scroll time: " + String(getSettings().getMouseButtonScrollTime()) + " ms";
}

void MouseButtonScrollTimeSettingsEntry::left() {
    int value = getSettings().getMouseButtonScrollTime();
    if (value - 1 >= 1) {
        value--;
        getSettings().setMouseButtonScrollTime(value);
        playToneSettings();
    }
}

void MouseButtonScrollTimeSettingsEntry::right() {
    int value = getSettings().getMouseButtonScrollTime();
    if (value + 1 <= 100) {
        value++;
        getSettings().setMouseButtonScrollTime(value);
        playToneSettings();
    }
}