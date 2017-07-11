/*
  ==============================================================================

    GUIPlayer.h
    Created: 26 Jun 2017 11:23:25pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once


#include "../../JuceLibraryCode/JuceHeader.h"
#include "../MainComponent.h"

class GUIPlayer : public Component
{
public:
    GUIPlayer()
    {
        addAndMakeVisible(component);
    }
    
    ~GUIPlayer()
    {
        delete component;
    }
    
    void paint(Graphics& g)override
    {
        g.fillAll (juce::Colours::grey);
        
    }
    
    void resized() override
    {
        component->setBounds (0, 0, getWidth(), getHeight());
    }
    
private:
    MainContentComponent* component=new MainContentComponent();
    
    
};
