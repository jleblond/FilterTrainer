/*
  ==============================================================================

    GUIPlayer.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once


#include "../../JuceLibraryCode/JuceHeader.h"
#include "../MainComponent.h"
#include "TransportBar.h"

class GUIPlayer : public Component
{
public:
    GUIPlayer()
    {
        addAndMakeVisible(component);
        addAndMakeVisible(transport);
    }
    
    ~GUIPlayer()
    {
        delete component;
    }
    
    void paint(Graphics& g)override
    {
        g.fillAll (juce::Colours::darkgrey);
        
    }
    
    void resized() override
    {
        Rectangle<int> area (getLocalBounds());

        component->setBounds ( area.removeFromTop( 0.8*getHeight() ));
        transport.setBounds ( area.removeFromTop( 0.2*getHeight() ) );
    }
    
private:
    MainContentComponent* component = new MainContentComponent();
    TransportBar transport;

    
};
