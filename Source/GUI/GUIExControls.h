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
        
        
        //Amplification Atttenuation Buttons Section

        
        addAndMakeVisible(g_answerAmpButton);
        g_answerAmpButton.setButtonText("It's a boost!");
        g_answerAmpButton.setColour (TextButton::buttonColourId, Colours::white);
        g_answerAmpButton.addListener(this);
        g_answerAmpButton.setVisible(false);
        
        addAndMakeVisible(g_answerAttButton);
        g_answerAttButton.setButtonText("It's a cut!");
        g_answerAttButton.setColour (TextButton::buttonColourId, Colours::white);
        g_answerAttButton.addListener(this);
        g_answerAttButton.setVisible(false);
        
        
        //Dummy Filter button
        
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
        g.setColour(Colours::white);

    }
    
    void resized() override
    {
        mExerciseSettings.setBounds(0, 0, getWidth(), 0.75*getHeight() );
        mExerciseAnswering.setBounds(0, 0, getWidth(), 0.75*getHeight() );
        mExerciseCorrection.setBounds(0, 0, getWidth(), 0.75*getHeight() );
        
        g_questionButton.setBounds (0.3*getWidth(), 0.75*getHeight(), 120, 0.25*getHeight() );
        g_answerButton.setBounds (0.3*getWidth(), 0.75*getHeight(), 120, 0.25*getHeight() );
        g_correctionButton.setBounds (0.3*getWidth(), 0.75*getHeight(), 120, 0.25*getHeight() );
        
        
        g_answerAmpButton.setBounds(0.2*getWidth(), 0.75*getHeight(), 70, 70);
        g_answerAttButton.setBounds(0.55*getWidth(), 0.75*getHeight(), 70, 70);
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
            
            
            g_filterButton.setVisible(true);
            g_filterButton.setEnabled(true);
            g_filterButton.setColour(TextButton::buttonColourId, Colours::white);
            
             changePanelVisibility(false, true, false);
            
            //order is important, changePanelVisibility affect g_answerButton visibility
            //so this function must be called before the next one (down there) in order for the g_answerButton visibility to be modified
            
            if(g_gainAmplification && g_gainAttenuation)
            {
                g_answerButton.setVisible(false);
                setAmpAttButtonsVisibility(true);
            }
            else
            {
                g_answerButton.setVisible(true);
                setAmpAttButtonsVisibility(false);
            }
            
           
                
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
            
            setAmpAttButtonsVisibility(false);
            
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
        
        if (button == &g_answerAmpButton)
        {
            mExerciseAnswering.ampButtonSelect(true);
            g_answerButton.triggerClick();
        }
        if (button == &g_answerAttButton)
        {
            mExerciseAnswering.ampButtonSelect(false);
            g_answerButton.triggerClick();
        }
        
    }
    
   void updateExCorrectionSlider()
    {
        mExerciseCorrection.updateSliderRange();
    }
    

    void setAmpAttButtonsVisibility(bool isVisible)
    {
        if(isVisible)
        {
            g_answerAmpButton.setVisible(true);
            g_answerAttButton.setVisible(true);
        }
        else
        {
            g_answerAmpButton.setVisible(false);
            g_answerAttButton.setVisible(false);
        }
    }
    
    
    
private:
    ExerciseSettings mExerciseSettings;
    ExerciseAnswering mExerciseAnswering;
    ExerciseCorrection mExerciseCorrection;
};
