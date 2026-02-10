#pragma once

class Display {
  private:
    Adafruit_SSD1306* display;

  public:
    void setup() {
        this->display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
        display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
        display->clearDisplay();
        display->display();
    }

    Adafruit_SSD1306& getDisplay() {
      return *this->display;
    }
};