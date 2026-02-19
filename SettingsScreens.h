#pragma once

class SettingsEntry {
  private:
    Settings* settings;

    Buzzer* buzzer;

    Screen* nextScreen;

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

    void playTone() {
      getBuzzer().playTone(1000, 25);
    }

    void setSettings(Settings* settings) {
      this->settings = settings;
    }

    void setBuzzer(Buzzer* buzzer) {
      this->buzzer = buzzer;
    }

    Settings& getSettings() {
      return *this->settings;
    }

    Buzzer& getBuzzer() {
      return *this->buzzer;
    }

    virtual bool hasNextScreen() {
      return false;
    }

    virtual void setNextScreen(Screen* nextScreen) {
      this->nextScreen = nextScreen;
    }

    virtual Screen& getNextScreen() {
      return *this->nextScreen;
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
    bool select = false;

    int selectedIndex = 0;
    int selectedOffset = 0;

    bool leftPress = false;
    bool rightPress = false;
    bool upPress = false;
    bool downPress = false;
    unsigned long leftPressMillis = 0;
    unsigned long rightPressMillis = 0;
    unsigned long upPressMillis = 0;
    unsigned long downPressMillis = 0;

    SettingsEntryNode* settingsEntries;

  public:
    virtual void begin() override {
      Screen::begin();
      previousMillis = millis();
      next = false;
      select = false;
      selectedIndex = 0;
      selectedOffset = 0;
      getSettings().setScreenFocus(true);
    }

    virtual void loop() override {
      unsigned long currentMillis = millis();
      bool scroll = getSettings().isButtonScroll();
      int scrollDelay = getSettings().getButtonScrollDelay();
      int scrollTime = getSettings().getButtonScrollTime();

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

      bool left = false;
      bool right = false;
      if (isLeftPress() || isAPress()) {
        left = true;
        leftPressMillis = millis();
        leftPress = false;
      }
      if (scroll && (isLeftPressed() || isAPressed())) {
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
      if (isRightPress() || isDPress() || isEnterPress() || isSpacePress()) {
        right = true;
        rightPressMillis = millis();
        rightPress = false;
      }
      if (scroll && (isRightPressed() || isDPressed())) {
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
      }

      bool up = false;
      bool down = false;
      bool sound = false;
      if (isUpPress() || isWPress()) {
        up = true;
        upPressMillis = millis();
        upPress = false;
      }
      if (scroll && (isUpPressed() || isWPressed())) {
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
      if (isDownPress() || isSPress()) {
        down = true;
        downPressMillis = millis();
        downPress = false;
      }
      if (scroll && (isDownPressed() || isSPressed())) {
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
        getBuzzer().playTone(1000, 25);
      }

      if (isEscPress()) {
        next = true;
        if (getSettings().isPressSound()) {
          getBuzzer().playTone(2000, 50);
        }
      }
    }

    virtual bool hasNextScreen() override {
      return next || select;
    }

    virtual Screen& getNextScreen() override {
      if (select) {
        SettingsEntryNode* node = settingsEntries;
        int i = 0;
        while (true) {
          if (i == selectedIndex) {
            SettingsEntry* entry = &node->getData();
            if (entry->hasNextScreen()) return entry->getNextScreen();
          }

          if (!node->hasNext()) break;
          node = &(node->getNextNode());
          i++;
        }
      }
      return Screen::getNextScreen();
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

    bool leftPress = false;
    bool rightPress = false;
    unsigned long leftPressMillis = 0;
    unsigned long rightPressMillis = 0;

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
      bool scroll = getSettings().isButtonScroll();
      int scrollDelay = getSettings().getButtonScrollDelay();
      int scrollTime = getSettings().getButtonScrollTime();

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

      bool left = false;
      bool right = false;
      bool sound = false;
      if (isLeftPress() || isAPress()) {
        left = true;
        leftPressMillis = millis();
        leftPress = false;
      }
      if (scroll && (isLeftPressed() || isAPressed())) {
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
      if (isRightPress() || isDPress()) {
        right = true;
        rightPressMillis = millis();
        rightPress = false;
      }
      if (scroll && (isRightPressed() || isDPressed())) {
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

      if (left) {
        if (selectedIndex - 1 >= 0) {
          selectedIndex--;
          sound = true;
        }
        if (selectedOffset - 1 >= 0 && selectedIndex - selectedOffset < 0) selectedOffset--;
      }
      if (right) {
        if (selectedIndex + 1 < max) {
          selectedIndex++;
          sound = true;
        }
        if (selectedOffset + 5 < max && selectedIndex - selectedOffset > 4) selectedOffset++;
      }

      if (isEnterPress() || isSpacePress()) {
        select = true;
        sound = true;
      }

      if (isEscPress()) {
        next = true;
        sound = true;
      }

      if (sound && getSettings().isPressSound()) {
        getBuzzer().playTone(2000, 50);
      }
    }

    virtual bool hasNextScreen() override {
      return next || select;
    }

    virtual Screen& getNextScreen() override {
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
      if (getSettings().isPressSound()) playTone();
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
  private:
    EPROM* eprom;
    
  public:
    virtual String getName() override {
      return "Save settings";
    }

    virtual void use() override {
      if (getSettings().isPressSound()) playTone();
      getEPROM().save();
    }

    void setEPROM(EPROM* eprom) {
      this->eprom = eprom;
    }

    EPROM& getEPROM() {
      return *this->eprom;
    }
};

class ResetSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Reset settings";
    }

    virtual void use() override {
      if (getSettings().isPressSound()) playTone();
      getSettings().reset();
    }
};

class ResetEPROMSettingsEntry : public SettingsEntry {
  private:
    EPROM* eprom;
    
  public:
    virtual String getName() override {
      return "Reset EPROM";
    }

    virtual void use() override {
      if (getSettings().isPressSound()) playTone();
      getEPROM().reset();
    }

    void setEPROM(EPROM* eprom) {
      this->eprom = eprom;
    }

    EPROM& getEPROM() {
      return *this->eprom;
    }
};


class DebounceSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("Debounce: ", getSettings().isDebounce());
    }

    virtual void use() override {
      getSettings().setDebounce(!getSettings().isDebounce());
      if (getSettings().isPressSound()) playTone();
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
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      int value = getSettings().getDebounceTime();
      if (value + 1 <= 100) {
        value++;
        getSettings().setDebounceTime(value);
        if (getSettings().isPressSound()) playTone();
      }
    }
};

class ButtonScrollSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("Scroll: ", getSettings().isButtonScroll());
    }

