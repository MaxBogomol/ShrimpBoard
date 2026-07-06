#pragma once

#include <Arduino.h>
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