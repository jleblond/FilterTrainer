/*
  ==============================================================================

    ExerciseCorrection.h
    Created: 18 Jul 2017 1:41:42am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../ExerciseGenerator.h"
#include "../global.h"


class ExerciseCorrection : public Component,
public Button::Listener
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

        mCurrFreqLabel.setBounds ( 0.2*getWidth(), 0.2*getHeight(), 120, 60 );
        mCorrectAnswerLabel.setBounds (0.2*getWidth(), 0.3*getHeight(), 120, 60 );
        mFreqBoostLabel.setBounds (0.2*getWidth(), 0.7*getHeight(), 120, 60 );
    }
    
    void update()
    {
        String freqanswered = "";
        String correctanswer = static_cast<String>( g_centreFrequency );
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
    }
    
    void buttonClicked(Button* button) override
    {
        
        
    }
    

    
    
private:
    Label mCurrFreqLabel;
    Label mCorrectAnswerLabel;
    Label mFreqBoostLabel;
    
    Label mTitleLabel;
    
    

    
};

