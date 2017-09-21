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

        }
        
        if(button == &g_EndSessionButton)
        {
            mStartSession.setVisible(true);
            mMainApp.setVisible(false);
            mHeader.displayEndSessionButton(false);
            mHeader.displayCommentButton(false);
        }
        
    }

private:
    GUIHeader mHeader;
    GUIStartSession mStartSession;
    GUIMainApp mMainApp;

    //GUI sections proportions
    const float mHeaderHeight = 0.15;
};
