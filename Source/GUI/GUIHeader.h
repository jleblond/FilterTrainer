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
        menu1.setButtonText(str_menu1);
        addAndMakeVisible(menu1);
        
        menu2.setButtonText(str_menu2);
        addAndMakeVisible(menu2);
        
        menu3.setButtonText(str_menu3);
        addAndMakeVisible(menu3);
    }
    
    ~GUIHeader()
    {
        
    }
    
    void paint(Graphics& g)override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        
        g.setColour (Colours::white);
        
        g.setFont (22.0f);
        g.drawText (str_title, 0, getHeight()/2, getWidth(), getHeight()/2,
                    Justification::centred, true);
        
        g.setFont (16.0f);
        g.drawText (str_subtitle, getLocalBounds(),
                    Justification::centred, true);
    }
    
    void resized() override
    {
        float menuxoffset=getWidth()*0.75;
        float elementheight=getHeight()/6;
        float elementwidth=getWidth()/12;
        
        Rectangle<int> area = getLocalBounds();
        
        menu1.setBounds(menuxoffset, 0, elementwidth, elementheight);
        menu2.setBounds(menuxoffset+elementwidth, 0, elementwidth, elementheight);
        menu3.setBounds(menuxoffset+2*elementwidth, 0, elementwidth, elementheight);
        
        //        std::cout<<"elheight: "<<elementheight<<std::endl;
        //        std::cout<<"elwidth: "<<elementwidth<<std::endl;
    }

private:
    String str_subtitle="FILTER [prototype]";
    String str_title="Inner Ear";
    
    TextButton menu1;
    String str_menu1="INFO";
    
    TextButton menu2;
    String str_menu2="ABOUT";
    
    TextButton menu3;
    String str_menu3="STATS";
    
};
