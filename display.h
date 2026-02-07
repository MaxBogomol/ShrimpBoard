class Display {
  private:
    Adafruit_SSD1306* display;

  public:
    void setup() {
        this->display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
        getDisplay().begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
        getDisplay().clearDisplay();
        getDisplay().display();
    }

    Adafruit_SSD1306& getDisplay() {
      return *this->display;
    }
};