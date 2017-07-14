/*
  ==============================================================================

    MasterVolume.h
    Created: 13 Jul 2017 8:13:05pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/


#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../global.h"


class MasterVolume : public Component,
public Button::Listener, public Slider::Listener
{
public:
    MasterVolume()
    {
        addAndMakeVisible(volumeSlider);
        volumeSlider.setRange(0, 10, 0.1);
        volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
        volumeSlider.setTextBoxIsEditable(false);
        volumeSlider.setValue(10);
        volumeSlider.addListener(this);
    }
    
    ~MasterVolume()
    {
    };
    
    void paint(Graphics& g) override
    {
        //sidebar
        g.fillAll(Colours::grey);
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    }
    
    void resized() override
    {
        volumeSlider.setBounds (getWidth()/2, 0.3*getHeight(), 30, 200);
    }
    
    void buttonClicked(Button* button) override
    {
        
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        
        if(slider == &volumeSlider)
            g_mainVolume = volumeSlider.getValue() /10;
    }
    
    
    
private:
    Slider volumeSlider;
    
};
