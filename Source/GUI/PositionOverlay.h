/*
  ==============================================================================

    PositionOverlay.h
    Created: 12 Jul 2017 4:42:14pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../global.h"
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
        
            if( g_srcDurationInSec > 0.0 )
                paintLine(g, g_srcDurationInSec);
            
            //Loop button pressed - draw rectangle
            if( g_srcDurationInSec > 0.0 && g_loopOn )
            {
                const float drawStartPosition = (g_loopStartPos / g_srcDurationInSec) * getParentWidth () ;
                const float drawEndPosition = (g_loopEndPos / g_srcDurationInSec) * getParentWidth () ;
            
                //Draw loop rectangle for whole file vs region
                if(g_loopOnRecentClick)
                {
                    g_loopStartPos = 0;
                    g_loopEndPos = 0;
                    
                    paintRectangle(g, 0.0f, getWidth() );
                }
                else
                {
                    paintRectangle(g, drawStartPosition, drawEndPosition);
                    
                    //Loop selection is smaller than required min loop duration, toggle off loop button
                    if( std::abs(g_loopEndPos - g_loopStartPos) < g_minLoopDuration )
                        g_loopingButton.triggerClick();
                }
  
                
            }

        
    }
    
    //Current position bar
    void paintLine (Graphics& g, double duration)
    {
        g.setColour (Colours::black);
        g.drawLine (g_currDrawPosition, 0.0f, g_currDrawPosition, (float) getHeight(), 2.0f);
    }
    
    
    void paintRectangle (Graphics& g, float startPos, float endPos)
    {
        Rectangle<float> rect( startPos, 0.0f,
                              ( std::abs(endPos - startPos) ), (float) getHeight() );
        
        g.setColour (Colours::darkgrey);
        g.setOpacity (0.6f);
        g.drawRect( rect, 1.0f );
        g.fillRect(rect);
    }
    
    
    void resized() override
    {
        
    }
    
    
    void mouseDown (const MouseEvent& event) override
    {
    
        if (g_srcDurationInSec > 0.0)
        {
            const double clickPosition = event.position.x;
            const double audioPosition = (clickPosition / getParentWidth () ) * g_srcDurationInSec;
            
            std::cout<<"clickPosition: "<<clickPosition<<"  audioPosition: "<<audioPosition<<std::endl;

            if( audioPosition < g_srcDurationInSec )
            {
                transportSource.setPosition (audioPosition);
            
                g_loopStartPos = audioPosition;
            
                mMouseDownXPosition = audioPosition;
            }
            
            
        }

    }
    
    void mouseDrag (const MouseEvent& event) override
    {
        
            mLastMouseXPosition = event.position.x;
            double lastAudioPosition = (mLastMouseXPosition / getParentWidth () ) * g_srcDurationInSec;
            
            g_loopStartPos = mMouseDownXPosition;
            
            if( lastAudioPosition < g_srcDurationInSec )
                g_loopEndPos = lastAudioPosition;
        
            
            // Ensures StartPos < EndPos
            if( g_loopEndPos < g_loopStartPos )
            {
                double temp = g_loopStartPos;
                
                g_loopStartPos = g_loopEndPos;
                g_loopEndPos = temp;
            }
            
            //LoopDuration is long enough to loop
            if( std::abs( g_loopEndPos - g_loopStartPos ) >= g_minLoopDuration )
            {
                
                //LoopButton is off
                if( !g_loopOn )
                    g_loopingButton.triggerClick();
                
                
                g_loopOnRecentClick = false;
            }
     
    }
    
    
private:
    void timerCallback() override
    {
        repaint();
    }
    
    AudioTransportSource& transportSource;

    double mLastMouseXPosition;
    double mMouseDownXPosition;

    
   // JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PositionOverlay)
};

