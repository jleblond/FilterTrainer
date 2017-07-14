/*
  ==============================================================================

    GUIExControls.h
    Created: 26 Jun 2017 11:23:45pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../ExerciseGenerator.h"
#include "../global.h"


class GUIExControls : public Component,
                    public Button::Listener, public Slider::Listener, public ComboBox::Listener
{
public:
    GUIExControls()
    {
        addAndMakeVisible(freqrange);
        freqrange->addItem("ALL", 1);
        freqrange->addSeparator();
        freqrange->addItem("High", 2);
        freqrange->addItem("Mid", 3);
        freqrange->addItem("Low", 4);
        freqrange->setSelectedId(1);
        freqrange->addListener(this);
        
        addAndMakeVisible(dBAmpSlider);
        dBAmpSlider.setRange(3, 12, 3);
        dBAmpSlider.setTextValueSuffix("dB");
        dBAmpSlider.setSliderStyle(juce::Slider::LinearVertical);
        dBAmpSlider.setTextBoxIsEditable(false);
        dBAmpSlider.setValue(6);
        dBAmpSlider.addListener(this);
        
        amplify.setButtonText("+");
        amplify.addListener(this);
        addAndMakeVisible(amplify);
        
        attenuate.setButtonText("-");
        attenuate.addListener(this);
        addAndMakeVisible(attenuate);
        
        g_questionButton.setButtonText("NEW QUESTION");
        g_questionButton.addListener(this);
        addAndMakeVisible(g_questionButton);
    }
    
    ~GUIExControls()
    {
        delete freqrange;
    }
    
    void paint(Graphics& g) override
    {
        //sidebar
       //g.fillAll(Colours::darkred);
       // g.fillAll(Colour::Colour(191, 92, 0) ); //dark red
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    }
    
    void resized() override
    {
        
        dBAmpSlider.setBounds (0.2*getWidth(), 0.25*getHeight(), 30, 135);
        amplify.setBounds (0.15*getWidth(), 0.6*getHeight(), 30, 30);
        attenuate.setBounds (0.27*getWidth(), 0.6*getHeight(), 30, 30);
        
        freqrange->setBounds (0.5*getWidth(), 0.4*getHeight(), 100, 30);
        
        g_questionButton.setBounds (0.3*getWidth(), 0.75*getHeight(), 120, 40);
    }
    
    void buttonClicked(Button* button) override
    {
        if(button == &amplify)
            g_gainAmplification = !g_gainAmplification;
            
        if(button == &attenuate)
            g_gainAttenuation = !g_gainAttenuation;
        
        if(button == &g_questionButton)
        {
            std::cout<<"GUIExControls"<<std::endl;
            std::cout<<"freqrange_value:"<<g_freqRangeValue<<" dBAmpSlider_value:"<<g_filterGainValue<<
            " amplification_value:"<<g_gainAmplification<<" attenuation_value:"<<g_gainAttenuation<<
            std::endl;
            
        }
        
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        if(slider == &dBAmpSlider)
            g_filterGainValue = dBAmpSlider.getValue();
        
        if(slider == &volumeSlider)
            g_mainVolume = volumeSlider.getValue() /10;
    }
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override
    {
        if(comboBoxThatHasChanged == freqrange)
            g_freqRangeValue=freqrange->getSelectedId();
    }
    
    
private:
    Slider dBAmpSlider;
    Slider volumeSlider;
    ComboBox* freqrange=new ComboBox("Frequency Range");
    TextButton amplify;
    TextButton attenuate;
    
};
