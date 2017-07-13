

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../global.h"

class TransportBar  : public Component
{
public:

    TransportBar ()
    {
        
        addAndMakeVisible (g_playButton);
        g_playButton.setButtonText ("Play");
        g_playButton.setColour (TextButton::buttonColourId, Colours::green);
        g_playButton.setEnabled (false);
        
        addAndMakeVisible (g_stopButton);
        g_stopButton.setButtonText ("Stop");
        g_stopButton.setColour (TextButton::buttonColourId, Colours::red);
        g_stopButton.setEnabled (false);
        
        addAndMakeVisible (g_loopingButton);
        g_loopingButton.setButtonText ("Looping");
        g_loopingButton.setColour (TextButton::buttonColourId,
                                   getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        g_loopingButton.setEnabled (false);
        
        addAndMakeVisible (g_filterButton);
        g_filterButton.setButtonText ("Filter is off");
        g_filterButton.setColour (TextButton::buttonColourId,
                                  getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        g_filterButton.setEnabled (false);
        
        
    };
    
    ~TransportBar(){}


    void paint (Graphics& g) override
    {
        // g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    }
    
    void resized() override
    {
        
        
        g_playButton.setBounds   (10, mTransportHeight, 80, 30);
        g_stopButton.setBounds   (100, mTransportHeight, 80, 30);
        g_loopingButton.setBounds (190 , mTransportHeight, 80, 30);
     
        g_filterButton.setBounds (-10 + getWidth() - 80, mTransportHeight, 80, 30);
    }



private:
    int mTransportHeight = 0;
    
    
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportBar)
};


