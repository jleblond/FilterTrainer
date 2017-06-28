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
        dBAmpSlider.addListener(this);
        
        amplify.setButtonText("+");
        amplify.addListener(this);
        addAndMakeVisible(amplify);
        //amplify.triggerClick();
        
        attenuate.setButtonText("-");
        attenuate.addListener(this);
        addAndMakeVisible(attenuate);
        
        addAndMakeVisible(volumeSlider);
        volumeSlider.setRange(1, 10, 1); //temporary range
        volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
        volumeSlider.setTextBoxIsEditable(false);
        volumeSlider.addListener(this);
        
        question.setButtonText("NEW QUESTION");
        question.addListener(this);
        addAndMakeVisible(question);
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
        amplify.setBounds (0.25*getWidth(), 0.8*getHeight(), 30, 30);
        attenuate.setBounds (0.35*getWidth(), 0.8*getHeight(), 30, 30);
        
        volumeSlider.setBounds (0.6*getWidth(), 0.45*getHeight(), 30, 135);
        
        question.setBounds (0.5*getWidth(), 0.85*getHeight(), 120, 40);
    }
    
    void buttonClicked(Button* button) override
    {
        if(button == &amplify)
            amplification_value = !amplification_value;
            
        if(button == &attenuate)
            attenuation_value = !attenuation_value;
        
        if(button == &question)
        {
            std::cout<<"NEW QUESTION BUTTON"<<std::endl;
            std::cout<<"freqrange_value:"<<freqrange_value<<" dBAmpSlider_value:"<<dBAmpSlider_value<<
            " amplification_value:"<<amplification_value<<" attenuation_value:"<<attenuation_value<<
            std::endl;
            
          ExerciseGenerator::Instance().createExercise(freqrange_value, dBAmpSlider_value, amplification_value, attenuation_value);
        }
        
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        if(slider == &dBAmpSlider)
            dBAmpSlider_value=dBAmpSlider.getValue();
    }
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override
    {
        if(comboBoxThatHasChanged == freqrange)
            freqrange_value=freqrange->getSelectedId();
    }
    
    
private:
    Slider dBAmpSlider;
    Slider volumeSlider;
    ComboBox* freqrange=new ComboBox("Frequency Range");
    TextButton amplify;
    TextButton attenuate;
    TextButton question;
    
    int freqrange_value=0;
    int dBAmpSlider_value=3;
    bool amplification_value=false;
    bool attenuation_value=false;

};
