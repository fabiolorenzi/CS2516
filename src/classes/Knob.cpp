#include "Knob.h"

Knob::Knob(const juce::String& name, juce::AudioProcessorValueTreeState& state, const juce::String& paramID) {
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    knob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    knob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knob.setLookAndFeel(&knobLookAndFeel);

    addAndMakeVisible(knob);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(state, paramID, knob);
}

void Knob::resized() {
    auto bounds = getLocalBounds();

    // Top label height
    const int labelHeight = 20;
    label.setBounds(bounds.removeFromTop(labelHeight));

    // Padding around knob for ticks/labels
    const int padding = 10;

    // Final knob face size (fixed)
    const int knobSize = 60;

    // Center the knob in the remaining area
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
    // Draw ticks and labels outside the knob
    const int numTicks = 6;
    const float minVal = 0.0f;
    const float maxVal = 24.0f;

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
            juce::String text = juce::String(value, 0) + "dB";

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