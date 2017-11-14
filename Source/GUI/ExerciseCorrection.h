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

#include <math.h>       /* fabs */

class ExerciseCorrection : public Component,
public Button::Listener, Slider::Listener
{
public:
    ExerciseCorrection()
    {
        addAndMakeVisible(mTitleLabel);
        mTitleLabel.setText("EXERCISE FEEDBACK", dontSendNotification);
        
        addAndMakeVisible(mFreqAnsweredLabel);
        mFreqAnsweredLabel.setText("", dontSendNotification);
        
        addAndMakeVisible(mFreqAnsweredButton);
        mFreqAnsweredButton.setButtonText("");
        mFreqAnsweredButton.addListener(this);
        
        addAndMakeVisible(mCorrectAnswerLabel);
        mCorrectAnswerLabel.setText("", dontSendNotification);
        
        addAndMakeVisible(mCorrectAnswerButton);
        mCorrectAnswerButton.setButtonText("");
        mCorrectAnswerButton.addListener(this);
        
        addAndMakeVisible(mFreqBoostLabel);
        mFreqBoostLabel.setText("", dontSendNotification);
        

        //SLIDER REGION
        
        addAndMakeVisible(mTestFreqTitleLabel);
        mTestFreqTitleLabel.setText("Try out other frequencies: ", dontSendNotification);
        
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
        mFreqLabel.setText("Hz ", dontSendNotification);
        
        addAndMakeVisible(mNoSliderLabel);
        mNoSliderLabel.setText("(bypass the filter to modify the parameters)", dontSendNotification);
        mNoSliderLabel.setVisible(false);
 
        
        //Amplification Atttenuation Toggle Text Buttons Section
        addAndMakeVisible(mAmpAttLabel);
        mAmpAttLabel.setText("[Amplify / Attenuate]", dontSendNotification);
        mAmpAttLabel.setVisible(false);
        
        addAndMakeVisible(mAmpToggleButton);
        mAmpToggleButton.setButtonText("+");
        mAmpToggleButton.setClickingTogglesState (true);
        mAmpToggleButton.setRadioGroupId (1);
        mAmpToggleButton.setColour (TextButton::textColourOffId, Colours::white);
        mAmpToggleButton.setColour (TextButton::textColourOnId, Colours::black);
        mAmpToggleButton.setColour (TextButton::buttonColourId, getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        mAmpToggleButton.setColour (TextButton::buttonOnColourId, (getLookAndFeel().findColour (ResizableWindow::backgroundColourId)).brighter());
        mAmpToggleButton.setToggleState (true, dontSendNotification);
        mAmpToggleButton.addListener(this);
        
        addAndMakeVisible(mAttToggleButton);
        mAttToggleButton.setButtonText("-");
        mAttToggleButton.setClickingTogglesState (true);
        mAttToggleButton.setRadioGroupId (1);
        mAttToggleButton.setColour (TextButton::textColourOffId, Colours::white);
        mAttToggleButton.setColour (TextButton::textColourOnId, Colours::black);
        mAttToggleButton.setColour (TextButton::buttonColourId, getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        mAttToggleButton.setColour (TextButton::buttonOnColourId, (getLookAndFeel().findColour (ResizableWindow::backgroundColourId)).brighter());
        mAttToggleButton.setToggleState (false, dontSendNotification);
        mAttToggleButton.addListener(this);
        
//        mAmpToggleButton.setConnectedEdges (((i != 0) ? Button::ConnectedOnLeft : 0)
//                               | ((i != 3) ? Button::ConnectedOnRight : 0));

        
    }
    
    ~ExerciseCorrection()
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

        mFreqAnsweredLabel.setBounds ( 0.05*getWidth(), 0.2*getHeight(), 80, 40 );
        mFreqAnsweredButton.setBounds(0.1*getWidth(), 0.3*getHeight(), 60, 30 );
        
        mCorrectAnswerLabel.setBounds (0.35*getWidth(), 0.2*getHeight(), 90, 40 );
        mCorrectAnswerButton.setBounds(0.4*getWidth(), 0.3*getHeight(), 60, 30);
        
        mFreqBoostLabel.setBounds (0.7*getWidth(), 0.2*getHeight(), 80, 60 );
        
        
        mTestFreqTitleLabel.setBounds(0.15*getWidth(), 0.45*getHeight(), 0.4*getWidth(), 70);
        g_filterCorrectionButton.setBounds (0.55*getWidth(), 0.55*getHeight(), 80, 40 );
        mFreqLabel.setBounds (0.1*getWidth(), 0.65*getHeight(), 65, 60 );
        mFreqSlider.setBounds (0.35*getWidth(), 0.65*getHeight(), 0.6*getWidth(), 60 );
        mNoSliderLabel.setBounds (0.35*getWidth(), 0.7*getHeight(), 0.65*getWidth(), 80);
        
        mAmpAttLabel.setBounds(0.1*getWidth(), 0.8*getHeight(), 65, 60);
        mAmpToggleButton.setBounds (0.5*getWidth(), 0.8*getHeight(), 40, 30 );
        mAttToggleButton.setBounds (0.65*getWidth(), 0.8*getHeight(), 40, 30) ;
    }
    
    void update()
    {
        mCorrectAnswer =  g_exerciseCentreFrequency ;
        
        
        if( ExerciseGenerator::listexercises.size() > 0 )
        {
            mFreqAnswered =  (ExerciseGenerator::listexercises.back() )-> getCenterFreqAnswered();
            
            mFreqBoost =  (ExerciseGenerator::listexercises.back() )-> getFreqBoost();
        }
        
        
        mFreqAnsweredLabel.setText( "Your answer: ", dontSendNotification);
        mFreqAnsweredButton.setButtonText(
            static_cast<String> (mFreqAnswered) + "Hz" );
        
        mCorrectAnswerLabel.setText( "Correct answer: " , dontSendNotification);
        mCorrectAnswerButton.setButtonText(
            static_cast<String> (mCorrectAnswer) + "Hz");
        
        
        mFreqBoostLabel.setText( "Boost Amount: " +
            static_cast<String> (mFreqBoost) + "dB",
                                dontSendNotification );
        
        
        updateSliderCursorPos(g_exerciseCentreFrequency);
        
        if(g_gainAmplification && g_gainAttenuation)
        {
            mAmpToggleButton.setVisible(true);
            mAttToggleButton.setVisible(true);
            mAmpAttLabel.setVisible(true);
        }
        else
        {
            mAmpToggleButton.setVisible(false);
            mAttToggleButton.setVisible(false);
            mAmpAttLabel.setVisible(false);
        }
        
        if(mFreqBoost>0)
        {
            mAmpToggleButton.triggerClick();
        }
        else
        {
            mAttToggleButton.triggerClick();
        }
    }
    
    void buttonClicked(Button* button) override
    {
        if( button == &g_filterCorrectionButton)
        {
           if(g_filterOn)
           {
               mFreqSlider.setVisible(false);
               mAmpToggleButton.setVisible(false);
               mAttToggleButton.setVisible(false);
               mNoSliderLabel.setVisible(true);
               mFreqAnsweredButton.setEnabled(false);
               mCorrectAnswerButton.setEnabled(false);
               
           }
            else
            {
                mFreqSlider.setVisible(true);
                
                if(g_gainAmplification && g_gainAttenuation)
                {
                    mAmpToggleButton.setVisible(true);
                    mAttToggleButton.setVisible(true);
                }

                mNoSliderLabel.setVisible(false);
                mFreqAnsweredButton.setEnabled(true);
                mCorrectAnswerButton.setEnabled(true);
            }
            
        }
        
        if ( button == &mFreqAnsweredButton)
        {
            updateSliderCursorPos(mFreqAnswered);
            
        }
        
        if ( button == &mCorrectAnswerButton )
        {
            updateSliderCursorPos(mCorrectAnswer);
        }
        
        
        if ( button == &mAmpToggleButton )
        {
            g_gainFactor = fabs(mFreqBoost);
        }
        
        if ( button == &mAttToggleButton )
        {
            g_gainFactor = -(fabs(mFreqBoost));

        }
    }
    

    void sliderValueChanged (Slider* slider) override
    {
                if(slider == &mFreqSlider)
                {
                    int freqValue = mFreqSlider.getValue();
                    g_centreFrequency = getFreq(freqValue);
                    
                    
                    String freqStr = "[" + static_cast<String>(g_centreFrequency)+" Hz]";
                    mFreqLabel.setText(freqStr, dontSendNotification);
                    
                    buttonValueSameSliderValue();
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
        int currSliderValue = mFreqSlider.getValue();
        
        //in case, when program is first loaded, no freqlabel value ("") is displayed because correct centrefreq value = 1
        if( currSliderValue == val )
        {
            String freqStr = "[" + static_cast<String>(freq)+" Hz]";
            mFreqLabel.setText(freqStr, dontSendNotification);
        }
        
        
        mFreqSlider.setValue(val);

        buttonValueSameSliderValue();
    };
    
    
    //in case the user answered correctly (displayed freq is the same as the one suggested by default by the slider when the exercise control panel is updated)
    void buttonValueSameSliderValue()
    {
        int currSliderValue = mFreqSlider.getValue();
        
        if ( getFreqValue(mFreqAnswered, g_freqRangeValue) ==
                getFreqValue( mCorrectAnswer, g_freqRangeValue) )
        {
            mCorrectAnswerButton.setEnabled(false);
            mFreqAnsweredButton.setEnabled(false);
        }
        if( currSliderValue == getFreqValue(mFreqAnswered, g_freqRangeValue))
        {
            mCorrectAnswerButton.setEnabled(true);
            mFreqAnsweredButton.setEnabled(false);
        }
        else if (currSliderValue == getFreqValue( mCorrectAnswer, g_freqRangeValue) )
        {
            mCorrectAnswerButton.setEnabled(false);
            mFreqAnsweredButton.setEnabled(true);
        }
        else
        {
            mCorrectAnswerButton.setEnabled(true);
            mFreqAnsweredButton.setEnabled(true);
        }
    }
    
    
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
    Label mFreqAnsweredLabel;
    TextButton mFreqAnsweredButton;
    Label mCorrectAnswerLabel;
    TextButton mCorrectAnswerButton;
    Label mFreqBoostLabel;
    Label mTitleLabel;
    Label mNoSliderLabel;
    
    Slider mFreqSlider;
    Label mFreqLabel;
    Label mTestFreqTitleLabel;
    
    Label mAmpAttLabel;
    TextButton mAmpToggleButton;
    TextButton mAttToggleButton;
        
    
    //arbitrary default values
    float mFreqAnswered = 20000;
    float mCorrectAnswer = 20000;
    float mFreqBoost = 12;
    
};

