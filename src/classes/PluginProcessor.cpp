#include "PluginProcessor.h"

PluginProcessor::PluginProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
    ), apvts(*this, nullptr, "Parameters", createParameterLayout()) {
    noiseDist = std::uniform_real_distribution<float>(-1.0f, 1.0f);
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

void PluginProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    juce::dsp::ProcessSpec spec {
        sampleRate,
        (juce::uint32)samplesPerBlock,
        (juce::uint32)getMainBusNumOutputChannels()
    };

    for (int channel = 0; channel < 2; ++channel) {
        colourHPFilter[channel].prepare(spec);
        colourLSFilter[channel].prepare(spec);
        colourLPFilter[channel].prepare(spec);
        hpFilter[channel].prepare(spec);
        lpFilter[channel].prepare(spec);
    }

    randomEngine.seed(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
}

void PluginProcessor::releaseResources() {}

bool PluginProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo() && (layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo() 
        || layouts.getMainInputChannelSet() == juce::AudioChannelSet::disabled());
}

void PluginProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    juce::ScopedNoDenormals noDenormals;

    auto* leftChannelParam  = apvts.getRawParameterValue("LEFTCHANNEL");
    auto* rightChannelParam = apvts.getRawParameterValue("RIGHTCHANNEL");
    auto* inputGainParam = apvts.getRawParameterValue("INPUT");
    auto* micModeParam = apvts.getRawParameterValue("MICMODE");
    auto* outputGainParam = apvts.getRawParameterValue("OUTPUT");

    leftChannel = static_cast<int>(leftChannelParam->load());
    rightChannel = static_cast<int>(rightChannelParam->load());
    float inputGain = juce::Decibels::decibelsToGain(inputGainParam->load());
    bool micMode = micModeParam->load() > 0.5f;
    float hpFreq = apvts.getRawParameterValue("HPFILTER")->load();
    float lpFreq = apvts.getRawParameterValue("LPFILTER")->load();
    float outputGain = outputGainParam->load() <= -99.0f ? 0.0f : juce::Decibels::decibelsToGain(outputGainParam->load());

    float micPreGain = micMode ? juce::Decibels::decibelsToGain(30.0f) : 1.0f;
    float micPostGain = micMode ? juce::Decibels::decibelsToGain(-18.0f) : 1.0f;

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        float* channelData = buffer.getWritePointer(channel);
        const SaturationSetting& saturationSetting = (channel == 0)
            ? channelSettingsManager.getSaturationSetting(leftChannel)
            : channelSettingsManager.getSaturationSetting(rightChannel);

        const ColourSetting& colourSetting = (channel == 0)
            ? channelSettingsManager.getColourSetting(leftChannel)
            : channelSettingsManager.getColourSetting(rightChannel);

        const float& noiseLevelSetting = (channel == 0)
            ? channelSettingsManager.getNoiseLevelSetting(leftChannel)
            : channelSettingsManager.getNoiseLevelSetting(rightChannel);

        updateFilters(colourSetting, channel, getSampleRate());

        *hpFilter[channel].state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(getSampleRate(), hpFreq, std::sqrt(0.5f));
        *lpFilter[channel].state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), lpFreq, std::sqrt(0.5f));

        juce::dsp::AudioBlock<float> block(buffer);
        auto singleChannelBlock = block.getSingleChannelBlock(channel);

        for (int i = 0; i < singleChannelBlock.getNumSamples(); ++i) {
            float sample = channelData[i];
            sample *= inputGain;
            sample *= micPreGain;
            sample = applySaturation(sample, saturationSetting);

            float noiseSample = noiseDist(randomEngine) * noiseLevelSetting;
            singleChannelBlock.getChannelPointer(0)[i] = sample + noiseSample;
        }

        juce::dsp::ProcessContextReplacing<float> context(singleChannelBlock);
        colourHPFilter[channel].process(context);
        colourLSFilter[channel].process(context);
        colourLPFilter[channel].process(context);
        hpFilter[channel].process(context);
        lpFilter[channel].process(context);

        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            channelData[i] *= micPostGain * outputGain;
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

    layout.add(std::make_unique<juce::AudioParameterInt>("LEFTCHANNEL", "Left Preset", 1, 16, 1));
    layout.add(std::make_unique<juce::AudioParameterInt>("RIGHTCHANNEL", "Right Preset", 1, 16, 1));
    layout.add(std::make_unique<juce::AudioParameterFloat>("INPUT", "Input Gain", juce::NormalisableRange<float>(0.0f, 24.0f, 0.1f), 0.0f));
    layout.add(std::make_unique<juce::AudioParameterBool>("MICMODE", "Mic Mode", false));
    layout.add(std::make_unique<juce::AudioParameterFloat>("HPFILTER", "Highpass", juce::NormalisableRange<float>(16.0f, 320.0f, 1.0f), 10.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("LPFILTER", "Lowpass", juce::NormalisableRange<float>(2500.0f, 20000.0f, 1.0f), 20000.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("OUTPUT", "Output Gain", juce::NormalisableRange<float>(-100.0f, 6.0f, 0.1f), 0.0f));

    return layout;
}

float PluginProcessor::applySaturation(float sample, const SaturationSetting& saturationSetting) {
    const float asymBias = 0.1f;
    float sampleBias = sample + saturationSetting.asymBias;
    float oddHarmonics = std::tanh(sampleBias);

    float squared = sampleBias * sampleBias;
    float evenHarmonics = (squared / (1.0f + squared)) * ((sampleBias >= 0.0f) ? 1.0f : -1.0f);
    float out = saturationSetting.oddMix * oddHarmonics + saturationSetting.evenMix * evenHarmonics;

    out -= asymBias * 0.1f;
    return out;
}

void PluginProcessor::updateFilters(const ColourSetting& colourSetting, int channel, double sampleRate) {
    using Coeffs = juce::dsp::IIR::Coefficients<float>;

    *colourHPFilter[channel].state = *Coeffs::makeHighPass(sampleRate, colourSetting.hpFreq, juce::MathConstants<float>::sqrt2);
    *colourLSFilter[channel].state = *Coeffs::makeLowShelf(sampleRate, colourSetting.lsFreq, colourSetting.lsQ, juce::Decibels::decibelsToGain(colourSetting.lsGain));
    *colourLPFilter[channel].state = *Coeffs::makeLowPass(sampleRate, colourSetting.lpFreq, 0.5f);
}



juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}