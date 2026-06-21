#include "Display.h"

void Display::setup() {
    this->display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    clear();
    update();
}

Adafruit_SSD1306& Display::getDisplay() {
    return *this->display;
}

void Display::update() {
    display->display();
}

void Display::clear() {
    display->clearDisplay();
}

void Display::invert(bool i) {
    display->invertDisplay(i);
}

int Display::black() {
    return SSD1306_BLACK;
}

int Display::white() {
    return SSD1306_WHITE;
}

int Display::inverse() {
    return SSD1306_INVERSE;
}

int Display::width() {
    return display->width();
}

int Display::height() {
    return display->height();
}

void Display::drawPixel(int x, int y, int color) {
    display->drawPixel(x, y, color);
}

void Display::drawLine(int x1, int y1, int x2, int y2, int color) {
    display->drawLine(x1, y1, x2, y2, color);
}

void Display::setTextSize(int size) {
    display->setTextSize(size);
}

void Display::setTextPos(int x, int y) {
    display->setCursor(x, y);
}

void Display::setTextColor(int color) {
    display->setTextColor(color);
}

void Display::setTextWrap(bool wrap) {
    display->setTextWrap(wrap);
}

void Display::drawText(String text) {
    display->print(text);
}

void Display::drawTextln(String text) {
    display->println(text);
}

void Display::textReset() {
    setTextSize(1);
    setTextPos(0, 0);
    setTextColor(white());
    setTextWrap(true);
}

void Display::drawBitmap(const uint8_t bitmap[], int x, int y, int w, int h, int color) {
    display->drawBitmap(x, y, bitmap, w, h, color);
}

void Display::drawRectangle(int x, int y, int w, int h, int color) {
    display->drawRect(x, y, w, h, color);
}

void Display::drawFilledRectangle(int x, int y, int w, int h, int color) {
    display->fillRect(x, y, w, h, color);
}

void Display::drawRoundRectangle(int x, int y, int w, int h, int radius, int color) {
    display->drawRoundRect(x, y, w, h, radius, color);
}

void Display::drawFilledRoundRectangle(int x, int y, int w, int h, int radius, int color) {
    display->fillRoundRect(x, y, w, h, radius, color);
}