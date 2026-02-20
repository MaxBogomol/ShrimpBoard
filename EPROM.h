#pragma once

class EPROM {
  private:
    AT24C256* eprom;
    Settings* settings;
    Settings* settingsSaved;

    int index = 0;

  public:
    void setup() {
      this->eprom = new AT24C256(EPROM_ADDRESS);
      this->settings = new Settings();
      this->settingsSaved = new Settings();
    }

    void load() {
      index = 0;
      settings->setDebounce(readBool());
      settings->setDebounceTime(readIntLimit(1, 100, 5));
      settings->setButtonScroll(readBool());
      settings->setButtonScrollDelay(readIntLimit(10, 1000, 500));
      settings->setButtonScrollTime(readIntLimit(10, 1000, 100));

      index = 100;
      settings->setMouseSpeed(readFloatLimit(0.1, 3, 1));
      settings->setTouchpadScroll(readBool());
      settings->setMouseLockScroll(readBool());
      settings->setLeftMouseLockScroll(readBool());
      settings->setRightMouseLockScroll(readBool());
      settings->setMouseScrollSpeed(readFloatLimit(0.1, 2, 1));
      settings->setMouseButtonScrollTime(readIntLimit(1, 100, 10));
      settings->setTouchpadRounded(readBool());
      settings->setTouchpadRoundLimit(readIntLimit(2, 10, 5));
      settings->setTouchpadInertia(readBool());
      settings->setTouchpadInertiaRounded(readBool());
      settings->setTouchpadInertiaStresshold(readIntLimit(5, 300, 50));
      settings->setTouchpadInertiaStep(readIntLimit(1, 50, 5));

      index = 200;
      settings->setDisplayUpdateDelay(readIntLimit(0, 100, 25));
      settings->setLoadingScreen(readIntLimit(0, 1, 0));
      settings->setLoadingScreenType(readIntLimit(0, 3, 0));
      settings->setLoadingScreenSpeed(readIntLimit(1, 10, 2));

      index = 300;
      settings->setInactive(readBool());
      settings->setInactiveTime(readIntLimit(1, 60, 5));

      index = 400;
      settings->setLeds(readBool());
      settings->setLedBrightness(readIntLimit(0, 100, 100));

      index = 500;
      settings->setSound(readBool());
      settings->setPressSound(readBool());
      settings->setPressSoundFrequency(readIntLimit(10, 5000, 1000));
      settings->setPressSoundDuration(readIntLimit(10, 250, 50));

      settingsSaved->copy(settings);
    }

