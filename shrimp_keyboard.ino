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