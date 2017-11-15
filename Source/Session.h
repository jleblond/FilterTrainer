/*
  ==============================================================================

    Session.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "StatsStructs.h"
#include "Comment.h"

#include <vector>
#include <ctime>
#include <cmath> //fabs
#include <math.h> //roundf


//gain factors only avail to ReportGenerator (due to global being above Session.h in the file hierarchy)

class Session
{
public:
    FreqStats mSessionStats;
    
    Session(int range, float gainFactor, bool gainAmplification, bool gainAttenuation)
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
        
        mGainFactor = gainFactor;
        mGainAmplification = gainAmplification;
        mGainAttenuation = gainAttenuation;
        
    }
    
    ~Session()
    {

   }
    
    String getStrCurrentTime()
    {
        // current date/time based on current system
        time_t now = time(0);
        // convert now to string form
        char* dt = ctime(&now);
        
        return dt;
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
        Comment c;
        c.mText = ctext;
        c.mDate = getStrCurrentTime();
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
    
    int getQuestionsCount()
    {
        return mQuestionsCount;
    }
    
    String getStrRange()
    {
        String s = "";
        
        switch(mRange)
        {
            case all:
                s = "All";
                break;
            case high:
                s = "High";
                break;
            case mid:
                s = "Mid";
                break;
            case low:
                s = "Low";
                break;
            case mid8:
                s = "Mid8";
                break;
                
        }
        
        return s;
    }
    
    
    
    std::vector<Comment>& getComments()
    {
        return mVecComments;
    }
    
    float getScore()
    {
        return mScore;
    }
    
    
    float getMaxScore()
    {
        return mMaxScore;
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
        
        
        mQuestionsCount +=1;
        std::cout<<"mQuestionsCount: "<<mQuestionsCount<<std::endl;
        
        //in order to get a good measure total score
        if(mQuestionsCount >= mMinQuestionsNeeded)
        {
            calculateScore();
        }
        
    }
    
    
    void calculateMaxScore()
    {
        mMaxScore = 100;
        
        // A) # of bands
        
        int freqRange = getRange();
        
        if (freqRange == 1)
                mMaxScore *= mDiffFactor1;
        else if (freqRange == 5)
                mMaxScore *= mDiffFactor2;
        else //high, mid, low
                mMaxScore *= 1;

        
        
        // B) Amplification/Attenuation
        if(mGainAmplification && mGainAttenuation)
            mMaxScore *= mDiffFactor1;
        else if(mGainAttenuation && !mGainAmplification)
            mMaxScore *= mDiffFactor2;
        else //only amplification
            mMaxScore *= 1;
        
        
        // C) dB Level
        
        float absGain = std::fabs(mGainFactor);
        std::cout<<"absGain: "<<absGain<<std::endl;
        
        if(absGain ==3)
        {
            mMaxScore *= (mDiffFactor1 * mDiffFactor2 * mDiffFactor2);
        }
        else if (absGain == 6)
        {
            mMaxScore *= (mDiffFactor2 * mDiffFactor2);
        }
        else if (absGain == 9)
        {
            mMaxScore *= mDiffFactor2;
        }
        else //absGain == 12
        {
            mMaxScore *= 1;
        }
        
        std::cout<<"Session - mMaxScore: "<<mMaxScore<<std::endl;
        
    }
    
    void calculateWeightedAverage()
    {
        mWeightedAverage = 0;
        
        for (int j=0 ; j< 10 ; j++)
        {
            float freqScore = mSessionStats.correctans[mAllRange[j]] / mSessionStats.count[mAllRange[j]] ;
            std::cout<<freqScore<<"(freqscore)  -  (freqweight) ";
            float freqWeight = mSessionStats.count[mAllRange[j]] / mQuestionsCount;
            std::cout<<freqWeight<<std::endl;
            
            //required otherwise freq for which freqWeight == 0 will result in NaN
            if(freqWeight != 0)
                mWeightedAverage += freqScore * freqWeight;
        }
        
        std::cout<<"Session - mWeightedAverage: "<<mWeightedAverage<<std::endl;
        
    }
    
    void calculateScore()
    {
        calculateMaxScore();
        calculateWeightedAverage();
        
        mScore = mWeightedAverage * mMaxScore;
        
        std::cout<<"Session - mScore: "<<mScore<<std::endl;

    }
    
    String getScoreText()
    {
        if (mQuestionsCount >= mMinQuestionsNeeded)
        {
            float nearest = roundf( (mWeightedAverage*100) * 100) / 100;
            mScoreTextGUIStats = static_cast<String>(nearest)+"%";
        }
        return mScoreTextGUIStats;
    }
    
    void setDuration(double duration)
    {
        mDuration = static_cast<int>(duration);
    }
    
    int getDuration()
    {
        return mDuration;
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
            std::cout<<i<<": "<<mVecComments[i].mText<<std::endl;
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
    std::vector<Comment>  mVecComments;
    std::vector<String> mAudioFileNames;
    
    int mQuestionsCount = 0;
    
    enum Range {all, high, mid, low, mid8};
    Range mRange = all;
   // float mGainFactor = 0;
    
    float mGainFactor = 3;
    bool mGainAmplification = true;
    bool mGainAttenuation = false;
    
    //default score values
    float mScore= -1; //mScore = mWeightedAverage (%) * mMaxScore ;
    float mPercentTotalScore = 0;
    float mMaxScore = 100;
    float mWeightedAverage = 0; //user weighted average of bands
    
    String mScoreTextGUIStats = "\n[Answer at least 50 questions]";
    
    //Difficulty factors
    float mDiffFactor1 = (100.0/62.0);
    float mDiffFactor2 = (100.0/80.0);
    
    int mMinQuestionsNeeded = 50;
    
    //Date date;
    //Time time;
    
    int mDuration = 0;
    
    std::vector<float> mAllRange {31.25, 62.5, 125, 250, 500, 1000, 2000, 4000, 8000, 16000};
};
