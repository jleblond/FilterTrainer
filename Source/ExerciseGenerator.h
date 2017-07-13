/*
  ==============================================================================

    ExerciseGenerator.h
    Created: 27 Jun 2017 11:53:38pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "Exercise.h"
#include <vector>

#include "global.h"

class ExerciseGenerator
{
public:
    
    static ExerciseGenerator& Instance();
    
    void createExercise(int freqrange, int absfreqboost, bool amplification, bool attenuation);
    
    static std::vector<Exercise*> listexercises;
    
private:
    
    ExerciseGenerator();
    
    ~ExerciseGenerator();
    
    static ExerciseGenerator exercisegenerator;
    
    int configExerciseFreqBoost(int absfreqboost, bool amplification, bool attenuation);
    
    float configExerciseFreq(int range);
    
    //rnd in configExerciseFreq according to fixed size
    std::vector<float> mAllRange {31.25, 62.5, 125, 250, 500, 1000, 2000, 4000, 8000, 16000};
    std::vector<float> mHighRange {1000, 2000, 4000, 8000, 16000};
    std::vector<float> mMidRange {250, 500, 1000, 2000, 4000};
    std::vector<float> mLowRange {31.25, 62.5, 125, 250, 500};
    
    
};
