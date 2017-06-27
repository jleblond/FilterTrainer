/*
  ==============================================================================

    GUIPlayer.h
    Created: 26 Jun 2017 11:23:25pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once


#include "../../JuceLibraryCode/JuceHeader.h"

class GUIPlayer : public Component
{
public:
    GUIPlayer()
    {
        
    }
    
    ~GUIPlayer()
    {
        
    }
    
    void paint(Graphics& g)override
    {
        g.fillAll(Colours::gold);
        
    }
    
    
};
