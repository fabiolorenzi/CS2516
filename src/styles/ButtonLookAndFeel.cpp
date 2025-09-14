#include "ButtonLookAndFeel.h"

ButtonLookAndFeel::ButtonLookAndFeel() = default;
ButtonLookAndFeel::~ButtonLookAndFeel() = default;

void ButtonLookAndFeel::drawButtonBackground(juce::Graphics& graphics, juce::Button& b, const juce::Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) {
    auto bounds = b.getLocalBounds().toFloat();
    auto baseColour = backgroundColour;

    if (isButtonDown) {
        baseColour = baseColour.darker();
    } else if (isMouseOverButton) {
        baseColour = baseColour.brighter();
    }

    graphics.setColour(baseColour);
    graphics.fillRoundedRectangle(bounds, 2.0f);
}