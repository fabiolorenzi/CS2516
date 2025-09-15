#include "Fader.h"

FaderLookAndFeel::FaderLookAndFeel() = default;
FaderLookAndFeel::~FaderLookAndFeel() = default;

void FaderLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider) {
    auto bounds = juce::Rectangle<int>(x, y, width, height);
    auto centerX = bounds.getCentreX();

    // === Draw the fader background track ===
    int trackWidth = 18;
    juce::Rectangle<int> track(centerX - trackWidth, y - 20, trackWidth + 20, height + 40);

    g.setColour(juce::Colour(30, 30, 30));
    g.fillRoundedRectangle(track.toFloat(), 4.0f);

    // === Draw the center rail slot ===
    g.setColour(juce::Colour(10, 10, 10)); // black slot
    g.drawLine((float)centerX, (float)y, (float)centerX, (float)(y + height), 1.0f);

    // === Draw the fader cap ===
    int capWidth = 24;
    int capHeight = 40;

    // Clamp sliderPos so thumb stays visible
    float minPos = (float)y + capHeight / 2.0f;
    float maxPos = (float)(y + height) - capHeight / 2.0f;
    float clampedSliderPos = juce::jlimit(minPos, maxPos, sliderPos);

    juce::Rectangle<float> thumbRect(
        bounds.getCentreX() - capWidth / 2.0f,
        clampedSliderPos - capHeight / 2.0f,
        (float)capWidth,
        (float)capHeight
    );

    // Fader cap fill
    g.setColour(juce::Colour(70, 70, 70)); // light grey plastic
    g.fillRoundedRectangle(thumbRect, 1.0f);

    // Fader cap border
    g.setColour(juce::Colours::black.withAlpha(0.8f));
    g.drawRoundedRectangle(thumbRect, 4.0f, 1.5f);

    // Optional: Add a line or groove in the cap for realism
    g.setColour(juce::Colours::black.withAlpha(0.6f));
    g.drawLine(thumbRect.getX() + 4,
               thumbRect.getCentreY(),
               thumbRect.getRight() - 4,
               thumbRect.getCentreY(),
               1.0f);
}

void FaderLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label) {
    g.fillAll(juce::Colours::transparentBlack);
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(14.0f, juce::Font::bold));
    g.drawText(label.getText(), label.getLocalBounds(), juce::Justification::centred);
}

Fader::Fader(const juce::String& name, juce::AudioProcessorValueTreeState& state, const juce::String& paramID) {
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    fader.setSliderStyle(juce::Slider::LinearVertical);
    fader.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    fader.setLookAndFeel(&faderLookAndFeel);
    fader.setPopupDisplayEnabled(true, false, this);
    addAndMakeVisible(fader);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(state, paramID, fader);
}

void Fader::resized() {
    auto bounds = getLocalBounds();
    label.setBounds(bounds.removeFromTop(20));

    bounds = bounds.reduced(0, 20);
    fader.setBounds(bounds);
}