
/*
 ==============================================================================
 
 MainComponent.cpp
 
 ==============================================================================
 */


#include "MainComponent.h"
#include "../JuceLibraryCode/JuceHeader.h"


MainContentComponent::MainContentComponent()
:   state (Stopped),
peakfilter(2),
thumbnailCache (5),
waveform( 512, formatManager, thumbnailCache, transportSource )

{
    //Static button Listeners
    g_questionButton.addListener(this);
    g_filterCorrectionButton.addListener(this);
    
    //Open Button
    addAndMakeVisible (g_openButton);
    g_openButton.setButtonText ("Open...");
    g_openButton.setColour(TextButton::buttonColourId, Colours::white);
    g_openButton.addListener (this);
    
    //Zoom IN & Zoom OUT
    addAndMakeVisible (g_ZoomInButton);
    g_ZoomInButton.setButtonText ("+");
    g_ZoomInButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    //g_ZoomInButton.setEnabled(false);
    
    addAndMakeVisible (g_ZoomOutButton);
    g_ZoomOutButton.setButtonText ("-");
    g_ZoomOutButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
    // g_ZoomOutButton.setEnabled(false);
    
    //CurrentPosition
    addAndMakeVisible (&currentPositionLabel);
    currentPositionLabel.setText ("Stopped", dontSendNotification);
    currentPositionLabel.setJustificationType(Justification::right);
    
    //Waveform
    addAndMakeVisible(&waveform);
    
    //TransportBar.h buttons Listeners
    g_playButton.addListener (this);
    g_stopButton.addListener (this);
    g_loopingButton.addListener (this);
    g_filterButton.addListener (this);
    
    //in order to stop audio when session ended
    g_EndSessionButton.addListener (this);
    
    formatManager.registerBasicFormats();
    transportSource.addChangeListener (this);
    
    setAudioChannels (0, 2);
    
    startTimer(20);
    
}


MainContentComponent::~MainContentComponent()
{
    shutdownAudio();
}


void MainContentComponent::prepareToPlay ( int samplesPerBlockExpected, double sampleRate )
{
    this->mSampleRate=sampleRate;
    
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
    
    peakfilter.reset();
    peakfilter.changeParam(sampleRate, g_centreFrequency, g_Q, g_gainFactor);
    
    bandshelf.setup( 2, mSampleRate, g_centreFrequency, g_centreFrequency/g_Q , g_gainFactor, 1 );
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
    
    
}


void MainContentComponent::releaseResources()
{
    transportSource.releaseResources();
}


void MainContentComponent::resized()
{
    g_openButton.setBounds (10, 15, getWidth()/4, 25);
    
    currentPositionLabel.setBounds (-10 + getWidth()/2 , 10, 100, 35);
    
    g_ZoomInButton.setBounds (-10 + getWidth() - 65 , 10, 30, 30);
    g_ZoomOutButton.setBounds (-10 + getWidth() - 30 , 10, 30, 30);
    
    const Rectangle<int> thumbnailBounds (10, 50, getWidth() - 20, getHeight() - 50);
    waveform.setBounds (thumbnailBounds);
    
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
    if (button == &g_filterButton) filterButtonClicked();
    if (button == &g_questionButton) questionButtonChanged();
    if (button == &g_EndSessionButton)   endSessionStopButtonClicked();
    
    if (button == &g_filterCorrectionButton) filterCorrectionButtonClicked();
    
}


void MainContentComponent::timerCallback()
{
    g_currAudioPosition = transportSource.getCurrentPosition();
    g_currDrawPosition = ( g_currAudioPosition / g_srcDurationInSec )
    * waveform.getThumbnailWidth();
    
    
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
    
    
    waveform.updatePositionOverlay();
    
}


String MainContentComponent::currentTime(double currentposition)
{
    //does not check for transportSource.isPlaying - caller function's responsability
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
        }//switch
    }
}

void MainContentComponent::changeFilterSettings(double cFreq, double q, float gainFactor)
{
    peakfilter.updateCoeff( cFreq, q, gainFactor );
    
    assert(this->mSampleRate != 0);
    bandshelf.setup( 2, mSampleRate, cFreq, cFreq/q, gainFactor, 1 );
}

