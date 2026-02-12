#pragma once

class LoadingScreenLines : public Screen {
  private:

  public:
    virtual void loop() override {
      getDisplay().clear();
      getDisplay().drawPixel(0, 0, getDisplay().white());
      getDisplay().update();
    }
};