#pragma once

class SettingsEntry {
  private:
    Settings* settings;

  public:
    virtual String getName() {
      return "Entry";
    }

    String getBoolName(String name, bool value) {
      if (value) {
        name = name + "+";
      } else {
        name = name + "-";
      }
      return name;
    }

    virtual void use() {
      
    }

    virtual void left() {
      use();
    }

    virtual void right() {
      use();
    }

    void setSettings(Settings* settings) {
      this->settings = settings;
    }

    Settings& getSettings() {
      return *this->settings;
    }
};

class SettingsEntryNode {
  private:
    SettingsEntry* data;
    SettingsEntryNode* nextNode;
    bool next = false;

  public:
    void setData(SettingsEntry* data) {
      this->data = data;
    }

    void setNextNode(SettingsEntryNode* nextNode) {
      this->nextNode = nextNode;
      next = true;
    }

    SettingsEntry& getData() {
      return *this->data;
    }

    SettingsEntryNode& getNextNode() {
      return *this->nextNode;
    }

    bool hasNext() {
      return next;
    }
};

class SettingsIndexScreen : public Screen {
  private:
    unsigned long previousMillis = 0;
    bool next = false;

    int selectedIndex = 0;
    int selectedOffset = 0;

    SettingsEntryNode* settingsEntries;

  public:
    virtual void begin() override {
      Screen::begin();
      previousMillis = millis();
      next = false;
      selectedIndex = 0;
      selectedOffset = 0;
      getSettings().setScreenFocus(true);
    }

    virtual void loop() override {
      unsigned long currentMillis = millis();

      SettingsEntryNode* node = settingsEntries;
      int i = 0;
      while (true) {
        if (!node->hasNext()) break;
        node = &(node->getNextNode());
        i++;
      }
      int max = i + 1;

      if (currentMillis - previousMillis >= getSettings().getDisplayUpdateDelay()) {
        getDisplay().clear();
        getDisplay().textReset();
        getDisplay().setTextWrap(false);
        node = settingsEntries;
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
        }
        getDisplay().update();

        previousMillis = currentMillis;
      }

      node = settingsEntries;
      i = 0;
      while (true) {
        if (i == selectedIndex) {
          SettingsEntry* index = &node->getData();
          if (isLeftPress() || isAPress()) index->left();
          if (isRightPress() || isDPress() || isEnterPress() || isSpacePress()) index->right();
        }

        if (!node->hasNext()) break;
        node = &(node->getNextNode());
        i++;
      }

      if (isUpPress() || isWPress()) {
        if (selectedIndex - 1 >= 0) selectedIndex--;
        if (selectedOffset - 1 >= 0 && selectedIndex - selectedOffset < 1) selectedOffset--;
      }

      if (isDownPress() || isSPress()) {
        if (selectedIndex + 1 < max) selectedIndex++;
        if (selectedOffset + 4 < max && selectedIndex - selectedOffset > 2) selectedOffset++;
      }

      if (isEscPress()) next = true;
    }

    virtual bool hasNextScreen() override {
      return next;
    }

    void setSettingsEntries(SettingsEntryNode* settingsEntries) {
      this->settingsEntries = settingsEntries;
    }

    SettingsEntryNode& getSettingsEntries() {
      return *this->settingsEntries;
    }
};

class SettingsIndexNode {
  private:
    Screen* data;
    SettingsIndexNode* nextNode;
    bool next = false;

    const uint8_t* BMP = SETTINGS_BMP;

  public:
    void setData(Screen* data) {
      this->data = data;
    }

    void setNextNode(SettingsIndexNode* nextNode) {
      this->nextNode = nextNode;
      next = true;
    }

    Screen& getData() {
      return *this->data;
    }

    SettingsIndexNode& getNextNode() {
      return *this->nextNode;
    }

    bool hasNext() {
      return next;
    }

    void setBitmap(const uint8_t BMP[]) {
      this->BMP = BMP;
    }

    const uint8_t (*getBitmap()) {
      return BMP;
    }
};

class SettingsScreen : public Screen {
  private:
    unsigned long previousMillis = 0;
    bool next = false;
    bool select = false;

