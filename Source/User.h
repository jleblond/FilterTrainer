/*
  ==============================================================================

    User.h
    Created: 15 Aug 2017 9:21:53pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Session.h"
#include "StatsStructs.h"


class User
{
public:
    User(String name)
    {
        this->mUsername = name;
    }
    String mUsername;
    
    void changeUsername(String name)
    {
        this->mUsername = name;
    }
    
    void addSession(Session& s)
    {
        mVecSessions.push_back(s);
        mLastNbSessions++;
        
        updateGlobalStats();
    }
    void removeSession(int index)
    {
        delete mVecSessions.at(index);
        mVecSessions.erase( mVecSessions.begin() + (index) );
        mLastNbSessions--;
    }
    const std::vec<Session*>& getVecSessions();
    {
        return mVecSessions;
    }
    const FreqStats& getGlobalStats()
    {
        return mGlobalStats;
    }
    void updateGlobalStats( )
    {
        //go through mVecSessions data to update mGlobalStats
        
        for( int i =  mLastNbSessions; i<mVecSessions.size(); i++)
        {
            for (int j=0 ; j<g_AllRange.size() ; j++)
            {
                mGlobalStats.count[j] +=
                mVecSessions[i]->mSessionStats.count[j];
                
                mGlobalStats.correctans[j] +=
                mVecSessions[i]->mSessionStats.correctans[j];
            }
        }
        
    }
    
    
private:
    std::vec<Session*> mVecSessions;
    int mLastNbSessions = 0; //keep track of last size of mVecSessions
    FreqStats mGlobalStats;
    
    
};

