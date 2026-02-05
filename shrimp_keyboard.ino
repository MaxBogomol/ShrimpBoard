#include <BleCompositeHID.h>
#include <KeyboardDevice.h>
#include <MouseDevice.h>
#include <USBHIDKeyboard.h>
#include <USBHIDMouse.h>
#include "USB.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <at24c256.h>

#include <ps4_touchpad.h>
#include <keys.h>

#define BUTTON_COLUMN_PIN_MOSI 11
#define BUTTON_COLUMN_PIN_SCK 12
#define BUTTON_COLUMN_PIN_MISO 13
#define BUTTON_COLUMN_PIN_1 14

#define BUTTON_ROW_PIN_1 4
#define BUTTON_ROW_PIN_2 5
#define BUTTON_ROW_PIN_3 6
#define BUTTON_ROW_PIN_4 7
#define BUTTON_ROW_PIN_5 15
#define BUTTON_ROW_PIN_6 16

#define TOUCHPAD_ADDRESS 0x64

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define EEPROM_ADDRESS 0x50

KeyboardDevice* keyboard;
MouseDevice* mouse;
BleCompositeHID compositeHID("Shrimpboard", "Pink Joke", 100);
USBHIDKeyboard keyboardUSB;
USBHIDMouse mouseUSB;
PS4Touchpad touchpad;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
AT24C256 eeprom(EEPROM_ADDRESS);

bool DEBUG = true;
bool USB_MODE = false;

float x = 0;
float y = 0;
float xOld = 0;
float yOld = 0;
bool old = false;
bool oldS = false;

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

  touchpad.setAddress(TOUCHPAD_ADDRESS);

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

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

  display.display();
}

void loop() {
  touchpad.read();
  keyboardLoop();
  mouseLoop();

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
}

void keyboardLoop() {
  if (!USB_MODE && isBLEConnected()) {

  } else if (USB_MODE) {

  }
}

void mouseLoop() {
  if (!USB_MODE && isBLEConnected()) {

  } else if (USB_MODE) {

  }
}

bool isBLEConnected() {
  return compositeHID.isConnected();
}