    int selectedIndex = 0;
    int selectedOffset = 0;

    SettingsIndexNode* settingsIndices;

  public:
    virtual void begin() override {
      Screen::begin();
      previousMillis = millis();
      next = false;
      select = false;
      getSettings().setScreenFocus(true);
    }

    virtual void loop() override {
      unsigned long currentMillis = millis();

      SettingsIndexNode* node = settingsIndices;
      int i = 0;
      while (true) {
        if (!node->hasNext()) break;
        node = &(node->getNextNode());
        i++;
      }
      int max = i + 1;

      if (currentMillis - previousMillis >= getSettings().getDisplayUpdateDelay()) {
        getDisplay().clear();
        node = settingsIndices;
        i = 0;
        while (true) {
          int offset = i - selectedOffset;
          if (offset >= -1 && offset <= 6) drawIndex(6 + (offset * 24), (i == selectedIndex) ? 2 : 6, node->getBitmap());

          if (!node->hasNext()) break;
          node = &(node->getNextNode());
          i++;
        }
        getDisplay().update();

        previousMillis = currentMillis;
      }

      if (isLeftPress() || isAPress()) {
        if (selectedIndex - 1 >= 0) selectedIndex--;
        if (selectedOffset - 1 >= 0 && selectedIndex - selectedOffset < 0) selectedOffset--;
      }

      if (isRightPress() || isDPress()) {
        if (selectedIndex + 1 < max) selectedIndex++;
        if (selectedOffset + 5 < max && selectedIndex - selectedOffset > 4) selectedOffset++;
      }

      if (isEnterPress() || isSpacePress()) select = true;

      if (isEscPress()) next = true;
    }

    virtual bool hasNextScreen() override {
      return next || select;
    }

    virtual Screen& getNextScreen() {
      if (select) {
        SettingsIndexNode* node = settingsIndices;
        int i = 0;
        while (true) {
          if (i == selectedIndex) return node->getData();

          if (!node->hasNext()) break;
          node = &(node->getNextNode());
          i++;
        }
      }
      return Screen::getNextScreen();
    }

    void setSettingsIndices(SettingsIndexNode* settingsIndices) {
      this->settingsIndices = settingsIndices;
    }

    SettingsIndexNode& getSettingsIndices() {
      return *this->settingsIndices;
    }

    void drawIndex(int x, int y, const uint8_t BMP[]) {
      getDisplay().drawRoundRectangle(x, y, 20, 20, 3, getDisplay().white());
      getDisplay().drawBitmap(BMP, x + 2, y + 2, 16, 16, getDisplay().white());
    }
};

class ModeSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      String name = "Mode: ";
      if (getSettings().isUSBMode()) {
        name = name + "USB";
      } else {
        name = name + "BLE";
      }
      return name;
    }

    virtual void use() override {
      getSettings().setUSBMode(!getSettings().isUSBMode());
    }
};

class BLEStatusSettingsEntry : public SettingsEntry {
  private:
    BleCompositeHID* compositeHID;

  public:
    virtual String getName() override {
      return getBoolName("BLE: ", isBLEConnected());
    }

    void setCompositeHID(BleCompositeHID* compositeHID) {
      this->compositeHID = compositeHID;
    }

    BleCompositeHID& getCompositeHID() {
      return *this->compositeHID;
    }

    bool isBLEConnected() {
      return getCompositeHID().isConnected();
    }
};

class SaveSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Save settings";
    }

    virtual void use() override {

    }
};

class ResetSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Reset settings";
    }

    virtual void use() override {
      getSettings().reset();
    }
};

class DebounceSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("Debounce: ", getSettings().isDebounce());
    }

    virtual void use() override {
      getSettings().setDebounce(!getSettings().isDebounce());
    }
};

class DebounceTimeSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Debounce time: " + String(getSettings().getDebounceTime()) + " ms";
    }

    virtual void left() override {
      int value = getSettings().getDebounceTime();
      if (value - 1 >= 1) {
        value--;
        getSettings().setDebounceTime(value);
      }
    }

    virtual void right() override {
      int value = getSettings().getDebounceTime();
      if (value + 1 <= 100) {
        value++;
        getSettings().setDebounceTime(value);
      }
    }
};

class MouseSpeedSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Mouse speed: " + String(getSettings().getMouseSpeed());
    }

    virtual void left() override {
      float value = getSettings().getMouseSpeed();
      if (value - 0.1 >= 0.09) {
        value -= 0.1;
        getSettings().setMouseSpeed(value);
      }
    }

    virtual void right() override {
      float value = getSettings().getMouseSpeed();
      if (value + 0.1 <= 3.01) {
        value += 0.1;
        getSettings().setMouseSpeed(value);
      }
    }
};

class TouchpadScrollSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("Touchpad scroll: ", getSettings().isTouchpadScroll());
    }

    virtual void use() override {
      getSettings().setTouchpadScroll(!getSettings().isTouchpadScroll());
    }
};

class MouseLockScrollSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("M lock scroll: ", getSettings().isMouseLockScroll());
    }

    virtual void use() override {
      getSettings().setMouseLockScroll(!getSettings().isMouseLockScroll());
    }
};

class LeftMouseLockScrollSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("L M lock scroll: ", getSettings().isLeftMouseLockScroll());
    }

    virtual void use() override {
      getSettings().setLeftMouseLockScroll(!getSettings().isLeftMouseLockScroll());
    }
};

class RightMouseLockScrollSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("R M lock scroll: ", getSettings().isRightMouseLockScroll());
    }

    virtual void use() override {
      getSettings().setRightMouseLockScroll(!getSettings().isRightMouseLockScroll());
    }
};

class MouseScrollSpeedSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Scroll speed: " + String(getSettings().getMouseScrollSpeed());
    }

    virtual void left() override {
      float value = getSettings().getMouseScrollSpeed();
      if (value - 0.1 >= 0.09) {
        value -= 0.1;
        getSettings().setMouseScrollSpeed(value);
      }
    }

    virtual void right() override {
      float value = getSettings().getMouseScrollSpeed();
      if (value + 0.1 <= 2.01) {
        value += 0.1;
        getSettings().setMouseScrollSpeed(value);
      }
    }
};

class TouchpadRoundedSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("Rounded: ", getSettings().isTouchpadRounded());
    }

    virtual void use() override {
      getSettings().setTouchpadRounded(!getSettings().isTouchpadRounded());
    }
};

class TouchpadRoundLimitSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Round limit: " + String(getSettings().getTouchpadRoundLimit());
    }

    virtual void left() override {
      int value = getSettings().getTouchpadRoundLimit();
      if (value - 1 >= 2) {
        value--;
        getSettings().setTouchpadRoundLimit(value);
      }
    }

    virtual void right() override {
      int value = getSettings().getTouchpadRoundLimit();
      if (value + 1 <= 10) {
        value++;
        getSettings().setTouchpadRoundLimit(value);
      }
    }
};

class TouchpadInertiaSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("Inertia: ", getSettings().isTouchpadInertia());
    }

    virtual void use() override {
      getSettings().setTouchpadInertia(!getSettings().isTouchpadInertia());
    }
};

class TouchpadInertiaRoundedSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("Inertia rounded: ", getSettings().isTouchpadInertiaRounded());
    }

    virtual void use() override {
      getSettings().setTouchpadInertiaRounded(!getSettings().isTouchpadInertiaRounded());
    }
};

class TouchpadInertiaStressholdSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Inertia stresshold: " + String(getSettings().getTouchpadInertiaStresshold());
    }

    virtual void left() override {
      int value = getSettings().getTouchpadInertiaStresshold();
      if (value - 5 >= 5) {
        value -= 5;
        getSettings().setTouchpadInertiaStresshold(value);
      }
    }

    virtual void right() override {
      int value = getSettings().getTouchpadInertiaStresshold();
      if (value + 5 <= 300) {
        value += 5;
        getSettings().setTouchpadInertiaStresshold(value);
      }
    }
};

class TouchpadInertiaStepSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Inertia step: " + String(getSettings().getTouchpadInertiaStep());
    }

    virtual void left() override {
      int value = getSettings().getTouchpadInertiaStep();
      if (value - 1 >= 1) {
        value--;
        getSettings().setTouchpadInertiaStep(value);
      }
    }

    virtual void right() override {
      int value = getSettings().getTouchpadInertiaStep();
      if (value + 1 <= 50) {
        value++;
        getSettings().setTouchpadInertiaStep(value);
      }
    }
};

class DisplayUpdateDelaySettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Update delay: " + String(getSettings().getDisplayUpdateDelay()) + " ms";
    }

    virtual void left() override {
      int value = getSettings().getDisplayUpdateDelay();
      if (value - 5 >= 0) {
        value -=5;
        getSettings().setDisplayUpdateDelay(value);
      }
    }

    virtual void right() override {
      int value = getSettings().getDisplayUpdateDelay();
      if (value + 5 <= 100) {
        value += 5;
        getSettings().setDisplayUpdateDelay(value);
      }
    }
};

class LoadingScreenSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      String name = "Loading: ";
      int loading = getSettings().getLoadingScreen();
      if (loading == 0) name = name + "Lines";
      if (loading == 1) name = name + "Name";
      return name;
    }

    virtual void left() override {
      int value = getSettings().getLoadingScreen();
      if (value - 1 >= 0) {
        value--;
        getSettings().setLoadingScreen(value);
        getSettings().setLoadingScreenType(0);
      }
    }

    virtual void right() override {
      int value = getSettings().getLoadingScreen();
      if (value + 1 <= 1) {
        value++;
        getSettings().setLoadingScreen(value);
        getSettings().setLoadingScreenType(0);
      }
    }
};

class LoadingScreenTypeSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      String name = "Loading type: ";
      int value = getSettings().getLoadingScreenType();
      int loading = getSettings().getLoadingScreen();
      if (loading == 0) {
        if (value == 0) name = name + "Up Right";
        if (value == 1) name = name + "Up Left";
        if (value == 2) name = name + "Down Right";
        if (value == 3) name = name + "Down Left";
      }
      if (loading == 1) {
        if (value == 0) name = name + "Right";
        if (value == 1) name = name + "Left";
      }
      return name;
    }

    virtual void left() override {
      int value = getSettings().getLoadingScreenType();
      int loading = getSettings().getLoadingScreen();
      if (value - 1 >= 0) {
        value--;
        getSettings().setLoadingScreenType(value);
      }
    }

    virtual void right() override {
      int value = getSettings().getLoadingScreenType();
      int loading = getSettings().getLoadingScreen();
      if ((value + 1 <= 3 && loading == 0) ||
          (value + 1 <= 1 && loading == 1)) {
        value++;
        getSettings().setLoadingScreenType(value);
      }
    }
};

class LoadingScreenSpeedSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Loading speed: " + String(getSettings().getLoadingScreenSpeed());
    }

    virtual void left() override {
      int value = getSettings().getLoadingScreenSpeed();
      if (value - 1 >= 1) {
        value--;
        getSettings().setLoadingScreenSpeed(value);
      }
    }

    virtual void right() override {
      int value = getSettings().getLoadingScreenSpeed();
      if (value + 1 <= 10) {
        value++;
        getSettings().setLoadingScreenSpeed(value);
      }
    }
};

class ShowLoadingDelaySettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Show loading";
    }

    virtual void use() override {
      getSettings().setShowLoadingScreen(true);
    }
};

class InactiveSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("Inactive: ", getSettings().isInactive());
    }

    virtual void use() override {
      getSettings().setInactive(!getSettings().isInactive());
    }
};

class InactiveTimeSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Inactive time: " + String(getSettings().getInactiveTime()) + " min";
    }

    virtual void left() override {
      int value = getSettings().getInactiveTime();
      if (value - 1 >= 1) {
        value--;
        getSettings().setInactiveTime(value);
      }
    }

    virtual void right() override {
      int value = getSettings().getInactiveTime();
      if (value + 1 <= 60) {
        value++;
        getSettings().setInactiveTime(value);
      }
    }
};