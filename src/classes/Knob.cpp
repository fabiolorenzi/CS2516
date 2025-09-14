#include "Knob.h"

Knob::Knob(const juce::String& name, juce::AudioProcessorValueTreeState& state, const juce::String& paramID, float _minVal, float _maxVal, juce::String _unit, bool _linear) {
    minVal = _minVal;
    maxVal = _maxVal;
    unit = _unit;
    linear = _linear;

    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    knob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knob.setLookAndFeel(&knobLookAndFeel);

    if (linear) {
        knob.setRange(minVal, maxVal);
    } else {
        auto range = juce::NormalisableRange<double>(minVal, maxVal);
        range.setSkewForCentre(std::sqrt(minVal * maxVal));
        knob.setNormalisableRange(range);
    }

    addAndMakeVisible(knob);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(state, paramID, knob);
}

void Knob::resized() {
    auto bounds = getLocalBounds();

    label.setBounds(bounds.removeFromTop(20));

    const int knobSize = 60;

    juce::Rectangle<int> knobArea = bounds;
    juce::Rectangle<int> knobBounds(
        (knobArea.getWidth() - knobSize) / 2,
        (knobArea.getHeight() - knobSize) / 2,
        knobSize,
        knobSize
    );

    knob.setBounds(knobBounds);
}

void Knob::paint(juce::Graphics& g) {
    const int numTicks = 6;

    const int knobSize = 60;
    const int labelHeight = 20;
    juce::Rectangle<int> knobArea = getLocalBounds().withTrimmedTop(labelHeight);
    
    juce::Point<float> centre = knob.getBounds().toFloat().getCentre();
    float radius = knobSize / 2.0f + 1.0f;

    float rotaryStartAngle = juce::MathConstants<float>::pi * 1.2f;
    float rotaryEndAngle = juce::MathConstants<float>::pi * 2.8f;

    g.setFont(10.0f);
    g.setColour(juce::Colours::white);

    for (int i = 0; i <= numTicks; ++i) {
        float value = juce::jmap((float)i, 0.0f, (float)numTicks, minVal, maxVal);
        float proportion = (float)i / (float)numTicks;
        float tickAngle = rotaryStartAngle + proportion * (rotaryEndAngle - rotaryStartAngle);

        juce::Point<float> tickStart(0.0f, -radius);
        juce::Point<float> tickEnd(0.0f, -radius - 5.0f);

        auto rotation = juce::AffineTransform::rotation(tickAngle);
        tickStart = tickStart.transformedBy(rotation) + centre;
        tickEnd = tickEnd.transformedBy(rotation) + centre;

        g.drawLine({ tickStart, tickEnd }, 1.2f);

        if (i == 0 || i == numTicks) {
            juce::String text = juce::String(value, 0) + unit;

            juce::Point<float> textPoint(0.0f, -radius - 12.0f);
            textPoint = textPoint.transformedBy(rotation) + centre;

            g.drawFittedText(text, 
                (int)textPoint.getX() - 15, 
                (int)textPoint.getY() - 7, 
                30, 14, 
                juce::Justification::centred, 1);
        }
    }
}