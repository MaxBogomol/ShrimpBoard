#include <BleCompositeHID.h>
#include <KeyboardDevice.h>
#include <MouseDevice.h>
#include <USBHIDKeyboard.h>
#include <USBHIDMouse.h>
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

KeyboardDevice* keyboard;
MouseDevice* mouse;
BleCompositeHID* compositeHID;
USBHIDKeyboard keyboardUSB;
USBHIDMouse mouseUSB;
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

static const unsigned char PROGMEM MATRIX_LIST[6][17] = {
  {KEY_NONE, KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_SYSRQ, KEY_SCROLLLOCK, KEY_PAUSE},
  {KEY_NONE, KEY_GRAVE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, KEY_INSERT, KEY_HOME},
  {KEY_NONE, KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFTBRACE, KEY_RIGHTBRACE, KEY_BACKSLASH, KEY_DELETE, KEY_END},
  {KEY_NONE, KEY_CAPSLOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_APOSTROPHE, KEY_ENTER, KEY_NONE, KEY_NONE, KEY_PAGEUP},
  {KEY_NONE, KEY_LEFTSHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_DOT, KEY_SLASH, KEY_RIGHTSHIFT, KEY_UP, KEY_NONE, KEY_NONE, KEY_PAGEDOWN},
  {KEY_NONE, KEY_RIGHTSHIFT, KEY_LEFTGUI, KEY_LEFTALT, KEY_SPACE, KEY_SPACE, KEY_RIGHTALT, KEY_RIGHTGUI, KEY_NONE, KEY_RIGHTCTRL, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE}
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
  keyboard = new KeyboardDevice(keyboardConfig);

  MouseConfiguration mouseConfig;
  mouse = new MouseDevice(mouseConfig);

  compositeHID->addDevice(keyboard);
  compositeHID->addDevice(mouse);

  BLEHostConfiguration hostConfiguration;
  hostConfiguration.setHidType(HID_KEYBOARD);

  compositeHID->begin(hostConfiguration);
}

void setupUSB() {
  if (DEBUG) Serial.println("Setup USB.");
  keyboardUSB.begin();
  mouseUSB.begin();
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
    mouseUSB.move(x, y, 0);
  } else {
    old = true;
  }

  if (touchpad.isSecondPressed()) {
    if (oldS) {
      mouseUSB.click(MOUSE_LEFT);
      oldS = false;
    }
  } else {
    oldS = true;
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

}

void loopMouse() {

}

bool isBLEConnected() {
  return compositeHID->isConnected();
}