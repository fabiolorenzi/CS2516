#pragma once

#include <JuceHeader.h>
#include "classes/ChannelSelector.h"
#include "classes/CustomButton.h"
#include "classes/Fader.h"
#include "classes/Knob.h"
#include "classes/VuMeter.h"

class PluginProcessor;

class PluginEditor : public juce::AudioProcessorEditor {
    public:
        PluginEditor(PluginProcessor& pluginProcessor);
        ~PluginEditor() override;
        void paint(juce::Graphics& graphics) override;
        void resized() override;
    
    private:
        PluginProcessor& pluginProcessor;
        ChannelSelector leftChannel;
        ChannelSelector rightChannel;
        Knob inputKnob;
        CustomButton micButton;
        Knob hpKnob;
        Knob lpKnob;
        Knob highFreq;
        Knob highGain;
        Knob midHighFreq;
        Knob midHighGain;
        Knob midLowFreq;
        Knob midLowGain;
        Knob lowFreq;
        Knob lowGain;
        CustomButton highBell;
        CustomButton lowBell;
        Fader outputFader;
        VuMeter vuMeter;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor);
};