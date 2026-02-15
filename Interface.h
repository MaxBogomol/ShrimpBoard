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
    SettingsIndexScreen gamesSettingsIndexScreen;

    ModeSettingsEntry modeSettingsEntry;
    SaveSettingsEntry saveSettingsEntry;
    ResetSettingsEntry resetSettingsEntry;

  public:
    void setupScreens() {
      setupScreensParameters();
      setupScreensNexts();

      setScreen(&loadingLinesScreen);
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
      setScreenParameters(&gamesSettingsIndexScreen);

      SettingsIndexNode* settingsIndexNode = new SettingsIndexNode();
      setSettingsIndexNode(settingsIndexNode, &mainSettingsIndexScreen, SETTINGS_BMP);
      addSettingsIndexNode(settingsIndexNode, &keyboardSettingsIndexScreen, KEYBOARD_BMP);
      addSettingsIndexNode(settingsIndexNode, &mouseSettingsIndexScreen, MOUSE_BMP);
      addSettingsIndexNode(settingsIndexNode, &screenSettingsIndexScreen, SCREEN_BMP);
      addSettingsIndexNode(settingsIndexNode, &batterySettingsIndexScreen, BATTERY_8_BMP);
      addSettingsIndexNode(settingsIndexNode, &gamesSettingsIndexScreen, GAMEPAD_BMP);
      settingsScreen.setSettingsIndices(settingsIndexNode);

      SettingsEntryNode* settingsEntryNodeMain = new SettingsEntryNode();
      setSettingsEntryNode(settingsEntryNodeMain, &modeSettingsEntry);
      addSettingsEntryNode(settingsEntryNodeMain, &saveSettingsEntry);
      addSettingsEntryNode(settingsEntryNodeMain, &resetSettingsEntry);
      mainSettingsIndexScreen.setSettingsEntries(settingsEntryNodeMain);

      modeSettingsEntry.setSettings(settings);
      saveSettingsEntry.setSettings(settings);
      resetSettingsEntry.setSettings(settings);
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
      gamesSettingsIndexScreen.setNextScreen(&settingsScreen);
    }

    void loop() {
      getScreen().loop();

      if (getScreen().hasNextScreen()) {
        getScreen().end();
        setScreen(&(getScreen().getNextScreen()));
        getScreen().begin();
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
};