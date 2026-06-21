#include "Interface.h"

void Interface::setupScreens() {
    setupScreensParameters();
    setupScreensNexts();

    setScreen(&getLoadingScreen());
    getScreen().begin();
}

void Interface::setupScreensParameters() {
    setScreenParameters(&loadingLinesScreen);
    setScreenParameters(&loadingShrimpBoardScreen);

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
    SettingsIndexNode* settingsIndexNode = new SettingsIndexNode();
    setSettingsIndexNode(settingsIndexNode, &mainSettingsIndexScreen, SETTINGS_BMP);
    addSettingsIndexNode(settingsIndexNode, &keyboardSettingsIndexScreen, KEYBOARD_BMP);
    addSettingsIndexNode(settingsIndexNode, &mouseSettingsIndexScreen, MOUSE_BMP);
    addSettingsIndexNode(settingsIndexNode, &screenSettingsIndexScreen, SCREEN_BMP);
    addSettingsIndexNode(settingsIndexNode, &batterySettingsIndexScreen, BATTERY_8_BMP);
    addSettingsIndexNode(settingsIndexNode, &ledsSettingsIndexScreen, LED_BMP);
    addSettingsIndexNode(settingsIndexNode, &buzzerSettingsIndexScreen, BUZZER_BMP);
    addSettingsIndexNode(settingsIndexNode, &gamesSettingsIndexScreen, GAMEPAD_BMP);
    settingsScreen.setSettingsIndices(settingsIndexNode);

    //Main
    SettingsEntryNode* mainSettingsEntryNode = new SettingsEntryNode();
    setSettingsEntryNode(mainSettingsEntryNode, &modeSettingsEntry);
    addSettingsEntryNode(mainSettingsEntryNode, &usbStatusSettingsEntry);
    addSettingsEntryNode(mainSettingsEntryNode, &bleStatusSettingsEntry);
    addSettingsEntryNode(mainSettingsEntryNode, &saveSettingsEntry);
    saveSettingsEntry.setEPROM(eprom);
    addSettingsEntryNode(mainSettingsEntryNode, &resetSettingsEntry);
    addSettingsEntryNode(mainSettingsEntryNode, &resetEPROMSettingsEntry);
    resetEPROMSettingsEntry.setEPROM(eprom);
    mainSettingsIndexScreen.setSettingsEntries(mainSettingsEntryNode);

    setSettingsEntryParameters(&modeSettingsEntry);
    setSettingsEntryParameters(&usbStatusSettingsEntry);
    setSettingsEntryParameters(&bleStatusSettingsEntry);
    bleStatusSettingsEntry.setCompositeHID(compositeHID);
    setSettingsEntryParameters(&saveSettingsEntry);
    setSettingsEntryParameters(&resetSettingsEntry);
    setSettingsEntryParameters(&resetEPROMSettingsEntry);

    //Keyboard
    SettingsEntryNode* keyboardSettingsEntryNode = new SettingsEntryNode();
    setSettingsEntryNode(keyboardSettingsEntryNode, &debounceSettingsEntry);
    addSettingsEntryNode(keyboardSettingsEntryNode, &debounceTimeSettingsEntry);
    addSettingsEntryNode(keyboardSettingsEntryNode, &buttonScrollSettingsEntry);
    addSettingsEntryNode(keyboardSettingsEntryNode, &buttonScrollDelaySettingsEntry);
    addSettingsEntryNode(keyboardSettingsEntryNode, &buttonScrollTimeSettingsEntry);
    keyboardSettingsIndexScreen.setSettingsEntries(keyboardSettingsEntryNode);

    setSettingsEntryParameters(&debounceSettingsEntry);
    setSettingsEntryParameters(&debounceTimeSettingsEntry);
    setSettingsEntryParameters(&buttonScrollSettingsEntry);
    setSettingsEntryParameters(&buttonScrollDelaySettingsEntry);
    setSettingsEntryParameters(&buttonScrollTimeSettingsEntry);

    //Mouse
    SettingsEntryNode* mouseSettingsEntryNode = new SettingsEntryNode();
    setSettingsEntryNode(mouseSettingsEntryNode, &mouseSpeedSettingsEntry);
    addSettingsEntryNode(mouseSettingsEntryNode, &touchpadScrollSettingsEntry);
    addSettingsEntryNode(mouseSettingsEntryNode, &mouseLockScrollSettingsEntry);
    addSettingsEntryNode(mouseSettingsEntryNode, &leftMouseLockScrollSettingsEntry);
    addSettingsEntryNode(mouseSettingsEntryNode, &rightMouseLockScrollSettingsEntry);
    addSettingsEntryNode(mouseSettingsEntryNode, &mouseScrollSpeedSettingsEntry);
    addSettingsEntryNode(mouseSettingsEntryNode, &mouseButtonScrollTimeSettingsEntry);
    addSettingsEntryNode(mouseSettingsEntryNode, &touchpadRoundedSettingsEntry);
    addSettingsEntryNode(mouseSettingsEntryNode, &touchpadRoundLimitSettingsEntry);
    addSettingsEntryNode(mouseSettingsEntryNode, &touchpadInertiaSettingsEntry);
    addSettingsEntryNode(mouseSettingsEntryNode, &touchpadInertiaRoundedSettingsEntry);
    addSettingsEntryNode(mouseSettingsEntryNode, &touchpadInertiaThresholdSettingsEntry);
    addSettingsEntryNode(mouseSettingsEntryNode, &touchpadInertiaStepSettingsEntry);
    mouseSettingsIndexScreen.setSettingsEntries(mouseSettingsEntryNode);

    setSettingsEntryParameters(&mouseSpeedSettingsEntry);
    setSettingsEntryParameters(&touchpadScrollSettingsEntry);
    setSettingsEntryParameters(&mouseLockScrollSettingsEntry);
    setSettingsEntryParameters(&leftMouseLockScrollSettingsEntry);
    setSettingsEntryParameters(&rightMouseLockScrollSettingsEntry);
    setSettingsEntryParameters(&mouseScrollSpeedSettingsEntry);
    setSettingsEntryParameters(&mouseButtonScrollTimeSettingsEntry);
    setSettingsEntryParameters(&touchpadRoundedSettingsEntry);
    setSettingsEntryParameters(&touchpadRoundLimitSettingsEntry);
    setSettingsEntryParameters(&touchpadInertiaSettingsEntry);
    setSettingsEntryParameters(&touchpadInertiaRoundedSettingsEntry);
    setSettingsEntryParameters(&touchpadInertiaThresholdSettingsEntry);
    setSettingsEntryParameters(&touchpadInertiaStepSettingsEntry);

    //Screen
    SettingsEntryNode* screenSettingsEntryNode = new SettingsEntryNode();
    setSettingsEntryNode(screenSettingsEntryNode, &displayUpdateDelaySettingsEntry);
    addSettingsEntryNode(screenSettingsEntryNode, &loadingScreenSettingsEntry);
    addSettingsEntryNode(screenSettingsEntryNode, &loadingScreenTypeSettingsEntry);
    addSettingsEntryNode(screenSettingsEntryNode, &loadingScreenSpeedSettingsEntry);
    addSettingsEntryNode(screenSettingsEntryNode, &showLoadingScreenSettingsEntry);
    screenSettingsIndexScreen.setSettingsEntries(screenSettingsEntryNode);

    setSettingsEntryParameters(&displayUpdateDelaySettingsEntry);
    setSettingsEntryParameters(&loadingScreenSettingsEntry);
    setSettingsEntryParameters(&loadingScreenTypeSettingsEntry);
    setSettingsEntryParameters(&loadingScreenSpeedSettingsEntry);
    setSettingsEntryParameters(&showLoadingScreenSettingsEntry);

    //Battery
    SettingsEntryNode* batterySettingsEntryNode = new SettingsEntryNode();
    setSettingsEntryNode(batterySettingsEntryNode, &inactiveSettingsEntry);
    addSettingsEntryNode(batterySettingsEntryNode, &inactiveTimeSettingsEntry);
    addSettingsEntryNode(batterySettingsEntryNode, &showSleepSettingsEntry);
    addSettingsEntryNode(batterySettingsEntryNode, &reloadSettingsEntry);
    batterySettingsIndexScreen.setSettingsEntries(batterySettingsEntryNode);

    setSettingsEntryParameters(&inactiveSettingsEntry);
    setSettingsEntryParameters(&inactiveTimeSettingsEntry);
    setSettingsEntryParameters(&showSleepSettingsEntry);
    setSettingsEntryParameters(&reloadSettingsEntry);
    reloadSettingsEntry.setBattery(battery);

    //Leds
    SettingsEntryNode* ledsSettingsEntryNode = new SettingsEntryNode();
    setSettingsEntryNode(ledsSettingsEntryNode, &ledsSettingsEntry);
    addSettingsEntryNode(ledsSettingsEntryNode, &ledsBrightnessSettingsEntry);
    ledsSettingsIndexScreen.setSettingsEntries(ledsSettingsEntryNode);

    setSettingsEntryParameters(&ledsSettingsEntry);
    setSettingsEntryParameters(&ledsBrightnessSettingsEntry);

    //Buzzer
    SettingsEntryNode* buzzerSettingsEntryNode = new SettingsEntryNode();
    setSettingsEntryNode(buzzerSettingsEntryNode, &soundSettingsEntry);
    addSettingsEntryNode(buzzerSettingsEntryNode, &pressSoundSettingsEntry);
    addSettingsEntryNode(buzzerSettingsEntryNode, &pressSoundFrequencySettingsEntry);
    addSettingsEntryNode(buzzerSettingsEntryNode, &pressSoundDurationSettingsEntry);
    buzzerSettingsIndexScreen.setSettingsEntries(buzzerSettingsEntryNode);

    setSettingsEntryParameters(&soundSettingsEntry);
    setSettingsEntryParameters(&pressSoundSettingsEntry);
    setSettingsEntryParameters(&pressSoundFrequencySettingsEntry);
    setSettingsEntryParameters(&pressSoundDurationSettingsEntry);

    //Games
    SettingsIndexNode* gamesSettingsIndexNode = new SettingsIndexNode();
    setSettingsIndexNode(gamesSettingsIndexNode, &badAppleScreen, BAD_APPLE_BMP);
    gamesSettingsIndexScreen.setSettingsIndices(gamesSettingsIndexNode);
}

