


#include "MainComponent.h"





MainContentComponent::MainContentComponent()
:   state (Stopped), peakfilter(2)
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

MainContentComponent::~MainContentComponent()
{
    shutdownAudio();
}

void MainContentComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    this->sampleRate=sampleRate;
    
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
 
    peakfilter.reset();
    peakfilter.changeParam(sampleRate, centreFrequency, Q, gainFactor);
    
    bandshelf.setup(2, this->sampleRate, centreFrequency, centreFrequency/Q, gainFactor, 1);
    
    std::cout<< " prepare to play " <<std::endl;
    
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
    if(filteron)
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
                                       lastgain, mainVolume);
    lastgain = mainVolume;
    
}

void MainContentComponent::releaseResources() 
{
    transportSource.releaseResources();
   
}

void MainContentComponent::resized()
{
    openButton.setBounds   (10, 10, getWidth() - 20, 20);
    playButton.setBounds   (10, 40, getWidth() - 20, 20);
    stopButton.setBounds   (10, 70, getWidth() - 20, 20);
    filterButton.setBounds (10, 100, getWidth() - 20, 20);
    
    loopingToggle.setBounds(10, 130, getWidth() - 20, 20);
    currentPositionLabel.setBounds (10+0.3*getWidth(), 130, getWidth() - 20, 20);
}

void MainContentComponent::changeListenerCallback (ChangeBroadcaster* source)
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

void MainContentComponent::buttonClicked (Button* button)
{
    if (button == &openButton)  openButtonClicked();
    if (button == &playButton)  playButtonClicked();
    if (button == &stopButton)  stopButtonClicked();
    if (button == &filterButton) filterButtonClicked();
    if (button == &loopingToggle)   loopButtonChanged();
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
        currentPositionLabel.setText (pausedtime, dontSendNotification);
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
            
            playButton.setEnabled (true);
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
    
    std::cout<<"centrefreq "<<centreFrequency<<std::endl;
    std::cout<<"gain "<<gainFactor<<std::endl;
    
    peakfilter.updateCoeff(centreFrequency, Q, gainFactor );
    
    assert(this->sampleRate != 0);
    bandshelf.setup(2, this->sampleRate, centreFrequency, centreFrequency/Q, gainFactor, 1);
    
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
    filteron = !filteron;
    
    if(filteron)
        filterButton.setButtonText ("Filter is on");
    else
        filterButton.setButtonText ("Filter is off");
}

void MainContentComponent::loopButtonChanged()
{
    updateLoopState (loopingToggle.getToggleState());
}
