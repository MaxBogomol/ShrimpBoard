#pragma once

#include "../Screen.h"

class LinesLoadingScreen : public Screen {
    private:
        unsigned long previousMillis = 0;
        bool next = false;
        int line = 0;

    public:
        virtual void begin() override;
        virtual void loop() override;

        virtual bool hasNextScreen();
};