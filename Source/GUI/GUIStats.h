/*
  ==============================================================================

    GUIStats.h
    Created: 26 Jun 2017 11:24:10pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once


#include "../../JuceLibraryCode/JuceHeader.h"

class GUIStats : public Component
{
public:
    GUIStats()
    {
        
    }
    
    ~GUIStats()
    {
        
    }
    
    void paint(Graphics& g)override
    {
         g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
         g.fillAll(Colours::white);
    }
    
    
};
