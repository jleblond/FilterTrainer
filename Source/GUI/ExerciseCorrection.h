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
        
        
        addAndMakeVisible(mCurrFreqLabel);
        mCurrFreqLabel.setText("", dontSendNotification);
        
        
        
        //        amplify.setButtonText("+");
        //        amplify.addListener(this);
        //        addAndMakeVisible(amplify);
        //
        //        attenuate.setButtonText("-");
        //        attenuate.addListener(this);
        //        addAndMakeVisible(attenuate);
        
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
        mCurrFreqLabel.setBounds ( 0.2*getWidth(), 0.15*getHeight(), 60, 35 );
        
    }
    
    void update()
    {
        mCurrFreqLabel.setText( "text here" , dontSendNotification);
        
    }
    
    void buttonClicked(Button* button) override
    {
        
        //        if(button == &amplify)
        //            g_gainAmplification = !g_gainAmplification;
        //
        //        if(button == &attenuate)
        //            g_gainAttenuation = !g_gainAttenuation;
        
    }
    

    
    
private:

    Label mCurrFreqLabel;
    
    

    
};

