/*
  ==============================================================================

    ExerciseAnswering.h
    Created: 15 Jul 2017 10:59:57pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../ExerciseGenerator.h"
#include "../global.h"

//class filled with test code for now

class ExerciseAnswering : public Component,
public Button::Listener, public Slider::Listener, public ComboBox::Listener
{
public:
    ExerciseAnswering()
    {
        addAndMakeVisible(freqrange);
        freqrange->addItem("ALL", 1);
        freqrange->addSeparator();
        freqrange->addItem("High", 2);
        freqrange->addItem("Mid", 3);
        freqrange->addItem("Low", 4);
        freqrange->setSelectedId( g_freqRangeValue );
        freqrange->setEnabled(false);
        
        
        addAndMakeVisible(mAnswerSlider);
        mAnswerSlider.setRange(1, 5, 1);
        mAnswerSlider.setTextValueSuffix("Hz");
        mAnswerSlider.setSliderStyle(juce::Slider::LinearVertical);
        mAnswerSlider.setTextBoxIsEditable(false);
        mAnswerSlider.setValue(1);
        mAnswerSlider.addListener(this);
        
//        amplify.setButtonText("+");
//        amplify.addListener(this);
//        addAndMakeVisible(amplify);
//        
//        attenuate.setButtonText("-");
//        attenuate.addListener(this);
//        addAndMakeVisible(attenuate);
        
    }
    
    ~ExerciseAnswering()
    {
        delete freqrange;
    }
    
    void paint(Graphics& g) override
    {
        //sidebar
        //g.fillAll(Colours::darkred);
        // g.fillAll(Colour::Colour(191, 92, 0) ); //dark red
        //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    }
    
    void resized() override
    {
        
        mAnswerSlider.setBounds (0.2*getWidth(), 0.25*getHeight(), 30, 135);
       // amplify.setBounds (0.15*getWidth(), 0.8*getHeight(), 30, 30);
       // attenuate.setBounds (0.27*getWidth(), 0.8*getHeight(), 30, 30);
        
        freqrange->setBounds (0.5*getWidth(), 0.4*getHeight(), 100, 30);
    
    }
    
    void update()
    {
        freqrange->setSelectedId( g_freqRangeValue );
        
        int sliderRange = 5;
        
        if ( g_freqRangeValue == 1)
            sliderRange = 10;
        
         mAnswerSlider.setRange(1, sliderRange, 1);
    }
    
    void buttonClicked(Button* button) override
    {

//        if(button == &amplify)
//            g_gainAmplification = !g_gainAmplification;
//        
//        if(button == &attenuate)
//            g_gainAttenuation = !g_gainAttenuation;
        
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        if(slider == &mAnswerSlider)
            g_answerValue = mAnswerSlider.getValue();
        
    }
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override
    {
//        if(comboBoxThatHasChanged == freqrange)
//           g_answerValue =freqrange->getSelectedId();
    }
    
    
    void answer()
    {
        if( ExerciseGenerator::listexercises.size() > 0 )
        {
            ( ExerciseGenerator::Instance() ) .Answering( mAnswerSlider.getValue() );
        }
    }
    
    
private:
    Slider mAnswerSlider;
    ComboBox* freqrange=new ComboBox("Frequency Range");
    
};
