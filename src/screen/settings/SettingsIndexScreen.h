#pragma once

#include <vector>

#include "../Screen.h"
#include "SettingsEntry.h"

using namespace std;

class SettingsIndexScreen : public Screen {
    private:
        unsigned long previousMillis = 0;
        bool next = false;
        bool select = false;

        int selectedIndex = 0;
        int selectedOffset = 0;

        bool leftPress = false;
        bool rightPress = false;
        bool upPress = false;
        bool downPress = false;
        unsigned long leftPressMillis = 0;
        unsigned long rightPressMillis = 0;
        unsigned long upPressMillis = 0;
        unsigned long downPressMillis = 0;

        vector<SettingsEntry*> settingsEntries;

    public:
        virtual void begin() override;
        virtual void loop() override;

        virtual bool hasNextScreen() override;
        virtual Screen& getNextScreen() override;

        void addSettingsEntry(SettingsEntry* settingsEntry);

        vector<SettingsEntry*>& getSettingsEntries();
};