#include <BleCompositeHID.h>
#include <KeyboardDevice.h>
#include <MouseDevice.h>
#include <USBHIDKeyboard.h>
#include <USBHIDMouse.h>
#include "USBHIDConsumerControl.h"
#include "USB.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <at24c256.h>

/*
ESP32-S3
16MB (128Mb)
16M Flash (3MB APP)
OPI PSRAM

Touchpad cable
1 - GND
2 - VDD
4 - SDA
5 - SCL
*/

//Button matrix
#define BUTTON_COLUMN_PIN_SS 10
#define BUTTON_COLUMN_PIN_MOSI 11
#define BUTTON_COLUMN_PIN_SCK 12
#define BUTTON_COLUMN_PIN_OE 13
#define BUTTON_COLUMN_PIN_17 14

#define BUTTON_ROW_PIN_1 16
#define BUTTON_ROW_PIN_2 15
#define BUTTON_ROW_PIN_3 7
#define BUTTON_ROW_PIN_4 6
#define BUTTON_ROW_PIN_5 5
#define BUTTON_ROW_PIN_6 4

//Touchpad
#define TOUCHPAD_ADDRESS 0x64

//Screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

//EPROM
#define EPROM_ADDRESS 0x50

//BLE
#define BLE_DEVICE_NAME "Shrimpboard"
#define BLE_DEVICE_MANUFACTURER "Pink Joke"

//Setings
#define DEBUG true

#include <PS4Touchpad.h>
#include <Settings.h>
#include <ButtonMatrix.h>
#include <Touchpad.h>
#include <Display.h>
#include <EPROM.h>
#include <ScanCodes.h>
#include <ScanMatrix.h>

KeyboardDevice* keyboardBLE;
MouseDevice* mouseBLE;
BleCompositeHID* compositeHID;
USBHIDKeyboard keyboardUSB;
USBHIDMouse mouseUSB;
USBHIDConsumerControl consumerControl;
Settings* settings;
ButtonMatrix buttonMatrix;
Touchpad touchpad;
Display display;
EPROM eprom;

void setup() {
  Serial.begin(115200);
  USB.begin();
  Wire.begin();

  setupPins();
  setupBLE();
  setupUSB();
  setupButtonMatrix();
  setupTouchpad();
  setupDisplay();
  setupEPROM();
  setupSettings();
}

void setupPins() {
  if (DEBUG) Serial.println("Setup pins.");
  pinMode(BUTTON_COLUMN_PIN_SS, OUTPUT);
  pinMode(BUTTON_COLUMN_PIN_MOSI, OUTPUT);
  pinMode(BUTTON_COLUMN_PIN_SCK, OUTPUT);
  pinMode(BUTTON_COLUMN_PIN_OE, OUTPUT);
  pinMode(BUTTON_COLUMN_PIN_17, OUTPUT);

  pinMode(BUTTON_ROW_PIN_1, INPUT_PULLDOWN);
  pinMode(BUTTON_ROW_PIN_2, INPUT_PULLDOWN);
  pinMode(BUTTON_ROW_PIN_3, INPUT_PULLDOWN);
  pinMode(BUTTON_ROW_PIN_4, INPUT_PULLDOWN);
  pinMode(BUTTON_ROW_PIN_5, INPUT_PULLDOWN);
  pinMode(BUTTON_ROW_PIN_6, INPUT_PULLDOWN);
}

void setupBLE() {
  if (DEBUG) Serial.println("Setup BLE.");
  compositeHID = new BleCompositeHID(BLE_DEVICE_NAME, BLE_DEVICE_MANUFACTURER, 100);

  KeyboardConfiguration keyboardConfig;
  keyboardBLE = new KeyboardDevice(keyboardConfig);

  MouseConfiguration mouseConfig;
  mouseBLE = new MouseDevice(mouseConfig);

  compositeHID->addDevice(keyboardBLE);
  compositeHID->addDevice(mouseBLE);

  BLEHostConfiguration hostConfiguration;
  hostConfiguration.setHidType(HID_KEYBOARD);

  compositeHID->begin(hostConfiguration);
}

