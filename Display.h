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

    void drawPixel(int x, int y, int color) {
      display->drawPixel(x, y, color);
    }
};