#include "ChannelSelector.h"

ChannelSelector::ChannelSelector(const juce::String& name, juce::AudioProcessorValueTreeState& state, const juce::String& paramID) {
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    valueLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(valueLabel);

    addAndMakeVisible(decButton);
    addAndMakeVisible(incButton);

    if (auto* param = state.getParameter(paramID)) {
        attachment = std::make_unique<juce::ParameterAttachment>(*param, [this](float newValue) {
            valueLabel.setText(juce::String((int)newValue), juce::dontSendNotification);
        },
        nullptr);

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
    auto bounds = getLocalBounds().reduced(2);
    label.setBounds(bounds.removeFromTop(20));

    auto buttonArea = bounds.removeFromBottom(25);
    decButton.setBounds(buttonArea.removeFromLeft(30));
    incButton.setBounds(buttonArea.removeFromRight(30));
    valueLabel.setBounds(bounds);
}