void MainContentComponent::questionButtonChanged()
{
    ExerciseGenerator::Instance().createExercise( g_freqRangeValue, g_filterGainValue,                                 g_gainAmplification, g_gainAttenuation);
    
    
    changeFilterSettings(g_centreFrequency, g_Q, g_gainFactor);
    
}


void MainContentComponent::openButtonClicked()
{
    FileChooser chooser ("Select a Wave file to play...",
                         File::nonexistent,
                         "*.wav; *.aiff; *.mp3; *.flac; *.ogg; *.m4a");
    
    if (chooser.browseForFileToOpen())
    {
        File file = chooser.getResult();
        mCurrAudioFile = file.getFileName();
        
        
        AudioFormatReader* reader = formatManager.createReaderFor (file);
        
        if (reader != nullptr)
        {
            ScopedPointer<LoopingAudioFormatReaderSource> newSource =
            new LoopingAudioFormatReaderSource ( reader, true );
            
            transportSource.setSource ( newSource, 0, nullptr, reader->sampleRate );
            newSource->setLooping(false);   //(required?)
            
            g_srcDurationInSec = transportSource.getLengthInSeconds();
            
            g_playButton.setEnabled (true);
            g_loopingButton.setEnabled (true);
            //g_loopingButton.setColour(TextButton::buttonColourId, Colours::orange);
            g_ZoomInButton.setEnabled(true);
            g_ZoomInButton.setColour(TextButton::buttonColourId, Colours::white);
            
            waveform.setWaveformDisplay(file);
            waveform.resetLoopSelection();
            
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
    
//    if (state == Starting)
//        std::cout<<"Starting"<<std::endl;
//    else if(state == Stopping)
//        std::cout<<"Stopping"<<std::endl;
//    else if(state == Stopped)
//        std::cout<<"Stopped"<<std::endl;
//    else if(state == Paused)
//        std::cout<<"Paused"<<std::endl;
//    else if(state == Pausing)
//        std::cout<<"Pausing"<<std::endl;
//    else if(state == Playing)
//        std::cout<<"Playing"<<std::endl;
//    else
//        std::cout<<"UnknownState"<<std::endl;
    
    if(g_User.getLastSession() != nullptr)
    {
        if( (g_User.getLastSession())->getAudioFileNames().size() > 0 )
        {
            if( (g_User.getLastSession())->getAudioFileNames().back()  != mCurrAudioFile )
                addAudioFileNameSession();
        }
        else
        {
            addAudioFileNameSession();
        }
    }
    
}


void MainContentComponent::stopButtonClicked()
{
    
    if (state == Paused)
        changeState (Stopped);
    else
        changeState (Stopping);
}

void MainContentComponent::endSessionStopButtonClicked()
{
    if (state == Playing)
        playButtonClicked();
    else if (state == Paused)
        ;
    else if (state == Stopped)
        ;
}




void MainContentComponent::filterButtonClicked()
{
    
    g_filterOn = !g_filterOn;
    
    if(g_filterOn)
    {
        g_filterButton.setButtonText ("Filter is ON");
        g_filterButton.setColour(TextButton::buttonColourId, Colours::blue);
    }
    else
    {
        g_filterButton.setButtonText ("Filter is OFF");
        g_filterButton.setColour(TextButton::buttonColourId,
                                 Colours::white );
    }
}

void MainContentComponent::filterCorrectionButtonClicked()
{
    g_filterOn = !g_filterOn;
    
    if(g_filterOn)
    {
        g_filterCorrectionButton.setButtonText ("Filter is ON");
        g_filterCorrectionButton.setColour(TextButton::buttonColourId, Colours::blue);
        
        changeFilterSettings(g_centreFrequency, g_Q, g_gainFactor);
        std::cout<<g_gainFactor<<std::endl;
    }
    else
    {
        g_filterCorrectionButton.setButtonText ("Filter is OFF");
        g_filterCorrectionButton.setColour(TextButton::buttonColourId,
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


void MainContentComponent::addAudioFileNameSession()
{
    if(g_User.getLastSession() != nullptr  &&  mCurrAudioFile != "")
    {
        (g_User.getLastSession())->addAudioFileName(mCurrAudioFile);
        (g_User.getLastSession())->printAudioFileNames();
    }
    
}



