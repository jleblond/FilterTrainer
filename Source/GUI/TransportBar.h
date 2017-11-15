/*
 ==============================================================================
 
 TransportBar.h
 Author:  Jasmine Leblond-Chartrand
 
 ==============================================================================
 */


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
                                   Colours::darkgrey);
        g_loopingButton.setEnabled (false);
        
        //while looping function is not working...
        g_loopingButton.setVisible(false);
        
        
        
        
        addAndMakeVisible (g_dummyFilterButton);
        g_dummyFilterButton.setButtonText ("Filter is OFF");
        g_dummyFilterButton.setColour (TextButton::buttonColourId,
                                  Colours::darkgrey);
        g_dummyFilterButton.setEnabled (false);
        
        
        addAndMakeVisible (g_filterButton);
        g_filterButton.setButtonText ("Filter is OFF");
        g_filterButton.setColour (TextButton::buttonColourId,
                                  Colours::darkgrey);
        g_filterButton.setEnabled (false);
        
        
    };
    
    ~TransportBar(){}


    void paint (Graphics& g) override
    {
        // g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    }
    
    void resized() override
    {
        g_dummyFilterButton.setBounds (10, mTransportHeight, 120, 30);
        g_filterButton.setBounds (10, mTransportHeight, 120, 30);
        //-10 + getWidth() - 80
        
        int xstart = getWidth() - 10 ;
        g_playButton.setBounds   (xstart - 250, mTransportHeight, 70, 30);
        g_stopButton.setBounds   (xstart - 160, mTransportHeight, 70, 30);
        g_loopingButton.setBounds (xstart - 80, mTransportHeight, 70, 30);
     
      
    }



private:
    int mTransportHeight = 10;

    
    
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TransportBar)
};


