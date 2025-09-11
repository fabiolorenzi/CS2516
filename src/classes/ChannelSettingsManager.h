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
    
    private:
        std::array<SaturationSetting, 16> saturationSettings;
        std::array<ColourSetting, 16> colourSettings;

        void populateSaturationSettings();
        void populateColourSettings();
};