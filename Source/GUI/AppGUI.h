/*
  ==============================================================================

    AppGUI.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"


#include "GUIHeader.h"
#include "GUIStartSession.h"
#include "GUIMainApp.h"

#include "../ReportGenerator.h"

#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;

//APP dimensions
const int HEIGHT=700;
const int WIDTH=900;    //must ensure same value GUIMainApp member called width

class AppGUI : public Component,
                public Button::Listener
{
public:
    AppGUI()
    {
        setSize (WIDTH, HEIGHT);
        

        setLookAndFeel( mLF );
        
        addAndMakeVisible (mHeader);
        
        addAndMakeVisible(mStartSession);
        
        addAndMakeVisible(mMainApp);
        mMainApp.setVisible(false);
        
        g_StartSessionButton.addListener(this);
        g_EndSessionButton.addListener(this);
        
        
    }
    
    ~AppGUI()
    {
        delete mLF;
    }
    
    void paint(Graphics& g)override
    {
        //g.fillAll(Colours::midnightblue);
       // g.fillAll(Colour::Colour(0, 51, 102) );
        // g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
         g.fillAll(Colour::fromRGB(69, 0, 3) );  //very dark red
    }

    void resized() override
    {
        Rectangle<int> area (getLocalBounds());
        
        mHeader.setBounds (area.removeFromTop( mHeaderHeight*getHeight()));
        
        //mStartSession.setBounds( rectAvail.removeFromTop(0.5*getHeight()) );
        mStartSession.setBounds( area );
        mMainApp.setBounds (area);
    }
    
    void buttonClicked(Button* button) override
    {
        
        if(button == &g_StartSessionButton)
        {
            
            mHeader.setUserLabel(g_User.mUsername);
            
            mStartSession.setVisible(false);
            
            //Entering the Main APP
            //IMPORTANT: SESSION IS ONLY CREATED AT THIS POINT
            //everything before the audioapp regular display panel can't use any SESSION stuff
            
            g_User.createSession(g_freqRangeValue, g_filterGainValue, g_gainAmplification, g_gainAttenuation);
            bool isset = mMainApp.setSession( g_User.getLastSession() );
            
            if(isset)
            {
                mMainApp.setVisible(true);
                mHeader.displayEndSessionButton(true);
                mHeader.displayCommentButton(true);
            }
            else
                std::cout<<"Failure in 'mMainApp.setSession(Session*)"<<std::endl;
            
            
            t1 = steady_clock::now();
            
            
            mMainApp.update();

        }
        
        if(button == &g_EndSessionButton)
        {
            
            t2 = steady_clock::now();
            
            duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
            double timeInSeconds = time_span.count();
            
            (g_User.getLastSession())->setDuration(timeInSeconds);
            
            
            
            int sessionQcount = (g_User.getLastSession())->getQuestionsCount();
            
            
            if( sessionQcount >= mNbQuestionsReportGen )
            {
                
                Report report = ( ReportGenerator::Instance().createReport(
                                                                           *(g_User.getLastSession()),
                                                                           g_User
                                                                           )
                                 );
                report.print();
                
                
                if (ReportGenerator::Instance().generateReportFile(report) )
                {
                    endSession();
                }
                
            }
            else //nb of min questions asked required for report generation has not been reached
            {
                String creditsStr = String(CharPointer_UTF8 (
                                                             "You need to answer at least 10 questions.\n\nDo you want to end this session without generating a report?     ")
                                           );
                
                juce::AlertWindow *alert = new juce::AlertWindow ("Report was not generated",creditsStr, juce::AlertWindow::WarningIcon );
                alert->setColour(AlertWindow::backgroundColourId, Colours::black);
                //alert->setBounds(300,150,700,200);
                
                alert->addButton ("Yes",     1, KeyPress (KeyPress::returnKey, 0, 0));
                alert->addButton ("No", 0, KeyPress (KeyPress::escapeKey, 0, 0));
                
                
                int returnValue = alert->runModalLoop();
                delete alert;
                
                if(returnValue)
                {
                    endSession();
                }

                
            }
            

        } //button endSession listener
        
    } //general button clicked listener function
    
    
    void endSession()
    {
        mStartSession.setVisible(true);
        mMainApp.setVisible(false);
        mHeader.displayEndSessionButton(false);
        mHeader.displayCommentButton(false);
        
        mMainApp.resetExControlsPanel();
    }
    
    

private:
    GUIHeader mHeader;
    GUIStartSession mStartSession;
    GUIMainApp mMainApp;
                       
    LookAndFeel *mLF = new LookAndFeel_V4( (LookAndFeel_V4::getLightColourScheme() ) );
  
    int mNbQuestionsReportGen = 10;
    
    //GUI sections proportions
    const float mHeaderHeight = 0.15;
    
    steady_clock::time_point t1, t2;
};
