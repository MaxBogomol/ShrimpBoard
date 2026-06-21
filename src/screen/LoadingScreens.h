#pragma once

#include "Screen.h"

class LoadingLinesScreen : public Screen {
    private:
        unsigned long previousMillis = 0;
        bool next = false;
        int line = 0;

    public:
        virtual void begin() override;
        virtual void loop() override;

        virtual bool hasNextScreen();
};

class LoadingShrimpBoardScreen : public Screen {
    private:
        unsigned long previousMillis = 0;
        bool next = false;
        int step = 0;
        String text = "ShrimpBoard";

    public:
        virtual void begin() override;
        virtual void loop() override;

        virtual bool hasNextScreen() override;
};