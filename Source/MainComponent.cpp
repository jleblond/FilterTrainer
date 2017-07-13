


#include "MainComponent.h"



MainContentComponent::MainContentComponent()
    :   state (Stopped),
        peakfilter(2),
        thumbnailCache (5),
        thumbnailComp (512, formatManager, thumbnailCache),
        positionOverlay (transportSource)
{
    
    g_questionButton.addListener(this);
    
    addAndMakeVisible (g_openButton);
    g_openButton.setButtonText ("Open...");
    g_openButton.addListener (this);
    
   // addAndMakeVisible (g_playButton);
   // g_playButton.setButtonText ("Play");
    g_playButton.addListener (this);
   // g_playButton.setColour (TextButton::buttonColourId, Colours::green);
   // g_playButton.setEnabled (false);
    
   // addAndMakeVisible (g_stopButton);
  //  g_stopButton.setButtonText ("Stop");
    g_stopButton.addListener (this);
  //  g_stopButton.setColour (TextButton::buttonColourId, Colours::red);
  //  g_stopButton.setEnabled (false);
    
  //  addAndMakeVisible (g_loopingButton);
  //  g_loopingButton.setButtonText ("Looping");
    g_loopingButton.addListener (this);
 //   g_loopingButton.setColour (TextButton::buttonColourId,
  //                          getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
  //  g_loopingButton.setEnabled (false);
    
  //  addAndMakeVisible (g_filterButton);
  //  g_filterButton.setButtonText ("Filter is off");
    g_filterButton.addListener (this);
 //   g_filterButton.setColour (TextButton::buttonColourId,
  //                          getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
 //   g_filterButton.setEnabled (false);
    
    addAndMakeVisible (&currentPositionLabel);
    currentPositionLabel.setText ("Stopped", dontSendNotification);
    currentPositionLabel.setJustificationType(Justification::right);
    
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
    
    
    if(g_loopOn && !g_loopOnRecentClick )
        looping();
    
    
}

void MainContentComponent::looping()
{
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
        if( std::abs( g_loopEndPos - g_loopStartPos ) >= g_minLoopDuration )
            transportSource.setPosition(g_loopStartPos);
    }

}

void MainContentComponent::releaseResources()
{
    transportSource.releaseResources();
   
}


void MainContentComponent::resized()
{
    g_openButton.setBounds   (10, 10, getWidth()/3, 25);
    
    currentPositionLabel.setBounds (-10 + getWidth() - 100 , 10, 100, 35);
    
    const Rectangle<int> thumbnailBounds (10, 40, getWidth() - 20, getHeight() - 50);
    
    thumbnailComp.setBounds (thumbnailBounds);
    positionOverlay.setBounds (thumbnailBounds);

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
    if (button == &g_openButton)  openButtonClicked();
    if (button == &g_playButton)  playButtonClicked();
    if (button == &g_stopButton)  stopButtonClicked();
    if (button == &g_loopingButton) loopButtonChanged();
    if (button == &g_filterButton) filterButtonClicked();
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
    
    if( g_loopOn && g_loopOnRecentClick )
        updateLoopState(true);
    else
        updateLoopState(false);
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

//TransportSource loop for the whole file
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
                g_playButton.setButtonText ("Play");
                g_stopButton.setEnabled (false);
                g_openButton.setEnabled (true);
                transportSource.setPosition (0.0);
                break;
                
            case Starting:
                transportSource.start();
                break;
                
            case Playing:
                g_playButton.setButtonText ("Pause");
                g_stopButton.setEnabled (true);
                g_openButton.setEnabled (false);
                break;
                
            case Pausing:
                g_pausedTime = currentTime ( transportSource.getCurrentPosition() );
                transportSource.stop();
                break;
                
            case Paused:
                g_playButton.setButtonText ("Resume");
                g_openButton.setEnabled (false);
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
            
            g_playButton.setEnabled (true);
            g_filterButton.setEnabled (true);
            g_loopingButton.setEnabled (true);
            
            thumbnailComp.setFile (file);
            readerSource = newSource.release();
        }
    }
}


void MainContentComponent::playButtonClicked()
{
    
    if ((state == Stopped) || (state == Paused))
        changeState (Starting);
    else if (state == Playing)
        changeState (Pausing);
    
}


void MainContentComponent::stopButtonClicked()
{
    
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
        g_filterButton.setButtonText ("Filter is on");
        g_filterButton.setColour(TextButton::buttonColourId, Colours::blue);
    }
    else
    {
        g_filterButton.setButtonText ("Filter is off");
        g_filterButton.setColour(TextButton::buttonColourId,
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
    
    if(g_loopOn)
    {
        //LoopButton was just clicked
        g_loopOnRecentClick = true;
        
        g_loopingButton.setColour (TextButton::buttonColourId, Colours::orange );
        
    }
    else
    {
        g_loopingButton.setColour (TextButton::buttonColourId,
                                 getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    }

}
