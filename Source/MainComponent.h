/*
  ==============================================================================

    MainComponent.h

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ExerciseGenerator.h"
#include "global.h"
#include "IIRPeakFilter.h"



class MainContentComponent   : public AudioAppComponent,
public ChangeListener,
public Button::Listener,
public Timer
{
public:
    MainContentComponent();
    
    ~MainContentComponent();
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
    void releaseResources() override;
    
    void resized() override;

    void changeListenerCallback (ChangeBroadcaster* source) override;
    
    void buttonClicked (Button* button) override;

    
    void timerCallback() override;
    
    String currentTime(double currentposition);
    
    void updateLoopState (bool shouldLoop);
    
    
private:
    enum TransportState
    {
        Stopped,
        Starting,
        Playing,
        Pausing,
        Paused,
        Stopping
    };
    
    void changeState (TransportState newState);
    
    void openButtonClicked();
    
    void playButtonClicked();
    
    void stopButtonClicked();
    
    void filterButtonClicked();
    
    void loopButtonChanged();
    
    //==========================================================================
    
    TextButton openButton;
    TextButton playButton;
    TextButton stopButton;
    TextButton filterButton;
    ToggleButton loopingToggle;
    Label currentPositionLabel;
    
    String pausedtime;
    bool filteron = false;
    
    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    
    IIRPeakFilter peakfilter;
    
    TransportState state;
    
    //LookAndFeel_V3 lookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
