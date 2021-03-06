/*
  ==============================================================================

    UserSession.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class UserSession : public Component,
private TextEditor::Listener
{
public:
    UserSession()
    {
        addAndMakeVisible(mTxtFieldLabel);
        mTxtFieldLabel.setText("Username: ", dontSendNotification);
        mTxtFieldLabel.setBounds(250, 250, 60, 30);
        addAndMakeVisible(mTextField);
        
        mTextField.setBounds(375, 250, 250, 30);
        mTextField.setColour(juce::TextEditor::textColourId, Colours::black);
        mTextField.setColour(juce::TextEditor::outlineColourId, juce::Colour::fromRGB(0,0,0));
        mTextField.setColour(juce::TextEditor::backgroundColourId, juce::Colour::fromRGB(247, 249, 252));
        mTextField.setColour(juce::TextEditor::focusedOutlineColourId, juce::Colour::fromRGB(0,0,0));
        mTextField.setText("");
        
    }
    
    ~UserSession()
    {
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
    
    String getTextFieldValue()
    {
        String s = "";
        s = mTextField.getText();
        return s;
    }
    
    
private:
    TextEditor mTextField;
    Label mTxtFieldLabel;
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUIStartSession)
};
