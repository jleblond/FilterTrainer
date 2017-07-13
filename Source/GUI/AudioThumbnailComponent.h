/*
  ==============================================================================

    AudioThumbnailComponent.h
    Created: 12 Jul 2017 4:41:30pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once


#include "../JuceLibraryCode/JuceHeader.h"



class AudioThumbnailComponent : public Component,
private ChangeListener
{
public:
    AudioThumbnailComponent (int sourceSamplesPerThumbnailSample,
                              AudioFormatManager& formatManager,
                              AudioThumbnailCache& cache)
    : thumbnail (sourceSamplesPerThumbnailSample, formatManager, cache)
    {
        thumbnail.addChangeListener (this);
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
        
        g.setColour (Colours::red);
        thumbnail.drawChannels (g, getLocalBounds(), 0.0, thumbnail.getTotalLength(), 0.9f);
    }
    
    void changeListenerCallback (ChangeBroadcaster* source) override
    {
        if (source == &thumbnail)
            thumbnailChanged();
    }
    
private:
    void thumbnailChanged()
    {
        repaint();
    }
    
    AudioThumbnail thumbnail;
    
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioThumbnailComponent)
};
