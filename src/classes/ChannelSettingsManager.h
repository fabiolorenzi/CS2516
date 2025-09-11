#pragma once

#include <array>
#include "types/ColourSetting.h"
#include "types/SaturationSetting.h"

class ChannelSettingsManager {
    public:
        ChannelSettingsManager();
        ~ChannelSettingsManager();
        const SaturationSetting& getSaturationSetting(int index);
        const ColourSetting& getColourSetting(int index);
        const float& getNoiseLevelSetting(int index);
    
    private:
        std::array<SaturationSetting, 16> saturationSettings;
        std::array<ColourSetting, 16> colourSettings;
        std::array<float, 16> noiseLevelSettings;

        void populateSaturationSettings();
        void populateColourSettings();
        void populateNoiseSettings();
};