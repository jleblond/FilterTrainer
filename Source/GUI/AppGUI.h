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
        
        
        addAndMakeVisible (mHeader);
        
        addAndMakeVisible(mStartSession);
        
        addAndMakeVisible(mMainApp);
        mMainApp.setVisible(false);
        
        g_StartSessionButton.addListener(this);
        g_EndSessionButton.addListener(this);
        
    }
    
    ~AppGUI()
    {
        
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
            
            g_User.createSession(g_freqRangeValue);
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
            
            
            mMainApp.updateExCorrectionSlider();

        }
        
        if(button == &g_EndSessionButton)
        {
            
            t2 = steady_clock::now();
            
            duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
            double timeInSeconds = time_span.count();
            
            (g_User.getLastSession())->setDuration(timeInSeconds);
            
            Report report = ( ReportGenerator::Instance().createReport(
                                                               *(g_User.getLastSession()),
                                                                 g_User
                                                                      )
                             );
            report.print();
            
            
            if (ReportGenerator::Instance().generateReportFile(report) )
            {
                mStartSession.setVisible(true);
                mMainApp.setVisible(false);
                mHeader.displayEndSessionButton(false);
                mHeader.displayCommentButton(false);
                
                mMainApp.resetExControlsPanel();
            }
            
        }
        
    }
    
    

private:
    GUIHeader mHeader;
    GUIStartSession mStartSession;
    GUIMainApp mMainApp;

    //GUI sections proportions
    const float mHeaderHeight = 0.15;
    
    steady_clock::time_point t1, t2;
};
