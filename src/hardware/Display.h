#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "../defines/Defines.h"

class Display {
    private:
        Adafruit_SSD1306* display;

    public:
        void setup();
        Adafruit_SSD1306& getDisplay();
        void update();
        void clear();
        void invert(bool i);
        int black();
        int white();
        int inverse();
        int width();
        int height();
        void drawPixel(int x, int y, int color);
        void drawLine(int x1, int y1, int x2, int y2, int color);
        void setTextSize(int size);
        void setTextPos(int x, int y);
        void setTextColor(int color);
        void setTextWrap(bool wrap);
        void drawText(String text);
        void drawTextln(String text);
        void textReset();
        void drawBitmap(const uint8_t bitmap[], int x, int y, int w, int h, int color);
        void drawRectangle(int x, int y, int w, int h, int color);
        void drawFilledRectangle(int x, int y, int w, int h, int color);
        void drawRoundRectangle(int x, int y, int w, int h, int radius, int color);
        void drawFilledRoundRectangle(int x, int y, int w, int h, int radius, int color);
};