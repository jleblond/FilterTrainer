


#include "MainComponent.h"



MainContentComponent::MainContentComponent()
    :   state (Stopped),
        peakfilter(2),
        thumbnailCache (5),
        thumbnailComp (512, formatManager, thumbnailCache),
        positionOverlay (transportSource)
{
    
    g_questionButton.addListener(this);
    
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
    
    addAndMakeVisible (&loopingButton);
    loopingButton.setButtonText ("Looping");
    loopingButton.addListener (this);
    loopingButton.setColour (TextButton::buttonColourId,
                            getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    loopingButton.setEnabled (false);
    
    addAndMakeVisible (&filterButton);
    filterButton.setButtonText ("Filter is off");
    filterButton.addListener (this);
    filterButton.setColour (TextButton::buttonColourId,
                            getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    filterButton.setEnabled (false);
    
    addAndMakeVisible (&currentPositionLabel);
    currentPositionLabel.setText ("Stopped", dontSendNotification);
    
    addAndMakeVisible (&thumbnailComp);
    addAndMakeVisible (&positionOverlay);
    
    formatManager.registerBasicFormats();
    transportSource.addChangeListener (this);
    
    setAudioChannels (0, 2);
    
    startTimer(20);
    
}


MainContentComponent::~MainContentComponent()
{
    shutdownAudio();
}


void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    this->mSampleRate=sampleRate;
    
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
 
    peakfilter.reset();
    peakfilter.changeParam(sampleRate, g_centreFrequency, g_Q, g_gainFactor);
    
    bandshelf.setup(2, mSampleRate, g_centreFrequency, g_centreFrequency/g_Q, g_gainFactor, 1);
    
}


void MainContentComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    
    // Clear buffer
    if (readerSource == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    
    //Regular audio playback
    transportSource.getNextAudioBlock (bufferToFill);

    
    // Filter processing
    if(g_filterOn)
    {
#if IIRFILTERON
        peakfilter.process( *bufferToFill.buffer );
#else
        bandshelf.process( (*bufferToFill.buffer).getNumSamples(),
                           (*bufferToFill.buffer).getArrayOfWritePointers() );
#endif
    }
    
    
    // Apply gain to buffer
    bufferToFill.buffer->applyGainRamp( bufferToFill.startSample, bufferToFill.numSamples,
                                       mLastGain, g_mainVolume);
    mLastGain = g_mainVolume;
    
    
    //Loop Pre-Conditions
    if(g_loopStartPos < 0)
        g_loopStartPos = 0;
    
    if(g_loopEndPos < 0)
        g_loopEndPos = 0;
    
    if(g_loopStartPos > transportSource.getLengthInSeconds() - 1)
        g_loopStartPos = transportSource.getLengthInSeconds() - 1;
    
    if(g_loopEndPos > transportSource.getLengthInSeconds() - 1 )
        g_loopEndPos = transportSource.getLengthInSeconds() - 1;
    
    //Loop
    if( transportSource.getCurrentPosition() >= g_loopEndPos  )
    {
            if( std::abs( g_loopEndPos - g_loopStartPos ) >= 0.1 )
                transportSource.setPosition(g_loopStartPos);
    }
    
}


void MainContentComponent::releaseResources() 
{
    transportSource.releaseResources();
   
}


void MainContentComponent::resized()
{
    openButton.setBounds   (10, 10, getWidth() - 20, 20);
    
    const Rectangle<int> thumbnailBounds (10, 40, getWidth() - 20, getHeight() - 120);
    thumbnailComp.setBounds (thumbnailBounds);
    positionOverlay.setBounds (thumbnailBounds);
    
    
    playButton.setBounds   (10, 350, 80, 30);
    stopButton.setBounds   (100, 350, 80, 30);
    loopingButton.setBounds (190 , 350, 80, 30);
    loopingToggle.setBounds(280, 350, 100, 30);
    
    currentPositionLabel.setBounds (400, 350, 100, 30);
    
    filterButton.setBounds (500, 350, 80, 30);
}


void MainContentComponent::changeListenerCallback (ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        transportSourceChanged();
    }
}


void MainContentComponent::buttonClicked (Button* button)
{
    if (button == &openButton)  openButtonClicked();
    if (button == &playButton)  playButtonClicked();
    if (button == &stopButton)  stopButtonClicked();
    if (button == &loopingButton) loopButtonChanged();
    if (button == &filterButton) filterButtonClicked();
    if (button == &g_questionButton) questionButtonChanged();
}


