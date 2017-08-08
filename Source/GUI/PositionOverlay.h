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
#include "../LoopingAudioTransportSource.h"
#include <cmath>        // std::abs

class PositionOverlay : public Component
//private Timer
{
    float startPosition;
    float endPosition;
    bool isMouseDown;
    
public:
    PositionOverlay (LoopingAudioTransportSource& transportSourceToUse)
    : transportSource (transportSourceToUse)
    {
            //startTimer (40);
    }
    
    void resetSelection(){
        startPosition = 0;
        endPosition = getWidth();
        transportSource.resetPosition();
    }
    void paint (Graphics& g) override
    {
        const double duration = transportSource.getLengthInSeconds();
        
        if (duration > 0.0)
        {
            const double audioPosition = transportSource.getCurrentPosition();
            const float drawPosition = (audioPosition / duration) * getWidth();
            
            g.setColour (Colours::green);
            g.drawLine (drawPosition, 0.0f, drawPosition, (float) getHeight(), 2.0f);
            
            
            
            g.setColour (Colours::darkred);
            
            //Loop button pressed
//            const float drawStartPosition = (g_loopStartPos / duration) * getWidth();
//            const float drawEndPosition = (g_loopEndPos / duration) * getWidth();
            
            if(g_loopOn)
                paintRectangle(g, Colours::darkgrey, startPosition, endPosition);
            
            
            
//            
//            g.drawLine (startPosition, 0.0f, startPosition, (float) getHeight(), 2.0f);
//            g.drawLine (endPosition, 0.0f, endPosition, (float) getHeight(), 2.0f);
        }
    }
    
    void paintRectangle (Graphics& g, Colour c, float startPos, float endPos)
    {
        Rectangle<float> rect( startPos, 0.0f,
                              ( std::abs(endPos - startPos) ), (float) getHeight() );
        
        g.setColour (c);
        g.setOpacity (0.5f);
        g.drawRect( rect, 1.0f );
        g.fillRect(rect);
    }
    
    void mouseDrag (const MouseEvent& event) override {
        const double duration = transportSource.getLengthInSeconds();
        
        if ( duration > 0.0 && isMouseDown)
        {
            endPosition = event.position.x;
            if(endPosition > getWidth()){
                endPosition = getWidth();
            }
        }
    }
    void mouseMove (const MouseEvent& event) override {
        const double duration = transportSource.getLengthInSeconds();
        
        if ( duration > 0.0 && isMouseDown)
        {
            endPosition = event.position.x;
            if(endPosition > getWidth()){
                endPosition = getWidth();
            }
        }
    }
    
    void mouseUp (const MouseEvent& event) override {
        const double duration = transportSource.getLengthInSeconds();
        
        if ( duration > 0.0 && isMouseDown)
        {
            isMouseDown = false;
            endPosition = event.position.x;
            if(endPosition > getWidth()){
                endPosition = getWidth();
            }
            const double audioPosition = (endPosition / getWidth()) * duration;
            
           if(g_loopOn)
               transportSource.setEndPosition(audioPosition);
            
        }
    }
    void mouseDown (const MouseEvent& event) override
    {
        const double duration = transportSource.getLengthInSeconds();
        isMouseDown = true;
        if (duration > 0.0)
        {
            startPosition = event.position.x;
            const double audioPosition = (startPosition / getWidth()) * duration;
           
            transportSource.setPosition (audioPosition);
            
             //  transportSource.setNextPos (audioPosition);
        }
    }
            

    
private:
    LoopingAudioTransportSource& transportSource;
    
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PositionOverlay)
};
