/*
  ==============================================================================

    MeterComponent.h
    Created: 17 Apr 2018 10:45:30am
    Author:  Yi Wu

  ==============================================================================
*/

#ifndef METERCOMPONENT_H
#define METERCOMPONENT_H

#include "../JuceLibraryCode/JuceHeader.h"

class MeterComponent: public Component
{
public:
    MeterComponent();
    ~MeterComponent();

    void paint(Graphics& g);
    void setPMValue(float fPeakMeterValue);
    
private:
    float m_fPeakMeterValueindB = 0.0f;
};

MeterComponent::MeterComponent()
{
    
}

MeterComponent::~MeterComponent()
{
    
}

void MeterComponent::paint(Graphics& g)
{
    g.fillAll(Colours::black);
    if (m_fPeakMeterValueindB > -12.0f)
    {
        g.setColour(Colours::green);
        int position_x = 0;
        int position_y = getHeight() * (-m_fPeakMeterValueindB/12);
        int width = getWidth();
        int height = getHeight() - position_y;
        g.fillRect(position_x, position_y, width, height);
    }
    
}


void MeterComponent::setPMValue(float fPeakMeterValue)
{
    if (fPeakMeterValue > 1)
    {
        m_fPeakMeterValueindB = 0;
    }
    else
    {
        m_fPeakMeterValueindB = 20*log10f(fPeakMeterValue);
    }
    repaint();
}



#endif