    void save() {
      index = 0;
      writeBoolIf(settings->isDebounce() != settingsSaved->isDebounce(), settings->isDebounce());
      writeIntIf(settings->getDebounceTime() != settingsSaved->getDebounceTime(), settings->getDebounceTime());
      writeBoolIf(settings->isButtonScroll() != settingsSaved->isButtonScroll(), settings->isButtonScroll());
      writeIntIf(settings->getButtonScrollDelay() != settingsSaved->getButtonScrollDelay(), settings->getButtonScrollDelay());
      writeIntIf(settings->getButtonScrollTime() != settingsSaved->getButtonScrollTime(), settings->getButtonScrollTime());

      index = 100;
      writeFloatIf(settings->getMouseSpeed() != settingsSaved->getMouseSpeed(), settings->getMouseSpeed());
      writeBoolIf(settings->isTouchpadScroll() != settingsSaved->isTouchpadScroll(), settings->isTouchpadScroll());
      writeBoolIf(settings->isMouseLockScroll() != settingsSaved->isMouseLockScroll(), settings->isMouseLockScroll());
      writeBoolIf(settings->isLeftMouseLockScroll() != settingsSaved->isLeftMouseLockScroll(), settings->isLeftMouseLockScroll());
      writeBoolIf(settings->isRightMouseLockScroll() != settingsSaved->isRightMouseLockScroll(), settings->isRightMouseLockScroll());
      writeFloatIf(settings->getMouseScrollSpeed() != settingsSaved->getMouseScrollSpeed(), settings->getMouseScrollSpeed());
      writeIntIf(settings->getMouseButtonScrollTime() != settingsSaved->getMouseButtonScrollTime(), settings->getMouseButtonScrollTime());
      writeBoolIf(settings->isTouchpadRounded() != settingsSaved->isTouchpadRounded(), settings->isTouchpadRounded());
      writeIntIf(settings->getTouchpadRoundLimit() != settingsSaved->getTouchpadRoundLimit(), settings->getTouchpadRoundLimit());
      writeBoolIf(settings->isTouchpadInertia() != settingsSaved->isTouchpadInertia(), settings->isTouchpadInertia());
      writeBoolIf(settings->isTouchpadInertiaRounded() != settingsSaved->isTouchpadInertiaRounded(), settings->isTouchpadInertiaRounded());
      writeIntIf(settings->getTouchpadInertiaStresshold() != settingsSaved->getTouchpadInertiaStresshold(), settings->getTouchpadInertiaStresshold());
      writeIntIf(settings->getTouchpadInertiaStep() != settingsSaved->getTouchpadInertiaStep(), settings->getTouchpadInertiaStep());

      index = 200;
      writeIntIf(settings->getDisplayUpdateDelay() != settingsSaved->getDisplayUpdateDelay(), settings->getDisplayUpdateDelay());
      writeIntIf(settings->getLoadingScreen() != settingsSaved->getLoadingScreen(), settings->getLoadingScreen());
      writeIntIf(settings->getLoadingScreenType() != settingsSaved->getLoadingScreenType(), settings->getLoadingScreenType());
      writeIntIf(settings->getLoadingScreenSpeed() != settingsSaved->getLoadingScreenSpeed(), settings->getLoadingScreenSpeed());

      index = 300;
      writeBoolIf(settings->isInactive() != settingsSaved->isInactive(), settings->isInactive());
      writeIntIf(settings->getInactiveTime() != settingsSaved->getInactiveTime(), settings->getInactiveTime());

      index = 400;
      writeBoolIf(settings->isLeds() != settingsSaved->isLeds(), settings->isLeds());
      writeIntIf(settings->getLedBrightness() != settingsSaved->getLedBrightness(), settings->getLedBrightness());

      index = 500;
      writeBoolIf(settings->isSound() != settingsSaved->isSound(), settings->isSound());
      writeBoolIf(settings->isPressSound() != settingsSaved->isPressSound(), settings->isPressSound());
      writeIntIf(settings->getPressSoundFrequency() != settingsSaved->getPressSoundFrequency(), settings->getPressSoundFrequency());
      writeIntIf(settings->getPressSoundDuration() != settingsSaved->getPressSoundDuration(), settings->getPressSoundDuration());

      settingsSaved->copy(settings);
    }

    void reset() {
      for (int i = 0; i < eprom->length(); i++) {
        uint8_t b = eprom->read(i);
        if (b != 0) {
          eprom->update(i, 0);
        }
      }
    }

    AT24C256& getEPROM() {
      return *this->eprom;
    }

    Settings& getSettings() {
      return *this->settings;
    }

    Settings& getSettingsSaved() {
      return *this->settingsSaved;
    }

    bool readBool(int address) {
      bool value;
      eprom->get(address, value);
      return value;
    }

    int readInt(int address) {
      int value;
      eprom->get(address, value);
      return value;
    }

    float readFloat(int address) {
      float value;
      eprom->get(address, value);
      return value;
    }

    bool readBool() {
      bool value = readBool(index);
      index += 1;
      return value;
    }

    int readInt() {
      int value = readInt(index);
      index += 2;
      return value;
    }

    float readFloat() {
      float value = readFloat(index);
      index += 4;
      return value;
    }

    int readIntLimit(int minValue, int maxValue, int standardValue) {
      int value = readInt();
      if (value < minValue || value > maxValue) value = standardValue;
      return value;
    }

    float readFloatLimit(float minValue, float maxValue, float standardValue) {
      float value = readFloat();
      if (value < minValue || value > maxValue) value = standardValue;
      return value;
    }

    void writeBool(int address, bool value) {
      eprom->put(address, value);
    }

    void writeInt(int address, int value) {
      eprom->put(address, value);
    }

    void writeFloat(int address, float value) {
      eprom->put(address, value);
    }

    void writeBool(bool value) {
      writeBool(index, value);
      index += 1;
    }

    void writeInt(int value) {
      writeInt(index, value);
      index += 2;
    }

    void writeFloat(float value) {
      writeFloat(index, value);
      index += 4;
    }

    void writeBoolIf(bool write, bool value) {
      if (write) writeBool(index, value);
      index += 1;
    }

    void writeIntIf(bool write, int value) {
      if (write) writeInt(index, value);
      index += 2;
    }

    void writeFloatIf(bool write, float value) {
      if (write) writeFloat(index, value);
      index += 4;
    }
};