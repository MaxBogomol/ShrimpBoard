#include "Interface.h"

#include "../defines/Images.h"

#include "../keyboard/ShrimpBoard.h"

void Interface::setupScreens() {
    setupScreensParameters();
    setupScreensNexts();

    setScreen(&getLoadingScreen());
    getScreen().begin();
}

void Interface::setupScreensParameters() {
    setScreenParameters(&linesLoadingScreen);
    setScreenParameters(&nameLoadingScreen);

    setScreenParameters(&mainScreen);

    setScreenParameters(&settingsScreen);

    setScreenParameters(&mainSettingsIndexScreen);
    setScreenParameters(&keyboardSettingsIndexScreen);
    setScreenParameters(&mouseSettingsIndexScreen);
    setScreenParameters(&screenSettingsIndexScreen);
    setScreenParameters(&batterySettingsIndexScreen);
    setScreenParameters(&ledsSettingsIndexScreen);
    setScreenParameters(&buzzerSettingsIndexScreen);
    setScreenParameters(&gamesSettingsIndexScreen);

    setScreenParameters(&badAppleScreen);

    //Settings
    settingsScreen.addSettingsIndex(&getSettingsIndex(&mainSettingsIndexScreen, SETTINGS_BMP));
    settingsScreen.addSettingsIndex(&getSettingsIndex(&keyboardSettingsIndexScreen, KEYBOARD_BMP));
    settingsScreen.addSettingsIndex(&getSettingsIndex(&mouseSettingsIndexScreen, MOUSE_BMP));
    settingsScreen.addSettingsIndex(&getSettingsIndex(&screenSettingsIndexScreen, SCREEN_BMP));
    settingsScreen.addSettingsIndex(&getSettingsIndex(&batterySettingsIndexScreen, BATTERY_8_BMP));
    settingsScreen.addSettingsIndex(&getSettingsIndex(&ledsSettingsIndexScreen, LED_BMP));
    settingsScreen.addSettingsIndex(&getSettingsIndex(&buzzerSettingsIndexScreen, BUZZER_BMP));
    settingsScreen.addSettingsIndex(&getSettingsIndex(&gamesSettingsIndexScreen, GAMEPAD_BMP));

    //Main
    mainSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&modeSettingsEntry));
    mainSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&usbStatusSettingsEntry));
    mainSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&bleStatusSettingsEntry));
    mainSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&saveSettingsEntry));
    mainSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&resetSettingsEntry));
    mainSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&resetEPROMSettingsEntry));

    //Keyboard
    keyboardSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&debounceSettingsEntry));
    keyboardSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&debounceTimeSettingsEntry));
    keyboardSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&buttonScrollSettingsEntry));
    keyboardSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&buttonScrollDelaySettingsEntry));
    keyboardSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&buttonScrollTimeSettingsEntry));

    //Mouse
    mouseSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&mouseSpeedSettingsEntry));
    mouseSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&touchpadScrollSettingsEntry));
    mouseSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&mouseLockScrollSettingsEntry));
    mouseSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&leftMouseLockScrollSettingsEntry));
    mouseSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&rightMouseLockScrollSettingsEntry));
    mouseSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&mouseScrollSpeedSettingsEntry));
    mouseSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&mouseButtonScrollTimeSettingsEntry));
    mouseSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&touchpadRoundedSettingsEntry));
    mouseSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&touchpadRoundLimitSettingsEntry));
    mouseSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&touchpadInertiaSettingsEntry));
    mouseSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&touchpadInertiaRoundedSettingsEntry));
    mouseSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&touchpadInertiaThresholdSettingsEntry));
    mouseSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&touchpadInertiaStepSettingsEntry));

    //Screen
    screenSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&displayUpdateDelaySettingsEntry));
    screenSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&loadingScreenSettingsEntry));
    screenSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&loadingScreenTypeSettingsEntry));
    screenSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&loadingScreenSpeedSettingsEntry));
    screenSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&showLoadingScreenSettingsEntry));
    
    //Battery
    batterySettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&inactiveSettingsEntry));
    batterySettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&inactiveTimeSettingsEntry));
    batterySettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&showSleepSettingsEntry));
    batterySettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&reloadSettingsEntry));

    //Leds
    ledsSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&ledsSettingsEntry));
    ledsSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&ledsBrightnessSettingsEntry));

    //Buzzer
    buzzerSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&soundSettingsEntry));
    buzzerSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&pressSoundSettingsEntry));
    buzzerSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&pressSoundFrequencySettingsEntry));
    buzzerSettingsIndexScreen.addSettingsEntry(&setSettingsEntryParameters(&pressSoundDurationSettingsEntry));

    //Games
    gamesSettingsIndexScreen.addSettingsIndex(&getSettingsIndex(&badAppleScreen, BAD_APPLE_BMP));
}

