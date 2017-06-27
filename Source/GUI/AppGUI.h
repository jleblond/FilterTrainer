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

//APP dimensions
const int HEIGHT=700;
const int WIDTH=800;

class AppGUI : public Component
{
public:
    AppGUI()
    {
        addAndMakeVisible (gheader);
        addAndMakeVisible (gplayer);
        addAndMakeVisible (gexcontrols);
        addAndMakeVisible (gstats);
    }
    
    ~AppGUI()
    {
        
    }
    
    void paint(Graphics& g)override
    {
        g.fillAll(Colours::lightblue);
    
    }

    void resized() override
    {
        Rectangle<int> area (getLocalBounds());
        
        gheader.setBounds (area.removeFromTop( headerHeight*getHeight() ));
        gstats.setBounds(area.removeFromBottom( footerHeight*getHeight() ));
        gexcontrols.setBounds (area.removeFromRight( sidebarWidth*getWidth() ));
        gplayer.setBounds(area.removeFromLeft( (WIDTH-sidebarWidth)*getWidth() ));
    }

private:
    GUIExControls gexcontrols;
    GUIHeader gheader;
    GUIPlayer gplayer;
    GUIStats gstats;
    
    //GUI sections proportions
    const float headerHeight = 0.15;
    const float sidebarWidth = 0.4;
    const float footerHeight = 0.3;
};
