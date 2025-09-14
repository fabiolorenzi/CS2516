#include "PluginEditor.h"
#include "PluginProcessor.h"

PluginEditor::PluginEditor(PluginProcessor& pluginProcessor)
    : AudioProcessorEditor(&pluginProcessor),
      pluginProcessor(pluginProcessor),
      leftChannel("Left", pluginProcessor.apvts, "LEFTCHANNEL"),
      rightChannel("Right", pluginProcessor.apvts, "RIGHTCHANNEL"),
      inputKnob("Input", pluginProcessor.apvts, "INPUT"),
      micButton("Mic", pluginProcessor.apvts, "MICMODE"),
      hpKnob("HP", pluginProcessor.apvts, "HPFILTER"),
      lpKnob("LP", pluginProcessor.apvts, "LPFILTER"),
      highFreq("High Freq", pluginProcessor.apvts, "HIGHFREQ"),
      highGain("High Gain", pluginProcessor.apvts, "HIGHGAIN"),
      midHighFreq("MidHigh Freq", pluginProcessor.apvts, "MIDHIGHFREQ"),
      midHighGain("MidHigh Gain", pluginProcessor.apvts, "MIDHIGHGAIN"),
      midLowFreq("MidLow Freq", pluginProcessor.apvts, "MIDLOWFREQ"),
      midLowGain("MidLow Gain", pluginProcessor.apvts, "MIDLOWGAIN"),
      lowFreq("Low Freq", pluginProcessor.apvts, "LOWFREQ"),
      lowGain("Low Gain", pluginProcessor.apvts, "LOWGAIN"),
      highBell("High Bell", pluginProcessor.apvts, "HIGHBELL"),
      lowBell("Low Bell", pluginProcessor.apvts, "LOWBELL"),
      outputFader("Output", pluginProcessor.apvts, "OUTPUT")
{
    setSize(184 * 3, 514);

    addAndMakeVisible(leftChannel);
    addAndMakeVisible(rightChannel);
    addAndMakeVisible(inputKnob);
    /*addAndMakeVisible(micButton);
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
    addAndMakeVisible(vuMeter);*/
}

PluginEditor::~PluginEditor() = default;

void PluginEditor::paint(juce::Graphics& graphics) {
    graphics.fillAll(juce::Colours::darkgrey);

    auto area = getLocalBounds();

    auto leftArea = area.removeFromLeft(184);
    auto midArea = area.removeFromLeft(184);
    auto rightArea = area;

    graphics.setColour(juce::Colours::grey);
    graphics.drawRect(leftArea, 2);
    graphics.drawRect(midArea, 2);
    graphics.drawRect(rightArea, 2);
}

void PluginEditor::resized() {
    auto area = getLocalBounds();

    auto leftArea = area.removeFromLeft(184);
    auto midArea = area.removeFromLeft(184);
    auto rightArea = area;

    {
        leftChannel.setBounds(35, 0, 50, 100);
        rightChannel.setBounds(95, 0, 50, 100);

        inputKnob.setBounds(40, 120, 100, 160);

        /*auto buttonsArea = leftArea.removeFromTop(20);
        micButton.setBounds(leftArea.removeFromTop(40));
        hpKnob.setBounds(leftArea.removeFromTop(80));
        lpKnob.setBounds(leftArea.removeFromTop(80));*/
    }

    // ==== MIDDLE COLUMN (Vertical EQ) ====
    /*{
        int knobHeight = 50;
        int spacing = 10;
        int y = 0;

        auto placeKnob = [&](juce::Component& comp) {
            comp.setBounds(10, y, midArea.getWidth() - 20, knobHeight);
            y += knobHeight + spacing;
        };

        placeKnob(highFreq);
        placeKnob(highBell);
        placeKnob(highGain);
        placeKnob(midHighFreq);
        placeKnob(midHighGain);
        placeKnob(midLowFreq);
        placeKnob(midLowGain);
        placeKnob(lowFreq);
        placeKnob(lowGain);
        placeKnob(lowBell);
    }

    // ==== RIGHT COLUMN (VU Meter + Fader) ====
    {
        outputFader.setBounds(rightArea.withTrimmedTop(10).reduced(40, 10));
    }*/
}