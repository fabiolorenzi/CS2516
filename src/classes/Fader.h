#pragma once

#include <JuceHeader.h>

struct FaderLookAndFeel : public juce::LookAndFeel_V4 {
    public:
        FaderLookAndFeel();
        ~FaderLookAndFeel() override;
        void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider) override;
        void drawLabel(juce::Graphics& g, juce::Label& label) override;
};

class Fader : public juce::Component {
    public:
        Fader(const juce::String& name, juce::AudioProcessorValueTreeState& state, const juce::String& paramID);
        void resized() override;

    private:
        juce::Label label;
        juce::Slider fader;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
        FaderLookAndFeel faderLookAndFeel;
};