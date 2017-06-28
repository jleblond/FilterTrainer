/*
  ==============================================================================

    GUIExControls.h
    Created: 26 Jun 2017 11:23:45pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class GUIExControls : public Component
{
public:
    GUIExControls()
    {
        addAndMakeVisible(freqrange);
       // freqrange->setBounds (0.6*getWidth(), 0.15*getHeight(), 100, 50);
        freqrange->addItem("ALL", 1);
        freqrange->addSeparator();
        freqrange->addItem("High", 2);
        freqrange->addItem("Mid", 3);
        freqrange->addItem("Low", 4);
        freqrange->setSelectedId(1);
        
        addAndMakeVisible(dBAmpSlider);
        dBAmpSlider.setRange(3, 12, 3);
        dBAmpSlider.setTextValueSuffix("dB");
        dBAmpSlider.setSliderStyle(juce::Slider::LinearVertical);
        dBAmpSlider.setTextBoxIsEditable(false);
       // dBAmpSlider.addListener(this);
        
        amplify.setButtonText("+");
       // amplify.addListener(this);
        addAndMakeVisible(amplify);
        
        attenuate.setButtonText("-");
        addAndMakeVisible(attenuate);
        
        addAndMakeVisible(volumeSlider);
        volumeSlider.setRange(1, 10, 1); //temporary range
        volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
        volumeSlider.setTextBoxIsEditable(false);
    }
    
    ~GUIExControls()
    {
        delete freqrange;
    }
    
    void paint(Graphics& g) override
    {
        //sidebar
       g.fillAll(Colours::green);
    }
    
    void resized() override
    {
        freqrange->setBounds (0.4*getWidth(), 0.2*getHeight(), 80, 40);
        
        dBAmpSlider.setBounds (0.3*getWidth(), 0.45*getHeight(), 30, 135);
        amplify.setBounds (0.25*getWidth(), 0.85*getHeight(), 30, 30);
        attenuate.setBounds (0.35*getWidth(), 0.85*getHeight(), 30, 30);
        
        volumeSlider.setBounds (0.6*getWidth(), 0.45*getHeight(), 30, 135);
    }
    
private:
    Slider dBAmpSlider;
    Slider volumeSlider;
    ComboBox* freqrange=new ComboBox("Frequency Range");
    TextButton amplify;
    TextButton attenuate;

};
