#include "soc/rtc_cntl_reg.h"
#include <BleCompositeHID.h>
#include <KeyboardDevice.h>
#include <MouseDevice.h>
#include <USBHIDKeyboard.h>
#include <USBHIDMouse.h>
#include "USBHIDConsumerControl.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <at24c256.h>
#include "USB.h"
#include <Wire.h>
#include <SPI.h>

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

#define BUTTON_ROW_PIN_1 39
#define BUTTON_ROW_PIN_2 40
#define BUTTON_ROW_PIN_3 41
#define BUTTON_ROW_PIN_4 42
#define BUTTON_ROW_PIN_5 2
#define BUTTON_ROW_PIN_6 1

//Touch button
#define TOUCH_BUTTON_PIN 17
#define TOUCH_BUTTON_PIN_GPIO GPIO_NUM_17

//Leds
#define LED_NUM_LOCK_PIN 6
#define LED_CAPS_LOCK_PIN 7
#define LED_SCROLL_LOCK_PIN 15
#define LED_LEFT_MOUSE_LOCK_PIN 4
#define LED_RIGHT_MOUSE_LOCK_PIN 16
#define LED_SPECIAL_PIN 5

//Buzzer
#define BUZZER_PIN 18

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
#include <Leds.h>
#include <Buzzer.h>
#include <Touchpad.h>
#include <Display.h>
#include <EPROM.h>
#include <ScanCodes.h>
#include <ScanMatrix.h>
#include <Images.h>
#include <Interface.h>

KeyboardDevice* keyboardBLE;
MouseDevice* mouseBLE;
BleCompositeHID* compositeHID;
USBHIDKeyboard keyboardUSB;
USBHIDMouse mouseUSB;
USBHIDConsumerControl consumerControl;
Settings* settings;
ButtonMatrix buttonMatrix;
Leds leds;
Buzzer buzzer;
Touchpad touchpad;
Display display;
EPROM eprom;
Interface interface;

int sleepCount = 0;
int awakeCount = 0;

bool screenFocus = false;
bool mouseScroll = false;

bool leftMouseUp = false;
bool leftMouseDown = false;
bool rightMouseUp = false;
bool rightMouseDown = false;
unsigned long leftMouseUpMillis = 0;
unsigned long leftMouseDownMillis = 0;
unsigned long rightMouseUpMillis = 0;
unsigned long rightMouseDownMillis = 0;

void keyboardBLEOnLEDEvent(KeyboardOutputReport data) {
    settings->setNumLockBLE(data.numLockActive);
    settings->setCapsLockBLE(data.capsLockActive);
    settings->setScrollLockBLE(data.scrollLockActive);
}

void keyboardUSBEventCallback(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
  if (event_base == ARDUINO_USB_HID_KEYBOARD_EVENTS) {
    arduino_usb_hid_keyboard_event_data_t* data = (arduino_usb_hid_keyboard_event_data_t*)event_data;
    if (event_id == ARDUINO_USB_HID_KEYBOARD_LED_EVENT) {
      settings->setNumLockUSB(data->numlock);
      settings->setCapsLockUSB(data->capslock);
      settings->setScrollLockUSB(data->scrolllock);
    }
  }
}

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
  setupInterface();
  setupSettings();
  setupScreens();
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

  pinMode(TOUCH_BUTTON_PIN, INPUT_PULLUP);

  pinMode(LED_NUM_LOCK_PIN, OUTPUT);
  pinMode(LED_SCROLL_LOCK_PIN, OUTPUT);
  pinMode(LED_CAPS_LOCK_PIN, OUTPUT);
  pinMode(LED_LEFT_MOUSE_LOCK_PIN, OUTPUT);
  pinMode(LED_RIGHT_MOUSE_LOCK_PIN, OUTPUT);
  pinMode(LED_SPECIAL_PIN, OUTPUT);

  analogWriteResolution(LED_NUM_LOCK_PIN, 12);
  analogWriteResolution(LED_SCROLL_LOCK_PIN, 12);
  analogWriteResolution(LED_CAPS_LOCK_PIN, 12);
  analogWriteResolution(LED_LEFT_MOUSE_LOCK_PIN, 12);
  analogWriteResolution(LED_RIGHT_MOUSE_LOCK_PIN, 12);
  analogWriteResolution(LED_SPECIAL_PIN, 12);

  analogSetPinAttenuation(LED_NUM_LOCK_PIN, ADC_11db);
  analogSetPinAttenuation(LED_SCROLL_LOCK_PIN, ADC_11db);
  analogSetPinAttenuation(LED_CAPS_LOCK_PIN, ADC_11db);
  analogSetPinAttenuation(LED_LEFT_MOUSE_LOCK_PIN, ADC_11db);
  analogSetPinAttenuation(LED_RIGHT_MOUSE_LOCK_PIN, ADC_11db);
  analogSetPinAttenuation(LED_SPECIAL_PIN, ADC_11db);

  pinMode(BUZZER_PIN, OUTPUT);

  esp_sleep_enable_ext0_wakeup(TOUCH_BUTTON_PIN_GPIO, 1);
}

