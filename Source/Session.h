/*
  ==============================================================================

    Session.h
    Created: 15 Aug 2017 9:21:30pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "StatsStructs.h"

class Session
{
public:
    FreqStats mSessionStats;
    
    Session(int range)
    {
        switch(range)
        {
            case 1:
                mRange = mid8;
                break;
            case 2:
                mRange = high;
                break;
            case 3:
                mRange = mid;
                break;
            case 4:
                mRange = low;
                break;
            default:	 //includes case 0
                mRange = all;
        }
    }
    
    ~Session()
    {
       // for(int i = 0; i <mVecComments.size(); ++i)
       //     delete mVecComments[i];
    }
    
    
    int getRange()
    {
        int value = 0;  //also used as ‘case all’ and ‘default’
        
        switch(mRange)
        {
            case mid8:
                value = 1;
                break;
            case high:
                value = 2;
                break;
            case mid:
                value = 3;
                break;
            case low:
                value = 4;
                break;

        }
        
        return value;
    }
    
//    void addComment(String ctext)
//    {
//        Comment * c = new Comment();  //check for c (heap ok?) and delete
//        c->commentText = ctext;
//        mVecComments.push_back(c);
//    }
//    void removeComment(int index)
//    {
//        delete mVecComments.at(index);
//        mVecComments.erase( mVecComments.begin() + (index) );
//    }
//    const std::vec<Comment*>&  getVecComments()
//    {
//        return mVecComments;
//    }
    
    void updateStats(float centerFreq, float centerFreqAnswered,
                     int answerDistance)   //update mSessionStats
    {
        //Increase count of freq asked in the exercise (for all cases)
        mSessionStats.count[centerFreq] +=1;
        
        if(centerFreq == centerFreqAnswered && answerDistance == 0)
        {
            mSessionStats.correctans[centerFreq]  +=1;
        }
        else if (answerDistance == 1)
        {
            mSessionStats.count[centerFreqAnswered] +=1;
            mSessionStats.correctans[centerFreq]  +=0.5;
        }
        else
        {
            mSessionStats.count[centerFreqAnswered] +=1;
        }
        
    }
    
    void printStats()
    {
        mSessionStats.print();
    }
    
private:
    //std::vec<Comment*>  mVecComments;
    enum Range {all, high, mid, low, mid8};
    Range mRange = all;
    //Date date;
    //Time time;
};
