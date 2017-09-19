/*
  ==============================================================================

    GUIHeader.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "GUIBasicWindow.h"


class GUIHeader : public Component, public Button::Listener
{
public:
    GUIHeader()
    {
        menu1.setButtonText(str_menu1);
        menu1.addListener(this);
        addAndMakeVisible(menu1);
       // menu1.setEnabled(false);
        
        menu2.setButtonText(str_menu2);
        menu2.addListener(this);
        addAndMakeVisible(menu2);
      //  menu2.setEnabled(false);
        
        menu3.setButtonText(str_menu3);
        menu3.addListener(this);
        addAndMakeVisible(menu3);
       // menu3.setEnabled(false);
    }
    
    ~GUIHeader()
    {
        
    }
    
    void paint(Graphics& g)override
    {
        g.fillAll(Colours::black);
        
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
        
        menu1.setBounds(0, 0, elementwidth, elementheight);
        menu2.setBounds(menuxoffset+elementwidth, 0, elementwidth, elementheight);
        menu3.setBounds(menuxoffset+2*elementwidth, 0, elementwidth, elementheight);
        
        //        std::cout<<"elheight: "<<elementheight<<std::endl;
        //        std::cout<<"elwidth: "<<elementwidth<<std::endl;
    }
    
    void buttonClicked(Button* button) override
    {
    
        
        if(button== &menu1)
        {
            std::cout<<"menu1"<<std::endl;
            commentDialogBox();
            
            
        }
        else if(button == &menu2)
        {
            std::cout<<"menu2"<<std::endl;
            infoDialogBox();
            
        }
        else if(button == &menu3)
        {
            std::cout<<"menu3"<<std::endl;
            
        }

    }
    
    void commentDialogBox()
    {
#if JUCE_MODAL_LOOPS_PERMITTED
        AlertWindow w ("AlertWindow demo..",
                       "This AlertWindow has a couple of extra components added to show how to add drop-down lists and text entry boxes.",
                       AlertWindow::NoIcon);
        
       // w.addTextEditor ("text", "", "Enter your comment here:");

        
//        const char* options[] = { "option 1", "option 2", "option 3", "option 4", nullptr };
//        w.addComboBox ("option", StringArray (options), "some options");
        
        w.addCustomComponent(&mPropertyPanel);
        mPropertyPanel.setSize(400,400);
        mPropertyPanel.addSection ("Comment", createTextEditor());
        
        w.addButton ("OK",     1, KeyPress (KeyPress::returnKey, 0, 0));
        w.addButton ("Cancel", 0, KeyPress (KeyPress::escapeKey, 0, 0));
        
        
        if (w.runModalLoop() != 0) // is they picked 'ok'
        {
            // this is the item they chose in the drop-down list..
//            const int optaionIndexChosen = w.getComboBoxComponent ("option")->getSelectedItemIndex();
//            ignoreUnused (optionIndexChosen);
            
            // this is the text they entered..
           // String commentText = w.getTextEditorContents ("text");
           // (g_User.getLastSession())->addComment(commentText);
        }
#endif
    }
    
    void infoDialogBox()
    {
        AlertWindow::AlertIconType icon = AlertWindow::InfoIcon;
        
        AlertWindow::showMessageBoxAsync (icon,
                                          "This is an AlertWindow",
                                          "And this is the AlertWindow's message. Blah blah blah blah blah blah blah blah blah blah blah blah blah.",
                                          "OK");
    }
    
    static Array<PropertyComponent*> createTextEditor()
    {
        Array<PropertyComponent*> comps;
        
        comps.add (new TextPropertyComponent (Value (var (
                                                          "")),
                                              "Multi-line text",
                                              1000, true));
        
        return comps;
    }
    
    
private:
    
    String str_title="FILTER ";
    String str_subtitle=""; 
    
    TextButton menu1;
    String str_menu1="Add a comment";
    
    TextButton menu2;
    String str_menu2="INFO";
    
    TextButton menu3;
    String str_menu3="END SESSION";
    
    PropertyPanel mPropertyPanel;
    
    
};
