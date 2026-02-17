#pragma once

#include <Screen.h>
#include <LoadingScreens.h>
#include <MainScreens.h>
#include <SettingsScreens.h>

class Interface {
  private:
    Settings* settings;

    BleCompositeHID* compositeHID;

    ButtonMatrix* buttonMatrix;
    Touchpad* touchpad;
    Display* display;
    EPROM* eprom;

    Screen* screen;

    LoadingLinesScreen loadingLinesScreen;
    LoadingShrimpBoardScreen loadingShrimpBoardScreen;

    MainScreen mainScreen;

    SettingsScreen settingsScreen;

    SettingsIndexScreen mainSettingsIndexScreen;
    SettingsIndexScreen keyboardSettingsIndexScreen;
    SettingsIndexScreen mouseSettingsIndexScreen;
    SettingsIndexScreen screenSettingsIndexScreen;
    SettingsIndexScreen batterySettingsIndexScreen;
    SettingsIndexScreen ledSettingsIndexScreen;
    SettingsIndexScreen buzzerSettingsIndexScreen;
    SettingsIndexScreen gamesSettingsIndexScreen;

    ModeSettingsEntry modeSettingsEntry;
    BLEStatusSettingsEntry bleStatusSettingsEntry;
    SaveSettingsEntry saveSettingsEntry;
    ResetSettingsEntry resetSettingsEntry;

    DebounceSettingsEntry debounceSettingsEntry;
    DebounceTimeSettingsEntry debounceTimeSettingsEntry;

    MouseSpeedSettingsEntry mouseSpeedSettingsEntry;
    TouchpadScrollSettingsEntry touchpadScrollSettingsEntry;
    MouseLockScrollSettingsEntry mouseLockScrollSettingsEntry;
    LeftMouseLockScrollSettingsEntry leftMouseLockScrollSettingsEntry;
    RightMouseLockScrollSettingsEntry rightMouseLockScrollSettingsEntry;
    MouseScrollSpeedSettingsEntry mouseScrollSpeedSettingsEntry;
    TouchpadRoundedSettingsEntry touchpadRoundedSettingsEntry;
    TouchpadRoundLimitSettingsEntry touchpadRoundLimitSettingsEntry;
    TouchpadInertiaSettingsEntry touchpadInertiaSettingsEntry;
    TouchpadInertiaRoundedSettingsEntry touchpadInertiaRoundedSettingsEntry;
    TouchpadInertiaStressholdSettingsEntry touchpadInertiaStressholdSettingsEntry;
    TouchpadInertiaStepSettingsEntry touchpadInertiaStepSettingsEntry;

    DisplayUpdateDelaySettingsEntry displayUpdateDelaySettingsEntry;
    LoadingScreenSettingsEntry loadingScreenSettingsEntry;
    LoadingScreenSpeedSettingsEntry loadingScreenSpeedSettingsEntry;
    ShowLoadingDelaySettingsEntry showLoadingDelaySettingsEntry;

    InactiveSettingsEntry inactiveSettingsEntry;
    InactiveTimeSettingsEntry inactiveTimeSettingsEntry;

  public:
    void setupScreens() {
      setupScreensParameters();
      setupScreensNexts();

      setScreen(&getLoadingScreen());
      getScreen().begin();
    }

