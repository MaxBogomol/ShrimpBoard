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

    SettingsEntryNode* settingsEntries;
    SettingsEntry* index;
    SettingsEntryNode* node;

  public:
    virtual void begin() override {
      Screen::begin();
      previousMillis = millis();
      next = false;
      getSettings().setScreenFocus(true);
    }

    virtual void loop() override {
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis > 25) {
        getDisplay().clear();
        getDisplay().textReset();
        node = settingsEntries;
        int i = 0;
        while (true) {
          index = &node->getData();

          String s = index->getName();
          if (i == selectedIndex) s = ">" + s;
          getDisplay().setTextPos(0, i * 8);
          getDisplay().drawText(s);

          if (!node->hasNext()) break;
          node = &(node->getNextNode());
          i++;
        }
        getDisplay().update();

        previousMillis = millis();
      }

      node = settingsEntries;
      int i = 0;
      while (true) {
        if (i == selectedIndex) {
          index = &node->getData();
          if (isLeftPress()) index->left();
          if (isRightPress() || isEnterPress()) index->right();
        }

        if (!node->hasNext()) break;
        node = &(node->getNextNode());
        i++;
      }
      int max = i + 1;

      if (isUpPress()) {
        selectedIndex--;
        if (selectedIndex < 0) selectedIndex = 0;
      }

      if (isDownPress()) {
        selectedIndex++;
        if (selectedIndex > max - 1) selectedIndex = max - 1;
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

    SettingsIndexNode* settingsIndices;
    Screen* index;
    SettingsIndexNode* node;

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

      if (currentMillis - previousMillis > 25) {
        getDisplay().clear();
        node = settingsIndices;
        int i = 0;
        while (true) {
          drawIndex(6 + (i * 24), (i == selectedIndex) ? 2 : 6, node->getBitmap());

          if (!node->hasNext()) break;
          node = &(node->getNextNode());
          i++;
        }
        getDisplay().update();

        previousMillis = millis();
      }
      
      node = settingsIndices;
      int i = 0;
      while (true) {
        if (!node->hasNext()) break;
        node = &(node->getNextNode());
        i++;
      }
      int max = i + 1;

      if (isLeftPress()) {
        selectedIndex--;
        if (selectedIndex < 0) selectedIndex = 0;
      }

      if (isRightPress()) {
        selectedIndex++;
        if (selectedIndex > max - 1) selectedIndex = max - 1;
      }

      if (isEnterPress()) select = true;

      if (isEscPress()) next = true;
    }

    virtual bool hasNextScreen() override {
      return next || select;
    }

    virtual Screen& getNextScreen() {
      if (select) {
        node = settingsIndices;
        int i = 0;
        while (true) {
          if (i == selectedIndex) return node->getData();

          if (!node->hasNext()) break;
          node = &(settingsIndices->getNextNode());
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

    virtual void left() override {
      getSettings().setUSBMode(!getSettings().isUSBMode());
    }
};

class ResetSettingsEntry : public SettingsEntry {
  public:
    virtual String getName() override {
      return "Reset settings";
    }

    virtual void use() override {
      getSettings().setUSBMode(!getSettings().isUSBMode());
    }
};