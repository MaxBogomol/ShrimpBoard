#pragma once

#include <vector>

#include "../Screen.h"
#include "SettingsIndex.h"

using namespace std;

class SettingsScreen : public Screen {
    private:
        unsigned long previousMillis = 0;
        bool next = false;
        bool select = false;

        int selectedIndex = 0;
        int selectedOffset = 0;

        bool leftPress = false;
        bool rightPress = false;
        unsigned long leftPressMillis = 0;
        unsigned long rightPressMillis = 0;

        vector<SettingsIndex*> settingsIndices;

    public:
        virtual void begin() override;
        virtual void loop() override;

        virtual bool hasNextScreen();
        virtual Screen& getNextScreen() override;

        void addSettingsIndex(SettingsIndex* settingsIndex);

        vector<SettingsIndex*>& getSettingsIndices();

        void drawIndex(int x, int y, const uint8_t BMP[]);
};