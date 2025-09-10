#include "PluginProcessor.h"

PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
    ), apvts(*this, nullptr, "Parameters", createParameterLayout()) {
}

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
    
    auto* inputGainParam = apvts.getRawParameterValue("INPUT");
    auto* micModeParam = apvts.getRawParameterValue("MICMODE");
    auto* outputGainParam = apvts.getRawParameterValue("OUTPUT");

    jassert(inputGainParam != nullptr);
    jassert(micModeParam != nullptr);
    jassert(outputGainParam != nullptr);

    float inputGain = juce::Decibels::decibelsToGain(inputGainParam->load());
    bool micMode = micModeParam->load() > 0.5f;
    float outputGain = outputGainParam->load() <= -99.0f ? 0.0f : juce::Decibels::decibelsToGain(outputGainParam->load());

    float micPreGain = micMode ? juce::Decibels::decibelsToGain(40.0f) : 1.0f;
    float micPostGain = micMode ? juce::Decibels::decibelsToGain(-18.0f) : 1.0f;

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        float* channelData = buffer.getWritePointer(channel);
        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            float sample = channelData[i];
            sample *= inputGain;
            sample *= micPreGain;
            sample = applySaturation(sample);
            sample *= micPostGain;
            sample *= outputGain;
            channelData[i] = sample;
        }
    }
}

bool PluginProcessor::hasEditor() const {
    return true;
}

juce::AudioProcessorEditor* PluginProcessor::createEditor() {
    return new juce::GenericAudioProcessorEditor(*this);
}

void PluginProcessor::getStateInformation(juce::MemoryBlock& destData) {
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PluginProcessor::setStateInformation(const void* data, int sizeInBytes) {
    if (data != nullptr && sizeInBytes > 0) {
        std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
        if (xmlState != nullptr && xmlState->hasTagName(apvts.state.getType())) {
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
        }
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout PluginProcessor::createParameterLayout() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>("INPUT", "Input Gain", juce::NormalisableRange<float>(0.0f, 24.0f, 0.1f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterBool>("MICMODE", "Mic Mode", false));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OUTPUT", "Output Gain", juce::NormalisableRange<float>(-100.0f, 6.0f, 0.1f), 0.0f));

    return layout;
}

float PluginProcessor::applySaturation(float sample) {
    const float asymBias = 0.1f;
    float sampleBias = sample + asymBias;
    float oddHarmonics = std::tanh(sampleBias);

    float squared = sampleBias * sampleBias;
    float evenHarmonics = (squared / (1.0f + squared)) * ((sampleBias >= 0.0f) ? 1.0f : -1.0f);
    float out = 0.8f * oddHarmonics + 0.2f * evenHarmonics;

    out -= asymBias * 0.1f;
    return out;
}



juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}