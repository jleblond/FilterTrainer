/*
  ==============================================================================

    MasterVolume.h
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
        volumeSlider.setValue(5);
        volumeSlider.addListener(this);
        
        addAndMakeVisible(volumeLabel);
        volumeLabel.setText("MAIN VOLUME", dontSendNotification);
        volumeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    }
    
    ~MasterVolume()
    {
    };
    
    void paint(Graphics& g) override
    {
        //sidebar
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        g.fillAll(Colours::black);
    }
    
    void resized() override
    {
        volumeLabel.setBounds( 0.1*getWidth(), 0.1*getHeight(), 80, 70 );
        volumeSlider.setBounds( getWidth()/2, 0.3*getHeight(), 30, 200 );
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
    Label volumeLabel;
    
};
