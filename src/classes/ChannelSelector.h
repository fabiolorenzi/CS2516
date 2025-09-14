#pragma once

#include <JuceHeader.h>
#include "styles/ButtonLookAndFeel.h"

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