#include "../../SettingsEntry.h"
#include "LoadingScreenSettingsEntry.h"

String LoadingScreenSettingsEntry::getName() {
    String name = "Loading: ";
    int loading = getSettings().getLoadingScreen();
    switch(loading) {
        case 0: name = name + "Lines"; break;
        case 1: name = name + "Name"; break;
    }
    return name;
}

void LoadingScreenSettingsEntry::left() {
    int value = getSettings().getLoadingScreen();
    if (value - 1 >= 0) {
        value--;
        getSettings().setLoadingScreen(value);
        getSettings().setLoadingScreenType(0);
        playToneSettings();
    }
}

void LoadingScreenSettingsEntry::right() {
    int value = getSettings().getLoadingScreen();
    if (value + 1 <= 1) {
        value++;
        getSettings().setLoadingScreen(value);
        getSettings().setLoadingScreenType(0);
        playToneSettings();
    }
}