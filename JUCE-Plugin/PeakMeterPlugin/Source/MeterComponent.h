/*
  ==============================================================================

    MeterComponent.h
    Created: 17 Apr 2018 3:13:10pm
    Author:  Yi Wu

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MeterComponent    : public Component
{
public:
    MeterComponent()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~MeterComponent()
    {
    }

    void paint (Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

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

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }
    
    void setPMValue(float fPeakMeterValue)
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

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeterComponent)
    float m_fPeakMeterValueindB = 0.0f;
};
