#include "ShrimpBoard.h"

#include <soc/rtc_cntl_reg.h>
#include <USB.h>
#include <Wire.h>

#include "../defines/Defines.h"
#include "../defines/ScanCodes.h"
#include "../defines/ScanMatrix.h"

#include "Events.h"

void ShrimpBoard::setup() {
    Serial.begin(115200);
    Wire.begin();

    setupPins();
    setupBLE();
    setupUSB();
    setupButtonMatrix();
    setupKeyboard();
    setupTouchpad();
    setupDisplay();
    setupEPROM();
    setupInterface();
    setupSettings();
    setupScreens();

    USB.begin();
}

void ShrimpBoard::setupPins() {
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
    esp_sleep_enable_ext0_wakeup(TOUCH_BUTTON_PIN_GPIO, 1);

    pinMode(BATTERY_PIN, INPUT);
    analogWriteResolution(BATTERY_PIN, 12);
    analogSetPinAttenuation(BATTERY_PIN, ADC_11db);

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
}

void ShrimpBoard::setupBLE() {
    if (DEBUG) Serial.println("Setup BLE.");
    compositeHID = new BleCompositeHID(DEVICE_NAME, DEVICE_MANUFACTURER, 100);

    KeyboardConfiguration keyboardConfig;
    keyboardConfig.setUseMediaKeys(true);
    keyboardBLE = new KeyboardDevice(keyboardConfig);
    FunctionSlot<KeyboardOutputReport> OnLEDEventSlot(Events::keyboardBLEOnLEDEvent);
    keyboardBLE->onLED.attach(OnLEDEventSlot);

    MouseConfiguration mouseConfig;
    mouseBLE = new MouseDevice(mouseConfig);

    compositeHID->addDevice(keyboardBLE);
    compositeHID->addDevice(mouseBLE);

    BLEHostConfiguration hostConfiguration;
    hostConfiguration.setHidType(HID_KEYBOARD);

    compositeHID->begin(hostConfiguration);
}

void ShrimpBoard::setupUSB() {
    if (DEBUG) Serial.println("Setup USB.");
    USB.productName(DEVICE_NAME);
    USB.manufacturerName(DEVICE_MANUFACTURER);
    USB.onEvent(Events::usbEventCallback);

    keyboardUSB.onEvent(Events::keyboardUSBEventCallback);
    keyboardUSB.begin();
    mouseUSB.begin();
    consumerControl.begin();
}

void ShrimpBoard::setupButtonMatrix() {
    if (DEBUG) Serial.println("Setup button matrix");
    buttonMatrix.setup();
}

void ShrimpBoard::setupKeyboard() {
    if (DEBUG) Serial.println("Setup keyboard");
    keyboard.setButtonMatrix(&buttonMatrix);
}

void ShrimpBoard::setupTouchpad() {
    if (DEBUG) Serial.println("Setup touchpad");
    touchpad.setup();
}

void ShrimpBoard::setupDisplay() {
    if (DEBUG) Serial.println("Setup display.");
    display.setup();
}

void ShrimpBoard::setupEPROM() {
    if (DEBUG) Serial.println("Setup EPROM.");
    eprom.setup();
}

void ShrimpBoard::setupInterface() {
    if (DEBUG) Serial.println("Setup interface.");
    interface.setShrimpBoard(this);
}

void ShrimpBoard::setupSettings() {
    if (DEBUG) Serial.println("Setup settings.");
    eprom.load();

    settings = &eprom.getSettings();

    buttonMatrix.setSettings(settings);
    battery.setSettings(settings);
    leds.setSettings(settings);
    buzzer.setSettings(settings);
    touchpad.setSettings(settings);
}

void ShrimpBoard::setupScreens() {
    if (DEBUG) Serial.println("Setup screens.");
    interface.setupScreens();
}

