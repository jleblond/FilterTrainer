/*
  ==============================================================================

    AudioThumbnailComponent.h
    Created: 12 Jul 2017 4:41:30pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once


#include "../JuceLibraryCode/JuceHeader.h"
#include "PositionOverlay.h"


class AudioThumbnailComponent : public Component,
private ChangeListener
{
public:
    AudioThumbnailComponent (int sourceSamplesPerThumbnailSample,
                             AudioFormatManager& formatManager,
                             AudioThumbnailCache& cache,
                             LoopingAudioTransportSource& transportSourceToUse
                             )
    : thumbnail (sourceSamplesPerThumbnailSample, formatManager, cache),
    positionOverlay (transportSourceToUse)
    {
        thumbnail.addChangeListener (this);
        
        addAndMakeVisible (&positionOverlay);
        
        //        mPositionOverlayWidth = positionOverlay.getWidth();
        //        mPositionOverlayHeight = positionOverlay.getHeight();
        
    }
    
    void resized() override
    {
        positionOverlay.setBounds ( getLocalBounds() );
        
        positionOverlay.setSize( g_scaleZoomWaveform *  positionOverlay.getWidth(),
                                positionOverlay.getHeight() );
        
    }
    
    void setFile (const File& file)
    {
        thumbnail.setSource (new FileInputSource (file));
    }
    
    void paint (Graphics& g) override
    {
        if (thumbnail.getNumChannels() == 0)
            paintIfNoFileLoaded (g);
        else
            paintIfFileLoaded (g);
    }
    
    void paintIfNoFileLoaded (Graphics& g)
    {
        g.fillAll (Colours::white);
        g.setColour (Colours::darkgrey);
        g.drawFittedText ("No File Loaded", getLocalBounds(), Justification::centred, 1.0f);
    }
    
    void paintIfFileLoaded (Graphics& g)
    {
        g.fillAll(Colours::white);
        
        g.setColour (Colours::blue);
        thumbnail.drawChannels (g, getLocalBounds(), 0.0, thumbnail.getTotalLength(), 1.0f);
    }
    
    void changeListenerCallback (ChangeBroadcaster* source) override
    {
        if (source == &thumbnail)
            thumbnailChanged();
    }
    
    void updatePositionOverlay()
    {
        positionOverlay.repaint();
    }
    
    void setZoomPosition(double zoomScale)
    {
        positionOverlay.setZoomPosition(zoomScale);
    }
    
private:
    void thumbnailChanged()
    {
        repaint();
    }
    
    AudioThumbnail thumbnail;
    PositionOverlay positionOverlay;
    
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioThumbnailComponent)
};

