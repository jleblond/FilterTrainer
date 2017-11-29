/*
  ==============================================================================

    ExerciseSettings.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../ExerciseGenerator.h"
#include "../global.h"


class ExerciseSettings : public Component,
public Button::Listener, public Slider::Listener, public ComboBox::Listener
{
public:
    ExerciseSettings()
    {
        addAndMakeVisible(mTitleLabel);
        mTitleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        mTitleLabel.setText("Ask a new question", dontSendNotification);
    
    }
    
    ~ExerciseSettings()
    {

    }
    
    void paint(Graphics& g) override
    {
        
    }
    
    void resized() override
    {
        mTitleLabel.setBounds(0.25*getWidth()+10, 0.3*getHeight(), 0.6*getWidth(), 80);
        
    
    }
    
    void buttonClicked(Button* button) override
    {

        
    }
    
    void sliderValueChanged (Slider* slider) override
    {
    
    }
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override
    {

    }
    
   
    
    
private:
    
    Label mTitleLabel;
    
};
