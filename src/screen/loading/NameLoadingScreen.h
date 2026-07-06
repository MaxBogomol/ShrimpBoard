#pragma once

#include "../Screen.h"

class NameLoadingScreen : public Screen {
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