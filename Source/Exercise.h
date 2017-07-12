/*
  ==============================================================================

    Exercise.h
    Created: 27 Jun 2017 10:29:05pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include <vector>
#include <algorithm> //min, max
#include <math.h>    //log2
#include <iostream>

class Exercise
{
public:
   // static std::vector<Exercise*> listexercises;
    
    Exercise(float cfreq, int freqchange) : mCenterFreq(cfreq), mFreqBoost(freqchange)
    {
        //listexercises.push_back(this);
        
        std::cout<<"EXERCISE"<<std::endl;
        std::cout<<"centerfreq:"<<mCenterFreq<<" freqboost:"<<mFreqBoost<<std::endl;
        
    }
    
    
    ~Exercise();
    
    
    
    void AnswerExercise(float answer)
    {
        this->mCenterFreqAnswered=answer;
        
        if( mFreqBoost!=0 && mCenterFreq!=0 && mCenterFreqAnswered!=0 ) //checks if Exercise parameters were set properly
        {
            if( mCenterFreq == mCenterFreqAnswered )
            {
                mCorrectAnswer=true;
                mAnswerDistance=1; //arbitrary value to distinguish from default 0
            }
            else if( SameSign(mCenterFreq, mCenterFreqAnswered) )
            {
                //coeff * [2^(exponent)] = result
                float coeff=std::min(mCenterFreq, mCenterFreqAnswered);
                float result=std::max(mCenterFreq, mCenterFreqAnswered);
                
                //n = [ 2^exponent ]
                float n= result/coeff;
                mAnswerDistance=log2(n);
            }
            else
            {
                //not the same sign, arbitrary distance value
                mAnswerDistance=12;
            }
            
        }
    }
    
    bool SameSign(float a, float b)
    {
        return (a >= 0) ^ (b < 0);
    }
    
    
protected:
    int mFreqBoost = 0;
    float mCenterFreq = 0;
    
    float mCenterFreqAnswered = 0;
    bool mCorrectAnswer = false;
    int mAnswerDistance = 0;
    
};

