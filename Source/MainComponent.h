/*
  ==============================================================================

    MainComponent.h

  ==============================================================================
*/

#define IIRFILTERON 1


#pragma once
#include <assert.h> 

#include "../JuceLibraryCode/JuceHeader.h"
#include "../DspFilters/DspFilters/Dsp.h"

#include "IIRPeakFilter.h"
#include "ExerciseGenerator.h"


#include "GUI/AudioThumbnailComponent.h"
#include "GUI/PositionOverlay.h"

#include "global.h"


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
    
    void questionButtonChanged();
    
    void openButtonClicked();
    
    void playButtonClicked();
    
    void stopButtonClicked();
    
    void filterButtonClicked();
    
    void loopingButtonClicked();
    
    void transportSourceChanged();
    
    void loopButtonChanged();
    
    //==========================================================================
    
    TextButton openButton;
    TextButton playButton;
    TextButton stopButton;
    TextButton filterButton;
    TextButton loopingButton;
    TextButton loopingToggle; //kept for state (check?)
    Label currentPositionLabel;
    
    
    double mSampleRate = 0;
    float mLastGain = 1.0f;
    
    
    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    TransportState state;
    
    IIRPeakFilter peakfilter;
    Dsp::SimpleFilter <Dsp::ChebyshevI::BandShelf <2>, 2> bandshelf;
    
    AudioThumbnailCache thumbnailCache;
    AudioThumbnailComponent thumbnailComp;
    PositionOverlay positionOverlay;

    
    //LookAndFeel_V3 lookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
