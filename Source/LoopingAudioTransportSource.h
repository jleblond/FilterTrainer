/*
  ==============================================================================

    LoopingTransportSource.h
    Created: 5 Aug 2017 6:50:39pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "LoopingAudioFormatReaderSource.h"


class LoopingAudioTransportSource : public AudioTransportSource {
    LoopingAudioFormatReaderSource* source;
    
    float sampleRate;
public:
    LoopingAudioTransportSource():
        AudioTransportSource(), sampleRate (44100.0)
    {
    };
    
    void setSource (LoopingAudioFormatReaderSource* newSource,
                    int readAheadBufferSize = 0,
                    TimeSliceThread* readAheadThread = nullptr,
                    double sourceSampleRateToCorrectFor = 0.0,
                    int maxNumChannels = 2) {
        source = newSource;
        AudioTransportSource::setSource(newSource, readAheadBufferSize, readAheadThread, sourceSampleRateToCorrectFor, maxNumChannels);
    }
    void prepareToPlay (int samplesPerBlockExpected, double newSampleRate)
    {
        sampleRate = newSampleRate;
        AudioTransportSource::prepareToPlay(samplesPerBlockExpected, newSampleRate);
    }
    
    void setNextPosition(float nextPosition)
    {
        if (source != nullptr)
            source->setNextReadPosition((int64) (nextPosition * sampleRate));
    }
    void setEndPosition(float endPosition){
        if (source != nullptr)
            source->setEndReadPosition((int64) (endPosition * sampleRate));
    }
    
    void setEndPosition(){
        if (source != nullptr)
            source->setEndReadPosition( (int64) (source->getTotalLength()) );
    }
    
    void resetPosition(){
        if (source != nullptr) {
            source->setNextReadPosition(0);
            source->setEndReadPosition(source->getTotalLength());
        }
    }
    
    
    
};
