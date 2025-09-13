#pragma once

#include <JuceHeader.h>

class CustomButton : public juce::Component {
    public:
        CustomButton(const juce::String& name, juce::AudioProcessorValueTreeState& state, const juce::String& paramID);
        void resized() override;
    
    private:
        juce::Label label;
        juce::ToggleButton button;
        std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attachment;
};