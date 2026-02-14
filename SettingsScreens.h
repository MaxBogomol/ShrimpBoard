#pragma once

class SettingsIndexScreen : public Screen {
  private:
    unsigned long previousMillis = 0;
    bool next = false;

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
        getDisplay().update();

        previousMillis = millis();
      }

      if (isEscPress()) next = true;
    }

    virtual bool hasNextScreen() override {
      return next;
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