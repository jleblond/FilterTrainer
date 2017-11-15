/*
  ==============================================================================

    ExerciseGenerator.cpp
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "ExerciseGenerator.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <assert.h>
#include <random>


ExerciseGenerator ExerciseGenerator::exercisegenerator = ExerciseGenerator();


std::vector<Exercise*> ExerciseGenerator::listexercises;



ExerciseGenerator& ExerciseGenerator::Instance()
{
    return exercisegenerator;
    
}



void ExerciseGenerator::createExercise( int freqrange, int absfreqboost,
                                        bool amplification, bool attenuation )
{
    float centerfreq = configExerciseFreq(freqrange);
    
    int freqboost = configExerciseFreqBoost( absfreqboost, amplification, attenuation );
    
    ExerciseGenerator::listexercises.push_back( new Exercise(centerfreq, freqboost) );
    
    g_exerciseCentreFrequency = static_cast<double>(centerfreq);
    g_centreFrequency = static_cast<double>(centerfreq);
    
    g_exerciseGainFactor = static_cast<float>(freqboost);
    g_gainFactor = static_cast<float>(freqboost);
    
}



int ExerciseGenerator::configExerciseFreqBoost( int freqboost,
                                                bool amplification, bool attenuation )
{
    srand(static_cast<unsigned int>(time(nullptr)));
    
    int negative = -freqboost;
    
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
    
    if(range == 2)
        return g_HighRange[rndchoice];
    
    else if(range == 3)
        return g_MidRange[rndchoice];
    
    else if(range == 4)
        return g_LowRange[rndchoice];
    else if(range == 5)
        return g_Mid8Range[ rand() % 8 ];
    else //including range==1
    {
        
       // rndchoice = rand() % ( g_AllRange.size() );
        
        return g_AllRange[rand() % 10 ];
    }
}



void ExerciseGenerator::Answering(int answer, int gainAnswer)
{
    assert( listexercises.size() > 0 && answer > 0 && answer <= 10);
    
    float answ = 0;
    
    
    switch( g_freqRangeValue )
    {
        case 1:
            answ = g_AllRange[answer - 1];
            break;
            
        case 2:
            answ = g_HighRange[answer - 1];
            break;
            
        case 3:
            answ = g_MidRange[answer - 1];
            break;
            
        case 4:
            answ = g_LowRange[answer - 1];
            break;
        case 5:
            answ = g_Mid8Range[answer - 1];
            break;
            
    }
    
    std::cout<< "exercise generator answ: " << answ <<std::endl;

    ( listexercises.back() )->AnswerExercise(answ, gainAnswer);

}
