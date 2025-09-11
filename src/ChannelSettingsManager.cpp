#include "ChannelSettingsManager.h"

ChannelSettingsManager::ChannelSettingsManager() {
    populateSaturationSettings();
}

ChannelSettingsManager::~ChannelSettingsManager() {}

const SaturationSetting& ChannelSettingsManager::getSaturationSetting(int index) {
    if (index < 1) {
        index = 1;
    } else if (index > 16) {
        index = 16;
    }

    return saturationSettings[index - 1];
}

void ChannelSettingsManager::populateSaturationSettings() {
    saturationSettings[0] = {0.1f, 0.8f, 0.2f};
    saturationSettings[1] = {0.12f, 0.78f, 0.22f};
    saturationSettings[2] = {0.09f, 0.82f, 0.18f};
    saturationSettings[3] = {0.11f, 0.79f, 0.21f};
    saturationSettings[4] = {0.13f, 0.77f, 0.23f};
    saturationSettings[5] = {0.08f, 0.83f, 0.17f};
    saturationSettings[6] = {0.1f, 0.81f, 0.19f};
    saturationSettings[7] = {0.12f, 0.8f, 0.2f};
    saturationSettings[8] = {0.11f, 0.79f, 0.2f};
    saturationSettings[9] = {0.09f, 0.82f, 0.19f};
    saturationSettings[10] = {0.13f, 0.78f, 0.21f};
    saturationSettings[11] = {0.1f, 0.6f, 0.4f};
    saturationSettings[12] = {0.12f, 0.79f, 0.21f};
    saturationSettings[13] = {0.1f, 0.81f, 0.19f};
    saturationSettings[14] = {0.11f, 0.8f, 0.2f};
    saturationSettings[15] = {0.09f, 0.82f, 0.19f};
}