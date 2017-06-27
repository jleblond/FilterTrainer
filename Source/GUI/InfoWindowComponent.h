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
    InfoWindowComponent()
    {
        setSize (600,600);
    }
    
    ~InfoWindowComponent()
    {
        
    }
    
    void paint(Graphics& g)override
    {
        g.fillAll(Colours::green);
        
    }
    
    
};
