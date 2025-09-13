#include "VuMeter.h"

VuMeter::VuMeter() {
    startTimerHz(30);
}

void VuMeter::setLevel(float newLevel) {
    level = juce::jlimit(0.0f, 1.0f, newLevel);
}

void VuMeter::paint(juce::Graphics& graphics) {
    auto bounds = getLocalBounds().toFloat();
    graphics.setColour(juce::Colours::black);
    graphics.fillRect(bounds);

    auto meterHeight = bounds.getHeight() * level;
    graphics.setColour(juce::Colours::green);
    graphics.fillRect(bounds.removeFromBottom((int)meterHeight));
}

void VuMeter::timerCallback() {
    repaint();
}