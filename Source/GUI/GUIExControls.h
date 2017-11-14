/*
  ==============================================================================

    GUIExControls.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../ExerciseGenerator.h"
#include "ExerciseSettings.h"
#include "ExerciseAnswering.h"
#include "ExerciseCorrection.h"
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
        
        addAndMakeVisible(&mExerciseCorrection);
        mExerciseCorrection.setVisible(false);
        
        g_questionButton.setButtonText("NEW QUESTION");
        g_questionButton.addListener(this);
        addAndMakeVisible(g_questionButton);
        
        g_answerButton.setButtonText("ANSWER");
        g_answerButton.addListener(this);
        addAndMakeVisible(g_answerButton);
        g_answerButton.setVisible(false);
        
        g_correctionButton.setButtonText("OK");
        g_correctionButton.addListener(this);
        addAndMakeVisible(g_correctionButton);
        g_correctionButton.setVisible(false);
        
        g_dummyFilterButton.addListener(this);
    }
    
    ~GUIExControls()
    {
        
    }
    
    void paint(Graphics& g) override
    {
        //sidebar
       // g.fillAll(Colour::Colour(191, 92, 0) ); //dark red
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        g.fillAll(Colours::black);

    }
    
    void resized() override
    {
        mExerciseSettings.setBounds(0, 0, getWidth(), 0.75*getHeight() );
        mExerciseAnswering.setBounds(0, 0, getWidth(), 0.75*getHeight() );
        mExerciseCorrection.setBounds(0, 0, getWidth(), 0.75*getHeight() );
        
        g_questionButton.setBounds (0.3*getWidth(), 0.75*getHeight(), 120, 0.25*getHeight() );
        g_answerButton.setBounds (0.3*getWidth(), 0.75*getHeight(), 120, 0.25*getHeight() );
        g_correctionButton.setBounds (0.3*getWidth(), 0.75*getHeight(), 120, 0.25*getHeight() );
    }
    
    void changePanelVisibility(bool vis1, bool vis2, bool vis3)
    {
        mExerciseSettings.setVisible(vis1);
        g_questionButton.setVisible(vis1);
        
        mExerciseAnswering.setVisible(vis2);
        g_answerButton.setVisible(vis2);
        
        mExerciseCorrection.setVisible(vis3);
        g_correctionButton.setVisible(vis3);
    }
    
    void buttonClicked(Button* button) override
    {
        
        if(button == &g_questionButton)
        {
            
            std::cout<<"GUIExControls"<<std::endl;
            std::cout<<"freqrange_value:"<<g_freqRangeValue<<" dBAmpSlider_value:"<<g_filterGainValue<<
            " amplification_value:"<<g_gainAmplification<<" attenuation_value:"<<g_gainAttenuation<<
            std::endl;
        

            mExerciseAnswering.update();
            
            changePanelVisibility(false, true, false);
            
            g_filterButton.setVisible(true);
            g_filterButton.setEnabled(true);
                
        }
        
        if(button == &g_answerButton )
        {
            mExerciseAnswering.answer();
            
            mExerciseCorrection.update();
            //mExerciseCorrection.updateSliderCursorPos(g_exerciseCentreFrequency);
            
            g_filterButton.setVisible(false);
            g_dummyFilterButton.setVisible(false);
            
            if( g_filterOn == true )
            {
                g_filterButton.triggerClick();
            }
            
            changePanelVisibility(false, false, true);
        }
        
        
        if( button == &g_correctionButton )
        {
            g_dummyFilterButton.setVisible(true);
            
            changePanelVisibility(true, false, false);
            
            if( g_filterOn == true )
            {
                g_filterCorrectionButton.triggerClick();
            }
            
            
        }
        
    }
    
   void updateExCorrectionSlider()
    {
        mExerciseCorrection.updateSliderRange();
    }

    
private:
    ExerciseSettings mExerciseSettings;
    ExerciseAnswering mExerciseAnswering;
    ExerciseCorrection mExerciseCorrection;
};
