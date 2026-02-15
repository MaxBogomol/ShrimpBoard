#pragma once

class SettingsEntry {
  private:
    Settings* settings;

  public:
    virtual String getName() {
      return "Entry";
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

      if (currentMillis - previousMillis > 25) {
        getDisplay().clear();
        getDisplay().textReset();
        node = settingsEntries;
        i = 0;
        while (true) {
          SettingsEntry* index = &node->getData();

          int offset = i - selectedOffset;
          String s = index->getName();
          if (i == selectedIndex) s = ">" + s;
          if (offset >= 0 && offset <= 3) {
            getDisplay().setTextPos(0, offset * 8);
            getDisplay().drawText(s);
          }

          if (!node->hasNext()) break;
          node = &(node->getNextNode());
          i++;
        }
        getDisplay().update();

        previousMillis = millis();
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

      if (currentMillis - previousMillis > 25) {
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

        previousMillis = millis();
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

class TouchpadScrollSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      String name = "Scroll: ";
      if (getSettings().isTouchpadScroll()) {
        name = name + "+";
      } else {
        name = name + "-";
      }
      return name;
    }

    virtual void use() override {
      getSettings().setTouchpadScroll(!getSettings().isTouchpadScroll());
    }
};

class TouchpadRoundedSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      String name = "Rounded: ";
      if (getSettings().isTouchpadRounded()) {
        name = name + "+";
      } else {
        name = name + "-";
      }
      return name;
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