#include <BleCompositeHID.h>
#include <KeyboardDevice.h>
#include <MouseDevice.h>
#include <USBHIDKeyboard.h>
#include <USBHIDMouse.h>
#include "USB.h"
#include <Wire.h>

#include <ps4_touchpad.h>
#include <keys.h>

#define BUTTON_COLUMN1_PIN 10
#define BUTTON_COLUMN2_PIN 11
#define BUTTON_ROW1_PIN 12
#define BUTTON_ROW2_PIN 13

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

  pinMode(BUTTON_COLUMN1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_COLUMN2_PIN, INPUT_PULLUP);

  pinMode(BUTTON_ROW1_PIN, OUTPUT);
  pinMode(BUTTON_ROW2_PIN, OUTPUT);

  digitalWrite(BUTTON_ROW1_PIN, HIGH);
  digitalWrite(BUTTON_ROW2_PIN, HIGH);

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

  Serial.print("---");
  Serial.println();
  digitalWrite(BUTTON_ROW1_PIN, LOW);
  Serial.print(!digitalRead(BUTTON_COLUMN1_PIN));
  Serial.print(" ");
  Serial.print(!digitalRead(BUTTON_COLUMN2_PIN));
  digitalWrite(BUTTON_ROW1_PIN, HIGH);
  Serial.println();
  digitalWrite(BUTTON_ROW2_PIN, LOW);
  Serial.print(!digitalRead(BUTTON_COLUMN1_PIN));
  Serial.print(" ");
  Serial.print(!digitalRead(BUTTON_COLUMN2_PIN));
  digitalWrite(BUTTON_ROW2_PIN, HIGH);
  Serial.println();
  Serial.print("---");
  Serial.println();
  delay(10);
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