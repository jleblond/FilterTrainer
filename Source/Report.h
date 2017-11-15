/*
  ==============================================================================

    Report.h


  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#include "User.h"

struct Report
{
        String username = "";
        String date = "";
        String timePractised = "";
        String freqRange = "";
        std::vector<int> gainFactor; //** to print
        std::vector<String> audioFiles;
        int nbQuestions = 0;
        float score = 0;
        float maxScore = 100;
        int percentScore = 0;
        std::vector<Comment> comments;
        FreqStats freqstats;  //** to print
    
        void print()
        {
            std::cout<<"***PRINT SESSION REPORT***"<<std::endl;
            std::cout<<username<<std::endl;
            std::cout<<date<<std::endl;
            std::cout<<"Time practised: "<<timePractised<<std::endl; //****
            std::cout<<freqRange<<std::endl;
            
            for(int i=0;i<gainFactor.size();i++)
            {
                std::cout<<static_cast<String>(gainFactor[i])<<std::endl;
            }
            
            for(int i=0;i<audioFiles.size();i++)
            {
                std::cout<<audioFiles[i]<<std::endl;
            }
            
            std::cout<<"Nb questions: "<<nbQuestions<<std::endl;
            std::cout<<"User score: "<<score<<std::endl;
            std::cout<<"Max possible score: "<<maxScore<<std::endl;
            std::cout<<"Percent score (%): "<<percentScore<<std::endl;
            
            for(int i=0;i<comments.size();i++)
            {
                std::cout<<"Comment "<<(i+1)<<" - "<<comments[i].mDate;
                std::cout<<comments[i].mText<<"\n"<<std::endl;
            }
        
        }


};
