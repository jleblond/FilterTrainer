/*
  ==============================================================================

    StatsWindowComponent.h
    Created: 27 Jun 2017 2:15:24pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once


#include "../../JuceLibraryCode/JuceHeader.h"

class StatsWindowComponent : public Component
{
public:
    StatsWindowComponent()
    {
        
    }
    
    ~StatsWindowComponent()
    {
        
    }
    
    void paint(Graphics& g)override
    {
        g.fillAll(Colours::red);
        
    }
    
    
};
