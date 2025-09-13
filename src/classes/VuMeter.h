#pragma once

#include <JuceHeader.h>

class VuMeter : public juce::Component, private juce::Timer {
    public:
        VuMeter();
        void paint(juce::Graphics& graphics) override;
        void setLevel(float newLevel);

    private:
        float level = 0.0f;

        void timerCallback() override;
};