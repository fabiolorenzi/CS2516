#include "ChannelSelector.h"

void ButtonLookAndFeel::drawButtonBackground(juce::Graphics& graphics, juce::Button& b, const juce::Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) {
    auto bounds = b.getLocalBounds().toFloat().reduced(0.5f);
    float cornerSize = 4.0f;

    // Adjust base colour depending on interaction
    auto baseColour = backgroundColour;
    if (isButtonDown) {
        baseColour = baseColour.darker(0.3f);
    } else if (isMouseOverButton) {
        baseColour = baseColour.brighter(0.2f);
    }

    // === Gradient background ===
    juce::ColourGradient gradient(
        baseColour.brighter(0.15f), bounds.getCentreX(), bounds.getY(),
        baseColour.darker(0.3f),    bounds.getCentreX(), bounds.getBottom(),
        false
    );

    graphics.setGradientFill(gradient);
    graphics.fillRoundedRectangle(bounds, cornerSize);

    graphics.setColour(juce::Colours::white.withAlpha(0.15f));
    graphics.drawLine(bounds.getX() + 1.0f, bounds.getY() + 1.0f, bounds.getRight() - 1.0f, bounds.getY() + 1.0f);

    // === Border ===
    graphics.setColour(juce::Colours::black.withAlpha(0.6f));
    graphics.drawRoundedRectangle(bounds, cornerSize, 1.0f);
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