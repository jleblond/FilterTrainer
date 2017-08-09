/*
  ==============================================================================

    ExerciseSettings.h
    Created: 15 Jul 2017 10:59:19pm
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
        mTitleLabel.setText("EXERCISE PARAMETERS", dontSendNotification);
        
        addAndMakeVisible(mFreqRangeLabel);
        mFreqRangeLabel.setText("Frequency Range", dontSendNotification);
        
        addAndMakeVisible(freqrange);
        freqrange->addItem("ALL", 1);
        freqrange->addSeparator();
        freqrange->addItem("High", 2);
        freqrange->addItem("Mid", 3);
        freqrange->addItem("Low", 4);
        freqrange->setSelectedId(1);
        freqrange->addListener(this);
        
        addAndMakeVisible(mdBAmpLabel);
        mdBAmpLabel.setText("Frequency Boost", dontSendNotification);
        
        addAndMakeVisible(dBAmpSlider);
        dBAmpSlider.setRange(3, 12, 3);
        dBAmpSlider.setTextValueSuffix("dB");
        dBAmpSlider.setSliderStyle(juce::Slider::LinearVertical);
        dBAmpSlider.setTextBoxIsEditable(false);
        dBAmpSlider.setValue(6);
        dBAmpSlider.addListener(this);
        
        
        amplify.setButtonText("+");
        amplify.setColour(TextButton::buttonColourId, Colours::grey);
        amplify.addListener(this);
        addAndMakeVisible(amplify);
        
        attenuate.setButtonText("-");
        attenuate.setColour(TextButton::buttonColourId, Colours::grey);
        attenuate.addListener(this);
        addAndMakeVisible(attenuate);
    
    }
    
    ~ExerciseSettings()
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
         mTitleLabel.setBounds(0.25*getWidth(), 0, 0.6*getWidth(), 80);
        
        mdBAmpLabel.setBounds(0.15*getWidth(), 0.25*getHeight(), 90, 30);
        dBAmpSlider.setBounds (0.2*getWidth(), 0.35*getHeight(), 30, 135);
        amplify.setBounds (0.15*getWidth(), 0.8*getHeight(), 30, 30);
        attenuate.setBounds (0.27*getWidth(), 0.8*getHeight(), 30, 30);
        
        mFreqRangeLabel.setBounds (0.5*getWidth(), 0.35*getHeight(), 90, 30);
        freqrange->setBounds (0.5*getWidth(), 0.5*getHeight(), 100, 30);
    
    }
    
    void buttonClicked(Button* button) override
    {
        if(button == &amplify)
            amplifyChanged();
        
        if(button == &attenuate)
            attenuateChanged();
        
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        if(slider == &dBAmpSlider)
            g_filterGainValue = dBAmpSlider.getValue();
    
    }
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override
    {
        if(comboBoxThatHasChanged == freqrange)
            g_freqRangeValue = freqrange->getSelectedId();
    }
    
    void amplifyChanged()
    {
        g_gainAmplification = !g_gainAmplification;
        
        checkAmplifyAttenuate();
        
        if(g_gainAmplification)
        {
            amplify.setColour(TextButton::buttonColourId, Colours::grey);
            
        }
        else
        {
            amplify.setColour (TextButton::buttonColourId,
                                getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        }
    }
    
    void attenuateChanged()
    {
        g_gainAttenuation = !g_gainAttenuation;
        
        checkAmplifyAttenuate();
        
        if(g_gainAttenuation)
        {
            attenuate.setColour(TextButton::buttonColourId, Colours::grey);
            
        }
        else
        {
            attenuate.setColour (TextButton::buttonColourId,
                               getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        }

    }
    
    void checkAmplifyAttenuate()
    {
        if( !g_gainAttenuation && !g_gainAmplification)
        {
            attenuate.triggerClick();
            amplify.triggerClick();
        }
    }
    
    
private:
    Slider dBAmpSlider;
    ComboBox* freqrange = new ComboBox("Frequency Range");
    TextButton amplify;
    TextButton attenuate;
    
    Label mFreqRangeLabel;
    Label mdBAmpLabel;
    
    Label mTitleLabel;
    
};