    void setupScreensParameters() {
      setScreenParameters(&loadingLinesScreen);
      setScreenParameters(&loadingShrimpBoardScreen);

      setScreenParameters(&mainScreen);

      setScreenParameters(&settingsScreen);

      setScreenParameters(&mainSettingsIndexScreen);
      setScreenParameters(&keyboardSettingsIndexScreen);
      setScreenParameters(&mouseSettingsIndexScreen);
      setScreenParameters(&screenSettingsIndexScreen);
      setScreenParameters(&batterySettingsIndexScreen);
      setScreenParameters(&ledSettingsIndexScreen);
      setScreenParameters(&buzzerSettingsIndexScreen);
      setScreenParameters(&gamesSettingsIndexScreen);

      //Settings
      SettingsIndexNode* settingsIndexNode = new SettingsIndexNode();
      setSettingsIndexNode(settingsIndexNode, &mainSettingsIndexScreen, SETTINGS_BMP);
      addSettingsIndexNode(settingsIndexNode, &keyboardSettingsIndexScreen, KEYBOARD_BMP);
      addSettingsIndexNode(settingsIndexNode, &mouseSettingsIndexScreen, MOUSE_BMP);
      addSettingsIndexNode(settingsIndexNode, &screenSettingsIndexScreen, SCREEN_BMP);
      addSettingsIndexNode(settingsIndexNode, &batterySettingsIndexScreen, BATTERY_8_BMP);
      addSettingsIndexNode(settingsIndexNode, &ledSettingsIndexScreen, LED_BMP);
      addSettingsIndexNode(settingsIndexNode, &buzzerSettingsIndexScreen, BUZZER_BMP);
      addSettingsIndexNode(settingsIndexNode, &gamesSettingsIndexScreen, GAMEPAD_BMP);
      settingsScreen.setSettingsIndices(settingsIndexNode);

      //Main
      SettingsEntryNode* mainSettingsEntryNode = new SettingsEntryNode();
      setSettingsEntryNode(mainSettingsEntryNode, &modeSettingsEntry);
      addSettingsEntryNode(mainSettingsEntryNode, &bleStatusSettingsEntry);
      addSettingsEntryNode(mainSettingsEntryNode, &saveSettingsEntry);
      addSettingsEntryNode(mainSettingsEntryNode, &resetSettingsEntry);
      mainSettingsIndexScreen.setSettingsEntries(mainSettingsEntryNode);

      modeSettingsEntry.setSettings(settings);
      bleStatusSettingsEntry.setSettings(settings);
      bleStatusSettingsEntry.setCompositeHID(compositeHID);
      saveSettingsEntry.setSettings(settings);
      resetSettingsEntry.setSettings(settings);

      //Keyboard
      SettingsEntryNode* keyboardSettingsEntryNode = new SettingsEntryNode();
      setSettingsEntryNode(keyboardSettingsEntryNode, &debounceSettingsEntry);
      addSettingsEntryNode(keyboardSettingsEntryNode, &debounceTimeSettingsEntry);
      keyboardSettingsIndexScreen.setSettingsEntries(keyboardSettingsEntryNode);

      debounceSettingsEntry.setSettings(settings);
      debounceTimeSettingsEntry.setSettings(settings);

      //Mouse
      SettingsEntryNode* mouseSettingsEntryNode = new SettingsEntryNode();
      setSettingsEntryNode(mouseSettingsEntryNode, &mouseSpeedSettingsEntry);
      addSettingsEntryNode(mouseSettingsEntryNode, &touchpadScrollSettingsEntry);
      addSettingsEntryNode(mouseSettingsEntryNode, &mouseLockScrollSettingsEntry);
      addSettingsEntryNode(mouseSettingsEntryNode, &leftMouseLockScrollSettingsEntry);
      addSettingsEntryNode(mouseSettingsEntryNode, &rightMouseLockScrollSettingsEntry);
      addSettingsEntryNode(mouseSettingsEntryNode, &mouseScrollSpeedSettingsEntry);
      addSettingsEntryNode(mouseSettingsEntryNode, &touchpadRoundedSettingsEntry);
      addSettingsEntryNode(mouseSettingsEntryNode, &touchpadRoundLimitSettingsEntry);
      addSettingsEntryNode(mouseSettingsEntryNode, &touchpadInertiaSettingsEntry);
      addSettingsEntryNode(mouseSettingsEntryNode, &touchpadInertiaRoundedSettingsEntry);
      addSettingsEntryNode(mouseSettingsEntryNode, &touchpadInertiaStressholdSettingsEntry);
      addSettingsEntryNode(mouseSettingsEntryNode, &touchpadInertiaStepSettingsEntry);
      mouseSettingsIndexScreen.setSettingsEntries(mouseSettingsEntryNode);

      mouseSpeedSettingsEntry.setSettings(settings);
      touchpadScrollSettingsEntry.setSettings(settings);
      mouseLockScrollSettingsEntry.setSettings(settings);
      leftMouseLockScrollSettingsEntry.setSettings(settings);
      rightMouseLockScrollSettingsEntry.setSettings(settings);
      mouseScrollSpeedSettingsEntry.setSettings(settings);
      touchpadRoundedSettingsEntry.setSettings(settings);
      touchpadRoundLimitSettingsEntry.setSettings(settings);
      touchpadInertiaSettingsEntry.setSettings(settings);
      touchpadInertiaRoundedSettingsEntry.setSettings(settings);
      touchpadInertiaStressholdSettingsEntry.setSettings(settings);
      touchpadInertiaStepSettingsEntry.setSettings(settings);

      //Screen
      SettingsEntryNode* screenSettingsEntryNode = new SettingsEntryNode();
      setSettingsEntryNode(screenSettingsEntryNode, &displayUpdateDelaySettingsEntry);
      addSettingsEntryNode(screenSettingsEntryNode, &loadingScreenSettingsEntry);
      addSettingsEntryNode(screenSettingsEntryNode, &loadingScreenSpeedSettingsEntry);
      addSettingsEntryNode(screenSettingsEntryNode, &showLoadingDelaySettingsEntry);
      screenSettingsIndexScreen.setSettingsEntries(screenSettingsEntryNode);

      displayUpdateDelaySettingsEntry.setSettings(settings);
      loadingScreenSettingsEntry.setSettings(settings);
      loadingScreenSpeedSettingsEntry.setSettings(settings);
      showLoadingDelaySettingsEntry.setSettings(settings);

      //Battery
      SettingsEntryNode* batterySettingsEntryNode = new SettingsEntryNode();
      setSettingsEntryNode(batterySettingsEntryNode, &inactiveSettingsEntry);
      addSettingsEntryNode(batterySettingsEntryNode, &inactiveTimeSettingsEntry);
      batterySettingsIndexScreen.setSettingsEntries(batterySettingsEntryNode);

      inactiveSettingsEntry.setSettings(settings);
      inactiveTimeSettingsEntry.setSettings(settings);

      //Led
      ledSettingsIndexScreen.setSettingsEntries(mainSettingsEntryNode);

      //Buzzer
      buzzerSettingsIndexScreen.setSettingsEntries(mainSettingsEntryNode);

      //Games
      gamesSettingsIndexScreen.setSettingsEntries(mainSettingsEntryNode);
    }

