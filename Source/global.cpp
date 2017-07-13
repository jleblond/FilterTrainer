/*
  ==============================================================================

    global.cpp
    Created: 30 Jun 2017 12:24:03am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "global.h"


//Buttons
TextButton g_questionButton;
TextButton g_openButton;
TextButton g_playButton;
TextButton g_stopButton;
TextButton g_filterButton;
TextButton g_loopingButton;
TextButton g_loopingToggle; //kept for state (check?)

//Playback settings
float g_mainVolume = 1.0f;
String g_pausedTime;
bool g_filterOn = false;
bool g_loopOn = false;
bool g_loopOnRecentClick = false;
double g_minLoopDuration = 0.2;
double g_loopStartPos = 0 ;
double g_loopEndPos = 0;


//Filter settings
double g_centreFrequency = 20000;
double g_Q = 1.4;
float g_gainFactor = 6;

//Exercise settings
int g_freqRangeValue = 0;
int g_filterGainValue = 6;
bool g_gainAmplification = false;
bool g_gainAttenuation = false;
