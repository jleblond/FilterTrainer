/*
  ==============================================================================

    AppGUI.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "GUIStartSession.h"
#include "GUIExControls.h"
#include "GUIHeader.h"
#include "GUIPlayer.h"
#include "GUIStats.h"

#include "MasterVolume.h"


//APP dimensions
const int HEIGHT=700;
const int WIDTH=900;

class AppGUI : public Component,
                public Button::Listener
{
public:
    AppGUI()
    {
        setSize (WIDTH, HEIGHT);
        
        
        addAndMakeVisible (mHeader);
        
        addAndMakeVisible(mStartSession);
        
        g_StartSessionButton.addListener(this);
        
        
        addAndMakeVisible (mPlayer);
        mPlayer.setVisible(false);
        
        addAndMakeVisible (mExcontrols);
        mExcontrols.setVisible(false);
        
        addAndMakeVisible (mStats);
        mStats.setVisible(false);
        
        addAndMakeVisible (mVolume);
        mVolume.setVisible(false);
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
        Rectangle<int> rectAvail(area);
        
        mStats.setBounds(area.removeFromBottom( mFooterHeight*getHeight() ));
        mExcontrols.setBounds (area.removeFromLeft( mLeftSidebarWidth*getWidth() ));
        mVolume.setBounds(area.removeFromRight( mRightSidebarWidth*getWidth() ));
        mPlayer.setBounds(area.removeFromRight( (WIDTH-mLeftSidebarWidth)*getWidth() ));
        
        mStartSession.setBounds( rectAvail.removeFromTop(0.5*getHeight()) );
    }
    
    void buttonClicked(Button* button) override
    {
        
        if(button == &g_StartSessionButton)
        {
            mStartSession.setVisible(false);
            
            g_User.createSession(g_freqRangeValue);
            mStats.setSession( g_User.getLastSession() );
            
            if(mStats.getSession() != nullptr)
            {
                mPlayer.setVisible(true);
                mExcontrols.setVisible(true);
                mStats.setVisible(true);
                mVolume.setVisible(true);
            }
            
        }
        
    }

private:
    GUIStartSession mStartSession;
    GUIExControls mExcontrols;
    GUIHeader mHeader;
    GUIPlayer mPlayer;
    GUIStats mStats;
    
    
    MasterVolume mVolume;
    
    //GUI sections proportions
    const float mHeaderHeight = 0.15;
    const float mLeftSidebarWidth = 0.3;
    const float mRightSidebarWidth = 0.1;
    const float mFooterHeight = 0.3;
};
