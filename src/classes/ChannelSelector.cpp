#include "ChannelSelector.h"

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

ChannelSelector::ChannelSelector(const juce::String& name, juce::AudioProcessorValueTreeState& state, const juce::String& paramID) {
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    valueLabel.setJustificationType(juce::Justification::centred);
    valueLabel.setColour(juce::Label::backgroundColourId, juce::Colours::black);
    valueLabel.setColour(juce::Label::textColourId, juce::Colours::limegreen);
    addAndMakeVisible(valueLabel);

    addAndMakeVisible(decButton);
    addAndMakeVisible(incButton);

    decButton.setLookAndFeel(&buttonLookAndFeel);
    incButton.setLookAndFeel(&buttonLookAndFeel);

    if (auto* param = state.getParameter(paramID)) {
        attachment = std::make_unique<juce::ParameterAttachment>(*param, [this, param](float) {
            valueLabel.setText(param->getCurrentValueAsText(), juce::dontSendNotification);
        }, nullptr);

        valueLabel.setText(param->getCurrentValueAsText(), juce::dontSendNotification);

        decButton.onClick = [this, param] {
            float v = param->getValue();
            param->setValueNotifyingHost(juce::jlimit(0.0f, 1.0f, v - 1.0f / (param->getNumSteps() - 1)));
        };

        incButton.onClick = [this, param] {
            float v = param->getValue();
            param->setValueNotifyingHost(juce::jlimit(0.0f, 1.0f, v + 1.0f / (param->getNumSteps() - 1)));
        };
    }
}

void ChannelSelector::resized() {
    auto area = getLocalBounds();
    label.setBounds(area.getCentreX() - 21, 10, 40, 15);

    valueLabel.setBounds(4, 30, 40, 35);

    decButton.setBounds(3, 69, 20, 20);
    incButton.setBounds(25, 69, 20, 20);
}