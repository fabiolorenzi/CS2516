#pragma once

#include <JuceHeader.h>
#include "styles/KnobLookAndFeel.h"

class Knob : public juce::Component {
    public:
        Knob(const juce::String& name, juce::AudioProcessorValueTreeState& state, const juce::String& paramID, float _minValue, float _maxValue, juce::String _unit, bool _linear);
        void resized() override;
        void paint(juce::Graphics& g) override;
    
    private:
        float minVal;
        float maxVal;
        juce::String unit;
        bool linear;
        juce::Label label;
        juce::Slider knob;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
        KnobLookAndFeel knobLookAndFeel;
};