/*
  ==============================================================================

    GUIHeader.h
    Created: 26 Jun 2017 11:23:08pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class GUIHeader : public Component
{
public:
    GUIHeader()
    {
        
    }
    
    ~GUIHeader()
    {
        
    }
    
    void paint(Graphics& g)override
    {
        g.fillAll (Colours::red);
//        g.setColour (Colours::red);
//        Path roof;
//        roof.addTriangle (0, getHeight(), getWidth(), getHeight(), getWidth() / 2, 0);
//        g.fillPath (roof);
        
    }
    
    
};
