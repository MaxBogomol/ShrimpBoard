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

      SettingsIndexNode* settingsIndexNode = new SettingsIndexNode();
      settingsIndexNode->setData(&mainSettingsIndexScreen);
      settingsIndexNode->setBitmap(SETTINGS_BMP);

      SettingsIndexNode* settingsIndexNode1 = new SettingsIndexNode();
      settingsIndexNode1->setData(&keyboardSettingsIndexScreen);
      settingsIndexNode1->setBitmap(KEYBOARD_BMP);
      settingsIndexNode->setNextNode(settingsIndexNode1);

      SettingsIndexNode* settingsIndexNode2 = new SettingsIndexNode();
      settingsIndexNode2->setData(&mouseSettingsIndexScreen);
      settingsIndexNode2->setBitmap(MOUSE_BMP);
      settingsIndexNode1->setNextNode(settingsIndexNode2);

      SettingsIndexNode* settingsIndexNode3 = new SettingsIndexNode();
      settingsIndexNode3->setData(&screenSettingsIndexScreen);
      settingsIndexNode3->setBitmap(SCREEN_BMP);
      settingsIndexNode2->setNextNode(settingsIndexNode3);

      settingsScreen.setSettingsIndices(settingsIndexNode);

      SettingsEntryNode* settingsEntryNodeMain = new SettingsEntryNode();
      settingsEntryNodeMain->setData(&modeSettingsEntry);

      SettingsEntryNode* settingsEntryNodeMain1 = new SettingsEntryNode();
      settingsEntryNodeMain1->setData(&saveSettingsEntry);
      settingsEntryNodeMain->setNextNode(settingsEntryNodeMain1);

      SettingsEntryNode* settingsEntryNodeMain2 = new SettingsEntryNode();
      settingsEntryNodeMain2->setData(&resetSettingsEntry);
      settingsEntryNodeMain1->setNextNode(settingsEntryNodeMain2);

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
};