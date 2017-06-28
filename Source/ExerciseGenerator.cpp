/*
  ==============================================================================

    ExerciseGenerator.cpp
    Created: 27 Jun 2017 11:53:38pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "ExerciseGenerator.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <random>


ExerciseGenerator ExerciseGenerator::exercisegenerator=ExerciseGenerator();

ExerciseGenerator::ExerciseGenerator()
{
    
}

ExerciseGenerator::~ExerciseGenerator()
{
    
}

std::vector<Exercise*> ExerciseGenerator::listexercises;

ExerciseGenerator& ExerciseGenerator::Instance()
{
    return exercisegenerator;
}

void ExerciseGenerator::createExercise(int freqrange, int absfreqboost, bool amplification, bool attenuation)
{
    float centerfreq=configExerciseFreq(freqrange);
    int freqboost=configExerciseFreqBoost(absfreqboost, amplification, attenuation);
    ExerciseGenerator::listexercises.push_back(new Exercise(centerfreq, freqboost));
    
}

int ExerciseGenerator::configExerciseFreqBoost(int freqboost, bool amplification, bool attenuation)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    
    int negative= -freqboost;
    
    if( amplification && !attenuation )
        return freqboost;
    else if( attenuation && !amplification )
        return negative;
    else
    {
        int choice = rand() % 2;
        
        if(choice==1)
            return freqboost;
        else
            return negative;
    }
}

float ExerciseGenerator::configExerciseFreq(int range)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    
    int rndchoice = rand() % 5;
    
    if(range==2)
        return highrange[rndchoice];
    else if(range==3)
        return midrange[rndchoice];
    else if(range==4)
        return lowrange[rndchoice];
    else //including range==1
    {
        rndchoice = rand() % (allrange.size());
        return allrange[rndchoice];
    }
}
