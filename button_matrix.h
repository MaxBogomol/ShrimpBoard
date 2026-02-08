#include "esp32-hal.h"
#pragma once

class ButtonMatrix {
  private:
    bool matrix[6][17] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

  public:
    void setup() {
      digitalWrite(BUTTON_COLUMN_PIN_OE, HIGH);
    }

    void read() {
      for (int i = 0; i < 16; i++) {
        uint16_t data = 0b1000000000000000;
        data = data >> i;

        digitalWrite(BUTTON_COLUMN_PIN_SS, LOW);
        shiftOut(BUTTON_COLUMN_PIN_MOSI, BUTTON_COLUMN_PIN_SCK, MSBFIRST, lowByte(data));
        shiftOut(BUTTON_COLUMN_PIN_MOSI, BUTTON_COLUMN_PIN_SCK, MSBFIRST, highByte(data));
        digitalWrite(BUTTON_COLUMN_PIN_SS, HIGH);

        readColumn(i);
      }

      //clearBytes();
      digitalWrite(BUTTON_COLUMN_PIN_OE, HIGH);
      digitalWrite(BUTTON_COLUMN_PIN_17, HIGH);
      readColumn(16);
      digitalWrite(BUTTON_COLUMN_PIN_17, LOW);
      digitalWrite(BUTTON_COLUMN_PIN_OE, LOW);
      
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 17; j++) {
          Serial.print(matrix[i][j]);
        }
        Serial.println();
      }
      Serial.println();
      delay(100);
    }

    void readColumn(int row) {
      matrix[0][row] = digitalRead(BUTTON_ROW_PIN_1);
      matrix[1][row] = digitalRead(BUTTON_ROW_PIN_2);
      matrix[2][row] = digitalRead(BUTTON_ROW_PIN_3);
      matrix[3][row] = digitalRead(BUTTON_ROW_PIN_4);
      matrix[4][row] = digitalRead(BUTTON_ROW_PIN_5);
      matrix[5][row] = digitalRead(BUTTON_ROW_PIN_6);
    }
};