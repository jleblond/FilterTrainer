/*
  ==============================================================================

    GUIHeaderBasicWindow.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "InfoWindowComponent.h"
#include "AboutWindowComponent.h"
#include "StatsWindowComponent.h"


const int basicwindowwidth=600;
const int basicwindowheight=600;


class BasicWindow : public DocumentWindow
{
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicWindow)
    
    
public:
    
    BasicWindow (const String& name, int menuitem)
    : DocumentWindow (name,
                      Colours::lightgrey,
                      DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar (true);
        setContentOwned (generateContent(menuitem), true);
        setResizable (true, true);
        centreWithSize (getWidth(), getHeight());
        setVisible (true);
        
    }
    
    ~BasicWindow()
    {
        
    }
    
    Component* generateContent(int menuitem)
    {
        switch(menuitem)
        {
            case 1:
                return new InfoWindowComponent(basicwindowwidth, basicwindowheight);
                break;
            case 2:
                return new AboutWindowComponent(basicwindowwidth, basicwindowheight);
                break;
            case 3:
                return new StatsWindowComponent(basicwindowwidth, basicwindowheight);
                break;
            default:
                return new AboutWindowComponent(basicwindowwidth, basicwindowheight);
        }
    }
    
    
    void closeButtonPressed() override
    {
        delete this;
    }
};