void setupBLE() {
  if (DEBUG) Serial.println("Setup BLE.");
  compositeHID = new BleCompositeHID(BLE_DEVICE_NAME, BLE_DEVICE_MANUFACTURER, 100);

  KeyboardConfiguration keyboardConfig;
  keyboardConfig.setUseMediaKeys(true);
  keyboardBLE = new KeyboardDevice(keyboardConfig);
  FunctionSlot<KeyboardOutputReport> OnLEDEventSlot(keyboardBLEOnLEDEvent);
  keyboardBLE->onLED.attach(OnLEDEventSlot);

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
  keyboardUSB.onEvent(keyboardUSBEventCallback);
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

void setupInterface() {
  if (DEBUG) Serial.println("Setup interface.");
  interface.setCompositeHID(compositeHID);
  interface.setButtonMatrix(&buttonMatrix);
  interface.setLeds(&leds);
  interface.setBuzzer(&buzzer);
  interface.setTouchpad(&touchpad);
  interface.setDisplay(&display);
  interface.setEPROM(&eprom);
}

void setupSettings() {
  if (DEBUG) Serial.println("Setup settings.");
  settings = &eprom.getSettings();

  buttonMatrix.setSettings(settings);
  leds.setSettings(settings);
  buzzer.setSettings(settings);
  touchpad.setSettings(settings);
  interface.setSettings(settings);
}

void setupScreens() {
  if (DEBUG) Serial.println("Setup screens.");
  interface.setupScreens();
}

void loop() {
  buttonMatrix.read();
  touchpad.read();

  loopSleep();
  loopLeds();
  if (!screenFocus) {
    loopKeyboard();
    loopMouse();
  }
  loopInterface();

  if (settings->isScreenFocus() && !screenFocus) screenFocus = true;
  if (!(settings->isScreenFocus()) && screenFocus) screenFocus = false;
}

void loopSleep() {
  unsigned long currentMillis = millis();
  bool active = false;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 17; j++) {
      if (buttonMatrix.getValue(i, j) > 0) active = true;
    }
  }
  if (touchpad.isFirstTouchPressed()) active = true;
  if (touchpad.isSecondTouchPressed()) active = true;
  if (active) settings->setActiveMillis(currentMillis);

  if (settings->isInactive()) {
    if (awakeCount != sleepCount) {
      awakeCount++;
      uint32_t save = REG_READ(RTC_CNTL_USB_CONF_REG);
      SET_PERI_REG_MASK(RTC_CNTL_USB_CONF_REG, RTC_CNTL_USB_PAD_PULL_OVERRIDE);
      SET_PERI_REG_MASK(RTC_CNTL_USB_CONF_REG, RTC_CNTL_USB_DP_PULLDOWN);
      vTaskDelay(5 / portTICK_PERIOD_MS);
      REG_WRITE(RTC_CNTL_USB_CONF_REG, save);
      settings->setActiveMillis(currentMillis);
    }

    if (currentMillis - settings->getActiveMillis() >= settings->getInactiveTime() * 1000 * 60) {
      sleepCount++;
      display.clear();
      display.update();
      esp_light_sleep_start();
    }
  }
}

