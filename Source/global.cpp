/*
  ==============================================================================

    global.cpp
    Created: 30 Jun 2017 12:24:03am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "global.h"


//Playback settings
String g_pausedTime;
bool g_filterOn = false;


//Filter settings
double g_centreFrequency = 20000;
double g_Q = 1.4;
float g_gainFactor = 6;


//General settings
float g_mainVolume = 1.0f;
