/*
  ==============================================================================

    GUIStats.h
    Created: 26 Jun 2017 11:24:10pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once


#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Session.h"
#include "../global.h"
#include "StatsBar.h"

class GUIStats : public Component,
                 public Button::Listener
{
public:
    GUIStats()
    {
        g_correctionButton.addListener(this);
        
        
        std::cout<<"GUISTATS - getWidth:"<<getWidth()<<" getHeight:"<<getHeight()<<std::endl;
        std::cout<<"getParentWidth:"<<getParentWidth()<<" getParentHeight:"<<getParentHeight()<<std::endl;
        
        
        //*warning: vecFreqRange is not fixed size, while mSessionStats is fixed size
        vecFreqRange = getFreqRange(s->getRange());
        
        for(int i=0; i<vecFreqRange.size(); i++)
        {
            mVecBars.push_back( new StatsBar(vecFreqRange[i]) );
            addAndMakeVisible(mVecBars[i]);
        }
        
        
        
    }
    
    ~GUIStats()
    {
        for(int i=0; i<vecFreqRange.size(); i++)
        {
            delete mVecBars[i];
        }
        
    }
    
    void paint(Graphics& g)override
    {
         g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
         g.fillAll(Colours::white);
        
       // std::vector<float> vecFreqRange = getFreqRange(s->getRange());
        
        
        if(vecFreqRange.size() > 0 && mVecBars.size()>0)
        {
            for(int i=0; i< vecFreqRange.size() ; i++ )
            {
                float freq = vecFreqRange[i];
                float percent = s->mSessionStats.getPercent(freq);
                float count = s->mSessionStats.count[freq];
                // std::cout<<"gui per freq - freq"<<freq<<" percent"<<percent<<std::endl;
                
                mVecBars[i]->updateValues(percent, count);
                
                mVecBars[i]->repaintBar();
                
            }
            
            
        }
        
        
      
    
    }
    
    void resized() override
    {
       if(mVecBars.size() > 0)
       {
           for(int i=0; i<mVecBars.size(); i++)
           {
               mVecBars[i]->setBounds( vecStartXPos[i]*getWidth(), 0.25*getHeight(),
                                       mBarSize, 0.7*getHeight() );
               
           }

       }
        
    }
    
    void paintRectangle (Graphics& g, Colour c,
                         float startX, float widthX, float startY, float heightY)
    {
        Rectangle<float> rect( startX, startY, widthX, heightY );
        
        g.setColour (c);
        g.setOpacity (0.5f);
        g.drawRect( rect, 1.0f );
        g.fillRect(rect);
    }
    
    const std::vector<float>& getFreqRange(int range)
    {
        switch(range)
        {
            case 1:
                return g_Mid8Range;
            case 2:
                return g_HighRange;
            case 3:
                return g_MidRange;
            case 4:
                return g_LowRange;
            default:
                return g_AllRange; //includes case 0
        }
        
    }
    
    
    
    void buttonClicked(Button* button) override
    {
        
        if( button == &g_correctionButton )
        {
            float centerFreq =
                ExerciseGenerator::listexercises.back()-> getCenterFreq();
            
            float centerFreqAnswered =
                ExerciseGenerator::listexercises.back()-> getCenterFreqAnswered();
            
            float answerDistance =
                ExerciseGenerator::listexercises.back()-> getAnswerDistance();
     
            s->updateStats(centerFreq, centerFreqAnswered, answerDistance);
            
            repaint();
            
            s->printStats(); //console print
            
        }
        
        
    }
    
    
private:
    Session* s = new Session(0);
    float mBarSize = 20; //0.05*getWidth(); //width
    
    std::vector<float> vecFreqRange; //current freq range
    std::vector<StatsBar*> mVecBars;
    std::vector<float> vecStartXPos =
        {0.2, 0.275, 0.35, 0.425, 0.5, 0.575, 0.65, 0.725, 0.8, 0.875};
};
