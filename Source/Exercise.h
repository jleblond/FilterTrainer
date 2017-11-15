/*
  ==============================================================================

    Exercise.h
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
        
        std::cout<<"EXERCISE.h"<<std::endl;
        std::cout<<"centerfreq:"<<mCenterFreq<<" freqboost:"<<mFreqBoost<<std::endl;
        
    }
    
    
    ~Exercise();
    
    
    void AnswerExercise(float answer, int gainAnswer)
    {
        
        this->mCenterFreqAnswered=answer;
        this->mFreqBoostAnswered = gainAnswer;
        
        
        if( mFreqBoost!=0 && mCenterFreq!=0 && mCenterFreqAnswered!=0 && mFreqBoostAnswered!=0) //checks if Exercise parameters were set properly
        {
            
            //FREQ
            
            if( mCenterFreq == mCenterFreqAnswered )
            {
                mCorrectAnswer = true;
                mAnswerDistance = 0 ; // same as default value though...
                
               
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
            
            std::cout<<"(exercise) answer distance: "<<mAnswerDistance<<std::endl;
            
    
            
        }
        
        std::cout<<"(exercise) freqboost answered: "<<mFreqBoostAnswered<<std::endl;
        
        
        
        
        
    }
    
    bool SameSign(float a, float b)
    {
        return (a >= 0) ^ (b < 0);
    }
    

    const int getFreqBoost()
    {
        return mFreqBoost;
    }
    
    const float getCenterFreq()
    {
        return mCenterFreq;
    }
    
    const float getCenterFreqAnswered()
    {
        return mCenterFreqAnswered;
    }
    
    const int getAnswerDistance()
    {
        return mAnswerDistance;
    }
    
    const int getFreqBoostAnswered()
    {
        return mFreqBoostAnswered;
    }
    
    
protected:
    int mFreqBoost = 0;
    float mCenterFreq = 0;
    
    float mCenterFreqAnswered = 0;
    bool mCorrectAnswer = false;
    int mAnswerDistance = 0;
    
    int mFreqBoostAnswered = 0;
    
};

