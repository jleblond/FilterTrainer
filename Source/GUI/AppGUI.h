/*
  ==============================================================================

    AppGUI.h
    Created: 26 Jun 2017 11:22:34pm
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


//APP dimensions
const int HEIGHT=700;
const int WIDTH=900;

class AppGUI : public Component
{
public:
    AppGUI()
    {
        setSize (WIDTH, HEIGHT);
        
        addAndMakeVisible (mHeader);
        addAndMakeVisible (mPlayer);
        addAndMakeVisible (mExcontrols);
        addAndMakeVisible (mStats);
        addAndMakeVisible (mVolume);
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
        
        mHeader.setBounds (area.removeFromTop( mHeaderHeight*getHeight() ));
        mStats.setBounds(area.removeFromBottom( mFooterHeight*getHeight() ));
        mExcontrols.setBounds (area.removeFromLeft( mLeftSidebarWidth*getWidth() ));
        mVolume.setBounds(area.removeFromRight( mRightSidebarWidth*getWidth() ));
        mPlayer.setBounds(area.removeFromRight( (WIDTH-mLeftSidebarWidth)*getWidth() ));
    }

private:
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
