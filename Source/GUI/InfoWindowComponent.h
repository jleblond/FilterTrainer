/*
  ==============================================================================

    InfoWindowComponent.h
    Created: 27 Jun 2017 2:14:35pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once


#include "../../JuceLibraryCode/JuceHeader.h"

class InfoWindowComponent : public Component
{
public:
    InfoWindowComponent(int basicwindowwidth, int basicwindowheight)
    {
        setSize (basicwindowwidth, basicwindowheight);
    }
    
    ~InfoWindowComponent()
    {
        
    }
    
    void paint(Graphics& g)override
    {
        g.fillAll(Colours::green);
        
    }
    
    
};
