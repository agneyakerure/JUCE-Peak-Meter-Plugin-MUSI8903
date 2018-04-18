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
    g.drawFittedText ("Peak Program Meter", 10, 2, 200, 20, Justification::left, 1);
    g.drawFittedText("dB", 50, 200, 20, 20, Justification::left, 1);
    g.drawFittedText("dB", 80, 200, 20, 20, Justification::left, 1);
    g.drawFittedText("L", 55, 30, 20, 20, Justification::left, 1);
    g.drawFittedText("R", 85, 30, 20, 20, Justification::left, 1);




}

void PeakMeterPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    m_pPeakMeterCh1.setBounds(50, 50, 20, 150);
    m_pPeakMeterCh2.setBounds(80, 50, 20, 150);
    
}

void PeakMeterPluginAudioProcessorEditor::timerCallback() {
    m_pPeakMeterCh1.setPMValue(processor.getMaxPeakMeterValue(0));
    m_pPeakMeterCh2.setPMValue(processor.getMaxPeakMeterValue(1));
    
}

