/*
  ==============================================================================

    global.h
    Created: 30 Jun 2017 12:24:03am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

extern double g_srcDurationInSec;
extern double g_currAudioPosition;
extern float g_currDrawPosition;

//Buttons
extern TextButton g_questionButton;
extern TextButton g_answerButton;
extern TextButton g_correctionButton;

extern TextButton g_openButton;
extern TextButton g_playButton;
extern TextButton g_stopButton;
extern TextButton g_filterButton;
extern TextButton g_loopingButton;
extern TextButton g_loopingToggle; //kept for state (check?)
extern TextButton g_ZoomInButton;
extern TextButton g_ZoomOutButton;

extern double g_scaleZoomWaveform;

//Playback settings
extern float g_mainVolume;
extern String g_pausedTime;
extern bool g_filterOn;

extern bool g_loopOn;  //used in LoopingAudioFormatReaderSource.h, MainComponent.cpp

//extern bool g_loopOnRecentClick;
extern double g_loopMinDuration;


//audio positions in s  (PositionOverlay.h)
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
//extern bool g_questionMode;
extern int g_answerValue;

//rnd in configExerciseFreq according to fixed size
extern std::vector<float> g_AllRange;
extern std::vector<float> g_HighRange;
extern std::vector<float> g_MidRange;
extern std::vector<float> g_LowRange;
