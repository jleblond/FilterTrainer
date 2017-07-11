/*
  ==============================================================================

    IIRFilters.h
    Created: 10 Jul 2017 8:30:52pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class IIRPeakFilter {
    Array<juce::IIRFilter> mIIRFilter;
    float mSampleRate;
    int mNumChans;
    juce::IIRCoefficients mCoefficients;
    
    ScopedPointer<LinearSmoothedValue<float>> mSmooth;
    
public:
    IIRPeakFilter( int numChans)
				:mSampleRate(0),
				mNumChans(numChans) {
                    for (int i = 0; i < numChans; i++) {
                        mIIRFilter.add(juce::IIRFilter());
                    }
                };
    
    ~IIRPeakFilter() {
        mIIRFilter.clearQuick();
    };
    void changeParam( double sampleRate, double centreFreq, double Q, float gainFactor )
    {
        mSampleRate = sampleRate;
       // mCoefficients = IIRCoefficients::makePeakFilter(mSampleRate, centreFreq, Q, gainFactor);
        
        updateCoeff(centreFreq, Q, gainFactor);
    };
    
    void updateCoeff( double centreFreq, double Q, float gainFactor )
    {
        mCoefficients = IIRCoefficients::makePeakFilter(mSampleRate, centreFreq, Q, gainFactor);
        for (int i = 0; i < mNumChans; i++) {
            mIIRFilter.getReference(i).setCoefficients(mCoefficients);
        }

    }
    
    void process( AudioBuffer<float> &buffer) {
        float **buffersCh = buffer.getArrayOfWritePointers();
        int numSamples = buffer.getNumSamples();
        int curChans = buffer.getNumChannels();
        int chans = juce::jmin<int>(curChans, mNumChans);
        for (int i = 0; i < numSamples; i++) {
            for (int c = 0; c < chans; c++) {
                buffersCh[c][i] = mIIRFilter.getReference(c).processSingleSampleRaw(buffersCh[c][i]);
            }
        }
    };
    void reset() {
        for (int i = 0; i < mNumChans; i++) {
            mIIRFilter.getReference(i).reset();
        }
    }
};









