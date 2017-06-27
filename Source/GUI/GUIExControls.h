/*
  ==============================================================================

    GUIExControls.h
    Created: 26 Jun 2017 11:23:45pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class GUIExControls : public Component
{
public:
    GUIExControls()
    {
        
    }
    
    ~GUIExControls()
    {
        
    }
    
    void paint(Graphics& g) override
    {
        //sidebar
        g.fillAll(Colours::green);
    }
    
private:



};
