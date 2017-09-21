/*
  ==============================================================================

    GUIMainApp.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "GUIExControls.h"
#include "GUIHeader.h"
#include "GUIPlayer.h"
#include "GUIStats.h"
#include "MasterVolume.h"

//==============================================================================
/*
*/
class GUIMainApp :   public Component
{
public:
    GUIMainApp()
    {
        
        addAndMakeVisible (mPlayer);
        
        addAndMakeVisible (mExcontrols);
        
        addAndMakeVisible (mStats);
        
        addAndMakeVisible (mVolume);
    }
    
    ~GUIMainApp()
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
        
        mStats.setBounds(area.removeFromBottom( mFooterHeight*getHeight() ));
        mExcontrols.setBounds (area.removeFromLeft( mLeftSidebarWidth*getWidth() ));
        mVolume.setBounds(area.removeFromRight( mRightSidebarWidth*getWidth() ));
        mPlayer.setBounds(area.removeFromRight( (width-mLeftSidebarWidth)*getWidth() ));
    
    }
    
    
    bool setSession(Session* s)
    {
        mStats.setSession(s);
        
        if(mStats.getSession() != nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    

    
private:
    GUIExControls mExcontrols;
    GUIPlayer mPlayer;
    GUIStats mStats;
    
    MasterVolume mVolume;
    
    //GUI sections proportions
    const int width = 900;
    const float mLeftSidebarWidth = 0.3;
    const float mRightSidebarWidth = 0.1;
    const float mFooterHeight = 0.35;
};
