/*
  ==============================================================================

    Session.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "StatsStructs.h"
#include "global.h"
#include "Report.h"
#include <vector>


class Comment
{
public:
    Comment(String ctext){
        mText = ctext;
    }
    
    ~Comment()
    {
        
    }
    void changeText(String ctext)
    {
        mText = ctext;
    }
    
    String getText()
    {
        return mText;
    }
    
private:
    String mText="";
};



class Session
{
public:
    FreqStats mSessionStats;
    
    Session(int range)
    {
        switch(range)
        {
            case 1:
                mRange = all;
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
            case 5:
                mRange = mid8;
                break;
        }
        
        
     //   mGainFactor = g_gainFactor;
        
    }
    
    ~Session()
    {

   }
    
    
    int getRange()
    {
        int value = 0;  //also used as ‘case all’ and ‘default’
        
        switch(mRange)
        {
            case all:
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
            case mid8:
                value = 5;
                break;

        }
        
        return value;
    }
    
    
    void addComment(String ctext)
    {
        Comment c(ctext);
        mVecComments.push_back(c);
      
    }
    void removeComment(int index)
    {
        mVecComments.erase( mVecComments.begin() + (index) );
    }
    const std::vector<Comment>&  getVecComments()
    {
        return mVecComments;
    }
    
    
    void addAudioFileName(String audiofilename)
    {
        mAudioFileNames.push_back(audiofilename);
    }
    
    void removeAudioFileName(int index)
    {
         mAudioFileNames.erase( mAudioFileNames.begin() + (index) );
    }
    
    const std::vector<String>& getAudioFileNames()
    {
        return mAudioFileNames;
    }
    
    
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
        
        
        mQuestionsCount++;
        
    }
    
    void printStats()
    {
        mSessionStats.print();
    }
    
    void printAllComments()
    {
        std::cout<<"Session - Print All Comments"<<std::endl;
        for(int i=0;i<mVecComments.size();i++)
        {
            std::cout<<i<<": "<<mVecComments[i].getText()<<std::endl;
        }
    }
    
    void printAudioFileNames()
    {
        std::cout<<"Session - Print All AudioFileNames"<<std::endl;
        for(int i=0;i<mAudioFileNames.size();i++)
        {
            std::cout<<i<<": "<<mAudioFileNames[i]<<std::endl;
        }
    }
    
    
private:
    Report mReport;
    std::vector<Comment>  mVecComments;
    std::vector<String> mAudioFileNames;
    
    int mQuestionsCount = 0;
    
    enum Range {all, high, mid, low, mid8};
    Range mRange = all;
   // float mGainFactor = 0;
    
    //Date date;
    //Time time;
};
