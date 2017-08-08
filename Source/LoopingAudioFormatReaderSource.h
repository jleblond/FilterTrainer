/*
  ==============================================================================

    LoopingAudioFormatReader.h
    Created: 5 Aug 2017 6:50:56pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "global.h"


class LoopingAudioFormatReaderSource : public PositionableAudioSource
{
    OptionalScopedPointer<AudioFormatReader> reader;
    int64 nStart, nEnd, nNumberSample;
    int64 volatile nextPlayPos;
    //bool volatile looping;
    
    bool valid;
    
public:
    LoopingAudioFormatReaderSource (AudioFormatReader* const r,
                                   const bool deleteReaderWhenThisIsDeleted)
    : reader (r, deleteReaderWhenThisIsDeleted),
    nStart(0),
    nNumberSample(0),
    nextPlayPos (0),
    //looping (false),
    valid(false)
    {
        jassert (reader != nullptr);
        if (reader != nullptr) {
            nEnd =  reader->lengthInSamples;
            nNumberSample = reader->lengthInSamples;
            valid = true;
        }
    };
    
    ~LoopingAudioFormatReaderSource() {};
    
    int64 getTotalLength() const     override              { return reader->lengthInSamples; };
    void setNextReadPosition (int64 newPosition) override  { nextPlayPos = newPosition;
        nStart = newPosition;
        nNumberSample = nEnd - nStart;
    };
    void setEndReadPosition (int64 endPosition) {
        nEnd = endPosition;
        nNumberSample = nEnd - nStart;
    }
    
    
//    void setLooping (bool shouldLoop)        override      {
//        looping = shouldLoop; };
    
    int64 getNextReadPosition() const override
    {
        return g_loopOn ? nextPlayPos % reader->lengthInSamples
        : nextPlayPos;
    };
    
    bool isLooping() const override                             { return g_loopOn; }
    
    AudioFormatReader* getAudioFormatReader() const noexcept    { return reader; }
    
    void prepareToPlay (int , double ) override {};
    void releaseResources() override {};
    
    void getNextAudioBlock (const AudioSourceChannelInfo& info) override
    {
        if (info.numSamples > 0 && nNumberSample > 0 && valid)
        {
            const int64 start = nextPlayPos - nStart;
            
            if (g_loopOn)
            {
                const int64 newStart = (start ) % nNumberSample;
                const int64 newEnd = (start  + info.numSamples) % nNumberSample;
                
                if (newEnd > newStart)
                {
                    reader->read (info.buffer, info.startSample,
                                  (int) (newEnd - newStart), newStart + nStart, true, true);
                }
                else
                {
                    const int endSamps = (int) (nNumberSample - newStart);
                    
                    reader->read (info.buffer, info.startSample,
                                  endSamps, newStart + nStart, true, true);
                    
                    reader->read (info.buffer, info.startSample + endSamps,
                                  (int) newEnd, nStart, true, true);
                }
                
                nextPlayPos = newEnd + nStart;
            }
            else
            {
                //Regular playback (no loop)
            
                setEndReadPosition( (int64) (getTotalLength()) );
                
                int64 nxtPos = nextPlayPos;
                
                reader->read (info.buffer, info.startSample,
                              info.numSamples, nxtPos, true, true);
                nextPlayPos += info.numSamples;
                

            }
            
            
        }
    };
};

