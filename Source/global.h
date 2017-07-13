/*
  ==============================================================================

    global.h
    Created: 30 Jun 2017 12:24:03am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


//Buttons
extern TextButton g_questionButton;

//Playback settings
extern float g_mainVolume;
extern String g_pausedTime;
extern bool g_filterOn;
extern bool g_loopOn;
    //audio positions in s (or ms?)
    extern double g_loopStartPos;
    extern double g_loopEndPos;
    extern double g_lastLoopStartPos;
    extern double g_lastLoopEndPos;

//Filter settings
extern double g_centreFrequency;
extern double g_Q;
extern float g_gainFactor;

//Exercise settings
extern int g_freqRangeValue;
extern int g_filterGainValue;
extern bool g_gainAmplification;
extern bool g_gainAttenuation;
