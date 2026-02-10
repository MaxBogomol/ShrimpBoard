#pragma once

class EPROM {
  private:
    AT24C256* eprom;
    Settings* setting;

  public:
    void setup() {
        this->eprom = new AT24C256(EPROM_ADDRESS);
    }

    AT24C256& getEPROM() {
      return *this->eprom;
    }
};