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

class PositionOverlay : public Component,
                        public Button::Listener
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
        g_loopingButton.addListener(this);
    }
    
    void resetSelection(){
        startPosition = 0;
        endPosition = getWidth();
        transportSource.resetPosition();
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
    
    
    void paint (Graphics& g) override
    {
        const double duration = transportSource.getLengthInSeconds();
        
        if (duration > 0.0)
        {
            const double audioPosition = transportSource.getCurrentPosition();
            const float drawPosition = (audioPosition / duration) * getWidth();
            
            g.setColour (Colours::black);
            g.drawLine (drawPosition, 0.0f, drawPosition, (float) getHeight(), 2.0f);
            
            if(g_loopOn)
            {
                g.setColour (Colours::darkslateblue);
                g.drawLine (startPosition, 0.0f, startPosition, (float) getHeight(), 2.0f);
                g.drawLine (endPosition, 0.0f, endPosition, (float) getHeight(), 2.0f);
                
                
                float rectStart = startPosition;
                float rectEnd = endPosition;
                
                if( rectEnd < rectStart)
                {
                    float temp = rectStart;
                    rectStart = rectEnd;
                    rectEnd = temp;
                }
                
                paintRectangle(g, Colours::darkgrey, rectStart, rectEnd);
            }
            
        }
        
    }
    
    void mouseDrag (const MouseEvent& event) override {
        const double duration = transportSource.getLengthInSeconds();
        
        if (duration > 0.0 && isMouseDown)
        {
            endPosition = event.position.x;
            if(endPosition > getWidth()){
                endPosition = getWidth();
            }
        }
    }
    void mouseMove (const MouseEvent& event) override {
        const double duration = transportSource.getLengthInSeconds();
        
        if (duration > 0.0 && isMouseDown)
        {
            endPosition = event.position.x;
            if(endPosition > getWidth()){
                endPosition = getWidth();
            }
        }
    }
    
    void mouseUp (const MouseEvent& event) override {
        const double duration = transportSource.getLengthInSeconds();
        
        if (duration > 0.0 && isMouseDown)
        {
            isMouseDown = false;
            endPosition = event.position.x;
            if(endPosition > getWidth()){
                endPosition = getWidth();
            }
            
            
            if( endPosition < startPosition )
            {
                float temp = startPosition;
                startPosition = endPosition;
                endPosition = temp;
                
                const double audioStartPosition = (startPosition / getWidth()) * duration;
                transportSource.setPosition (audioStartPosition);
            }
            
            
            //LOOP END POINT
            if(g_loopOn)
            {
                double audioEndPosition = (endPosition / getWidth()) * duration;
                
                    const double startingPosition = (startPosition / getWidth()) * duration;
                
                if( std::abs(audioEndPosition - startingPosition) < g_loopMinDuration )
                {
                    endPosition = getWidth();
                    audioEndPosition = (endPosition / getWidth()) * duration;
                    
                    g_loopingButton.triggerClick();
                }
                
                transportSource.setEndPosition(audioEndPosition);
            }
            else
            {
                transportSource.setEndPosition();
            }
            
            
        }
    }
    void mouseDown (const MouseEvent& event) override
    {
        const double duration = transportSource.getLengthInSeconds();
        isMouseDown = true;
        if (duration > 0.0)
        {
            startPosition = event.position.x;
            const double audioStartPosition = (startPosition / getWidth()) * duration;
            transportSource.setPosition (audioStartPosition);
  
        }
    }
    
    
    
    void buttonClicked (Button* button) override
    {
        if (button == &g_loopingButton) loopButtonChanged();
    }
    
    void loopButtonChanged()
    {
        std::cout<< g_loopOn;
        
        g_loopOn = !g_loopOn;
        
        if(g_loopOn)
        {
            g_loopingButton.setColour(TextButton::buttonColourId, Colours::orange);
           //transportSource.setLooping(true);
        }
        else
        {
            g_loopingButton.setColour(TextButton::buttonColourId,
                                      getLookAndFeel().findColour (ResizableWindow::backgroundColourId) );
            //transportSource.setLooping(false);
        }
        
        
    }
    
private:
    LoopingAudioTransportSource& transportSource;
    
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PositionOverlay)
};
