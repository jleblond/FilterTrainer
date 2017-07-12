/*
  ==============================================================================

    global.h
    Created: 30 Jun 2017 12:24:03am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


//Playback settings
extern String g_pausedTime;
extern bool g_filterOn;


//Filter settings
extern double g_centreFrequency;
extern double g_Q;
extern float g_gainFactor;


//General settings
extern float g_mainVolume;
