#include "FlatButton.h"

FlatButton::FlatButton(const juce::String& name, juce::AudioProcessorValueTreeState& state, const juce::String& paramID) {
    button.setButtonText(name);
    addAndMakeVisible(button);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(state, paramID, button);
}

void FlatButton::resized() {
    button.setBounds(getLocalBounds());
}