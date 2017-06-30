
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ExerciseGenerator.h"

class MainContentComponent   : public AudioAppComponent,
public ChangeListener,
public Button::Listener,
public Timer
{
public:
    MainContentComponent()
    :   state (Stopped)
    {
        addAndMakeVisible (&openButton);
        openButton.setButtonText ("Open...");
        openButton.addListener (this);
        
        addAndMakeVisible (&playButton);
        playButton.setButtonText ("Play");
        playButton.addListener (this);
        playButton.setColour (TextButton::buttonColourId, Colours::green);
        playButton.setEnabled (false);
        
        addAndMakeVisible (&stopButton);
        stopButton.setButtonText ("Stop");
        stopButton.addListener (this);
        stopButton.setColour (TextButton::buttonColourId, Colours::red);
        stopButton.setEnabled (false);
        
        addAndMakeVisible (&filterButton);
        filterButton.setButtonText ("Filter is off");
        filterButton.addListener (this);
        filterButton.setColour (TextButton::buttonColourId, Colours::blue);
        //filterButton.setEnabled (false);
        
        addAndMakeVisible (&loopingToggle);
        loopingToggle.setButtonText ("Loop");
        loopingToggle.addListener (this);
        
        addAndMakeVisible (&currentPositionLabel);
        currentPositionLabel.setText ("Stopped", dontSendNotification);
        
        formatManager.registerBasicFormats();
        transportSource.addChangeListener (this);
        
        setAudioChannels (0, 2);
        
        startTimer(20);
    }
    
    ~MainContentComponent()
    {
        shutdownAudio();
    }
    
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
    }
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        if (readerSource == nullptr)
        {
            bufferToFill.clearActiveBufferRegion();
            return;
        }
        
        
       // Exercise* currentexercise=ExerciseGenerator::listexercises.back();
       
        
        IIRFilterAudioSource(&transportSource, false);
//        IIRCoefficients iircoeff=IIRCoefficients::makePeakFilter(<#double sampleRate#>, <#double centreFrequency#>, 1.4, float gainFactor)
        //
        
        if(filteron)
        {
            //transportSource.getNextAudioBlock (bufferToFill); //temporary
        }
        else
        {
            transportSource.getNextAudioBlock (bufferToFill);
        }
        
    }
    
    void releaseResources() override
    {
        transportSource.releaseResources();
    }
    
    void resized() override
    {
        openButton.setBounds   (10, 10, getWidth() - 20, 20);
        playButton.setBounds   (10, 40, getWidth() - 20, 20);
        stopButton.setBounds   (10, 70, getWidth() - 20, 20);
        filterButton.setBounds (10, 100, getWidth() - 20, 20);
        
        loopingToggle.setBounds(10, 130, getWidth() - 20, 20);
        currentPositionLabel.setBounds (10+0.3*getWidth(), 130, getWidth() - 20, 20);
    }
    
    void changeListenerCallback (ChangeBroadcaster* source) override
    {
        if (source == &transportSource)
        {
            if (transportSource.isPlaying())
                changeState (Playing);
            else if ((state == Stopping) || (state == Playing))
                changeState (Stopped);
            else if (Pausing == state)
                changeState (Paused);
        }
    }
    
    void buttonClicked (Button* button) override
    {
        if (button == &openButton)  openButtonClicked();
        if (button == &playButton)  playButtonClicked();
        if (button == &stopButton)  stopButtonClicked();
        if (button == &filterButton) filterButtonClicked();
        if (button == &loopingToggle)   loopButtonChanged();
    }
    
    void timerCallback() override
    {
        if (transportSource.isPlaying())
        {
            String positionStr = currentTime ( transportSource.getCurrentPosition() );
            
            currentPositionLabel.setText (positionStr, dontSendNotification);
        }
        else if(state == Paused)
        {
            currentPositionLabel.setText (pausedtime, dontSendNotification);
        }
        else
        {
            currentPositionLabel.setText ("Stopped", dontSendNotification);
        }
    }
    
    String currentTime(double currentposition)
    {   //does not check for transportSource.isPlaying - caller function's responsability
        //very often currentposition = transportSource.getCurrentPosition()
        const RelativeTime position (currentposition);
        
        const int minutes = ((int) position.inMinutes()) % 60;
        const int seconds = ((int) position.inSeconds()) % 60;
        const int millis  = ((int) position.inMilliseconds()) % 1000;
        
        const String positionString (String::formatted ("%02d:%02d:%03d", minutes, seconds, millis));
        
        return positionString;
    }
    
    void updateLoopState (bool shouldLoop)
    {
        if (readerSource != nullptr)
            readerSource->setLooping (shouldLoop);
    }

    
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
    
    void changeState (TransportState newState)
    {
        if (state != newState)
        {
            state = newState;
            
            switch (state)
            {
                case Stopped:
                    playButton.setButtonText ("Play");
                    stopButton.setButtonText ("Stop");
                    stopButton.setEnabled (false);
                    openButton.setEnabled (true);
                    transportSource.setPosition (0.0);
                    break;
                    
                case Starting:
                    transportSource.start();
                    break;
                    
                case Playing:
                    playButton.setButtonText ("Pause");
                    stopButton.setButtonText ("Stop");
                    stopButton.setEnabled (true);
                    openButton.setEnabled (false);
                    break;
                    
                case Pausing:
                    pausedtime = currentTime ( transportSource.getCurrentPosition() );
                    transportSource.stop();
                    break;
                    
                case Paused:
                    playButton.setButtonText ("Resume");
                    stopButton.setButtonText ("Return to Zero");
                    openButton.setEnabled (false);
                    break;
                    
                case Stopping:
                    transportSource.stop();
                    break;
            }
        }
    }
    
    void openButtonClicked()
    {
        FileChooser chooser ("Select a Wave file to play...",
                             File::nonexistent,
                             "*.wav");
        
        if (chooser.browseForFileToOpen())
        {
            File file (chooser.getResult());
            AudioFormatReader* reader = formatManager.createReaderFor (file);
            
            if (reader != nullptr)
            {
                ScopedPointer<AudioFormatReaderSource> newSource = new AudioFormatReaderSource (reader, true);
                transportSource.setSource (newSource, 0, nullptr, reader->sampleRate);
                playButton.setEnabled (true);
                readerSource = newSource.release();
            }
        }
    }
    
    void playButtonClicked()
    {
        updateLoopState (loopingToggle.getToggleState());
        
        if ((state == Stopped) || (state == Paused))
            changeState (Starting);
        else if (state == Playing)
            changeState (Pausing);
    }

    
    void stopButtonClicked()
    {
        updateLoopState (loopingToggle.getToggleState());
        
        if (state == Paused)
            changeState (Stopped);
        else
            changeState (Stopping);
    }
    
    void filterButtonClicked()
    {
        filteron = !filteron;
        
        if(filteron)
            filterButton.setButtonText ("Filter is on");
        else
            filterButton.setButtonText ("Filter is off");
    }

    void loopButtonChanged()
    {
        updateLoopState (loopingToggle.getToggleState());
    }
    
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
    TransportState state;
    
    //LookAndFeel_V3 lookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
