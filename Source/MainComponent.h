/*
  ==============================================================================

    MainComponent.h

  ==============================================================================
*/




#define IIRFILTERON 0
//SELECT FILTER CLASS
//0: using Dsp::ChebyshevI::BandShelf
//              from DspFilters - "A Collection of Useful C++ Classes for Digital Signal Processing"
//1: using IIRPeakFilter custom class
//              based on JUCE::IIRFilter class


#pragma once
#include <assert.h> 

#include "../JuceLibraryCode/JuceHeader.h"
#include "../DspFilters/DspFilters/Dsp.h"

#include "IIRPeakFilter.h"
#include "LoopingAudioFormatReaderSource.h"
#include "LoopingAudioTransportSource.h"

#include "ExerciseGenerator.h"


#include "GUI/AudioThumbnailComponent.h"
#include "GUI/WaveformDisplay.h"

#include "global.h"


class MainContentComponent   : public AudioAppComponent,
public ChangeListener,
public Button::Listener,
public Timer
{
public:
    MainContentComponent();
    
    ~MainContentComponent();
    
    void prepareToPlay ( int samplesPerBlockExpected, double sampleRate ) override;
    
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
    
    void changeFilterSettings(double cFreq, double q, float gainFctr);
    
    void questionButtonChanged();
    
    void openButtonClicked();
    
    void playButtonClicked();
    
    void stopButtonClicked();
    
    void filterButtonClicked();
    
    void filterCorrectionButtonClicked();
    
    void loopingButtonClicked();
    
    void transportSourceChanged();
    
    void addAudioFileNameSession();
    
    //==========================================================================

    Label currentPositionLabel;
    
    double mSampleRate = 0;
    float mLastGain = 1.0f;
    
    String mCurrAudioFile = "";
    
    AudioFormatManager formatManager;
    ScopedPointer<LoopingAudioFormatReaderSource> readerSource;
    LoopingAudioTransportSource transportSource;
    TransportState state;
    
    IIRPeakFilter peakfilter;
    Dsp::SimpleFilter <Dsp::ChebyshevI::BandShelf <2>, 2> bandshelf;
    
    AudioThumbnailCache thumbnailCache;

    WaveformDisplay waveform;
    
    //LookAndFeel_V3 lookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
