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
    
    Exercise(){};
    Exercise(float cfreq, int freqchange) : centerfreq(cfreq), freqboost(freqchange)
    {
        //listexercises.push_back(this);
        
        std::cout<<"EXERCISE"<<std::endl;
        std::cout<<"centerfreq:"<<centerfreq<<" freqboost:"<<freqboost<<std::endl;
    }
    
    
    ~Exercise();
    
    
    
    void AnswerExercise(float answer)
    {
        this->centerfreq_answered=answer;
        
        if( freqboost!=0 && centerfreq!=0 && centerfreq_answered!=0 ) //checks if Exercise parameters were set properly
        {
            if( centerfreq == centerfreq_answered )
            {
                correctanswer=true;
                answerdistance=1; //arbitrary value to distinguish from default 0
            }
            else if( SameSign(centerfreq, centerfreq_answered) )
            {
                //coeff * [2^(exponent)] = result
                float coeff=std::min(centerfreq, centerfreq_answered);
                float result=std::max(centerfreq, centerfreq_answered);
                
                //n = [ 2^exponent ]
                float n= result/coeff;
                answerdistance=log2(n);
            }
            else
            {
                //not the same sign, arbitrary distance value
                answerdistance=12;
            }
            
        }
    }
    
    bool SameSign(float a, float b)
    {
        return (a >= 0) ^ (b < 0);
    }
    
    
protected:
    int freqboost=0;
    float centerfreq=0;
    
    float centerfreq_answered=0;
    bool correctanswer=false;
    int answerdistance=0;
    
};