    virtual void use() override {
      getSettings().setButtonScroll(!getSettings().isButtonScroll());
      if (getSettings().isPressSound()) playTone();
    }
};

class ButtonScrollDelaySettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Scroll delay: " + String(getSettings().getButtonScrollDelay()) + " ms";
    }

    virtual void left() override {
      int value = getSettings().getButtonScrollDelay();
      if (value - 10 >= 100) {
        value -=10;
        getSettings().setButtonScrollDelay(value);
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      int value = getSettings().getButtonScrollDelay();
      if (value + 10 <= 1000) {
        value += 10;
        getSettings().setButtonScrollDelay(value);
        if (getSettings().isPressSound()) playTone();
      }
    }
};

class ButtonScrollTimeSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Scroll time: " + String(getSettings().getButtonScrollTime()) + " ms";
    }

    virtual void left() override {
      int value = getSettings().getButtonScrollTime();
      if (value - 10 >= 10) {
        value -= 10;
        getSettings().setButtonScrollTime(value);
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      int value = getSettings().getButtonScrollTime();
      if (value + 10 <= 1000) {
        value += 10;
        getSettings().setButtonScrollTime(value);
        if (getSettings().isPressSound()) playTone();
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
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      float value = getSettings().getMouseSpeed();
      if (value + 0.1 <= 3.01) {
        value += 0.1;
        getSettings().setMouseSpeed(value);
        if (getSettings().isPressSound()) playTone();
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
      if (getSettings().isPressSound()) playTone();
    }
};

class MouseLockScrollSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("M lock scroll: ", getSettings().isMouseLockScroll());
    }

    virtual void use() override {
      getSettings().setMouseLockScroll(!getSettings().isMouseLockScroll());
      if (getSettings().isPressSound()) playTone();
    }
};

class LeftMouseLockScrollSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("L M lock scroll: ", getSettings().isLeftMouseLockScroll());
    }

    virtual void use() override {
      getSettings().setLeftMouseLockScroll(!getSettings().isLeftMouseLockScroll());
      if (getSettings().isPressSound()) playTone();
    }
};

class RightMouseLockScrollSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("R M lock scroll: ", getSettings().isRightMouseLockScroll());
    }

    virtual void use() override {
      getSettings().setRightMouseLockScroll(!getSettings().isRightMouseLockScroll());
      if (getSettings().isPressSound()) playTone();
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
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      float value = getSettings().getMouseScrollSpeed();
      if (value + 0.1 <= 2.01) {
        value += 0.1;
        getSettings().setMouseScrollSpeed(value);
        if (getSettings().isPressSound()) playTone();
      }
    }
};

class MouseButtonScrollTimeSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Button scroll time: " + String(getSettings().getMouseButtonScrollTime()) + " ms";
    }

    virtual void left() override {
      int value = getSettings().getMouseButtonScrollTime();
      if (value - 1 >= 1) {
        value--;
        getSettings().setMouseButtonScrollTime(value);
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      int value = getSettings().getMouseButtonScrollTime();
      if (value + 1 <= 100) {
        value++;
        getSettings().setMouseButtonScrollTime(value);
        if (getSettings().isPressSound()) playTone();
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
      if (getSettings().isPressSound()) playTone();
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
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      int value = getSettings().getTouchpadRoundLimit();
      if (value + 1 <= 10) {
        value++;
        getSettings().setTouchpadRoundLimit(value);
        if (getSettings().isPressSound()) playTone();
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
      if (getSettings().isPressSound()) playTone();
    }
};

class TouchpadInertiaRoundedSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("Inertia rounded: ", getSettings().isTouchpadInertiaRounded());
    }

    virtual void use() override {
      getSettings().setTouchpadInertiaRounded(!getSettings().isTouchpadInertiaRounded());
      if (getSettings().isPressSound()) playTone();
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
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      int value = getSettings().getTouchpadInertiaStresshold();
      if (value + 5 <= 300) {
        value += 5;
        getSettings().setTouchpadInertiaStresshold(value);
        if (getSettings().isPressSound()) playTone();
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
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      int value = getSettings().getTouchpadInertiaStep();
      if (value + 1 <= 50) {
        value++;
        getSettings().setTouchpadInertiaStep(value);
        if (getSettings().isPressSound()) playTone();
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
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      int value = getSettings().getDisplayUpdateDelay();
      if (value + 5 <= 100) {
        value += 5;
        getSettings().setDisplayUpdateDelay(value);
        if (getSettings().isPressSound()) playTone();
      }
    }
};

class LoadingScreenSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      String name = "Loading: ";
      int loading = getSettings().getLoadingScreen();
      switch(loading) {
        case 0: name = name + "Lines"; break;
        case 1: name = name + "Name"; break;
      }
      return name;
    }

    virtual void left() override {
      int value = getSettings().getLoadingScreen();
      if (value - 1 >= 0) {
        value--;
        getSettings().setLoadingScreen(value);
        getSettings().setLoadingScreenType(0);
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      int value = getSettings().getLoadingScreen();
      if (value + 1 <= 1) {
        value++;
        getSettings().setLoadingScreen(value);
        getSettings().setLoadingScreenType(0);
        if (getSettings().isPressSound()) playTone();
      }
    }
};

class LoadingScreenTypeSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      String name = "Loading type: ";
      int value = getSettings().getLoadingScreenType();
      int loading = getSettings().getLoadingScreen();
      switch (loading) {
        case 0:
          switch (value) {
            case 0: name = name + "Up Right"; break;
            case 1: name = name + "Up Left"; break;
            case 2: name = name + "Down Right"; break;
            case 3: name = name + "Down Left"; break;
          }
          break;
        case 1:
          switch (value) {
            case 0: name = name + "Right"; break;
            case 1: name = name + "Left"; break;
          }
          break;
      }
      return name;
    }

    virtual void left() override {
      int value = getSettings().getLoadingScreenType();
      int loading = getSettings().getLoadingScreen();
      if (value - 1 >= 0) {
        value--;
        getSettings().setLoadingScreenType(value);
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      int value = getSettings().getLoadingScreenType();
      int loading = getSettings().getLoadingScreen();
      if ((value + 1 <= 3 && loading == 0) ||
          (value + 1 <= 1 && loading == 1)) {
        value++;
        getSettings().setLoadingScreenType(value);
        if (getSettings().isPressSound()) playTone();
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
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      int value = getSettings().getLoadingScreenSpeed();
      if (value + 1 <= 10) {
        value++;
        getSettings().setLoadingScreenSpeed(value);
        if (getSettings().isPressSound()) playTone();
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
      if (getSettings().isPressSound()) playTone();
    }
};

class InactiveSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("Inactive: ", getSettings().isInactive());
    }

    virtual void use() override {
      getSettings().setInactive(!getSettings().isInactive());
      if (getSettings().isPressSound()) playTone();
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
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      int value = getSettings().getInactiveTime();
      if (value + 1 <= 60) {
        value++;
        getSettings().setInactiveTime(value);
        if (getSettings().isPressSound()) playTone();
      }
    }
};

class LedsSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("LEDs: ", getSettings().isLeds());
    }

    virtual void use() override {
      getSettings().setLeds(!getSettings().isLeds());
      if (getSettings().isPressSound()) playTone();
    }
};

class LedsBrightnessSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Brightness: " + String(getSettings().getLedBrightness()) + "%";
    }

    virtual void left() override {
      int value = getSettings().getLedBrightness();
      if (value - 5 >= 0) {
        value -= 5;
        getSettings().setLedBrightness(value);
        if (getSettings().isPressSound()) playTone();
      }
    }

    virtual void right() override {
      int value = getSettings().getLedBrightness();
      if (value + 5 <= 100) {
        value += 5;
        getSettings().setLedBrightness(value);
        if (getSettings().isPressSound()) playTone();
      }
    }
};

class SoundSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("Sound: ", getSettings().isSound());
    }

    virtual void use() override {
      getSettings().setSound(!getSettings().isSound());
      if (getSettings().isPressSound()) playTone();
    }
};

class PressSoundSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return getBoolName("Press sound: ", getSettings().isPressSound());
    }

    virtual void use() override {
      getSettings().setPressSound(!getSettings().isPressSound());
      if (getSettings().isPressSound()) playTone();
    }
};