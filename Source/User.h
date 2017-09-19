/*
  ==============================================================================

    User.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Session.h"
#include "StatsStructs.h"
#include "global.h"


class User
{
public:
    User(String name)
    {
        this->mUsername = name;
    }
    
    ~User()
    {
        for(int i=0;i<mVecSessions.size();i++)
        {
            delete mVecSessions[i];
        }
    }
    
    String mUsername = "";
    
    void changeUsername(String name)
    {
        this->mUsername = name;
    }
    
    void createSession(int range)
    {
        mVecSessions.push_back( new Session(range) );
        mLastNbSessions++;
    }
    
    void addSession(Session &s)
    {
        mVecSessions.push_back(&s);
        mLastNbSessions++;
        
        updateGlobalStats();
    }
    void removeSession(int index)
    {
        delete mVecSessions.at(index);
        mVecSessions.erase( mVecSessions.begin() + (index) );
        mLastNbSessions--;
    }
    const std::vector<Session*>& getVecSessions()
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
            for (int j=0 ; j< 10 ; j++)
            {
                mGlobalStats.count[j] +=
                mVecSessions[i]->mSessionStats.count[j];
                
                mGlobalStats.correctans[j] +=
                mVecSessions[i]->mSessionStats.correctans[j];
            }
        }
        
    }
    
    Session* getLastSession()
    {
        if(mVecSessions.size()>0)
        {
            return mVecSessions[ mVecSessions.size()-1 ];
        }
        else
            return nullptr;
    }
    
    
private:
    std::vector<Session*> mVecSessions;
    int mLastNbSessions = 0; //keep track of last size of mVecSessions
    FreqStats mGlobalStats;
    
    
};

