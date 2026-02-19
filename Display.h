#pragma once

class Display {
  private:
    Adafruit_SSD1306* display;

  public:
    void setup() {
      this->display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
      display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
      clear();
      update();
    }

    Adafruit_SSD1306& getDisplay() {
      return *this->display;
    }

    void update() {
      display->display();
    }

    void clear() {
      display->clearDisplay();
    }

    void invert(bool i) {
      display->invertDisplay(i);
    }

    int black() {
      return SSD1306_BLACK;
    }

    int white() {
      return SSD1306_WHITE;
    }

    int inverse() {
      return SSD1306_INVERSE;
    }

    int width() {
      return display->width();
    }

    int height() {
      return display->height();
    }

    void drawPixel(int x, int y, int color) {
      display->drawPixel(x, y, color);
    }

    void drawLine(int x1, int y1, int x2, int y2, int color) {
      display->drawLine(x1, y1, x2, y2, color);
    }

    void setTextSize(int size) {
      display->setTextSize(size);
    }

    void setTextPos(int x, int y) {
      display->setCursor(x, y);
    }

    void setTextColor(int color) {
      display->setTextColor(color);
    }

    void setTextWrap(bool wrap) {
      display->setTextWrap(wrap);
    }

    void drawText(String text) {
      display->print(text);
    }

    void drawTextln(String text) {
      display->println(text);
    }

    void textReset() {
      setTextSize(1);
      setTextPos(0, 0);
      setTextColor(white());
      setTextWrap(true);
    }

    void drawBitmap(const uint8_t bitmap[], int x, int y, int w, int h, int color) {
      display->drawBitmap(x, y, bitmap, w, h, color);
    }

    void drawRectangle(int x, int y, int w, int h, int color) {
      display->drawRect(x, y, w, h, color);
    }

    void drawFilledRectangle(int x, int y, int w, int h, int color) {
      display->fillRect(x, y, w, h, color);
    }

    void drawRoundRectangle(int x, int y, int w, int h, int radius, int color) {
      display->drawRoundRect(x, y, w, h, radius, color);
    }

    void drawFilledRoundRectangle(int x, int y, int w, int h, int radius, int color) {
      display->fillRoundRect(x, y, w, h, radius, color);
    }
};