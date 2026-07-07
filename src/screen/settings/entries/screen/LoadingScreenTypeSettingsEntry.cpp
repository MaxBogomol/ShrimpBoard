#include "LoadingScreenTypeSettingsEntry.h"

String LoadingScreenTypeSettingsEntry::getName() {
    String name = "Loading type: ";
    int value = getSettings().getLoadingScreenType();
    int loading = getSettings().getLoadingScreen();
    switch (loading) {
        case 0: {
            switch (value) {
                case 0: name = name + "Up Right"; break;
                case 1: name = name + "Up Left"; break;
                case 2: name = name + "Down Right"; break;
                case 3: name = name + "Down Left"; break;
            }
            break;
        }
        case 1: {
            switch (value) {
                case 0: name = name + "Right"; break;
                case 1: name = name + "Left"; break;
            }
            break;
        }
    }
    return name;
}

void LoadingScreenTypeSettingsEntry::left() {
    int value = getSettings().getLoadingScreenType();
    int loading = getSettings().getLoadingScreen();
    if (value - 1 >= 0) {
        value--;
        getSettings().setLoadingScreenType(value);
        playToneSettings();
    }
}

void LoadingScreenTypeSettingsEntry::right() {
    int value = getSettings().getLoadingScreenType();
    int loading = getSettings().getLoadingScreen();
    if ((value + 1 <= 3 && loading == 0) ||
            (value + 1 <= 1 && loading == 1)) {
        value++;
        getSettings().setLoadingScreenType(value);
        playToneSettings();
    }
}