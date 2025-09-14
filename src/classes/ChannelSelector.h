#pragma once

#include <JuceHeader.h>

struct ButtonLookAndFeel : public juce::LookAndFeel_V4 {
    public:
        ButtonLookAndFeel() = default;
        ~ButtonLookAndFeel() override = default;
        void drawButtonBackground(juce::Graphics& graphics, juce::Button& b, const juce::Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override;
};

class ChannelSelector : public juce::Component {
    public:
        ChannelSelector(const juce::String& name, juce::AudioProcessorValueTreeState& state, const juce::String& paramID);
        void resized() override;

    private:
        juce::Label label;
        juce::Label valueLabel;
        juce::TextButton decButton {"-"};
        juce::TextButton incButton {"+"};
        std::unique_ptr<juce::ParameterAttachment> attachment;

        ButtonLookAndFeel buttonLookAndFeel;
};