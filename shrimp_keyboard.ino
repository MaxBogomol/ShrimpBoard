#include <BleCompositeHID.h>
#include <KeyboardDevice.h>
#include <MouseDevice.h>
#include <USBHIDKeyboard.h>
#include <USBHIDMouse.h>
#include "USB.h"
#include <Wire.h>

#include <ps4_touchpad.h>
#include <keys.h>

#define BUTTON_COLUMN_PIN_MOSI 11
#define BUTTON_COLUMN_PIN_SCK 12
#define BUTTON_COLUMN_PIN_MISO 13

#define BUTTON_ROW_PIN_1 4
#define BUTTON_ROW_PIN_2 5
#define BUTTON_ROW_PIN_3 6
#define BUTTON_ROW_PIN_4 7
#define BUTTON_ROW_PIN_5 15
#define BUTTON_ROW_PIN_6 16

KeyboardDevice* keyboard;
MouseDevice* mouse;
BleCompositeHID compositeHID("Shrimpboard", "Pink Joke", 100);
USBHIDKeyboard keyboardUSB;
USBHIDMouse mouseUSB;
PS4Touchpad touchpad;

bool DEBUG = true;
bool USB_MODE = false;

/*
16MB (128Mb)
16M Flash (3MB APP)
OPI PSRAM

1 - GND
2 - VDD
4 - SDA
5 - SCL
*/

void setup() {
  Serial.begin(115200);
  USB.begin();
  Wire.begin();

  touchpad.setAddress(0x64);

  if (DEBUG) Serial.println("Setup BLE server.");
  KeyboardConfiguration keyboardConfig;
  keyboard = new KeyboardDevice(keyboardConfig);

  MouseConfiguration mouseConfig;
  mouse = new MouseDevice(mouseConfig);

  compositeHID.addDevice(keyboard);
  compositeHID.addDevice(mouse);

  BLEHostConfiguration hostConfiguration;
  hostConfiguration.setHidType(HID_KEYBOARD);

  compositeHID.begin(hostConfiguration);

  if (DEBUG) Serial.println("Setup USB.");
  keyboardUSB.begin();
  mouseUSB.begin();
}

void loop() {
  keyboardLoop();
  mouseLoop();


}

void keyboardLoop() {
  if (!USB_MODE && isBLEConnected()) {

  } else if (USB_MODE) {

  }
}

void mouseLoop() {
  touchpad.read();
  
  if (!USB_MODE && isBLEConnected()) {

  } else if (USB_MODE) {

  }
}

bool isBLEConnected() {
  return compositeHID.isConnected();
}