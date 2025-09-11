#pragma once

#include <array>

#include "types/SaturationSetting.h"

class ChannelSettingsManager {
    public:
        ChannelSettingsManager();
        ~ChannelSettingsManager();
        const SaturationSetting& getSaturationSetting(int index);
    
    private:
        std::array<SaturationSetting, 16> saturationSettings;

        void populateSaturationSettings();
};