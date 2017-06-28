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
    std::vector<float> allrange {31.25, 62.5, 125, 250, 500, 1000, 2000, 4000, 8000, 16000};
    std::vector<float> highrange {1000, 2000, 4000, 8000, 16000};
    std::vector<float> midrange {250, 500, 1000, 2000, 4000};
    std::vector<float> lowrange {31.25, 62.5, 125, 250, 500};
    
    
};
