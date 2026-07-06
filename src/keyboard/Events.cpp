#include "Events.h"

Settings* Events::settings = nullptr;

void Events::keyboardBLEOnLEDEvent(KeyboardOutputReport data) {
    settings->setNumLockBLE(data.numLockActive);
    settings->setCapsLockBLE(data.capsLockActive);
    settings->setScrollLockBLE(data.scrollLockActive);
}

void Events::usbEventCallback(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    if (event_base == ARDUINO_USB_EVENTS) {
        arduino_usb_event_data_t* data = (arduino_usb_event_data_t*) event_data;
        switch (event_id) {
            case ARDUINO_USB_STARTED_EVENT: settings->setUSB(true); break;
            case ARDUINO_USB_STOPPED_EVENT: settings->setUSB(false); break;
            case ARDUINO_USB_SUSPEND_EVENT: settings->setUSB(false); break;
            case ARDUINO_USB_RESUME_EVENT: settings->setUSB(true); break;
        }
    }
}

void Events::keyboardUSBEventCallback(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    if (event_base == ARDUINO_USB_HID_KEYBOARD_EVENTS) {
        arduino_usb_hid_keyboard_event_data_t* data = (arduino_usb_hid_keyboard_event_data_t*) event_data;
        switch (event_id) {
            case ARDUINO_USB_HID_KEYBOARD_LED_EVENT: {
                settings->setNumLockUSB(data->numlock);
                settings->setCapsLockUSB(data->capslock);
                settings->setScrollLockUSB(data->scrolllock);
                break;
            }
        }
    }
}

void Events::setSettings(Settings* settings) {
    Events::settings = settings;
}

Settings& Events::getSettings() {
    return *Events::settings;
}