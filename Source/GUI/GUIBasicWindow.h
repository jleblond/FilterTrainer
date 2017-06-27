/*
  ==============================================================================

    GUIHeaderBasicWindow.h
    Created: 27 Jun 2017 2:04:58pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "InfoWindowComponent.h"
#include "AboutWindowComponent.h"
#include "StatsWindowComponent.h"


class BasicWindow : public DocumentWindow
{
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicWindow)
    
public:
    BasicWindow (const String& name)
    : DocumentWindow (name,
                      Colours::lightgrey,
                      DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar (true);
        setContentOwned (new InfoWindowComponent(), true);
        setResizable (true, true);
        
        centreWithSize (getWidth(), getHeight());
        setVisible (true);
    }
    
    ~BasicWindow()
    {
        
    }
    
    
    
   // static BasicWindow* bwindow;
    
    void closeButtonPressed() override
    {
        delete this;
       // bwindow=nullptr;
    }
};

//BasicWindow* BasicWindow::bwindow=nullptr;