void setupUSB() {
  if (DEBUG) Serial.println("Setup USB.");
  keyboardUSB.begin();
  mouseUSB.begin();
  consumerControl.begin();
}

void setupButtonMatrix() {
  if (DEBUG) Serial.println("Setup button matrix");
  buttonMatrix.setup();
}

void setupTouchpad() {
  if (DEBUG) Serial.println("Setup touchpad");
  touchpad.setup();
}

void setupDisplay() {
  if (DEBUG) Serial.println("Setup display.");
  display.setup();
}

void setupEPROM() {
  if (DEBUG) Serial.println("Setup EPROM.");
  eprom.setup();
}

void setupSettings() {
  if (DEBUG) Serial.println("Setup settings.");
  settings = &eprom.getSettings();
}

void loop() {
  buttonMatrix.read();
  touchpad.read();

  loopKeyboard();
  loopMouse();

/*
  display.getDisplay().clearDisplay();
  display.getDisplay().setTextSize(1);
  display.getDisplay().setTextColor(SSD1306_WHITE);
  display.getDisplay().setCursor(0, 0);
  display.getDisplay().println("X: " + String(x, 1));
  display.getDisplay().println("y: " + String(y, 1));
  display.getDisplay().display();*/
}

void loopKeyboard() {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 17; j++) {
      uint8_t c = KEYBOARD_MATRIX[i][j];
      if (isFNPress() || isFNReleased()) {
        keyboardReleaseAll();
        mediaReleaseUSB();
      }
      if (isFNPressed()) {
        c = KEYBOARD_MATRIX_FN[i][j];
        if (isShiftPressed()) {
          c = KEYBOARD_MATRIX_FN_SHIFT[i][j];
        } else {
          if (c == KEY_NONE) {
            if (buttonMatrix.isPress(i, j)) {
              mediaPress(i, j);
            }
            if (buttonMatrix.isRelease(i, j)) {
              mediaRelease(i, j);
            }
          }
        }
      }
      if (c != KEY_NONE) {
        if (buttonMatrix.isPress(i, j)) {
          keyboardPress(c);
        }
        if (buttonMatrix.isRelease(i, j)) {
          keyboardRelease(c);
        }
      }
    }
  }

  if (!isFNPressed()) {
    if (isTwoLinkedButtonPress(5, 4, 5, 5)) keyboardPress(KEY_SPACE);
    if (isTwoLinkedButtonRelease(5, 4, 5, 5)) keyboardRelease(KEY_SPACE);
  } else {
    if (buttonMatrix.isPress(5, 2)) settings->setUSBMode(!settings->isUSBMode());
  }
}

void loopMouse() {
  if (touchpad.isFirstTocuhPressed()) {
    int x = touchpad.getFirstXMoved();
    int y = touchpad.getFirstYMoved();
    if (!touchpad.isSecondTocuhPressed()) {
      mouseMove(x, y);
    } else {
      mouseMove(0, 0, -y / 20, x / 20);
    }
  }

  if (isTwoLinkedButtonPress(1, 0, 4, 15)) mousePress(MOUSE_LEFT);
  if (isTwoLinkedButtonRelease(1, 0, 4, 15)) mouseRelease(MOUSE_LEFT);

  if (isTwoLinkedButtonPress(2, 0, 5, 13)) mousePress(MOUSE_MIDDLE);
  if (isTwoLinkedButtonRelease(2, 0, 5, 13)) mouseRelease(MOUSE_MIDDLE);

  if (isTwoLinkedButtonPress(3, 0, 5, 14)) mousePress(MOUSE_RIGHT);
  if (isTwoLinkedButtonRelease(3, 0, 5, 14)) mouseRelease(MOUSE_RIGHT);

  if (isTwoLinkedButtonPress(4, 0, 5, 15)) mousePress(MOUSE_FORWARD);
  if (isTwoLinkedButtonRelease(4, 0, 5, 15)) mouseRelease(MOUSE_FORWARD);

  if (isTwoLinkedButtonPress(5, 0, 5, 16)) mousePress(MOUSE_BACKWARD);
  if (isTwoLinkedButtonRelease(5, 0, 5, 16)) mouseRelease(MOUSE_BACKWARD);
}

bool isBLEConnected() {
  return compositeHID->isConnected();
}

