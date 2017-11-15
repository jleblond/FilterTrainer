/*
 ==============================================================================
 WaveformDisplay.h
 Author:  Jasmine Leblond-Chartrand
 ==============================================================================
 */

#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../LoopingAudioTransportSource.h"
#include "../global.h"

class WaveformDisplay : public Viewport,
public Button::Listener
{
public:
    WaveformDisplay(  int sourceSamplesPerThumbnailSample,
                    AudioFormatManager& formatManager,
                    AudioThumbnailCache& cache,
                    LoopingAudioTransportSource& transportSourceToUse
                    )
    
    :   thumbnailComp (sourceSamplesPerThumbnailSample, formatManager, cache, transportSourceToUse)
    {
        addAndMakeVisible (&thumbnailComp);
        
        setViewedComponent(&thumbnailComp);
        setScrollBarsShown(false, true);
        
        g_ZoomInButton.addListener(this);
        g_ZoomOutButton.addListener(this);
        
        g_ZoomInButton.setEnabled(false);
        g_ZoomOutButton.setEnabled(false);
        
    }
    
    ~WaveformDisplay()
    {
    }
    
    
    void resized() override
    {
        thumbnailComp.setBounds (getLocalBounds() );
        thumbnailComp.setSize( g_scaleZoomWaveform * thumbnailComp.getWidth(),
                              thumbnailComp.getHeight() );
  
    }
    
    void buttonClicked(Button* button) override
    {
        if (button == &g_ZoomInButton) zoomWaveform( g_scaleZoomWaveform + 1);
        if (button == &g_ZoomOutButton) zoomWaveform( g_scaleZoomWaveform - 1 );
    }
    
    //called on file load (openFile) from MainContentComponent
    void setWaveformDisplay(File& file)
    {
        thumbnailComp.setFile (file);
        mThumbnailCompWidth = thumbnailComp.getWidth();
    }
    
    
    void updatePositionOverlay()
    {
        
        thumbnailComp.updatePositionOverlay();
    }

    double getThumbnailWidth()
    {
        return thumbnailComp.getWidth();
    }
    

    void zoomWaveform(double scaleZoom)
    {
        if(scaleZoom <= 1)
        {
            g_ZoomOutButton.setEnabled(false);
            g_ZoomOutButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
        }
        else
        {
            g_ZoomOutButton.setEnabled(true);
            g_ZoomOutButton.setColour(TextButton::buttonColourId, Colours::white);
        }
        if(scaleZoom >=  g_srcDurationInSec/5 )
        {
            g_ZoomInButton.setEnabled(false);
            g_ZoomInButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
        }
        else
        {
            g_ZoomInButton.setEnabled(true);
            g_ZoomInButton.setColour(TextButton::buttonColourId, Colours::white);
        }
        
        thumbnailComp.centreWithSize( scaleZoom *  mThumbnailCompWidth,
                                     thumbnailComp.getHeight() );
        
        g_scaleZoomWaveform = scaleZoom;
        
        //update position overlay so grey selected rectangle can match new x component coordinates
        thumbnailComp.setZoomLoopSelection();
    
        
        std::cout<<"scale"<<scaleZoom<<std::endl;
    }

    void resetLoopSelection()
    {
        thumbnailComp.resetLoopSelection();
    }
    
private:
    AudioThumbnailComponent thumbnailComp;
    double mThumbnailCompWidth;
    
    
};
