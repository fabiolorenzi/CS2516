#include "PluginEditor.h"
#include "PluginProcessor.h"

PluginEditor::PluginEditor(PluginProcessor& pluginProcessor)
    : AudioProcessorEditor(&pluginProcessor),
      pluginProcessor(pluginProcessor),
      leftChannel("Left", pluginProcessor.apvts, "LEFTCHANNEL"),
      rightChannel("Right", pluginProcessor.apvts, "RIGHTCHANNEL"),
      inputKnob("Input", pluginProcessor.apvts, "INPUT", 0.0f, 24.0f, "dB", juce::Colours::grey, this),
      micButton("Mic", pluginProcessor.apvts, "MICMODE"),
      hpKnob("HP", pluginProcessor.apvts, "HPFILTER", 16.0f, 320.0f, "Hz", juce::Colours::grey, this),
      lpKnob("LP", pluginProcessor.apvts, "LPFILTER", 2500.0f, 20000.0f, "Hz", juce::Colours::grey, this),
      highFreq("High", pluginProcessor.apvts, "HIGHFREQ", 2000.0f, 20000.0f, "Hz", juce::Colours::blue, this),
      highGain("", pluginProcessor.apvts, "HIGHGAIN", -15.0f, 15.0f, "dB", juce::Colours::blue, this),
      midHighFreq("Mid High", pluginProcessor.apvts, "MIDHIGHFREQ", 800.0f, 8000.0f, "Hz", juce::Colours::turquoise, this),
      midHighGain("", pluginProcessor.apvts, "MIDHIGHGAIN", -15.0f, 15.0f, "dB", juce::Colours::turquoise, this),
      midLowFreq("Mid Low", pluginProcessor.apvts, "MIDLOWFREQ", 150.0f, 2500.0f, "Hz", juce::Colours::orange, this),
      midLowGain("", pluginProcessor.apvts, "MIDLOWGAIN", -15.0f, 15.0f, "dB", juce::Colours::orange, this),
      lowFreq("Low", pluginProcessor.apvts, "LOWFREQ", 40.0f, 250.0f, "Hz", juce::Colours::red, this),
      lowGain("", pluginProcessor.apvts, "LOWGAIN", -15.0f, 15.0f, "dB", juce::Colours::red, this),
      highBell("Bell", pluginProcessor.apvts, "HIGHBELL"),
      lowBell("Bell", pluginProcessor.apvts, "LOWBELL"),
      outputFader("Output", pluginProcessor.apvts, "OUTPUT")
{
    setSize(184 * 3, 514);

    addAndMakeVisible(leftChannel);
    addAndMakeVisible(rightChannel);
    addAndMakeVisible(inputKnob);
    addAndMakeVisible(micButton);
    addAndMakeVisible(hpKnob);
    addAndMakeVisible(lpKnob);
    addAndMakeVisible(highFreq);
    addAndMakeVisible(highGain);
    addAndMakeVisible(midHighFreq);
    addAndMakeVisible(midHighGain);
    addAndMakeVisible(midLowFreq);
    addAndMakeVisible(midLowGain);
    addAndMakeVisible(lowFreq);
    addAndMakeVisible(lowGain);
    addAndMakeVisible(highBell);
    addAndMakeVisible(lowBell);
    addAndMakeVisible(outputFader);
}

PluginEditor::~PluginEditor() = default;

void PluginEditor::paint(juce::Graphics& graphics) {
    juce::ColourGradient backgroundGradient(
        juce::Colours::darkgrey.brighter(0.1f),
        getWidth() / 2.0f, 0.0f,
        juce::Colours::darkgrey.darker(0.5f),
        getWidth() / 2.0f, (float)getHeight(),
        false
    );

    graphics.setGradientFill(backgroundGradient);
    graphics.fillAll();

    auto area = getLocalBounds();

    auto leftArea = area.removeFromLeft(184);
    auto midArea = area.removeFromLeft(184);
    auto rightArea = area;

    graphics.setColour(juce::Colours::grey);
    graphics.drawRect(leftArea, 2);
    graphics.drawRect(midArea, 2);
    graphics.drawRect(rightArea, 2);

    graphics.setColour(juce::Colours::whitesmoke);
    graphics.setFont(juce::Font(16.0f, juce::Font::bold));
    graphics.drawText("CS2516  ", getLocalBounds().removeFromTop(30).removeFromRight(140), juce::Justification::centredRight, false);
}

void PluginEditor::resized() {
    auto area = getLocalBounds();

    auto leftArea = area.removeFromLeft(184);
    auto midArea = area.removeFromLeft(184);
    auto rightArea = area;

    // Left section
    leftChannel.setBounds(35, 0, 50, 100);
    rightChannel.setBounds(95, 0, 50, 100);

    inputKnob.setBounds(40, 120, 100, 160);
    micButton.setBounds(138, 193, 35, 20);

    hpKnob.setBounds(40, 230, 100, 160);
    lpKnob.setBounds(40, 340, 100, 160);

    // Central section
    highFreq.setBounds(185, -15, 100, 160);
    highGain.setBounds(265, 35, 100, 160);
    highBell.setBounds(298, 48, 35, 20);
    midHighFreq.setBounds(185, 95, 100, 160);
    midHighGain.setBounds(265, 145, 100, 160);
    midLowFreq.setBounds(185, 205, 100, 160);
    midLowGain.setBounds(265, 255, 100, 160);
    lowFreq.setBounds(185, 315, 100, 160);
    lowGain.setBounds(265, 365, 100, 160);
    lowBell.setBounds(218, 448, 35, 20);

    // Right section
    outputFader.setBounds(400, 100, 120, 400);
}