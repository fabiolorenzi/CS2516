#pragma once

#include <array>
#include "types/ColourSetting.h"
#include "types/EQSetting.h"
#include "types/FiltersSetting.h"
#include "types/SaturationSetting.h"

class ChannelSettingsManager {
    public:
        ChannelSettingsManager();
        ~ChannelSettingsManager();
        const SaturationSetting& getSaturationSetting(int index);
        const ColourSetting& getColourSetting(int index);
        const float& getNoiseLevelSetting(int index);
        const FiltersSetting& getFiltersSetting(int index);
        const EQSetting& getEQSetting(int index);
    
    private:
        std::array<SaturationSetting, 16> saturationSettings;
        std::array<ColourSetting, 16> colourSettings;
        std::array<float, 16> noiseLevelSettings;
        std::array<FiltersSetting, 16> filtersSettings;
        std::array<EQSetting, 16> eqSettings;

        void populateSaturationSettings();
        void populateColourSettings();
        void populateNoiseSettings();
        void populateFiltersSettings();
        void populateEQSettings();
};