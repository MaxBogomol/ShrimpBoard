#include "ButtonMatrix.h"

#include <Arduino.h>

void ButtonMatrix::setup() {
    digitalWrite(BUTTON_COLUMN_PIN_OE, HIGH);
}

void ButtonMatrix::read() {
    unsigned long currentMillis = millis();
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
            int value = 0;
            if (button && !buttonOld) value = 1;
            if (button && buttonOld) value = 2;
            if (!button && buttonOld) value = 3;
            matrixNormalized[i][j] = value;

            if (button != buttonOld) matrixDebounce[i][j] = currentMillis;
        }
    }
}

void ButtonMatrix::readColumn(int row) {
    unsigned long currentMillis = millis();
    bool debounce = settings->isDebounce();
    bool debounceTime = settings->getDebounceTime();
    if (currentMillis - matrixDebounce[0][row] >= debounceTime || !debounce) matrix[0][row] = digitalRead(BUTTON_ROW_PIN_1);
    if (currentMillis - matrixDebounce[1][row] >= debounceTime || !debounce) matrix[1][row] = digitalRead(BUTTON_ROW_PIN_2);
    if (currentMillis - matrixDebounce[2][row] >= debounceTime || !debounce) matrix[2][row] = digitalRead(BUTTON_ROW_PIN_3);
    if (currentMillis - matrixDebounce[3][row] >= debounceTime || !debounce) matrix[3][row] = digitalRead(BUTTON_ROW_PIN_4);
    if (currentMillis - matrixDebounce[4][row] >= debounceTime || !debounce) matrix[4][row] = digitalRead(BUTTON_ROW_PIN_5);
    if (currentMillis - matrixDebounce[5][row] >= debounceTime || !debounce) matrix[5][row] = digitalRead(BUTTON_ROW_PIN_6);
}

void ButtonMatrix::setSettings(Settings* settings) {
    this->settings = settings;
}

Settings& ButtonMatrix::getSettings() {
    return *this->settings;
}

bool(*ButtonMatrix::getMatrix())[17] {
    return matrix;
}

bool (*ButtonMatrix::getMatrixOld())[17] {
    return matrix;
}

int (*ButtonMatrix::getMatrixNormalized())[17] {
    return matrixNormalized;
}

int ButtonMatrix::getValue(int row, int collumn) {
    return matrixNormalized[row][collumn];
}

bool ButtonMatrix::isPress(int row, int collumn) {
    return getValue(row, collumn) == 1;
}

bool ButtonMatrix::isPressed(int row, int collumn) {
    return getValue(row, collumn) == 2;
}

bool ButtonMatrix::isRelease(int row, int collumn) {
    return getValue(row, collumn) == 3;
}