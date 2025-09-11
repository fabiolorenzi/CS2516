#include "ChannelSettingsManager.h"

ChannelSettingsManager::ChannelSettingsManager() {
    populateSaturationSettings();
    populateColourSettings();
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

const ColourSetting& ChannelSettingsManager::getColourSetting(int index) {
    if (index < 1) {
        index = 1;
    } else if (index > 16) {
        index = 16;
    }
    
    return colourSettings[index - 1];
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

void ChannelSettingsManager::populateColourSettings() {
    colourSettings[0] = {20.0f, 60.0f, 0.1f, 0.22f, 15282.0f};
    colourSettings[1] = {25.0f, 70.0f, 0.15f, 0.30f, 16356.0f};
    colourSettings[2] = {18.0f, 80.0f, -0.1f, 0.28f, 15243.0f};
    colourSettings[3] = {30.0f, 100.0f, 0.2f, 0.35f, 17634.0f};
    colourSettings[4] = {15.0f, 40.0f, -0.2f, 0.18f, 14243.0f};
    colourSettings[5] = {22.0f, 55.0f, 0.0f, 0.25f, 15534.0f};
    colourSettings[6] = {28.0f, 90.0f, 0.25f, 0.33f, 18042.0f};
    colourSettings[7] = {12.0f, 35.0f, -0.15f, 0.15f, 13016.0f};
    colourSettings[8] = {20.0f, 60.0f, 0.05f, 0.27f, 15354.0f};
    colourSettings[9] = {14.0f, 45.0f, -0.05f, 0.20f, 12543.0f};
    colourSettings[10] = {26.0f, 75.0f, 0.15f, 0.32f, 15503.0f};
    colourSettings[11] = {22.0f, 65.0f, 0.14f, 0.35f, 16230.0f};
    colourSettings[12] = {18.0f, 50.0f, -0.1f, 0.24f, 18553.0f};
    colourSettings[13] = {32.0f, 95.0f, 0.2f, 0.29f, 17468.0f};
    colourSettings[14] = {16.0f, 42.0f, -0.05f, 0.19f, 12023.0f};
    colourSettings[15] = {24.0f, 85.0f, 0.1f, 0.31f, 15543.0f};
}