#pragma once

#include <JuceHeader.h>
#include "styles/KnobLookAndFeel.h"

class Knob : public juce::Component {
    public:
        Knob(const juce::String& name, juce::AudioProcessorValueTreeState& state, const juce::String& paramID);
        void resized() override;
        void paint(juce::Graphics& g) override;
    
    private:
        juce::Label label;
        juce::Slider knob;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
        KnobLookAndFeel knobLookAndFeel;
};