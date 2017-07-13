/*
  ==============================================================================

    PositionOverlay.h
    Created: 12 Jul 2017 4:42:14pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <cmath>        // std::abs

class PositionOverlay : public Component,
private Timer
{
public:
    PositionOverlay (AudioTransportSource& transportSourceToUse)
    : transportSource (transportSourceToUse)
    {
        startTimer (40);
    }
    
    void paint (Graphics& g) override
    {
        const double duration = transportSource.getLengthInSeconds();
        
        if (duration > 0.0)
        {
            //Current position bar
            const double audioPosition = transportSource.getCurrentPosition();
            const float drawPosition = (audioPosition / duration) * getWidth();
            
            g.setColour (Colours::black);
            g.drawLine (drawPosition, 0.0f, drawPosition, (float) getHeight(), 2.0f);
            
            //Loop button pressed
            const float drawStartPosition = (g_loopStartPos / duration) * getWidth();
            const float drawEndPosition = (g_loopEndPos / duration) * getWidth();
            
            if(g_loopOn)
                paintRectangle(g, 0.0f, getWidth() );
            else
                paintRectangle(g, drawStartPosition, drawEndPosition);

        }
    }
    
    void paintRectangle (Graphics& g, float startPos, float endPos)
    {
        Rectangle<float> rect( startPos, 0.0f,
                              ( std::abs(endPos - startPos) ), (float) getHeight() );
        
        g.setColour (Colours::darkgrey);
        g.setOpacity (0.5f);
        g.drawRect( rect, 1.0f );
        g.fillRect(rect);
    }
    
    
    void mouseDown (const MouseEvent& event) override
    {
        
        const double duration = transportSource.getLengthInSeconds();
        
        if (duration > 0.0)
        {
            const double clickPosition = event.position.x;
            const double audioPosition = (clickPosition / getWidth()) * duration;
            
            g_loopStartPos = audioPosition;

            if( audioPosition < duration )
                transportSource.setPosition (audioPosition);
            
        }

    }
    
    void mouseDrag (const MouseEvent& event) override
    {
            const double duration = transportSource.getLengthInSeconds();
        
            mLastMouseXPosition = event.position.x;
            double lastAudioPosition = (mLastMouseXPosition / getWidth()) * duration;
            
            if( lastAudioPosition < duration )
                g_loopEndPos = lastAudioPosition;
        
            
            if( g_loopEndPos < g_loopStartPos )
            {
                double temp = g_loopStartPos;
                
                g_loopStartPos = g_loopEndPos;
                g_loopEndPos = temp;
            }

    }
    
    
private:
    void timerCallback() override
    {
        repaint();
    }
    
    AudioTransportSource& transportSource;

    double mLastMouseXPosition;

    
   // JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PositionOverlay)
};

