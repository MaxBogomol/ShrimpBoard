#pragma once

class ButtonMatrix {
  private:
    

  public:
    void setup() {
        clearBytes();
    }

    void clearBytes() {
      digitalWrite(BUTTON_COLUMN_PIN_SS, LOW);
      shiftOut(BUTTON_COLUMN_PIN_MOSI, BUTTON_COLUMN_PIN_SCK, MSBFIRST, 0);
      shiftOut(BUTTON_COLUMN_PIN_MOSI, BUTTON_COLUMN_PIN_SCK, MSBFIRST, 0);
      digitalWrite(BUTTON_COLUMN_PIN_SS, HIGH);
    }

    void read() {

    }
};