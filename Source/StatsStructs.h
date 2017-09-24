/*
  ==============================================================================

    StatsStructs.h
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <map>
#include <string>
#include <typeinfo>


struct FreqStats
{

    
    std::map<float, float> count =
    {
        {31.25, 0}, {62.5, 0}, {125, 0}, {250, 0}, {500, 0},
        {1000, 0}, {2000, 0}, {4000, 0}, {8000, 0}, {16000, 0}
    
    };
    std::map<float, float> correctans =
    {
        {31.25, 0}, {62.5, 0}, {125, 0}, {250, 0}, {500, 0},
        {1000, 0}, {2000, 0}, {4000, 0}, {8000, 0}, {16000, 0}
        
    };
    

    
    float getPercent(float freq)
    {
        float percentage = 0;
        
        if (count[freq] != 0)
            percentage = static_cast<float>(correctans[freq]) / static_cast<float>(count[freq]);
        
        return percentage;
    }
    
    void print()
    {
//        std::cout<<"Count  - ";
//        for(auto it = count.cbegin(); it != count.cend(); ++it)
//        {
//            std::cout << it->first << " " << it->second<< " " << it->second<< "\n";
//        }
//        std::cout<<"\nCorrect answer  - ";
//        for(auto it = correctans.cbegin(); it != correctans.cend(); ++it)
//        {
//            std::cout << it->first << " " << it->second << " " << it->second<< "\n";
//        }
        
        std::map<float, float>::iterator it = count.begin();
        
        // Iterate over the map using Iterator till end.
        while (it != count.end())
        {
            // Accessing KEY from element pointed by it.
            float freq = it->first;
            
            // Accessing VALUE from element pointed by it.
            float value = it->second;
            
            std::cout << freq << " :: " << value << std::endl;
            
            // Increment the Iterator to point to next entry
            it++;
        }
        
        
        std::map<float, float>::iterator it2 = correctans.begin();
        
        // Iterate over the map using Iterator till end.
        while (it2 != correctans.end())
        {
            // Accessing KEY from element pointed by it.
            float freq = it2->first;
            
            // Accessing VALUE from element pointed by it.
            float value = it2->second;
            
            std::cout << freq << " :: " << value << std::endl;
            
            // Increment the Iterator to point to next entry
            it2++;
        }
        
    }
    
};