void loopLeds() {
  if (isUseUSB()) {
    if (settings->isNumLockUSB()) {
      analogWrite(LED_NUM_LOCK_PIN, 4095);
    } else {
      analogWrite(LED_NUM_LOCK_PIN, 0);
    }
    if (settings->isCapsLockUSB()) {
      analogWrite(LED_CAPS_LOCK_PIN, 4095);
    } else {
      analogWrite(LED_CAPS_LOCK_PIN, 0);
    }
    if (settings->isScrollLockUSB()) {
      analogWrite(LED_SCROLL_LOCK_PIN, 4095);
    } else {
      analogWrite(LED_SCROLL_LOCK_PIN, 0);
    }
  }
  if (isUseBLE()) {
    if (settings->isNumLockBLE()) {
      analogWrite(LED_NUM_LOCK_PIN, 4095);
    } else {
      analogWrite(LED_NUM_LOCK_PIN, 0);
    }
    if (settings->isCapsLockBLE()) {
      analogWrite(LED_CAPS_LOCK_PIN, 4095);
    } else {
      analogWrite(LED_CAPS_LOCK_PIN, 0);
    }
    if (settings->isScrollLockBLE()) {
      analogWrite(LED_SCROLL_LOCK_PIN, 4095);
    } else {
      analogWrite(LED_SCROLL_LOCK_PIN, 0);
    }
  }

  if (settings->isLeftMouseLock()) {
    analogWrite(LED_LEFT_MOUSE_LOCK_PIN, 4095);
  } else {
    analogWrite(LED_LEFT_MOUSE_LOCK_PIN, 0);
  }
  if (settings->isRightMouseLock()) {
    analogWrite(LED_RIGHT_MOUSE_LOCK_PIN, 4095);
  } else {
    analogWrite(LED_RIGHT_MOUSE_LOCK_PIN, 0);
  }
}

void loopKeyboard() {
  if (isFNPress() || isFNReleased() || (settings->isScreenFocus() && !screenFocus)) {
    keyboardReleaseAll();
    mediaReleaseUSB();
  }
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 17; j++) {
      uint8_t c = KEYBOARD_MATRIX[i][j];
      if (isFNPressed()) {
        c = KEYBOARD_MATRIX_FN[i][j];
        if (isShiftPressed()) {
          c = KEYBOARD_MATRIX_FN_SHIFT[i][j];
        } else {
          if (c == KEY_NONE) {
            if (buttonMatrix.isPress(i, j)) mediaPress(i, j);
            if (buttonMatrix.isRelease(i, j)) mediaRelease(i, j);
          }
        }
      }
      if (c != KEY_NONE) {
        if (buttonMatrix.isPress(i, j)) keyboardPress(c);
        if (buttonMatrix.isRelease(i, j)) keyboardRelease(c);
      }
      if (settings->isPressSound() && buttonMatrix.isPress(i, j)) {
        buzzer.playTone(1000, 25);
      }
    }
  }

  if (!isFNPressed()) {
    if (isTwoLinkedButtonPress(5, 4, 5, 5)) keyboardPress(KEY_SPACE);
    if (isTwoLinkedButtonRelease(5, 4, 5, 5)) keyboardRelease(KEY_SPACE);
  } else {
    if (isTwoLinkedButtonPress(5, 2, 5, 7)) {
      keyboardReleaseAll();
      mediaReleaseUSB();
      mouseReleaseAll();
      settings->setUSBMode(!settings->isUSBMode());
    }
  }
}

