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
    
    g_centreFrequency=static_cast<double>(centerfreq);
    g_gainFactor=static_cast<float>(freqboost);
    
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
        return mHighRange[rndchoice];
    else if(range==3)
        return mMidRange[rndchoice];
    else if(range==4)
        return mLowRange[rndchoice];
    else //including range==1
    {
        rndchoice = rand() % (mAllRange.size());
        return mAllRange[rndchoice];
    }
}


void ExerciseGenerator::Answering(int answer)
{
    assert( listexercises.size() > 0 && answer > 0 && answer <= 10);
    
    float answ = 0;
    
    
    switch( g_freqRangeValue )
    {
        case 1:
            answ = mAllRange[answer+1];
            break;
        case 2:
            answ = mHighRange[answer+1];
            break;
        case 3:
            answ = mMidRange[answer+1];
            break;
        case 4:
            answ = mLowRange[answer+1];
            break;
            
 
    }

    ( listexercises.back() )->AnswerExercise(answ);

}
