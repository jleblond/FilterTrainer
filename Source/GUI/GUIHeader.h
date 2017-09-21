/*
  ==============================================================================

    GUIHeader.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../global.h"

class GUIHeader : public Component, public Button::Listener
{
public:
    GUIHeader()
    {
        menu1.setButtonText(str_menu1);
        menu1.addListener(this);
        addAndMakeVisible(menu1);
       // menu1.setEnabled(false);
        menu1.setVisible(false);
        
        menu2.setButtonText(str_menu2);
        menu2.addListener(this);
        addAndMakeVisible(menu2);
      //  menu2.setEnabled(false);
        
        g_EndSessionButton.setButtonText(str_menu3);
       // g_EndSessionButton.addListener(this);
        addAndMakeVisible(g_EndSessionButton);
        g_EndSessionButton.setVisible(false);
       // g_EndSessionButton.setEnabled(false);
        
        
        addAndMakeVisible(mUserLabel);
        mUserLabel.setJustificationType(juce::Justification::right);
       // mTitleLabel.setText("ANSWER SECTION", dontSendNotification);
    }
    
    ~GUIHeader()
    {
        delete mTextEditor;
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
        g_EndSessionButton.setBounds(menuxoffset+2*elementwidth, 0, elementwidth, elementheight);
        
        mUserLabel.setBounds(0, getHeight()-20, getWidth(), elementheight);
        
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
        else if(button == &g_EndSessionButton)
        {
            std::cout<<"g_EndSessionButton"<<std::endl;
            
        }

    }
    
    void displayCommentButton(bool b)
    {
        menu1.setVisible(b);
    }
    
    void displayEndSessionButton(bool b)
    {
        g_EndSessionButton.setVisible(b);
    }
    
    
    void setUserLabel(String user)
    {
        mUserLabel.setText(user, dontSendNotification);
    }
    
    void commentDialogBox()
    {
#if JUCE_MODAL_LOOPS_PERMITTED
        AlertWindow w ("Comments",
                       "You can add comments whenever you like and they will appear in your session report.",
                       AlertWindow::NoIcon);

        
//        const char* options[] = { "option 1", "option 2", "option 3", "option 4", nullptr };
//        w.addComboBox ("option", StringArray (options), "some options");
        
        
        w.addCustomComponent(mTextEditor);
        mTextEditor->setSize(300,300);
        mTextEditor->setMultiLine(true);
        mTextEditor->setReturnKeyStartsNewLine (true);
       
        
        w.addButton ("OK",     1, KeyPress (KeyPress::returnKey, 0, 0));
        w.addButton ("Cancel", 0, KeyPress (KeyPress::escapeKey, 0, 0));
        
        
        if (w.runModalLoop() != 0) // is they picked 'ok'
        {
            // this is the item they chose in the drop-down list..
//            const int optaionIndexChosen = w.getComboBoxComponent ("option")->getSelectedItemIndex();
//            ignoreUnused (optionIndexChosen);

            
            String commentText = mTextEditor->getText();
            (g_User.getLastSession())->addComment(commentText);
            (g_User.getLastSession())->printAllComments();
            mTextEditor->clear();
            

            
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
    

    
private:
    
    String str_title="FILTER ";
    String str_subtitle=""; 
    
    TextButton menu1;
    String str_menu1="Add a comment";
    
    TextButton menu2;
    String str_menu2="INFO";
    
    //string for g_EndSessionButton
    String str_menu3="END SESSION";
    
    
    Label mUserLabel;

    
    TextEditor* mTextEditor = new TextEditor("textEditor");
    
};