void loopMouse() {
  float x = 0;
  float y = 0;
  if (touchpad.isFirstTouchPressed()) {
    if (settings->isTouchpadScroll() && touchpad.isSecondTouchPressed()) {
      if (!mouseScroll) mouseScroll = true;
    }
    x = touchpad.getFirstXMoved();
    y = touchpad.getFirstYMoved();
    if (settings->isTouchpadRounded()) {
      x = touchpad.getFirstXRounded();
      y = touchpad.getFirstYRounded();
    }
  } else {
    if (mouseScroll) mouseScroll = false;
    if (settings->isTouchpadInertia()) {
      x += touchpad.getFirstXInertial();
      y += touchpad.getFirstYInertial();
    }
  }

  if (x != 0 && y != 0) {
    if (!isMouseScroll()) {
      float speed = settings->getMouseSpeed();
      x = x * speed;
      y = y * speed;
      mouseMove(round(x), round(y));
    } else {
      float speed = settings->getMouseScrollSpeed();
      x = x * speed * 0.1;
      y = y * speed * 0.1;
      mouseMove(0, 0, round(-y), round(x));
    }
  }

  if (settings->isScreenFocus() && !screenFocus) {
    mouseReleaseAll();
  }

  if (buttonMatrix.isPress(0, 0)) {
    settings->setLeftMouseLock(!settings->isLeftMouseLock());
    mouseRelease(MOUSE_FORWARD);
    mouseRelease(MOUSE_BACKWARD);
  }
  if (buttonMatrix.isPress(4, 14)) {
    settings->setRightMouseLock(!settings->isRightMouseLock());
    mouseRelease(MOUSE_FORWARD);
    mouseRelease(MOUSE_BACKWARD);
  }

  if (isTwoLinkedButtonPress(1, 0, 4, 15)) mousePress(MOUSE_LEFT);
  if (isTwoLinkedButtonRelease(1, 0, 4, 15)) mouseRelease(MOUSE_LEFT);

  if (isTwoLinkedButtonPress(2, 0, 5, 13)) mousePress(MOUSE_MIDDLE);
  if (isTwoLinkedButtonRelease(2, 0, 5, 13)) mouseRelease(MOUSE_MIDDLE);

  if (isTwoLinkedButtonPress(3, 0, 5, 14)) mousePress(MOUSE_RIGHT);
  if (isTwoLinkedButtonRelease(3, 0, 5, 14)) mouseRelease(MOUSE_RIGHT);

  unsigned long currentMillis = millis();
  bool scroll = settings->isButtonScroll();
  int scrollDelay = settings->getButtonScrollDelay();
  int scrollTime = settings->getMouseButtonScrollTime();

  if (!isLeftMouseLock() && !isRightMouseLock()) {
    if (isTwoLinkedButtonPress(4, 0, 5, 15)) mousePress(MOUSE_FORWARD);
    if (isTwoLinkedButtonRelease(4, 0, 5, 15)) mouseRelease(MOUSE_FORWARD);

    if (isTwoLinkedButtonPress(5, 0, 5, 16)) mousePress(MOUSE_BACKWARD);
    if (isTwoLinkedButtonRelease(5, 0, 5, 16)) mouseRelease(MOUSE_BACKWARD);
  } else {
    if (isLeftMouseLock()) {
      if (buttonMatrix.isPress(4, 0)) {
        mouseMove(0, 0, 1);
        leftMouseUpMillis = millis();
        leftMouseUp = false;
      }
      if (buttonMatrix.isPress(5, 0)) {
        mouseMove(0, 0, -1);
        leftMouseDownMillis = millis();
        leftMouseDown = false;
      }

      if (scroll && buttonMatrix.isPressed(4, 0)) {
        if (!leftMouseUp && currentMillis - leftMouseUpMillis >= scrollDelay) {
          mouseMove(0, 0, 1);
          leftMouseUpMillis = millis();
          leftMouseUp = true;
        }
        if (leftMouseUp && currentMillis - leftMouseUpMillis >= scrollTime) {
          mouseMove(0, 0, 1);
          leftMouseUpMillis = millis();
        }
      }

      if (scroll && buttonMatrix.isPressed(5, 0)) {
        if (!leftMouseDown && currentMillis - leftMouseDownMillis >= scrollDelay) {
          mouseMove(0, 0, -1);
          leftMouseDownMillis = millis();
          leftMouseDown = true;
        }
        if (leftMouseDown && currentMillis - leftMouseDownMillis >= scrollTime) {
          mouseMove(0, 0, -1);
          leftMouseDownMillis = millis();
        }
      }
    } else {
      if (buttonMatrix.isPress(4, 0)) mousePress(MOUSE_FORWARD);
      if (buttonMatrix.isRelease(4, 0)) mouseRelease(MOUSE_FORWARD);

      if (buttonMatrix.isPress(5, 0)) mousePress(MOUSE_BACKWARD);
      if (buttonMatrix.isRelease(5, 0)) mouseRelease(MOUSE_BACKWARD);
    }
    if (isRightMouseLock()) {
      if (buttonMatrix.isPress(5, 15)) {
        mouseMove(0, 0, 1);
        rightMouseUpMillis = millis();
        rightMouseUp = false;
      }
      if (buttonMatrix.isPress(5, 16)) {
        mouseMove(0, 0, -1);
        rightMouseDownMillis = millis();
        rightMouseDown = false;
      }

      if (scroll && buttonMatrix.isPressed(5, 15)) {
        if (!rightMouseUp && currentMillis - rightMouseUpMillis >= scrollDelay) {
          mouseMove(0, 0, 1);
          rightMouseUpMillis = millis();
          rightMouseUp = true;
        }
        if (rightMouseUp && currentMillis - rightMouseUpMillis >= scrollTime) {
          mouseMove(0, 0, 1);
          rightMouseUpMillis = millis();
        }
      }

      if (scroll && buttonMatrix.isPressed(5, 16)) {
        if (!rightMouseDown && currentMillis - rightMouseDownMillis >= scrollDelay) {
          mouseMove(0, 0, -1);
          rightMouseDownMillis = millis();
          rightMouseDown = true;
        }
        if (rightMouseDown && currentMillis - rightMouseDownMillis >= scrollTime) {
          mouseMove(0, 0, -1);
          rightMouseDownMillis = millis();
        }
      }
    } else {
      if (buttonMatrix.isPress(5, 15)) mousePress(MOUSE_FORWARD);
      if (buttonMatrix.isRelease(5, 15)) mouseRelease(MOUSE_FORWARD);

      if (buttonMatrix.isPress(5, 16)) mousePress(MOUSE_BACKWARD);
      if (buttonMatrix.isRelease(5, 16)) mouseRelease(MOUSE_BACKWARD);
    }
  }

  if (isFNPressed()) {
    if (buttonMatrix.isPressed(4, 13)) mouseMove(0, -1);
    if (buttonMatrix.isPressed(5, 10)) mouseMove(-1, 0);
    if (buttonMatrix.isPressed(5, 11)) mouseMove(0, 1);
    if (buttonMatrix.isPressed(5, 12)) mouseMove(1, 0);
  }
}

