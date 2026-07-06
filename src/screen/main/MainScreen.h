#pragma once

#include "../Screen.h"

class MainScreen : public Screen {
    private:
        unsigned long previousMillis = 0;
        bool next = false;

    public:
        virtual void begin() override;
        virtual void loop() override;

        virtual bool hasNextScreen() override;

        void drawStats(int x, int y);
        void drawKeyboard(int x, int y);
};