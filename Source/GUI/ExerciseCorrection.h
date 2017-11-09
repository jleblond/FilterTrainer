/*
  ==============================================================================

    ExerciseCorrection.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../ExerciseGenerator.h"
#include "../global.h"


class ExerciseCorrection : public Component,
public Button::Listener, Slider::Listener
{
public:
    ExerciseCorrection()
    {
        addAndMakeVisible(mTitleLabel);
        mTitleLabel.setText("EXERCISE FEEDBACK", dontSendNotification);
        
        addAndMakeVisible(mCurrFreqLabel);
        mCurrFreqLabel.setText("", dontSendNotification);
        
        addAndMakeVisible(mCorrectAnswerLabel);
        mCorrectAnswerLabel.setText("", dontSendNotification);
        
        addAndMakeVisible(mFreqBoostLabel);
        mFreqBoostLabel.setText("", dontSendNotification);
        

        //SLIDER REGION
        
        addAndMakeVisible(mTestFreqTitleLabel);
        mTestFreqTitleLabel.setText("Try out other frequencies!", dontSendNotification);
        
        addAndMakeVisible (g_filterCorrectionButton);
        g_filterCorrectionButton.setButtonText ("Filter is OFF");
        g_filterCorrectionButton.setColour (TextButton::buttonColourId,
                                  getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        g_filterCorrectionButton.addListener(this);
        
        
        addAndMakeVisible(mFreqSlider);
        mFreqSlider.setRange(1, 10, 1);
        mFreqSlider.setSliderStyle(juce::Slider::LinearHorizontal);
        mFreqSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 10, 10);
        mFreqSlider.setValue(1);
        mFreqSlider.addListener(this);
        
        
        addAndMakeVisible(mFreqLabel);
        mFreqLabel.setText("", dontSendNotification);
        
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

        mCurrFreqLabel.setBounds ( 0.1*getWidth(), 0.2*getHeight(), 80, 60 );
        mCorrectAnswerLabel.setBounds (0.4*getWidth(), 0.2*getHeight(), 80, 60 );
        mFreqBoostLabel.setBounds (0.7*getWidth(), 0.2*getHeight(), 80, 60 );
        
        mTestFreqTitleLabel.setBounds(0.25*getWidth(), 0.4*getHeight(), 0.6*getWidth(), 70);
        g_filterCorrectionButton.setBounds (0.3*getWidth(), 0.6*getHeight(), 100, 30 );
        mFreqLabel.setBounds (0.1*getWidth(), 0.7*getHeight(), 60, 60 );
        mFreqSlider.setBounds (0.3*getWidth(), 0.7*getHeight(), 0.6*getWidth(), 60 );
    }
    
    void update()
    {
        String freqanswered = "";
        String correctanswer = static_cast<String>( g_exerciseCentreFrequency );
        String freqboost = "";
        
        
        if( ExerciseGenerator::listexercises.size() > 0 )
        {
            freqanswered = static_cast<String> (
                             (ExerciseGenerator::listexercises.back() )-> getCenterFreqAnswered()
                                                );
            
            freqboost = static_cast<String> (
                            (ExerciseGenerator::listexercises.back() )-> getFreqBoost()
                                            );
        }
        
        
        mCurrFreqLabel.setText( "Your answer: " + freqanswered , dontSendNotification);
        mCorrectAnswerLabel.setText( "Correct answer: " + correctanswer , dontSendNotification);
        mFreqBoostLabel.setText( "Boost Amount (dB): " + freqboost, dontSendNotification );
        
        
        updateSliderCursorPos(g_exerciseCentreFrequency);
    }
    
    void buttonClicked(Button* button) override
    {
        if( button == &g_filterCorrectionButton)
        {
           if(g_filterOn)
               mFreqSlider.setVisible(false);
            else
                mFreqSlider.setVisible(true);
            
        }
    }
    

    void sliderValueChanged (Slider* slider) override
    {
                if(slider == &mFreqSlider)
                {
                    int freqValue = mFreqSlider.getValue();
                    g_centreFrequency = getFreq(freqValue);
                    
                    
                    String freqStr = static_cast<String>(g_centreFrequency)+" Hz";
                    mFreqLabel.setText(freqStr, dontSendNotification);
                    
                }
        
    }
    
    
    std::vector<float>& getRange(int range)
    {
        if(range == 2)
            return g_HighRange;
        else if(range == 3)
            return g_MidRange;
        else if(range == 4)
            return g_LowRange;
        else if(range == 5)
            return g_Mid8Range;
        else //including range==1
            return g_AllRange;
    }

    
    
    //valid?
    void updateSliderRange()
    {
        int numberFreqs = static_cast<int> (
                            getRange(g_freqRangeValue).size()
                                            );
        mFreqSlider.setRange(1, numberFreqs, 1);
        mFreqLabel.setText("", dontSendNotification);
        
    }
    
    void updateSliderCursorPos(float freq)
    {
        int val = getFreqValue(freq, g_freqRangeValue);
        mFreqSlider.setValue(val);
    };
    
    double getFreq(int freqValue)
    {
        int index = freqValue - 1;
        
        assert(freqValue > 0);
        
        if(g_freqRangeValue == 2)
            return  g_HighRange[index];
        else if(g_freqRangeValue == 3)
            return  g_MidRange[index];
        else if(g_freqRangeValue == 4)
            return  g_LowRange[index];
        else if(g_freqRangeValue == 5)
            return  g_Mid8Range[index];
        else //including range==1
            return  g_AllRange[index];
    }
    
    int getFreqValue(float freq, int range)
    {
        int value = 1; //arbitrary default value 1
        switch(range)
        {
            case 2:
                value = matchFreqinRangeVec(g_HighRange, freq);
                break;
            case 3:
                value = matchFreqinRangeVec(g_MidRange, freq);
                break;
            case 4:
                value = matchFreqinRangeVec(g_LowRange, freq);
                break;
            case 5:
                value = matchFreqinRangeVec(g_Mid8Range, freq);
                break;
            default:
                value = matchFreqinRangeVec(g_AllRange, freq);
        };
        
        return value;
        
    }
  
    int matchFreqinRangeVec(std::vector<float>& g_RangeVec, float freq)
    {
        for(int i=0;i<g_RangeVec.size();i++)
        {
            if(freq == g_RangeVec[i])
                return i+1;  //values range [1..n]
        }
        
        
        //in case end reached (should not be the case)
        return 1;
    }
    
private:
    Label mCurrFreqLabel;
    Label mCorrectAnswerLabel;
    Label mFreqBoostLabel;
    Label mTitleLabel;
    
    Slider mFreqSlider;
    Label mFreqLabel;
    Label mTestFreqTitleLabel;
    
};

