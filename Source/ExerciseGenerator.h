/*
  ==============================================================================

    ExerciseGenerator.h
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
    
    void createExercise( int freqrange, int absfreqboost, bool amplification, bool attenuation );
    
    void Answering(int answer);
    
    static std::vector<Exercise*> listexercises;
    
private:
    
    ExerciseGenerator(){}
    
    ~ExerciseGenerator(){}
    
    static ExerciseGenerator exercisegenerator;
    
    int configExerciseFreqBoost( int absfreqboost, bool amplification, bool attenuation );
    
    float configExerciseFreq(int range);
    
    //rnd in configExerciseFreq according to fixed size
  
    
};
