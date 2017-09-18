/*
  ==============================================================================

    StatsBar.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class StatsBar    : public Component
{
public:
    StatsBar(float freq)
    {
        mFreq = freq;

    }

    ~StatsBar()
    {
    }

    void paint (Graphics& g) override
    {

//        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
        
        float startY = std::abs(getHeight() - mPercent*getHeight());
        
        if(mCount == 0)
        {
            paintRectangle(g, Colours::darkgrey, 0, getWidth(),
                           getHeight() - 0.005*getHeight(), 0.005*getHeight() );
        }
        else if(mPercent < 0.005)
        {
            paintRectangle(g, Colours::darkred, 0, getWidth(),
                           getHeight() - 0.005*getHeight(), 0.005*getHeight() );
        }
        else
        {
            paintRectangle(g, Colours::darkred, 0, getWidth(),
                           startY, std::abs(getHeight() - startY ) );
        }
        
        
        //Percent text within bars
        float percentValue = ( mPercent )*100.0;
        float percentRounded = static_cast<float>( static_cast<int>(percentValue * 10.) ) / 10.;
        String bartext = static_cast<String> (percentRounded) + "%";
        
        g.setColour (Colours::black);
        g.setFont (12.0f);
        g.drawText (bartext, getLocalBounds(),
                    Justification::centred, true);
    }

    void resized() override
    {
        

    }
    
    void paintRectangle (Graphics& g, Colour c,
                         float startX, float widthX, float startY, float heightY)
    {

        
        Rectangle<float> rect( startX, startY, widthX, heightY );
        
        g.setColour (c);
        g.setOpacity (0.5f);
        g.drawRect( rect, 1.0f );
        g.fillRect(rect);
    }
    
    void updateValues(float percent, int count)
    {
        mPercent = percent;
        mCount = count;
    }
    
    void repaintBar()
    {
        repaint();
    }

private:
    float mPercent = 0;
    float mFreq = 0;
    int mCount = 0;
    
};