void Interface::setupScreensNexts() {
    linesLoadingScreen.setNextScreen(&mainScreen);
    nameLoadingScreen.setNextScreen(&mainScreen);

    mainScreen.setNextScreen(&settingsScreen);

    settingsScreen.setNextScreen(&mainScreen);

    mainSettingsIndexScreen.setNextScreen(&settingsScreen);
    keyboardSettingsIndexScreen.setNextScreen(&settingsScreen);
    mouseSettingsIndexScreen.setNextScreen(&settingsScreen);
    screenSettingsIndexScreen.setNextScreen(&settingsScreen);
    batterySettingsIndexScreen.setNextScreen(&settingsScreen);
    ledsSettingsIndexScreen.setNextScreen(&settingsScreen);
    buzzerSettingsIndexScreen.setNextScreen(&settingsScreen);
    gamesSettingsIndexScreen.setNextScreen(&settingsScreen);

    badAppleScreen.setNextScreen(&gamesSettingsIndexScreen);
}

void Interface::loop() {
    getScreen().loop();

    if (getScreen().hasNextScreen()) {
        getScreen().end();
        setScreen(&(getScreen().getNextScreen()));
        getScreen().begin();
    }

    if (getSettings().isShowLoadingScreen()) {
        getScreen().end();
        setScreen(&(getLoadingScreen()));
        getScreen().begin();
        getSettings().setShowLoadingScreen(false);
    }
}

void Interface::setShrimpBoard(ShrimpBoard* shrimpBoard) {
    this->shrimpBoard = shrimpBoard;
}

void Interface::setScreen(Screen* screen) {
    this->screen = screen;
}

ShrimpBoard& Interface::getShrimpBoard() {
    return *this->shrimpBoard;
}

Screen& Interface::getScreen() {
    return *this->screen;
}

Screen& Interface::setScreenParameters(Screen* screen) {
    screen->setShrimpBoard(&getShrimpBoard());
    return *screen;
}

SettingsEntry& Interface::setSettingsEntryParameters(SettingsEntry* entry) {
    entry->setShrimpBoard(&getShrimpBoard());
    return *entry;
}

SettingsIndex& Interface::getSettingsIndex(Screen* screen, const uint8_t BMP[]) {
    SettingsIndex& index = getSettingsIndex(screen);
    index.setBitmap(BMP);
    return index;
}

SettingsIndex& Interface::getSettingsIndex(Screen* screen) {
    SettingsIndex index = SettingsIndex();
    index.setScreen(screen);
    return index;
}

Screen& Interface::getLoadingScreen() {
    int loading = getSettings().getLoadingScreen();
    if (loading == 0) return linesLoadingScreen;
    if (loading == 1) return nameLoadingScreen;
    return linesLoadingScreen;
}

Settings& Interface::getSettings() {
    return getShrimpBoard().getSettings();
}

ButtonMatrix& Interface::getButtonMatrix() {
    return getShrimpBoard().getButtonMatrix();
}

Battery& Interface::getBattery() {
    return getShrimpBoard().getBattery();
}

Leds& Interface::getLeds() {
    return getShrimpBoard().getLeds();
}

Buzzer& Interface::getBuzzer() {
    return getShrimpBoard().getBuzzer();
}

Keyboard& Interface::getKeyboard() {
    return getShrimpBoard().getKeyboard();
}

Touchpad& Interface::getTouchpad() {
    return getShrimpBoard().getTouchpad();
}

Display& Interface::getDisplay() {
    return getShrimpBoard().getDisplay();
}

EPROM& Interface::getEPROM() {
    return getShrimpBoard().getEPROM();
}