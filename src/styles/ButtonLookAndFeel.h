#pragma once

#include <JuceHeader.h>

class ButtonLookAndFeel : public juce::LookAndFeel_V4 {
    public:
        ButtonLookAndFeel();
        ~ButtonLookAndFeel() override;
        void drawButtonBackground(juce::Graphics& graphics, juce::Button& b, const juce::Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override;
};