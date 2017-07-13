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
            
            if (g_loopOn)
            {
                const float drawStartPosition = (g_loopStartPos / duration) * getWidth();
                const float drawEndPosition = (g_loopEndPos / duration) * getWidth();
                
                Rectangle<float> rect( drawStartPosition, 0.0f,
                               ( std::abs(drawEndPosition - drawStartPosition) ), (float) getHeight() );
                
                g.setColour (Colours::black);
                g.setOpacity (0.7f);
                g.drawRect( rect, 1.0f );
                g.fillRect(rect);
                
            }
            else
            {
                const double audioPosition = transportSource.getCurrentPosition();
                const float drawPosition = (audioPosition / duration) * getWidth();
                
                g.setColour (Colours::green);
                g.drawLine (drawPosition, 0.0f, drawPosition, (float) getHeight(), 2.0f);
            }
            
        }
    }
    
    
    void mouseDown (const MouseEvent& event) override
    {
        
        const double duration = transportSource.getLengthInSeconds();
        
        if (duration > 0.0)
        {
            const double clickPosition = event.position.x;
            const double audioPosition = (clickPosition / getWidth()) * duration;
            
            transportSource.setPosition (audioPosition);

            
            if (g_loopOn)
            {
                g_loopStartPos = audioPosition;
                std::cout<<"loopstartpos "<<g_loopStartPos<<std::endl;
               // mouseDrag (event);
            }

            
        }

    }
    
    void mouseDrag (const MouseEvent& event) override
    {
        if (g_loopOn)
        {
            const double duration = transportSource.getLengthInSeconds();
            
            //lastMousePosition = event.position;
            mLastMouseXPosition = event.position.x;
            double lastAudioPosition = (mLastMouseXPosition / getWidth()) * duration;
            
            g_loopEndPos = lastAudioPosition;
            std::cout<<"g_loopEndPos "<<g_loopEndPos<<std::endl;
            
            if( g_loopEndPos < g_loopStartPos )
            {
                double temp = g_loopStartPos;
                
                g_loopStartPos = g_loopEndPos;
                g_loopEndPos = temp;
            }

        }

    }
    
    void mouseUp (const MouseEvent& event) override
    {

    }
    
    
private:
    void timerCallback() override
    {
        repaint();
    }
    
    AudioTransportSource& transportSource;
    //double mClickMouseXPosition;
    double mLastMouseXPosition;
    //Point<float> lastMousePosition;
    
   // JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PositionOverlay)
};