void loopInterface() {
  interface.loop();
}

bool isBLEConnected() {
  return compositeHID->isConnected();
}

bool isUSBMode() {
  return settings->isUSBMode();
}

bool isUseUSB() {
  return isUSBMode();
}

bool isUseBLE() {
  return !isUSBMode() && isBLEConnected();
}

bool isMouseScroll() {
  return ((mouseScroll) ||
          (settings->isMouseLockScroll() && isMouseLock()) ||
          (settings->isLeftMouseLockScroll() && isLeftMouseLock()) ||
          (settings->isRightMouseLockScroll() && isRightMouseLock()));
}

bool isShiftPressed() {
  return isTwoLinkedButtonPressed(4, 1, 4, 12);
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

bool isTwoLinkedButtonPressed(int row1, int collumn1, int row2, int collumn2) {
  return (buttonMatrix.isPressed(row1, collumn1) || buttonMatrix.isPressed(row2, collumn2));
}

bool isTwoLinkedButtonRelease(int row1, int collumn1, int row2, int collumn2) {
  return ((buttonMatrix.isRelease(row1, collumn1) && !(buttonMatrix.isPressed(row2, collumn2))) ||
          (buttonMatrix.isRelease(row2, collumn2) && !(buttonMatrix.isPressed(row1, collumn1))));
}

bool isMouseLock() {
  return isLeftMouseLock() || isRightMouseLock();
}

bool isLeftMouseLock() {
  return settings->isLeftMouseLock();
}

bool isRightMouseLock() {
  return settings->isRightMouseLock();
}

void keyboardPress(uint8_t k) {
  if (isUseUSB()) {
    keyboardUSB.pressRaw(k);
  } else if (isUseBLE()) {
    keyboardBLE->keyPress(k);
  }
}

void keyboardRelease(uint8_t k) {
  if (isUseUSB()) {
    keyboardUSB.releaseRaw(k);
  } else if (isUseBLE()) {
    keyboardBLE->keyRelease(k);
  }
}

void keyboardReleaseAll() {
  if (isUseUSB()) {
    keyboardUSB.releaseAll();
  } else if (isUseBLE()) {
    keyboardBLE->resetKeys();
  }
}

void mousePress(uint8_t b) {
  if (isUseUSB()) {
    mouseUSB.press(b);
  } else if (isUseBLE()) {
    mouseBLE->mousePress(b);
  }
}

void mouseRelease(uint8_t b) {
  if (isUseUSB()) {
    mouseUSB.release(b);
  } else if (isUseBLE()) {
    mouseBLE->mouseRelease(b);
  }
}

void mouseReleaseAll() {
  if (isUseUSB()) {
    mouseUSB.release(MOUSE_ALL);
  } else if (isUseBLE()) {
    mouseBLE->resetButtons();
  }
}

void mouseMove(int x, int y, int wheel, int pan) {
  if (isUseUSB()) {
    mouseUSB.move(x, y, wheel, pan);
  } else if (isUseBLE()) {
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
  if (isUseUSB()) {
    uint16_t media_c = KEYBOARD_MATRIX_MEDIA_KEYS_USB[row][collumn];
    if (media_c != MEDIA_KEY_USB_NONE) {
      mediaPressUSB(media_c);
    }
  } else if (isUseBLE()) {
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
  if (isUseUSB()) {
    mediaReleaseUSB();
  } else if (isUseBLE()) {
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