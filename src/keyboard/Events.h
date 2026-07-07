#pragma once

#include <KeyboardDevice.h>
#include <USBHIDKeyboard.h>
#include <USB.h>

#include "Settings.h"

class Events {
    private:
        static Settings* settings;
        
    public:
        static void keyboardBLEOnLEDEvent(KeyboardOutputReport data);

        static void usbEventCallback(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
        
        static void keyboardUSBEventCallback(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

        static void setSettings(Settings* settings);
        static Settings& getSettings();
};