    void setupScreensNexts() {
      loadingLinesScreen.setNextScreen(&mainScreen);
      loadingShrimpBoardScreen.setNextScreen(&mainScreen);

      mainScreen.setNextScreen(&settingsScreen);

      settingsScreen.setNextScreen(&mainScreen);

      mainSettingsIndexScreen.setNextScreen(&settingsScreen);
      keyboardSettingsIndexScreen.setNextScreen(&settingsScreen);
      mouseSettingsIndexScreen.setNextScreen(&settingsScreen);
      screenSettingsIndexScreen.setNextScreen(&settingsScreen);
      batterySettingsIndexScreen.setNextScreen(&settingsScreen);
      ledSettingsIndexScreen.setNextScreen(&settingsScreen);
      buzzerSettingsIndexScreen.setNextScreen(&settingsScreen);
      gamesSettingsIndexScreen.setNextScreen(&settingsScreen);
    }

    void loop() {
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

    void setSettings(Settings* settings) {
      this->settings = settings;
    }

    void setCompositeHID(BleCompositeHID* compositeHID) {
      this->compositeHID = compositeHID;
    }

    void setButtonMatrix(ButtonMatrix* buttonMatrix) {
      this->buttonMatrix = buttonMatrix;
    }

    void setTouchpad(Touchpad* touchpad) {
      this->touchpad = touchpad;
    }

    void setDisplay(Display* display) {
      this->display = display;
    }

    void setEPROM(EPROM* eprom) {
      this->eprom = eprom;
    }

    void setScreen(Screen* screen) {
      this->screen = screen;
    }

    Settings& getSettings() {
      return *this->settings;
    }

    BleCompositeHID& getCompositeHID() {
      return *this->compositeHID;
    }

    ButtonMatrix& getButtonMatrix() {
      return *this->buttonMatrix;
    }

    Touchpad& getTouchpad() {
      return *this->touchpad;
    }

    Display& getDisplay() {
      return *this->display;
    }

    EPROM& getEPROM() {
      return *this->eprom;
    }

    Screen& getScreen() {
      return *this->screen;
    }

    void setScreenParameters(Screen* screen) {
      screen->setSettings(settings);
      screen->setCompositeHID(compositeHID);
      screen->setButtonMatrix(buttonMatrix);
      screen->setTouchpad(touchpad);
      screen->setDisplay(display);
      screen->setEPROM(eprom);
    }

    void addSettingsIndexNode(SettingsIndexNode* indexNode, Screen* data, const uint8_t BMP[]) {
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

    void setSettingsIndexNode(SettingsIndexNode* indexNode, Screen* data, const uint8_t BMP[]) {
      indexNode->setData(data);
      indexNode->setBitmap(BMP);
    }

    void addSettingsEntryNode(SettingsEntryNode* entryNode, SettingsEntry* data) {
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

    void setSettingsEntryNode(SettingsEntryNode* entryNode, SettingsEntry* data) {
      entryNode->setData(data);
    }

    Screen& getLoadingScreen() {
      int loading = getSettings().getLoadingScreen();
      if (loading == 0) return loadingLinesScreen;
      if (loading == 1) return loadingShrimpBoardScreen;
      return loadingLinesScreen;
    }
};