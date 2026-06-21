#pragma once

#include <at24c256.h>

#include "../defines/Defines.h"
#include "../keyboard/Settings.h"

class EPROM {
    private:
        AT24C256* eprom;
        Settings* settings;
        Settings* settingsSaved;

        int index = 0;

    public:
        void setup();
        void load();
        void save();
        void reset();

        AT24C256& getEPROM();
        Settings& getSettings();
        Settings& getSettingsSaved();

        bool readBool(int address);
        int readInt(int address);
        float readFloat(int address);
        bool readBool();
        int readInt();
        float readFloat();
        int readIntLimit(int minValue, int maxValue, int standardValue);
        float readFloatLimit(float minValue, float maxValue, float standardValue);

        void writeBool(int address, bool value);
        void writeInt(int address, int value);
        void writeFloat(int address, float value);
        void writeBool(bool value);
        void writeInt(int value);
        void writeFloat(float value);
        void writeBoolIf(bool write, bool value);
        void writeIntIf(bool write, int value);
        void writeFloatIf(bool write, float value);
};