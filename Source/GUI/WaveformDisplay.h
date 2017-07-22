/*
 ==============================================================================
 WaveformDisplay.h
 Created: 13 Jul 2017 11:30:34pm
 Author:  Jasmine Leblond-Chartrand
 ==============================================================================
 */

#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../global.h"

class WaveformDisplay : public Viewport,
public Button::Listener
{
public:
    WaveformDisplay(  int sourceSamplesPerThumbnailSample,
                    AudioFormatManager& formatManager,
                    AudioThumbnailCache& cache,
                    AudioTransportSource& transportSourceToUse
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
    };
    
    void paint(Graphics& g) override
    {
        g.fillAll(Colours::white);
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
        mThumbnailCompHeight = thumbnailComp.getHeight();
    }
    
    
    double getThumbnailWidth()
    {
        return thumbnailComp.getWidth();
    }
    
    
    void zoomWaveform(double scaleZoom)
    {
        if(scaleZoom <= 1)
            g_ZoomOutButton.setEnabled(false);
        else
            g_ZoomOutButton.setEnabled(true);
        
        if(scaleZoom >=  g_srcDurationInSec/5 )
            g_ZoomInButton.setEnabled(false);
        else
            g_ZoomInButton.setEnabled(true);
        
        
        
        thumbnailComp.centreWithSize( scaleZoom *  mThumbnailCompWidth,
                                     thumbnailComp.getHeight() );
        
        
        g_scaleZoomWaveform = scaleZoom;
        
        std::cout<<"scale"<<scaleZoom<<std::endl;
    }
    
    
    void updateDisplay()
    {
        
    }
    
private:
    AudioThumbnailComponent thumbnailComp;
    
    double mThumbnailCompWidth;
    double mThumbnailCompHeight;
    
};