void ShrimpBoard::loop() {
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

void ShrimpBoard::loopSleep() {
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

    if (settings->isInactive() || settings->isShowSleep()) {
        if (awakeCount != sleepCount) {
            awakeCount++;
            uint32_t save = REG_READ(RTC_CNTL_USB_CONF_REG);
            SET_PERI_REG_MASK(RTC_CNTL_USB_CONF_REG, RTC_CNTL_USB_PAD_PULL_OVERRIDE);
            SET_PERI_REG_MASK(RTC_CNTL_USB_CONF_REG, RTC_CNTL_USB_DP_PULLDOWN);
            vTaskDelay(5 / portTICK_PERIOD_MS);
            REG_WRITE(RTC_CNTL_USB_CONF_REG, save);
            settings->setActiveMillis(currentMillis);
            settings->setShowSleep(false);
        }

        if (currentMillis - settings->getActiveMillis() >= settings->getInactiveTime() * 1000 * 60 || settings->isShowSleep()) {
            sleepCount++;
            leds.disableAll();
            buzzer.playNoTone();
            display.clear();
            display.update();
            esp_light_sleep_start();
        }
    }
}

void ShrimpBoard::loopLeds() {
    bool numLock = ((isUseUSB() && settings->isNumLockUSB()) || (isUseBLE() && settings->isNumLockBLE()));
    bool capsLock = ((isUseUSB() && settings->isCapsLockUSB()) || (isUseBLE() && settings->isCapsLockBLE()));
    bool scrollLock = ((isUseUSB() && settings->isScrollLockUSB()) || (isUseBLE() && settings->isScrollLockBLE()));
    leds.setNumLockBrightness(numLock ? 100 : 0);
    leds.setCapsLockBrightness(capsLock ? 100 : 0);
    leds.setScrollLockBrightness(scrollLock ? 100 : 0);
    leds.setLeftMouseLockBrightness(settings->isLeftMouseLock() ? 100 : 0);
    leds.setRightMouseLockBrightness(settings->isRightMouseLock() ? 100 : 0);
}

void ShrimpBoard::loopKeyboard() {
    if (keyboard.isFNPress() || keyboard.isFNReleased() || (settings->isScreenFocus() && !screenFocus)) {
        keyboardReleaseAll();
        mediaReleaseUSB();
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 17; j++) {
            uint8_t c = KEYBOARD_MATRIX[i][j];
            if (keyboard.isFNPressed()) {
                c = KEYBOARD_MATRIX_FN[i][j];
                if (keyboard.isShiftPressed()) {
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
                int frequency = settings->getPressSoundFrequency();
                int duration = settings->getPressSoundDuration();
                buzzer.playTone(frequency, duration);
            }
        }
    }

    if (!keyboard.isFNPressed()) {
        if (keyboard.isTwoLinkedButtonPress(5, 4, 5, 5)) keyboardPress(KEY_SPACE);
        if (keyboard.isTwoLinkedButtonRelease(5, 4, 5, 5)) keyboardRelease(KEY_SPACE);
    } else {
        if (keyboard.isTwoLinkedButtonPress(5, 2, 5, 7)) {
            keyboardReleaseAll();
            mediaReleaseUSB();
            mouseReleaseAll();
            settings->setUSBMode(!settings->isUSBMode());
        }
    }
}

void ShrimpBoard::loopMouse() {
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
            mouseMove((int) x, (int) y);
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

    if (keyboard.isTwoLinkedButtonPress(1, 0, 4, 15)) mousePress(MOUSE_LEFT);
    if (keyboard.isTwoLinkedButtonRelease(1, 0, 4, 15)) mouseRelease(MOUSE_LEFT);

    if (keyboard.isTwoLinkedButtonPress(2, 0, 5, 13)) mousePress(MOUSE_MIDDLE);
    if (keyboard.isTwoLinkedButtonRelease(2, 0, 5, 13)) mouseRelease(MOUSE_MIDDLE);

    if (keyboard.isTwoLinkedButtonPress(3, 0, 5, 14)) mousePress(MOUSE_RIGHT);
    if (keyboard.isTwoLinkedButtonRelease(3, 0, 5, 14)) mouseRelease(MOUSE_RIGHT);

    unsigned long currentMillis = millis();
    bool scroll = settings->isButtonScroll();
    int scrollDelay = settings->getButtonScrollDelay();
    int scrollTime = settings->getMouseButtonScrollTime();

    if (!settings->isLeftMouseLock() && !settings->isRightMouseLock()) {
        if (keyboard.isTwoLinkedButtonPress(4, 0, 5, 15)) mousePress(MOUSE_FORWARD);
        if (keyboard.isTwoLinkedButtonRelease(4, 0, 5, 15)) mouseRelease(MOUSE_FORWARD);

        if (keyboard.isTwoLinkedButtonPress(5, 0, 5, 16)) mousePress(MOUSE_BACKWARD);
        if (keyboard.isTwoLinkedButtonRelease(5, 0, 5, 16)) mouseRelease(MOUSE_BACKWARD);
    } else {
        if (settings->isLeftMouseLock()) {
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
        if (settings->isRightMouseLock()) {
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

    if (keyboard.isFNPressed()) {
        if (buttonMatrix.isPressed(4, 13)) mouseMove(0, -1);
        if (buttonMatrix.isPressed(5, 10)) mouseMove(-1, 0);
        if (buttonMatrix.isPressed(5, 11)) mouseMove(0, 1);
        if (buttonMatrix.isPressed(5, 12)) mouseMove(1, 0);
    }
}

void ShrimpBoard::loopInterface() {
    interface.loop();
}

bool ShrimpBoard::isBLEConnected() {
    return compositeHID->isConnected();
}

bool ShrimpBoard::isUSBMode() {
    return settings->isUSBMode();
}

bool ShrimpBoard::isUseUSB() {
    return isUSBMode();
}

bool ShrimpBoard::isUseBLE() {
    return !isUSBMode() && isBLEConnected();
}

bool ShrimpBoard::isMouseScroll() {
    return ((mouseScroll) ||
                    (settings->isMouseLockScroll() && settings->isMouseLock()) ||
                    (settings->isLeftMouseLockScroll() && settings->isLeftMouseLock()) ||
                    (settings->isRightMouseLockScroll() && settings->isRightMouseLock()));
}

bool ShrimpBoard::isModifierKey(uint8_t k) {
    return (k >= 0xE0 && k <= 0xE7);
}

void ShrimpBoard::keyboardPress(uint8_t k) {
    if (isUseUSB()) {
        keyboardUSB.pressRaw(k);
    } else if (isUseBLE()) {
        if (isModifierKey(k)) {
            keyboardBLE->modifierKeyPress(1 << (k - 0xE0));
        } else {
            keyboardBLE->keyPress(k);
        }
    }
}

void ShrimpBoard::keyboardRelease(uint8_t k) {
    if (isUseUSB()) {
        keyboardUSB.releaseRaw(k);
    } else if (isUseBLE()) {
        if (isModifierKey(k)) {
            keyboardBLE->modifierKeyRelease(1 << (k - 0xE0));
        } else {
            keyboardBLE->keyRelease(k);
        }
    }
}

void ShrimpBoard::keyboardReleaseAll() {
    if (isUseUSB()) {
        keyboardUSB.releaseAll();
    } else if (isUseBLE()) {
        keyboardBLE->resetKeys();
    }
}

void ShrimpBoard::mousePress(uint8_t b) {
    if (isUseUSB()) {
        mouseUSB.press(b);
    } else if (isUseBLE()) {
        mouseBLE->mousePress(b);
    }
}

void ShrimpBoard::mouseRelease(uint8_t b) {
    if (isUseUSB()) {
        mouseUSB.release(b);
    } else if (isUseBLE()) {
        mouseBLE->mouseRelease(b);
    }
}

void ShrimpBoard::mouseReleaseAll() {
    if (isUseUSB()) {
        mouseUSB.release(MOUSE_ALL);
    } else if (isUseBLE()) {
        mouseBLE->resetButtons();
    }
}

void ShrimpBoard::mouseMove(int x, int y, int wheel, int pan) {
    if (isUseUSB()) {
        mouseUSB.move(x, y, wheel, pan);
    } else if (isUseBLE()) {
        mouseBLE->mouseMove(x, y, wheel, pan);
    }
}

void ShrimpBoard::mouseMove(int x, int y, int wheel) {
    mouseMove(x, y, wheel, 0);
}

void ShrimpBoard::mouseMove(int x, int y) {
    mouseMove(x, y, 0, 0);
}

void ShrimpBoard::mediaPress(int row, int collumn) {
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

void ShrimpBoard::mediaPressUSB(uint16_t c) {
    consumerControl.press(c);
}

void ShrimpBoard::mediaPressBLE(uint32_t c) {
    keyboardBLE->mediaKeyPress(c);
}

void ShrimpBoard::mediaRelease(int row, int collumn) {
    if (isUseUSB()) {
        mediaReleaseUSB();
    } else if (isUseBLE()) {
        uint32_t media_c = KEYBOARD_MATRIX_MEDIA_KEYS_BLE[row][collumn];
        if (media_c != MEDIA_KEY_BLE_NONE) {
            mediaReleaseBLE(media_c);
        }
    }
}

void ShrimpBoard::mediaReleaseUSB() {
    consumerControl.release();
}

void ShrimpBoard::mediaReleaseBLE(uint32_t c) {
    keyboardBLE->mediaKeyRelease(c);
}

Settings& ShrimpBoard::getSettings() {
    return *this->settings;
}

ButtonMatrix& ShrimpBoard::getButtonMatrix() {
    return this->buttonMatrix;
}

Battery& ShrimpBoard::getBattery() {
    return this->battery;
}

Leds& ShrimpBoard::getLeds() {
    return this->leds;
}

Buzzer& ShrimpBoard::getBuzzer() {
    return this->buzzer;
}

Keyboard& ShrimpBoard::getKeyboard() {
    return this->keyboard;
}

Touchpad& ShrimpBoard::getTouchpad() {
    return this->touchpad;
}

Display& ShrimpBoard::getDisplay() {
    return this->display;
}

EPROM& ShrimpBoard::getEPROM() {
    return this->eprom;
}

Interface& ShrimpBoard::getInterface() {
    return this->interface;
}