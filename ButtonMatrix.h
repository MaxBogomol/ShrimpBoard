#pragma once

class ButtonMatrix {
  private:
    Settings* settings;

    bool matrix[6][17] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    bool matrixOld[6][17] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    int matrixNormalized[6][17] = {
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
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 17; j++) {
          matrixOld[i][j] = matrix[i][j];
        }
      }

      for (int i = 0; i < 16; i++) {
        uint16_t data = 0b1000000000000000;
        data = data >> i;

        digitalWrite(BUTTON_COLUMN_PIN_SS, LOW);
        shiftOut(BUTTON_COLUMN_PIN_MOSI, BUTTON_COLUMN_PIN_SCK, MSBFIRST, lowByte(data));
        shiftOut(BUTTON_COLUMN_PIN_MOSI, BUTTON_COLUMN_PIN_SCK, MSBFIRST, highByte(data));
        digitalWrite(BUTTON_COLUMN_PIN_SS, HIGH);

        readColumn(i);
      }

      digitalWrite(BUTTON_COLUMN_PIN_OE, HIGH);
      digitalWrite(BUTTON_COLUMN_PIN_17, HIGH);
      readColumn(16);
      digitalWrite(BUTTON_COLUMN_PIN_17, LOW);
      digitalWrite(BUTTON_COLUMN_PIN_OE, LOW);

      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 17; j++) {
          bool button = matrix[i][j];
          bool buttonOld = matrixOld[i][j];
          matrixNormalized[i][j] = normalizeValue(button, buttonOld);
        }
      }
    }

    void readColumn(int row) {
      matrix[0][row] = digitalRead(BUTTON_ROW_PIN_1);
      matrix[1][row] = digitalRead(BUTTON_ROW_PIN_2);
      matrix[2][row] = digitalRead(BUTTON_ROW_PIN_3);
      matrix[3][row] = digitalRead(BUTTON_ROW_PIN_4);
      matrix[4][row] = digitalRead(BUTTON_ROW_PIN_5);
      matrix[5][row] = digitalRead(BUTTON_ROW_PIN_6);
    }

    void setSettings(Settings* settings) {
      this->settings = settings;
    }

    Settings& getSettings() {
      return *this->settings;
    }

    bool (*getMatrix())[17] {
      return matrix;
    }

    bool (*getMatrixOld())[17] {
      return matrix;
    }

    int (*getMatrixNormalized())[17] {
      return matrixNormalized;
    }

    int normalizeValue(bool button, bool buttonOld) {
      int value = 0;
      if (button && !buttonOld) value = 1;
      if (button && buttonOld) value = 2;
      if (!button && buttonOld) value = 3;
      return value;
    }

    int getValue(int row, int collumn) {
      return matrixNormalized[row][collumn];
    }

    bool isPress(int row, int collumn) {
      return getValue(row, collumn) == 1;
    }

    bool isPressed(int row, int collumn) {
      return getValue(row, collumn) == 2;
    }

    bool isRelease(int row, int collumn) {
      return getValue(row, collumn) == 3;
    }
};