void MainContentComponent::timerCallback()
{
    if (transportSource.isPlaying())
    {
        String positionStr = currentTime ( transportSource.getCurrentPosition() );
        
        currentPositionLabel.setText (positionStr, dontSendNotification);
    }
    else if(state == Paused)
    {
        currentPositionLabel.setText (g_pausedTime, dontSendNotification);
    }
    else
    {
        currentPositionLabel.setText ("Stopped", dontSendNotification);
    }
}


String MainContentComponent::currentTime(double currentposition)
{   //does not check for transportSource.isPlaying - caller function's responsability
    //very often currentposition = transportSource.getCurrentPosition()
    const RelativeTime position (currentposition);
    
    const int minutes = ((int) position.inMinutes()) % 60;
    const int seconds = ((int) position.inSeconds()) % 60;
    const int millis  = ((int) position.inMilliseconds()) % 1000;
    
    const String positionString (String::formatted ("%02d:%02d:%03d", minutes, seconds, millis));
    
    return positionString;
}


void MainContentComponent::updateLoopState (bool shouldLoop)
{
    if (readerSource != nullptr)
        readerSource->setLooping (shouldLoop);
}


void MainContentComponent::changeState (TransportState newState)
{
    if (state != newState)
    {
        state = newState;
        
        switch (state)
        {
            case Stopped:
                playButton.setButtonText ("Play");
                stopButton.setEnabled (false);
                openButton.setEnabled (true);
                transportSource.setPosition (0.0);
                break;
                
            case Starting:
                transportSource.start();
                break;
                
            case Playing:
                playButton.setButtonText ("Pause");
                stopButton.setEnabled (true);
                openButton.setEnabled (false);
                break;
                
            case Pausing:
                g_pausedTime = currentTime ( transportSource.getCurrentPosition() );
                transportSource.stop();
                break;
                
            case Paused:
                playButton.setButtonText ("Resume");
                openButton.setEnabled (false);
                break;
                
            case Stopping:
                transportSource.stop();
                break;
        }
    }
}


void MainContentComponent::questionButtonChanged()
{
    ExerciseGenerator::Instance().createExercise(g_freqRangeValue, g_filterGainValue, g_gainAmplification, g_gainAttenuation);
    
    peakfilter.updateCoeff(g_centreFrequency, g_Q, g_gainFactor );
    
    assert(this->mSampleRate != 0);
    bandshelf.setup(2, mSampleRate, g_centreFrequency, g_centreFrequency/g_Q, g_gainFactor, 1);

}


void MainContentComponent::openButtonClicked()
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
           // g_loopEndPos = transportSource.getLengthInSeconds();
            
            playButton.setEnabled (true);
            filterButton.setEnabled (true);
            loopingButton.setEnabled (true);
            
            thumbnailComp.setFile (file);
            readerSource = newSource.release();
        }
    }
}


void MainContentComponent::playButtonClicked()
{
    updateLoopState (loopingToggle.getToggleState());
    
    if ((state == Stopped) || (state == Paused))
        changeState (Starting);
    else if (state == Playing)
        changeState (Pausing);
    
}


void MainContentComponent::stopButtonClicked()
{
    updateLoopState (loopingToggle.getToggleState());
    
    if (state == Paused)
        changeState (Stopped);
    else
        changeState (Stopping);
}


void MainContentComponent::filterButtonClicked()
{
    g_filterOn = !g_filterOn;
    
    if(g_filterOn)
    {
        filterButton.setButtonText ("Filter is on");
        filterButton.setColour(TextButton::buttonColourId, Colours::blue);
    }
    else
    {
        filterButton.setButtonText ("Filter is off");
        filterButton.setColour(TextButton::buttonColourId,
                               getLookAndFeel().findColour (ResizableWindow::backgroundColourId) );
    }
}


void MainContentComponent::transportSourceChanged()
{
    if (transportSource.isPlaying())
        changeState (Playing);
    else if ((state == Stopping) || (state == Playing))
        changeState (Stopped);
    else if (Pausing == state)
        changeState (Paused);
}


void MainContentComponent::loopButtonChanged()
{
    
    g_loopOn = !g_loopOn;
    updateLoopState (g_loopOn);
    
    if(g_loopOn)
    {
        g_lastLoopStartPos = g_loopStartPos;
        g_lastLoopEndPos = g_loopEndPos;
        
        loopingButton.setColour (TextButton::buttonColourId, Colours::orange );
        g_loopStartPos = 0;
        g_loopEndPos = 0; //or  transportSource.getLengthInSeconds() ...?
        
    }
    else
    {
        g_loopStartPos = g_lastLoopStartPos;
        g_loopEndPos = g_lastLoopEndPos;
        
        loopingButton.setColour (TextButton::buttonColourId,
                                 getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        
    }

}
