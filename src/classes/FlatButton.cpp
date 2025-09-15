#include "FlatButton.h"

FlatButtonLookAndFeel::FlatButtonLookAndFeel() = default;
FlatButtonLookAndFeel::~FlatButtonLookAndFeel() = default;

void FlatButtonLookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& button, bool isMouseOverButton, bool isButtonDown) {
    auto bounds = button.getLocalBounds().toFloat().reduced(2.0f);
    const float cornerSize = 6.0f;

    bool isOn = button.getToggleState();

    // Color setup
    auto bgOff = juce::Colour(40, 40, 40); // dark background
    auto bgOn = juce::Colour(55, 55, 30);  // dark warm tint when on

    auto textOff = juce::Colours::white;
    auto textOn = juce::Colour(255, 223, 0); // warm yellow
    auto borderColour = juce::Colour(100, 100, 100); // 3D border

    // Background fill
    g.setColour(isOn ? bgOn : bgOff);
    g.fillRoundedRectangle(bounds, cornerSize);

    // 3D border
    g.setColour(borderColour.darker(0.5f));
    g.drawRoundedRectangle(bounds, cornerSize, 2.0f);

    // Draw text glow (when ON)
    if (isOn)
    {
        juce::DropShadow glowShadow(textOn.withAlpha(0.6f), 12, {});
        glowShadow.drawForPath(g, createTextPath(button, bounds));
    }

    // Pressed effect (slight dark overlay)
    if (isButtonDown)
    {
        g.setColour(juce::Colours::black.withAlpha(0.1f));
        g.fillRoundedRectangle(bounds, cornerSize);
    }

    // Draw text
    g.setColour(isOn ? textOn : textOff);
    g.setFont(juce::Font(10.0f, juce::Font::bold));
    g.drawText(button.getButtonText(), bounds, juce::Justification::centred);
}

juce::Path FlatButtonLookAndFeel::createTextPath(juce::ToggleButton& button, juce::Rectangle<float> bounds) {
    juce::Path textPath;
    juce::Font font(10.0f, juce::Font::bold);

    juce::GlyphArrangement arrangement;
    arrangement.addJustifiedText(font, button.getButtonText(), bounds.getX(), bounds.getCentreY(), bounds.getWidth(), juce::Justification::centred);

    arrangement.createPath(textPath);
    return textPath;
}

FlatButton::FlatButton(const juce::String& name, juce::AudioProcessorValueTreeState& state, const juce::String& paramID) {
    button.setButtonText(name);
    button.setLookAndFeel(&flatButtonLookAndFeel);
    addAndMakeVisible(button);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(state, paramID, button);
}

void FlatButton::resized() {
    button.setBounds(getLocalBounds());
}