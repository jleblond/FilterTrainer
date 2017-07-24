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

class WaveformDisplay : public Viewport
//public Button::Listener
{
public:
    WaveformDisplay(  int sourceSamplesPerThumbnailSample,
                    AudioFormatManager& formatManager,
                    AudioThumbnailCache& cache,
                    AudioTransportSource& transportSourceToUse
                    )
    
    :   thumbnailComp (sourceSamplesPerThumbnailSample, formatManager, cache),
        positionOverlay (transportSourceToUse)
    {
        addAndMakeVisible (&thumbnailComp);
        addAndMakeVisible (&positionOverlay);
    }
    
    ~WaveformDisplay()
    {
    }
    
    
    void resized() override
    {
        thumbnailComp.setBounds (getLocalBounds() );
        positionOverlay.setBounds ( getLocalBounds() );
  
        
    }

    double getThumbnailWidth()
    {
        return thumbnailComp.getWidth();
    }
    
    
    //called on file load (openFile) from MainContentComponent
    void setWaveformDisplay(File& file)
    {
        thumbnailComp.setFile (file);
    }
    
    
private:
    AudioThumbnailComponent thumbnailComp;
    PositionOverlay positionOverlay;
    
    
};
