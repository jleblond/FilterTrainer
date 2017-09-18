/*
  ==============================================================================

    GUIStartSession.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../User.h"

//==============================================================================
/*
*/
class GUIStartSession    : public Component,
                           private TextEditor::Listener
{
public:
    GUIStartSession()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        
        addAndMakeVisible(mTextField);
       // mTextField->setBounds (100, 250, 400, 48);
       // mTextField->setText ("Single-line text box");
        
        mTextField.setBounds(10, 50, 180, 24);
        mTextField.setColour(juce::TextEditor::textColourId, Colours::black);
        mTextField.setColour(juce::TextEditor::outlineColourId, juce::Colour::fromRGB(0,0,0));
        mTextField.setColour(juce::TextEditor::backgroundColourId, juce::Colour::fromRGB(247, 249, 252));
        mTextField.setColour(juce::TextEditor::focusedOutlineColourId, juce::Colour::fromRGB(0,0,0));
        mTextField.setText("username value lorem ipsum");
    }

    ~GUIStartSession()
    {
        //delete mUser;
    }

    void paint (Graphics& g) override
    {

        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        //g.setColour (Colours::white);
        g.setFont (14.0f);
        g.drawText ("Start a new session", getLocalBounds(),
                    Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
         Rectangle<int> area (getLocalBounds());
       // mTextField.setBounds(area.removeFromBottom(0.4*getHeight()));

    }

private:
    //User* mUser = new User("");
    TextEditor mTextField;
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUIStartSession)
};
