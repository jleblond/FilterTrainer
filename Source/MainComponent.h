/*
  ==============================================================================

    MainComponent.h

  ==============================================================================
*/

#define IIRFILTERON 1

#pragma once
#include <assert.h> 

#include "../JuceLibraryCode/JuceHeader.h"


#include "IIRPeakFilter.h"
#include "ExerciseGenerator.h"

#include "global.h"

#include "../DspFilters/DspFilters/Dsp.h"


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
    
    double sampleRate = 0;
    
    // Main volume
    float lastgain = 1.0f;
    //float gain = 1.0f;
    
    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    TransportState state;
    
    IIRPeakFilter peakfilter;
    Dsp::SimpleFilter <Dsp::ChebyshevI::BandShelf <2>, 2> bandshelf;

    
    //LookAndFeel_V3 lookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
