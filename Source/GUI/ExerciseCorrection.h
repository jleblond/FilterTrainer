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
        mTitleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        mTitleLabel.setText("EXERCISE FEEDBACK", dontSendNotification);
        
        addAndMakeVisible(mFreqAnsweredLabel);
        mFreqAnsweredLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        mFreqAnsweredLabel.setText("", dontSendNotification);
        
        addAndMakeVisible(mFreqAnsweredButton);
        mFreqAnsweredButton.setButtonText("");
        mFreqAnsweredButton.addListener(this);
        
        addAndMakeVisible(mCorrectAnswerLabel);
        mCorrectAnswerLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        mCorrectAnswerLabel.setText("", dontSendNotification);
        
        addAndMakeVisible(mCorrectAnswerButton);
        mCorrectAnswerButton.setButtonText("");
        mCorrectAnswerButton.addListener(this);
        
        addAndMakeVisible(mFreqBoostLabel);
        mFreqBoostLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        mFreqBoostLabel.setText("", dontSendNotification);
        
        addAndMakeVisible(mFreqBoostAnsweredLabel);
        mFreqBoostAnsweredLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        mFreqBoostAnsweredLabel.setText("", dontSendNotification);
        mFreqBoostAnsweredLabel.setVisible(false);
        

        //SLIDER REGION
        
        addAndMakeVisible(mTestFreqTitleLabel);
        mTestFreqTitleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        mTestFreqTitleLabel.setText("Try out other frequencies: ", dontSendNotification);
        
        addAndMakeVisible (g_filterCorrectionButton);
        g_filterCorrectionButton.setButtonText ("Filter is OFF");
        g_filterCorrectionButton.setColour (TextButton::buttonColourId,
                                            Colours::white);
        g_filterCorrectionButton.addListener(this);
        
        
        addAndMakeVisible(mFreqSlider);
        mFreqSlider.setRange(1, 10, 1);
        mFreqSlider.setSliderStyle(juce::Slider::LinearHorizontal);
        mFreqSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 10, 10);
        mFreqSlider.setValue(1);
        mFreqSlider.addListener(this);
        
        addAndMakeVisible(mFreqLabel);
        mFreqLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        mFreqLabel.setText("Hz ", dontSendNotification);
        
        addAndMakeVisible(mNoSliderLabel);
        mNoSliderLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        mNoSliderLabel.setText("(bypass the filter to modify the parameters)", dontSendNotification);
        mNoSliderLabel.setVisible(false);
 
        
        //Amplification Atttenuation Toggle Text Buttons Section
        addAndMakeVisible(mAmpAttLabel);
        mAmpAttLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        mAmpAttLabel.setText("[Boost / Cut]", dontSendNotification);
        mAmpAttLabel.setVisible(false);
        
        addAndMakeVisible(mAmpToggleButton);
        mAmpToggleButton.setButtonText("+");
        mAmpToggleButton.setClickingTogglesState (true);
        mAmpToggleButton.setRadioGroupId (1);
        mAmpToggleButton.setColour (TextButton::textColourOffId, Colours::black);
        mAmpToggleButton.setColour (TextButton::textColourOnId, Colours::black);
        mAmpToggleButton.setColour (TextButton::buttonColourId, Colours::white);
        mAmpToggleButton.setColour (TextButton::buttonOnColourId, Colours::lightgrey);
        mAmpToggleButton.setToggleState (true, dontSendNotification);
        mAmpToggleButton.addListener(this);
        
        addAndMakeVisible(mAttToggleButton);
        mAttToggleButton.setButtonText("-");
        mAttToggleButton.setClickingTogglesState (true);
        mAttToggleButton.setRadioGroupId (1);
        mAttToggleButton.setColour (TextButton::textColourOffId, Colours::black);
        mAttToggleButton.setColour (TextButton::textColourOnId, Colours::black);
        mAttToggleButton.setColour (TextButton::buttonColourId, Colours::white);
        mAttToggleButton.setColour (TextButton::buttonOnColourId, Colours::lightgrey);
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

        mFreqAnsweredLabel.setBounds ( 0.05*getWidth(), 0.15*getHeight(), 80, 40 );
        mFreqAnsweredButton.setBounds(0.1*getWidth(), 0.25*getHeight(), 60, 30 );
        
        mCorrectAnswerLabel.setBounds (0.35*getWidth(), 0.15*getHeight(), 90, 40 );
        mCorrectAnswerButton.setBounds(0.4*getWidth(), 0.25*getHeight(), 60, 30);
        
        mFreqBoostLabel.setBounds (0.7*getWidth(), 0.15*getHeight(), 80, 60 );
        mFreqBoostAnsweredLabel.setBounds (0.7*getWidth(), 0.3*getHeight(), 80, 60 );
        
        mTestFreqTitleLabel.setBounds(0.15*getWidth(), 0.53*getHeight(), 0.4*getWidth(), 70);
        g_filterCorrectionButton.setBounds (0.6*getWidth(), 0.58*getHeight(), 80, 40 );
        mFreqLabel.setBounds (0.1*getWidth(), 0.68*getHeight(), 65, 60 );
        mFreqSlider.setBounds (0.35*getWidth(), 0.68*getHeight(), 0.6*getWidth(), 60 );
        mNoSliderLabel.setBounds (0.35*getWidth(), 0.73*getHeight(), 0.65*getWidth(), 80);
        
        mAmpAttLabel.setBounds(0.1*getWidth(), 0.78*getHeight(), 65, 60);
        mAmpToggleButton.setBounds (0.5*getWidth(), 0.83*getHeight(), 40, 30 );
        mAttToggleButton.setBounds (0.65*getWidth(), 0.83*getHeight(), 40, 30) ;
    }
    
    void update()
    {
        mCorrectAnswer =  g_exerciseCentreFrequency ;
        
        
        if( ExerciseGenerator::listexercises.size() > 0 )
        {
            mFreqAnswered =  (ExerciseGenerator::listexercises.back() )-> getCenterFreqAnswered();
            
            mFreqBoost =  (ExerciseGenerator::listexercises.back() )-> getFreqBoost();
            
            mFreqBoostAnswered =  (ExerciseGenerator::listexercises.back() )-> getFreqBoostAnswered();
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
        
        mFreqBoostAnsweredLabel.setText( "Boost Amount Answered: " +
                                        static_cast<String> (mFreqBoostAnswered) + "dB",
                                        dontSendNotification );
        
        
        updateSliderCursorPos(g_exerciseCentreFrequency);
        
        if(g_gainAmplification && g_gainAttenuation)
        {
            mFreqBoostAnsweredLabel.setVisible(true);
            
            mAmpToggleButton.setVisible(true);
            mAttToggleButton.setVisible(true);
            mAmpAttLabel.setVisible(true);
        }
        else
        {
            mFreqBoostAnsweredLabel.setVisible(false);
            
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
        
        
        
        
        
        if ( mFreqAnswered == mCorrectAnswer )
        {
           
            mFreqAnsweredButton.setEnabled(false);
            mCorrectAnswerButton.setEnabled(false);
            
            
           // setButtonColour(false, false);
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
           // setFreqAnsweredButtonColour(true);
        }
        
        if ( button == &mCorrectAnswerButton )
        {
            updateSliderCursorPos(mCorrectAnswer);
           // setCorrectAnswerButtonColour(true);
        }
        
        
        if ( button == &mAmpToggleButton )
        {
            g_gainFactor = fabs(mFreqBoost);
            mAmpToggleButton.setEnabled(false);
            mAttToggleButton.setEnabled(true);
        }
        
        if ( button == &mAttToggleButton )
        {
            g_gainFactor = -(fabs(mFreqBoost));
            mAmpToggleButton.setEnabled(true);
            mAttToggleButton.setEnabled(false);

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
        
        if ( currSliderValue == getFreqValue(mFreqAnswered, g_freqRangeValue)
            && getFreqValue(mFreqAnswered, g_freqRangeValue) ==
                getFreqValue( mCorrectAnswer, g_freqRangeValue) )
        {
            mCorrectAnswerButton.setEnabled(false);
            mFreqAnsweredButton.setEnabled(false);
            
            //setButtonColour(false, false);
        }
        else if( currSliderValue == getFreqValue(mFreqAnswered, g_freqRangeValue))
        {
            mCorrectAnswerButton.setEnabled(true);
            mFreqAnsweredButton.setEnabled(false);
            
            //setButtonColour(true, false);
        }
        else if (currSliderValue == getFreqValue( mCorrectAnswer, g_freqRangeValue) )
        {
            mCorrectAnswerButton.setEnabled(false);
            mFreqAnsweredButton.setEnabled(true);
            
            //setButtonColour(false, true);
        }
        else
        {
            mCorrectAnswerButton.setEnabled(true);
            mFreqAnsweredButton.setEnabled(true);
            
            //setButtonColour(true, true);
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
    
    void setButtonColour(bool button1isWhite, bool button2isWhite)
    {
        setFreqAnsweredButtonColour(button1isWhite);
        setCorrectAnswerButtonColour(button2isWhite);
    }
    
    void setFreqAnsweredButtonColour(bool isWhite)
    {
        if(isWhite)
        {
            mFreqAnsweredButton.setColour(TextButton::buttonColourId, juce::Colours::white);
            mFreqAnsweredButton.setColour(TextButton::textColourOnId, juce::Colours::black);
            mFreqAnsweredButton.setColour(TextButton::textColourOffId, juce::Colours::black);
        }
        else
        {
            mFreqAnsweredButton.setColour(TextButton::buttonColourId, juce::Colours::black);
            mFreqAnsweredButton.setColour(TextButton::textColourOnId, juce::Colours::white);
            mFreqAnsweredButton.setColour(TextButton::textColourOffId, juce::Colours::white);
        }

    }
    
    void setCorrectAnswerButtonColour(bool isWhite)
    {
        if (isWhite)
        {
            mCorrectAnswerButton.setColour(TextButton::buttonColourId, juce::Colours::white);
            mCorrectAnswerButton.setColour(TextButton::textColourOnId, juce::Colours::black);
            mCorrectAnswerButton.setColour(TextButton::textColourOffId, juce::Colours::black);
        }
        else
        {
            mCorrectAnswerButton.setColour(TextButton::buttonColourId, juce::Colours::black);
            mCorrectAnswerButton.setColour(TextButton::textColourOnId, juce::Colours::white);
            mCorrectAnswerButton.setColour(TextButton::textColourOffId, juce::Colours::white);
        }

    }
    
private:
    Label mFreqAnsweredLabel;
    TextButton mFreqAnsweredButton;
    Label mCorrectAnswerLabel;
    TextButton mCorrectAnswerButton;
    Label mFreqBoostLabel;
    Label mFreqBoostAnsweredLabel;
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
    int mFreqBoostAnswered = 12;
    
};