bool isUSBMode() {
  return settings->isUSBMode();
}

bool isLeftShiftPressed() {
  return buttonMatrix.isPressed(4, 1);
}

bool isRightShiftPressed() {
  return buttonMatrix.isPressed(4, 12);
}

bool isShiftPressed() {
  return isLeftShiftPressed() || isRightShiftPressed();
}

bool isFNPress() {
  return buttonMatrix.isPress(5, 8);
}

bool isFNPressed() {
  return buttonMatrix.isPressed(5, 8);
}

bool isFNReleased() {
  return buttonMatrix.isRelease(5, 8);
}

bool isTwoLinkedButtonPress(int row1, int collumn1, int row2, int collumn2) {
  return ((buttonMatrix.isPress(row1, collumn1) && !(buttonMatrix.isPressed(row2, collumn2))) ||
          (buttonMatrix.isPress(row2, collumn2) && !(buttonMatrix.isPressed(row1, collumn1))));
}

bool isTwoLinkedButtonRelease(int row1, int collumn1, int row2, int collumn2) {
  return ((buttonMatrix.isRelease(row1, collumn1) && !(buttonMatrix.isPressed(row2, collumn2))) ||
          (buttonMatrix.isRelease(row2, collumn2) && !(buttonMatrix.isPressed(row1, collumn1))));
}

void keyboardPress(uint8_t k) {
  if (isUSBMode()) {
    keyboardUSB.pressRaw(k);
  } else if (isBLEConnected()) {
    keyboardBLE->keyPress(k);
  }
}

void keyboardRelease(uint8_t k) {
  if (isUSBMode()) {
    keyboardUSB.releaseRaw(k);
  } else if (isBLEConnected()) {
    keyboardBLE->keyRelease(k);
  }
}

void keyboardReleaseAll() {
  if (isUSBMode()) {
    keyboardUSB.releaseAll();
  } else if (isBLEConnected()) {
    keyboardBLE->resetKeys();
  }
}

void mousePress(uint8_t b) {
  if (isUSBMode()) {
    mouseUSB.press(b);
  } else if (isBLEConnected()) {
    mouseBLE->mousePress(b);
  }
}

void mouseRelease(uint8_t b) {
  if (isUSBMode()) {
    mouseUSB.release(b);
  } else if (isBLEConnected()) {
    mouseBLE->mouseRelease(b);
  }
}

void mouseMove(int x, int y, int wheel, int pan) {
  if (isUSBMode()) {
    mouseUSB.move(x, y, wheel, pan);
  } else if (isBLEConnected()) {
    mouseBLE->mouseMove(x, y, wheel, pan);
  }
}

void mouseMove(int x, int y, int wheel) {
  mouseMove(x, y, wheel, 0);
}

void mouseMove(int x, int y) {
  mouseMove(x, y, 0, 0);
}

void mediaPress(int row, int collumn) {
  if (isUSBMode()) {
    uint16_t media_c = KEYBOARD_MATRIX_MEDIA_KEYS_USB[row][collumn];
    if (media_c != MEDIA_KEY_USB_NONE) {
      mediaPressUSB(media_c);
    }
  } else if (isBLEConnected()) {
    uint32_t media_c = KEYBOARD_MATRIX_MEDIA_KEYS_BLE[row][collumn];
    if (media_c != MEDIA_KEY_BLE_NONE) {
      mediaPressBLE(media_c);
    }
  }
}

void mediaPressUSB(uint16_t c) {
  consumerControl.press(c);
}

void mediaPressBLE(uint32_t c) {
  keyboardBLE->mediaKeyPress(c);
}

void mediaRelease(int row, int collumn) {
  if (isUSBMode()) {
    mediaReleaseUSB();
  } else if (isBLEConnected()) {
    uint32_t media_c = KEYBOARD_MATRIX_MEDIA_KEYS_BLE[row][collumn];
    if (media_c != MEDIA_KEY_BLE_NONE) {
      mediaReleaseBLE(media_c);
    }
  }
}

void mediaReleaseUSB() {
  consumerControl.release();
}

void mediaReleaseBLE(uint32_t c) {
  keyboardBLE->mediaKeyRelease(c);
}