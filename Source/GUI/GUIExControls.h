/*
  ==============================================================================

    GUIExControls.h
    Created: 26 Jun 2017 11:23:45pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../ExerciseGenerator.h"
#include "ExerciseSettings.h"
#include "ExerciseAnswering.h"
#include "../global.h"


class GUIExControls : public Component,
                    public Button::Listener
{
public:
    GUIExControls()
    {
        addAndMakeVisible(&mExerciseSettings);
        mExerciseSettings.setVisible(true);
        addAndMakeVisible(&mExerciseAnswering);
        mExerciseAnswering.setVisible(false);
        
        g_questionButton.setButtonText("NEW QUESTION");
        g_questionButton.addListener(this);
        addAndMakeVisible(g_questionButton);
    }
    
    ~GUIExControls()
    {
        
    }
    
    void paint(Graphics& g) override
    {
        //sidebar
       //g.fillAll(Colours::darkred);
       // g.fillAll(Colour::Colour(191, 92, 0) ); //dark red
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    }
    
    void resized() override
    {
        mExerciseSettings.setBounds(0, 0, getWidth(), 0.75*getHeight() );
        mExerciseAnswering.setBounds(0, 0, getWidth(), 0.75*getHeight() );
        
        g_questionButton.setBounds (0.3*getWidth(), 0.75*getHeight(), 120, 0.25*getHeight() );
    }
    
    void buttonClicked(Button* button) override
    {
        
        if(button == &g_questionButton)
        {
            //std::cout<< g_questionMode<<std::endl;
            
            std::cout<<"GUIExControls"<<std::endl;
            std::cout<<"freqrange_value:"<<g_freqRangeValue<<" dBAmpSlider_value:"<<g_filterGainValue<<
            " amplification_value:"<<g_gainAmplification<<" attenuation_value:"<<g_gainAttenuation<<
            std::endl;
            
            g_questionMode = !g_questionMode;
            
            if( g_questionMode )
            {
                
                mExerciseSettings.setVisible(true);
                mExerciseAnswering.setVisible(false);
            }
            else
            {
               mExerciseSettings.setVisible(false);
               mExerciseAnswering.setVisible(true);
            }
                
        }
        
    }

    
private:
    ExerciseSettings mExerciseSettings;
    ExerciseAnswering mExerciseAnswering;
    
};
