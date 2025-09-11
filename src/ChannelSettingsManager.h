#pragma once

#include <array>

struct SaturationSetting {
    float asymBias;
    float oddMix;
    float evenMix;
};

class ChannelSettingsManager {
    public:
        ChannelSettingsManager();
        ~ChannelSettingsManager();
        const SaturationSetting& getSaturationSetting(int index);
    
    private:
        std::array<SaturationSetting, 16> saturationSettings;

        void populateSaturationSettings();
};