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
extern TextButton g_openButton;
extern TextButton g_playButton;
extern TextButton g_stopButton;
extern TextButton g_filterButton;
extern TextButton g_loopingButton;
extern TextButton g_loopingToggle; //kept for state (check?)

//Playback settings
extern float g_mainVolume;
extern String g_pausedTime;
extern bool g_filterOn;
extern bool g_loopOn;
extern bool g_loopOnRecentClick;
extern double g_minLoopDuration;
//audio positions in s
extern double g_loopStartPos;
extern double g_loopEndPos;

//Filter settings
extern double g_centreFrequency;
extern double g_Q;
extern float g_gainFactor;

//Exercise settings
extern int g_freqRangeValue;
extern int g_filterGainValue;
extern bool g_gainAmplification;
extern bool g_gainAttenuation;
