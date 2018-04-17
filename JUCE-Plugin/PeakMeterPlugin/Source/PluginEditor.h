/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "MeterComponent.h"


//==============================================================================
/**
*/
class PeakMeterPluginAudioProcessorEditor  : public AudioProcessorEditor, public Timer
{
public:
    PeakMeterPluginAudioProcessorEditor (PeakMeterPluginAudioProcessor&);
    ~PeakMeterPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PeakMeterPluginAudioProcessor& processor;
    
    MeterComponent m_pPeakMeterCh1;
    MeterComponent m_pPeakMeterCh2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PeakMeterPluginAudioProcessorEditor)
};
