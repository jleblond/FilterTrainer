/*
  ==============================================================================

    GUIStartSession.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "UserSession.h"
#include "ConfigExercise.h"

#include "../User.h"

#include "../global.h"


//==============================================================================
/*
*/
class GUIStartSession    : public Component,
                           private TextEditor::Listener,
                           public Button::Listener
{
public:
    GUIStartSession()
    {
        addAndMakeVisible(mUserSession);
        
        addAndMakeVisible(mConfigExercise);
        mConfigExercise.setVisible(false);
        
        addAndMakeVisible(mNextButton);
        mNextButton.setButtonText("NEXT");
        mNextButton.addListener(this);
        
        addAndMakeVisible(g_StartSessionButton);
        g_StartSessionButton.setButtonText("START SESSION");
        g_StartSessionButton.setVisible(false);
        
        
    }

    ~GUIStartSession()
    {
    }

    void paint (Graphics& g) override
    {

        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        //g.setColour (Colours::white);
        g.setFont (14.0f);
//        g.drawText ("Start a new session", getLocalBounds(),
//                    Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        Rectangle<int> area (getLocalBounds());
        Rectangle<int> area2 (getLocalBounds());
        mUserSession.setBounds(area.removeFromTop(0.7*getHeight() ));
        mConfigExercise.setBounds(area2.removeFromTop(0.7*getHeight() ));
        
        mNextButton.setBounds( area.removeFromBottom(0.5*getHeight() ) );
        g_StartSessionButton.setBounds( area2.removeFromBottom(0.5*getHeight() ) );

    }
    
    void buttonClicked(Button* button) override
    {
        
        if(button == &mNextButton)
        {
            mUserSession.setVisible(false);
            mConfigExercise.setVisible(true);
            
            mNextButton.setVisible(false);
            g_StartSessionButton.setVisible(true);
            
            g_User.changeUsername( mUserSession.getTextFieldValue() ) ;
        }
        
    }
        
private:

    TextButton mNextButton;
    
    UserSession mUserSession;
    ConfigExercise mConfigExercise;
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUIStartSession)
};
