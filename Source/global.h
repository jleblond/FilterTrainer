/*
  ==============================================================================

    global.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "User.h"


extern User g_User;
extern TextButton g_StartSessionButton;
extern TextButton g_EndSessionButton;

extern double g_srcDurationInSec;
extern double g_currAudioPosition;
extern float g_currDrawPosition;

//Buttons
extern TextButton g_questionButton;
extern TextButton g_answerButton;
extern TextButton g_correctionButton;

extern TextButton g_answerAmpButton;
extern TextButton g_answerAttButton;


extern TextButton g_filterCorrectionButton;

extern TextButton g_openButton;
extern TextButton g_playButton;
extern TextButton g_stopButton;
extern TextButton g_filterButton;
extern TextButton g_dummyFilterButton; // for cases when ExerciseSettings panel is shown (in which case g_filterButton setVisibility is false)
extern TextButton g_loopingButton;
extern TextButton g_loopingToggle; //kept for state (check?)
extern TextButton g_ZoomInButton;
extern TextButton g_ZoomOutButton;

//zoom
extern double g_scaleZoomWaveform;

//Playback settings
extern float g_mainVolume;
extern String g_pausedTime;
extern bool g_filterOn;

extern bool g_loopOn;  //used in LoopingAudioFormatReaderSource.h, MainComponent.cpp, PositionOverlay.h

extern double g_loopMinDuration;


//audio positions in s  (PositionOverlay.h)
extern double g_loopStartPos;
extern double g_loopEndPos;

//Actual filter settings
extern double g_centreFrequency;
extern double g_Q;
extern float g_gainFactor;

//Exercise settings for the filter (settings for the question)
extern double g_exerciseCentreFrequency;
extern double g_exerciseQ;
extern float g_exerciseGainFactor;

//Exercise settings
extern int g_freqRangeValue;
extern int g_filterGainValue;
extern bool g_gainAmplification;
extern bool g_gainAttenuation;
extern int g_answerValue;

//rnd in configExerciseFreq according to fixed size
extern std::vector<float> g_AllRange;
extern std::vector<float> g_HighRange;
extern std::vector<float> g_MidRange;
extern std::vector<float> g_LowRange;
extern std::vector<float> g_Mid8Range;
