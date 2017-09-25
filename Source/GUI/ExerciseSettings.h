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
        mTitleLabel.setText("Generate new question", dontSendNotification);
        
//        addAndMakeVisible(mFreqRangeLabel);
//        mFreqRangeLabel.setText("Frequency Range", dontSendNotification);
//        
//        addAndMakeVisible(freqrange);
//        freqrange->addItem("ALL", 1);
//        freqrange->addSeparator();
//        freqrange->addItem("High", 2);
//        freqrange->addItem("Mid", 3);
//        freqrange->addItem("Low", 4);
//        freqrange->addSeparator();
//        freqrange->addItem("Mid 8", 5);
//        freqrange->setSelectedId(1);
//        freqrange->addListener(this);
//        
//        addAndMakeVisible(mFreqRangeListLabel);
//        mFreqRangeListLabel.setText( listFreqInRange(g_AllRange) , dontSendNotification); //g_AllRange default
//    
//        
//        addAndMakeVisible(mdBAmpLabel);
//        mdBAmpLabel.setText("Boost Amount (dB)", dontSendNotification);
//        
//        addAndMakeVisible(dBAmpSlider);
//        dBAmpSlider.setRange(3, 12, 3);
//        dBAmpSlider.setTextValueSuffix("dB");
//        dBAmpSlider.setSliderStyle(juce::Slider::LinearVertical);
//        dBAmpSlider.setTextBoxIsEditable(false);
//        dBAmpSlider.setValue(12);
//        dBAmpSlider.addListener(this);
//        
//        addAndMakeVisible(mdBAmpValueLabel);
//        mdBAmpValueLabel.setText( dBAmpCurrValue() , dontSendNotification);
//        
//        
//        amplify.setButtonText("+");
//        amplify.setColour(TextButton::buttonColourId, Colours::darkgrey);
//        amplify.addListener(this);
//        addAndMakeVisible(amplify);
//        
//        attenuate.setButtonText("-");
//        attenuate.setColour (TextButton::buttonColourId,
//                             getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
//        attenuate.addListener(this);
//        addAndMakeVisible(attenuate);
    
    }
    
    ~ExerciseSettings()
    {
//        delete freqrange;
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
        
//        mdBAmpLabel.setBounds(0.15*getWidth(), 0.25*getHeight(), 100, 30);
//        dBAmpSlider.setBounds (0.2*getWidth(), 0.35*getHeight(), 30, 135);
//        mdBAmpValueLabel.setBounds (0.3*getWidth(), 0.45*getHeight(), 60, 30);
//        amplify.setBounds (0.15*getWidth(), 0.85*getHeight(), 30, 30);
//        attenuate.setBounds (0.27*getWidth(), 0.85*getHeight(), 30, 30);
//        
//        mFreqRangeLabel.setBounds (0.5*getWidth(), 0.35*getHeight(), 100, 30);
//        freqrange->setBounds (0.5*getWidth(), 0.5*getHeight(), 100, 30);
//        mFreqRangeListLabel.setBounds(0.5*getWidth(), 0.6*getHeight(), 150, 100);
    
    }
    
    void buttonClicked(Button* button) override
    {
//        if(button == &amplify)
//            amplifyChanged();
//
//        if(button == &attenuate)
//            attenuateChanged();
//        
//        mdBAmpValueLabel.setText( dBAmpCurrValue(), dontSendNotification);
        
    }
    
    void sliderValueChanged (Slider* slider) override
    {
//        if(slider == &dBAmpSlider)
//        {
//            g_filterGainValue = dBAmpSlider.getValue();
//            
//            mdBAmpValueLabel.setText( dBAmpCurrValue(), dontSendNotification);
//        }
    
    }
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override
    {
//        if(comboBoxThatHasChanged == freqrange)
//        {
//            g_freqRangeValue = freqrange->getSelectedId();
//            
//            String listfreqtext = "";
//            
//            switch( g_freqRangeValue )
//            {
//                case 1:
//                    listfreqtext = listFreqInRange(g_AllRange);
//                    break;
//                    
//                case 2:
//                    listfreqtext = listFreqInRange(g_HighRange);
//                    break;
//                    
//                case 3:
//                    listfreqtext = listFreqInRange(g_MidRange);
//                    break;
//                    
//                case 4:
//                    listfreqtext = listFreqInRange(g_LowRange);
//                    break;
//                case 5:
//                    listfreqtext = listFreqInRange(g_Mid8Range);
//                    break;
//
//                    
//            }
//            
//            mFreqRangeListLabel.setText( listfreqtext, dontSendNotification); //g_AllRange default
//            
//        }
    }
    
    void amplifyChanged()
    {
//        g_gainAmplification = !g_gainAmplification;
//        
//        checkAmplifyAttenuate();
//        
//        if(g_gainAmplification)
//        {
//            amplify.setColour(TextButton::buttonColourId, Colours::darkgrey);
//            
//        }
//        else
//        {
//            amplify.setColour (TextButton::buttonColourId,
//                                getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
//        }
        
    }
    
    void attenuateChanged()
    {
//        g_gainAttenuation = !g_gainAttenuation;
//        
//        checkAmplifyAttenuate();
//        
//        if(g_gainAttenuation)
//        {
//            attenuate.setColour(TextButton::buttonColourId, Colours::darkgrey);
//            
//        }
//        else
//        {
//            attenuate.setColour (TextButton::buttonColourId,
//                               getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
//        }
//        
//        mdBAmpValueLabel.setText( dBAmpCurrValue(), dontSendNotification);

    }
    
    void checkAmplifyAttenuate()
    {
//        if( !g_gainAttenuation && !g_gainAmplification)
//        {
//            amplify.triggerClick();
//        }
    }
    
    String listFreqInRange( const std::vector<float> &freqrangevec )
    {
        String str="List of frequencies: \n";
        
//        for(int i=0; i<freqrangevec.size(); i++)
//        {
//            str+= static_cast<String> (freqrangevec[i]);
//            
//            if(i != freqrangevec.size() - 1 )
//                str+= ", ";
//        }
//        
//        std::cout<<str<<std::endl;
        return str;
    }
    
    String dBAmpCurrValue()
    {
        String s="";
//        
//        if(g_gainAmplification )
//        {
//            s += "+";
//            s += static_cast<String>(dBAmpSlider.getValue());
//        }
//        if( g_gainAmplification && g_gainAttenuation )
//        {
//            s += ", ";
//        }
//        
//        if(g_gainAttenuation)
//        {
//            s += "-";
//            s += static_cast<String>(dBAmpSlider.getValue());
//        }
        
        return s;
    }
    
    
private:
//    Slider dBAmpSlider;
//    ComboBox* freqrange = new ComboBox("Frequency Range");
//    TextButton amplify;
//    TextButton attenuate;
//    
//    Label mFreqRangeLabel;
//    Label mFreqRangeListLabel;
//    Label mdBAmpLabel;
//    Label mdBAmpValueLabel;
    
    Label mTitleLabel;
    
};
