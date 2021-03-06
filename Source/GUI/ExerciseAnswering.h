/*
  ==============================================================================

    ExerciseAnswering.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../ExerciseGenerator.h"
#include "../global.h"


class ExerciseAnswering : public Component,
public Button::Listener, public Slider::Listener
{
public:
    ExerciseAnswering()
    {
        addAndMakeVisible(mTitleLabel);
        mTitleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        mTitleLabel.setText("ANSWER SECTION", dontSendNotification);
        
        addAndMakeVisible(freqrange);
        freqrange.addItem("ALL", 1);
        freqrange.addSeparator();
        freqrange.addItem("High", 2);
        freqrange.addItem("Mid", 3);
        freqrange.addItem("Low", 4);
        freqrange.addSeparator();
        freqrange.addItem("Mid 8", 5);
        freqrange.setSelectedId( g_freqRangeValue );
        freqrange.setEnabled(false);
        
        addAndMakeVisible(mFreqRangeListLabel);
        mFreqRangeListLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        mFreqRangeListLabel.setText( listFreqInRange(g_AllRange) , dontSendNotification); //g_AllRange arbitrary default
        
        
        addAndMakeVisible(mAnswerSlider);
        mAnswerSlider.setRange(1, 5, 1);
        mAnswerSlider.setTextValueSuffix("Hz");
        mAnswerSlider.setSliderStyle(juce::Slider::LinearVertical);
        mAnswerSlider.setTextBoxIsEditable(false);
        mAnswerSlider.setValue(1);
        mAnswerSlider.addListener(this);
        
        addAndMakeVisible(mAnswerLabel);
        mAnswerLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        mAnswerLabel.setText("Freq", dontSendNotification);
        mAnswerLabel.attachToComponent(&mAnswerSlider, true);
        
        
        addAndMakeVisible(mCurrFreqLabel);
        mCurrFreqLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        mCurrFreqLabel.setText("", dontSendNotification);
        
    
    }
    
    ~ExerciseAnswering()
    {
 
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
        
        mCurrFreqLabel.setBounds ( 0.2*getWidth(), 0.25*getHeight(), 60, 35 );
        mAnswerSlider.setBounds (0.2*getWidth(), 0.35*getHeight(), 30, 135);
        
        freqrange.setBounds (0.5*getWidth(), 0.3*getHeight(), 100, 30);
        mFreqRangeListLabel.setBounds(0.5*getWidth(), 0.4*getHeight(), 150, 100);
        
    
    }
    
    void update()
    {
        freqrange.setSelectedId( g_freqRangeValue );
        
        int sliderRange = 5;
        
        if ( g_freqRangeValue == 1)
            sliderRange = 10;
        else if (g_freqRangeValue == 5)
            sliderRange = 8;
        
         mAnswerSlider.setRange(1, sliderRange, 1);
         mAnswerSlider.setValue(1);
         mCurrFreqLabel.setText( static_cast<String>( getSliderAnswerValue() ) , dontSendNotification);
        
        
        String listfreqtext = "";
        
        switch( g_freqRangeValue )
        {
            case 1:
                listfreqtext = listFreqInRange(g_AllRange);
                break;
                
            case 2:
                listfreqtext = listFreqInRange(g_HighRange);
                break;
                
            case 3:
                listfreqtext = listFreqInRange(g_MidRange);
                break;
                
            case 4:
                listfreqtext = listFreqInRange(g_LowRange);
                break;
            case 5:
                listfreqtext = listFreqInRange(g_Mid8Range);
                break;
                
        }
        
        mFreqRangeListLabel.setText( listfreqtext , dontSendNotification);
        
  
    }
    
    void buttonClicked(Button* button) override
    {

    }
    
    void sliderValueChanged (Slider* slider) override
    {
        if(slider == &mAnswerSlider)
        {
            String str = static_cast<String>( getSliderAnswerValue() );
            mCurrFreqLabel.setText( str , dontSendNotification );
            g_answerValue = mAnswerSlider.getValue(); //needed?
        }
        
    }
    
    
    
    void answer()
    {
        if( ExerciseGenerator::listexercises.size() > 0 )
        {
            int boostAns = (ExerciseGenerator::listexercises).back()->getFreqBoost();
            boostAns = std::fabs(boostAns);

            // IN CASE Exercise is configured to both +/- possible answer choices,
            // mAmpButton is not selected => user had pressed the attenuation button in their answer
            // then we need to negate the int of their answer
            if( mAmpButtonSelected == false )
                boostAns = -boostAns;
            
            // IN CASE Exercise is only configured to '-' (attenuation)
            if ( g_gainAmplification == false && g_gainAttenuation == true)
                boostAns = -boostAns;
            
            
            ( ExerciseGenerator::Instance() ) .Answering( mAnswerSlider.getValue(), boostAns );
        }
    }
    
    int getSliderAnswerValue()
    {
        int answ = 0;
        
        
        switch( g_freqRangeValue )
        {
            case 1:
                answ = g_AllRange[ mAnswerSlider.getValue() - 1 ];
                break;
            case 2:
                answ = g_HighRange[ mAnswerSlider.getValue() - 1 ];
                break;
            case 3:
                answ = g_MidRange[ mAnswerSlider.getValue() - 1 ];
                break;
            case 4:
                answ = g_LowRange[ mAnswerSlider.getValue() - 1 ];
                break;
            case 5:
                answ = g_Mid8Range[ mAnswerSlider.getValue() - 1 ];
                break;
        }
        
        return answ;
    }
    
    
    String listFreqInRange( const std::vector<float> &freqrangevec )
    {
        String str="List of frequencies: \n";
        
        for(int i=0; i<freqrangevec.size(); i++)
        {
            str+= static_cast<String> (freqrangevec[i]);
            
            if(i != freqrangevec.size() - 1 )
                str+= ", ";
        }
        
        return str;
    }
    
    
    void ampButtonSelect(bool select)
    {
        if(select)
            mAmpButtonSelected = true;
        else
            mAmpButtonSelected = false;
    }
    

    
    
private:
    bool mAmpButtonSelected = true;
    
    Slider mAnswerSlider;
    Label mAnswerLabel;
    Label mCurrFreqLabel;
    Label mFreqRangeListLabel;
    ComboBox freqrange;
    
//    Label mAmpAttTextLabel;
//    TextButton mAmpButton;
//    TextButton mAttButton;
    
    Label mTitleLabel;
};