void Interface::setupScreensNexts() {
    loadingLinesScreen.setNextScreen(&mainScreen);
    loadingShrimpBoardScreen.setNextScreen(&mainScreen);

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

void Interface::setSettings(Settings* settings) {
    this->settings = settings;
}

void Interface::setCompositeHID(BleCompositeHID* compositeHID) {
    this->compositeHID = compositeHID;
}

void Interface::setButtonMatrix(ButtonMatrix* buttonMatrix) {
    this->buttonMatrix = buttonMatrix;
}

void Interface::setBattery(Battery* battery) {
    this->battery = battery;
}

void Interface::setLeds(Leds* leds) {
    this->leds = leds;
}

void Interface::setBuzzer(Buzzer* buzzer) {
    this->buzzer = buzzer;
}

void Interface::setTouchpad(Touchpad* touchpad) {
    this->touchpad = touchpad;
}

void Interface::setDisplay(Display* display) {
    this->display = display;
}

void Interface::setEPROM(EPROM* eprom) {
    this->eprom = eprom;
}

void Interface::setScreen(Screen* screen) {
    this->screen = screen;
}

Settings& Interface::getSettings() {
    return *this->settings;
}

BleCompositeHID& Interface::getCompositeHID() {
    return *this->compositeHID;
}

ButtonMatrix& Interface::getButtonMatrix() {
    return *this->buttonMatrix;
}

Battery& Interface::getBattery() {
    return *this->battery;
}

Leds& Interface::getLeds() {
    return *this->leds;
}

Buzzer& Interface::getBuzzer() {
    return *this->buzzer;
}

Touchpad& Interface::getTouchpad() {
    return *this->touchpad;
}

Display& Interface::getDisplay() {
    return *this->display;
}

EPROM& Interface::getEPROM() {
    return *this->eprom;
}

Screen& Interface::getScreen() {
    return *this->screen;
}

void Interface::setScreenParameters(Screen* screen) {
    screen->setSettings(settings);
    screen->setCompositeHID(compositeHID);
    screen->setButtonMatrix(buttonMatrix);
    screen->setBattery(battery);
    screen->setLeds(leds);
    screen->setBuzzer(buzzer);
    screen->setTouchpad(touchpad);
    screen->setDisplay(display);
    screen->setEPROM(eprom);
}

void Interface::setSettingsEntryParameters(SettingsEntry* entry) {
    entry->setSettings(settings);
    entry->setBuzzer(buzzer);
}

void Interface::addSettingsIndexNode(SettingsIndexNode* indexNode, Screen* data, const uint8_t BMP[]) {
    SettingsIndexNode* node = indexNode;
    int i = 0;
    while (true) {
        if (!node->hasNext()) {
            SettingsIndexNode* newNode = new SettingsIndexNode();
            setSettingsIndexNode(newNode, data, BMP);
            node->setNextNode(newNode);
            break;
        }
        node = &(node->getNextNode());
        i++;
    }
}

void Interface::setSettingsIndexNode(SettingsIndexNode* indexNode, Screen* data, const uint8_t BMP[]) {
    indexNode->setData(data);
    indexNode->setBitmap(BMP);
}

void Interface::addSettingsEntryNode(SettingsEntryNode* entryNode, SettingsEntry* data) {
    SettingsEntryNode* node = entryNode;
    int i = 0;
    while (true) {
        if (!node->hasNext()) {
            SettingsEntryNode* newNode = new SettingsEntryNode();
            setSettingsEntryNode(newNode, data);
            node->setNextNode(newNode);
            break;
        }
        node = &(node->getNextNode());
        i++;
    }
}

void Interface::setSettingsEntryNode(SettingsEntryNode* entryNode, SettingsEntry* data) {
    entryNode->setData(data);
}

Screen& Interface::getLoadingScreen() {
    int loading = getSettings().getLoadingScreen();
    if (loading == 0) return loadingLinesScreen;
    if (loading == 1) return loadingShrimpBoardScreen;
    return loadingLinesScreen;
}