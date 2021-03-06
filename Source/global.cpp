/*
  ==============================================================================

    global.cpp
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "global.h"

User g_User("");
TextButton g_StartSessionButton;
TextButton g_EndSessionButton;

double g_srcDurationInSec = 0;
double g_currAudioPosition = 0;
float g_currDrawPosition = 0;

//Buttons
TextButton g_questionButton;
TextButton g_answerButton;
TextButton g_correctionButton;

TextButton g_answerAmpButton;
TextButton g_answerAttButton;


TextButton g_filterCorrectionButton;

TextButton g_openButton;
TextButton g_playButton;
TextButton g_stopButton;
TextButton g_filterButton;
TextButton g_dummyFilterButton; // for cases when ExerciseSettings panel is shown (in which case g_filterButton setVisibility is false)
TextButton g_loopingButton;
TextButton g_loopingToggle; //kept for state (check?)
TextButton g_ZoomInButton;
TextButton g_ZoomOutButton;

double g_scaleZoomWaveform = 1;

//Playback settings
float g_mainVolume = 0.5f;
String g_pausedTime;
bool g_filterOn = false;

bool g_loopOn = false;
double g_loopMinDuration = 0.2;

double g_loopStartPos = 0 ;
double g_loopEndPos = 0;


//Actual filter settings
double g_centreFrequency = 20000;
double g_Q = 1.4;
float g_gainFactor = 6;

//Exercise settings for the filter
 double g_exerciseCentreFrequency;
 double g_exerciseQ;
 float g_exerciseGainFactor;

//Exercise settings
int g_freqRangeValue = 0;
int g_filterGainValue = 6;
bool g_gainAmplification = true;
bool g_gainAttenuation = false;
int g_answerValue = 0;

std::vector<float> g_AllRange {31.25, 62.5, 125, 250, 500, 1000, 2000, 4000, 8000, 16000};
std::vector<float> g_HighRange {1000, 2000, 4000, 8000, 16000};
std::vector<float> g_MidRange {250, 500, 1000, 2000, 4000};
std::vector<float> g_LowRange {31.25, 62.5, 125, 250, 500};
std::vector<float> g_Mid8Range {62.5, 125, 250, 500, 1000, 2000, 4000, 8000};
