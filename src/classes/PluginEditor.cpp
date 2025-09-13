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
    addAndMakeVisible(vuMeter);
}

PluginEditor::~PluginEditor() = default;

void PluginEditor::paint(juce::Graphics& graphics) {
    graphics.fillAll(juce::Colours::darkgrey);
}

void PluginEditor::resized() {
    auto area = getLocalBounds();

    auto leftArea = area.removeFromLeft(184);
    auto midArea = area.removeFromLeft(184);
    auto rightArea = area;

    auto top = leftArea.removeFromTop(100);
    leftChannel.setBounds(top.removeFromLeft(90));
    rightChannel.setBounds(top);

    auto next = leftArea.removeFromTop(200);
    inputKnob.setBounds(next.removeFromTop(100));
    micButton.setBounds(next.removeFromTop(50));
    hpKnob.setBounds(next.removeFromTop(100));
    lpKnob.setBounds(next);

    auto eqGrid = juce::Grid();
    eqGrid.templateRows = { juce::Grid::TrackInfo(juce::Grid::Fr(1)), juce::Grid::TrackInfo(juce::Grid::Fr(1)), juce::Grid::TrackInfo(juce::Grid::Fr(1)) };
    eqGrid.templateColumns = { juce::Grid::TrackInfo(juce::Grid::Fr(1)), juce::Grid::TrackInfo(juce::Grid::Fr(1)) };

    eqGrid.items = {
        juce::GridItem(highFreq), juce::GridItem(highBell),
        juce::GridItem(highGain), juce::GridItem(midHighFreq),
        juce::GridItem(midHighGain), juce::GridItem(midLowFreq),
        juce::GridItem(midLowGain), juce::GridItem(lowFreq),
        juce::GridItem(lowGain), juce::GridItem(lowBell)
    };

    eqGrid.performLayout(midArea);

    auto topOut = rightArea.removeFromTop(400);
    outputFader.setBounds(topOut.removeFromLeft(90));
    vuMeter.setBounds(topOut);
}