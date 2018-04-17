/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <iostream>
using namespace std;

//==============================================================================
PeakMeterPluginAudioProcessorEditor::PeakMeterPluginAudioProcessorEditor (PeakMeterPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    startTimerHz(100);
    setSize (400, 300);
    addAndMakeVisible(m_pPeakMeterCh1);
    addAndMakeVisible(m_pPeakMeterCh2);
}

PeakMeterPluginAudioProcessorEditor::~PeakMeterPluginAudioProcessorEditor()
{

}

//==============================================================================
void PeakMeterPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);

}

void PeakMeterPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
//    const int border = 120;
//    m_pPeakMeterCh1.setBounds(border, 20, getWidth() - border, 20);
//    m_pPeakMeterCh2.setBounds(border, 20, getWidth() - border, 50);
    
    m_pPeakMeterCh1.setBounds(getWidth()/2 - 150, 50, 20, 150);
    m_pPeakMeterCh2.setBounds(getWidth()/2 - 120, 50, 20, 150);
    
}

void PeakMeterPluginAudioProcessorEditor::timerCallback() {
    m_pPeakMeterCh1.setPMValue(processor.getMaxPeakMeterValue(0));
    m_pPeakMeterCh2.setPMValue(processor.getMaxPeakMeterValue(1));
    
}

