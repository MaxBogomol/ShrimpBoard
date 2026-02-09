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

#include <button_matrix.h>
#include <ps4_touchpad.h>
#include <display.h>
#include <eprom.h>
#include <settings.h>
#include <keys.h>

KeyboardDevice* keyboardBLE;
MouseDevice* mouseBLE;
BleCompositeHID* compositeHID;
USBHIDKeyboard keyboardUSB;
USBHIDMouse mouseUSB;
USBHIDConsumerControl consumerControl;
ButtonMatrix buttonMatrix;
PS4Touchpad touchpad;
Display display;
EPROM eprom;

bool USB_MODE = false;

float x = 0;
float y = 0;
float xOld = 0;
float yOld = 0;
bool old = false;
bool oldS = false;

static const uint8_t PROGMEM KEYBOARD_MATRIX[6][17] = {
  {KEY_NONE, KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_SYSRQ, KEY_SCROLLLOCK, KEY_PAUSE},
  {KEY_NONE, KEY_GRAVE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, KEY_INSERT, KEY_HOME},
  {KEY_NONE, KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFTBRACE, KEY_RIGHTBRACE, KEY_BACKSLASH, KEY_DELETE, KEY_END},
  {KEY_NONE, KEY_CAPSLOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_APOSTROPHE, KEY_ENTER, KEY_NONE, KEY_NONE, KEY_PAGEUP},
  {KEY_NONE, KEY_LEFTSHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_DOT, KEY_SLASH, KEY_RIGHTSHIFT, KEY_UP, KEY_NONE, KEY_NONE, KEY_PAGEDOWN},
  {KEY_NONE, KEY_RIGHTCTRL, KEY_LEFTGUI, KEY_LEFTALT, KEY_SPACE, KEY_SPACE, KEY_RIGHTALT, KEY_RIGHTGUI, KEY_NONE, KEY_RIGHTCTRL, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE}
};

static const uint8_t PROGMEM KEYBOARD_MATRIX_FN[6][17] = {
  {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
  {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
  {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
  {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
  {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
  {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
};

static const uint8_t PROGMEM KEYBOARD_MATRIX_FN_SHIFT[6][17] = {
  {KEY_NONE, KEY_NONE, KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F20, KEY_F21, KEY_F22, KEY_F23, KEY_F24, KEY_NONE, KEY_NONE, KEY_NONE},
  {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
  {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
  {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
  {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
  {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
};

#define MEDIA_KEY_USB_NONE 0x0000

static const uint16_t PROGMEM KEYBOARD_MATRIX_MEDIA_KEYS_USB[6][17] = {
  {MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, CONSUMER_CONTROL_SCAN_PREVIOUS, CONSUMER_CONTROL_PLAY_PAUSE, CONSUMER_CONTROL_SCAN_NEXT, CONSUMER_CONTROL_MUTE, CONSUMER_CONTROL_VOLUME_DECREMENT, CONSUMER_CONTROL_VOLUME_INCREMENT, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE},
  {MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE},
  {MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE},
  {MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE},
  {MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE},
  {MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE, MEDIA_KEY_USB_NONE}
};

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
  touchpad.setAddress(TOUCHPAD_ADDRESS);
}

void setupDisplay() {
  if (DEBUG) Serial.println("Setup display.");
  display.setup();
}

void loop() {
  buttonMatrix.read();
  touchpad.read();

  loopKeyboard();
  loopMouse();

  if (touchpad.isFirstPressed()) {
    if (old) {
      xOld = touchpad.getFirstY();
      yOld = touchpad.getFirstX();
      old = false;
    }
    x = touchpad.getFirstY() - xOld;
    y = yOld - touchpad.getFirstX();
    if (!touchpad.isSecondPressed()) {
      mouseUSB.move(x, y, 0);
    } else {
      mouseUSB.move(0, 0, -y / 10);
    }
  } else {
    old = true;
  }

  xOld = touchpad.getFirstY();
  yOld = touchpad.getFirstX();

  display.getDisplay().clearDisplay();
  display.getDisplay().setTextSize(1);
  display.getDisplay().setTextColor(SSD1306_WHITE);
  display.getDisplay().setCursor(0, 0);
  display.getDisplay().println("X: " + String(x, 1));
  display.getDisplay().println("y: " + String(y, 1));
  display.getDisplay().display();
}

void loopKeyboard() {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 17; j++) {
      uint8_t c = KEYBOARD_MATRIX[i][j];
      if (isFNPress() || isFNReleased()) {
        keyboardUSB.releaseAll();
        consumerControl.release();
      }
      if (isFNPressed()) {
        c = KEYBOARD_MATRIX_FN[i][j];
        if (isShiftPressed()) {
          c = KEYBOARD_MATRIX_FN_SHIFT[i][j];
        } else {
          if (c == KEY_NONE) {
            uint16_t media_c = KEYBOARD_MATRIX_MEDIA_KEYS_USB[i][j];
            if (media_c != MEDIA_KEY_USB_NONE) {
              if (buttonMatrix.isPress(i, j)) {
                consumerControl.press(media_c);
              }
              if (buttonMatrix.isRelease(i, j)) {
                consumerControl.release();
              }
            }
          }
        }
      }
      if (c != KEY_NONE) {
        if (buttonMatrix.isPress(i, j)) {
          keyboardUSB.pressRaw(c);
        }
        if (buttonMatrix.isRelease(i, j)) {
          keyboardUSB.releaseRaw(c);
        }
      }
    }
  }
}

void loopMouse() {
  if (isMouseButtonPress(1, 0, 4, 15)) mouseUSB.press(MOUSE_LEFT);
  if (isMouseButtonRelease(1, 0, 4, 15)) mouseUSB.release(MOUSE_LEFT);

  if (isMouseButtonPress(2, 0, 5, 13)) mouseUSB.press(MOUSE_MIDDLE);
  if (isMouseButtonRelease(2, 0, 5, 13)) mouseUSB.release(MOUSE_MIDDLE);

  if (isMouseButtonPress(3, 0, 5, 14)) mouseUSB.press(MOUSE_RIGHT);
  if (isMouseButtonRelease(3, 0, 5, 14)) mouseUSB.release(MOUSE_RIGHT);

  if (isMouseButtonPress(4, 0, 5, 15)) mouseUSB.press(MOUSE_FORWARD);
  if (isMouseButtonRelease(4, 0, 5, 15)) mouseUSB.release(MOUSE_FORWARD);

  if (isMouseButtonPress(5, 0, 5, 16)) mouseUSB.press(MOUSE_BACKWARD);
  if (isMouseButtonRelease(5, 0, 5, 16)) mouseUSB.release(MOUSE_BACKWARD);
}

bool isBLEConnected() {
  return compositeHID->isConnected();
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

bool isMouseButtonPress(int row1, int collumn1, int row2, int collumn2) {
  return ((buttonMatrix.isPress(row1, collumn1) && !(buttonMatrix.isPressed(row2, collumn2))) ||
          (buttonMatrix.isPress(row2, collumn2) && !(buttonMatrix.isPressed(row1, collumn1))));
}

bool isMouseButtonRelease(int row1, int collumn1, int row2, int collumn2) {
  return ((buttonMatrix.isRelease(row1, collumn1) && !(buttonMatrix.isPressed(row2, collumn2))) ||
          (buttonMatrix.isRelease(row2, collumn2) && !(buttonMatrix.isPressed(row1, collumn1))));
}