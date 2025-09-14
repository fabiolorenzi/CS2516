#include "KnobLookAndFeel.h"

KnobLookAndFeel::KnobLookAndFeel() = default;
KnobLookAndFeel::~KnobLookAndFeel() = default;

void KnobLookAndFeel::drawRotarySlider(juce::Graphics& graphics, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) {
    auto bounds = juce::Rectangle<float>(x, y, width, height).reduced(4);

    // ====== Knob background (outer ring) ======
    graphics.setColour(juce::Colours::darkgrey.darker(0.8f));
    graphics.fillEllipse(bounds);

    graphics.setColour(juce::Colours::black);
    graphics.drawEllipse(bounds, 1.5f);

    // ====== Knob fill (main knob face) ======
    auto knobBounds = bounds.reduced(6);
    juce::ColourGradient gradient(juce::Colours::grey.brighter(0.2f), knobBounds.getCentreX(), knobBounds.getY(), juce::Colours::grey.darker(0.6f), knobBounds.getCentreX(), knobBounds.getBottom(), true);

    graphics.setGradientFill(gradient);
    graphics.fillEllipse(knobBounds);

    graphics.setColour(juce::Colours::black.withAlpha(0.6f));
    graphics.drawEllipse(knobBounds, 1.0f);

    // ====== Pointer (indicator line) ======
    auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    juce::Path p;
    auto pointerLength = knobBounds.getWidth() * 0.4f;
    auto pointerThickness = 2.0f;
    p.addRectangle(-pointerThickness * 0.5f, -knobBounds.getHeight() / 2.5f, pointerThickness, pointerLength);

    graphics.setColour(juce::Colours::limegreen);
    graphics.fillPath(p, juce::AffineTransform::rotation(angle).translated(knobBounds.getCentreX(), knobBounds.getCentreY()));
}