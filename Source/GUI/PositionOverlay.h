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
        endPosition = getParentWidth();
        transportSource.resetPosition();
    }
    
    void setZoomPosition(double zoomScale)
    {
        startPosition *= zoomScale;
        endPosition *= zoomScale;
         std::cout<<"startPos: "<<startPosition;
        std::cout<<" endPos: "<<endPosition<<std::endl;
        
        repaint();
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
            const float drawPosition = (audioPosition / duration) * getParentWidth();
            
            g.setColour (Colours::black);
            g.drawLine (drawPosition, 0.0f, drawPosition, (float) getHeight(), 2.0f);
            
            
            
            
            if(g_loopOn)
            {
                
                g.setColour (Colours::darkslateblue);
                g.drawLine (startPosition, 0.0f, startPosition, (float) getHeight(), 2.0f);
                g.drawLine (endPosition, 0.0f, endPosition, (float) getHeight(), 2.0f);
                
                std::cout<<"startPos: "<<startPosition;
                std::cout<<" endPos: "<<endPosition<<std::endl;
                
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
            if(endPosition > getParentWidth()){
                endPosition = getParentWidth();
            }
        }
    }
    void mouseMove (const MouseEvent& event) override {
        const double duration = transportSource.getLengthInSeconds();
        
        if (duration > 0.0 && isMouseDown)
        {
            endPosition = event.position.x;
            if(endPosition > getParentWidth()){
                endPosition = getParentWidth();
            }
        }
    }
    
    void mouseUp (const MouseEvent& event) override {
        const double duration = transportSource.getLengthInSeconds();
        
        if (duration > 0.0 && isMouseDown)
        {
            isMouseDown = false;
            endPosition = event.position.x;
            if(endPosition > getParentWidth()){
                endPosition = getParentWidth();
            }
            
            
            if( endPosition < startPosition )
            {
                float temp = startPosition;
                startPosition = endPosition;
                endPosition = temp;
                
                const double audioStartPosition = (startPosition / getParentWidth()) * duration;
                transportSource.setPosition (audioStartPosition);
            }
    
            
            //LOOP END POINT
            if(g_loopOn)
            {
                double audioEndPosition = (endPosition / getParentWidth()) * duration;
                
                    const double startingPosition = (startPosition / getParentWidth()) * duration;
                
                if( std::abs(audioEndPosition - startingPosition) < g_loopMinDuration )
                {
                    endPosition = getParentWidth();
                    audioEndPosition = (endPosition / getParentWidth()) * duration;
                    
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
            const double audioStartPosition = (startPosition / getParentWidth()) * duration;
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
