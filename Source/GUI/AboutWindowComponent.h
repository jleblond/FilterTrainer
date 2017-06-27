/*
  ==============================================================================

    AboutWindowComponent.h
    Created: 27 Jun 2017 2:15:06pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once


#include "../../JuceLibraryCode/JuceHeader.h"

class AboutWindowComponent : public Component
{
public:
    AboutWindowComponent(int basicwindowwidth, int basicwindowheight)
    {
        setSize (basicwindowwidth, basicwindowheight);
    }
    
    
    ~AboutWindowComponent()
    {
        
    }
    
    void paint(Graphics& g)override
    {
        g.fillAll(Colours::blue);
        
    }
    
    void resized() override
    {

        //.setBounds (0, 0, getWidth(), getHeight());
    }
    
    
};
