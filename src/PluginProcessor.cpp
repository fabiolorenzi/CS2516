#include "PluginProcessor.h"

PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
) {}

PluginProcessor::~PluginProcessor() = default;

const juce::String PluginProcessor::getName() const {
    return "CS2516";
}

bool PluginProcessor::acceptsMidi() const {
    return false;
}

bool PluginProcessor::producesMidi() const {
    return false;
}

bool PluginProcessor::isMidiEffect() const {
    return false;
}

double PluginProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int PluginProcessor::getNumPrograms() {
    return 1;
}

int PluginProcessor::getCurrentProgram() {
    return 0;
}

void PluginProcessor::setCurrentProgram(int index) {}

const juce::String PluginProcessor::getProgramName(int) {
    return {};
}

void PluginProcessor::changeProgramName(int index, const juce::String& newName) {}

void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {}

void PluginProcessor::releaseResources() {}

bool PluginProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo() && (layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo() 
        || layouts.getMainInputChannelSet() == juce::AudioChannelSet::disabled());
}

void PluginProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer) {
    juce::ScopedNoDenormals noDenormals;
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        buffer.clear(channel, 0, buffer.getNumSamples());
    }
}

bool PluginProcessor::hasEditor() const {
    return false;
}

juce::AudioProcessorEditor* PluginProcessor::createEditor() {
    return nullptr;
}

void PluginProcessor::getStateInformation(juce::MemoryBlock& destData) {
    juce::MemoryOutputStream(destData, true).writeInt(0);
}

void PluginProcessor::setStateInformation(const void* data, int sizeInBytes) {
    juce::MemoryInputStream stream(data, static_cast<size_t>(sizeInBytes), false);
    stream.readInt();
}



juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}