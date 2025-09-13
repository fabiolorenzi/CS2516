#pragma once

#include <JuceHeader.h>

class Fader : public juce::Component {
    public:
        Fader(const juce::String& name, juce::AudioProcessorValueTreeState& state, const juce::String& paramID);
        void resized() override;

    private:
        juce::Label label;
        juce::Slider fader;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
};