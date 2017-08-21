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
        
        addAndMakeVisible(mTitle);
        mTitle.setText("STATISTICS", dontSendNotification);
        mTitle.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        mTitle.setFont(18);
        
        addAndMakeVisible(mCountTitle);
        mCountTitle.setText("Count: ", dontSendNotification);
        mCountTitle.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        mCountTitle.setFont(14);
        mCountTitle.setJustificationType(juce::Justification::right);
        
        addAndMakeVisible(mPercentTitle);
        mPercentTitle.setText("Score: ", dontSendNotification);
        mPercentTitle.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        mPercentTitle.setFont(14);
        mPercentTitle.setJustificationType(juce::Justification::right);
        
        addAndMakeVisible(mFreqTitle);
        mFreqTitle.setText("Centre\nfrequency: ", dontSendNotification);
        mFreqTitle.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        mFreqTitle.setFont(14);
        mFreqTitle.setJustificationType(juce::Justification::right);
        
        
        for(int i=0; i<vecFreqRange.size(); i++)
        {
            float currFreq = vecFreqRange[i];
            String freqStr = static_cast<String>( currFreq ) + "\nHz";
            String countStr = static_cast<String>( s->mSessionStats.count[currFreq] );
            
            
            //Bars
            mVecBars.push_back( new StatsBar(vecFreqRange[i]) );
            addAndMakeVisible(mVecBars[i]);
            
            
            //Count labels
            
            Label* countLabel = new Label(countStr, countStr);
            mVecCountLabels.push_back(countLabel);
            
            addAndMakeVisible(mVecCountLabels[i]);
            mVecCountLabels[i]->setText( countStr, dontSendNotification );
            mVecCountLabels[i]->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
            mVecCountLabels[i]->setFont(12);
            mVecCountLabels[i]->setJustificationType(juce::Justification::centred);
            
            
            //Frequency labels
            
            Label* freqLabel = new Label(freqStr, freqStr );
            mVecFreqLabels.push_back(freqLabel);
            
            addAndMakeVisible(mVecFreqLabels[i]);
            mVecFreqLabels[i]->setText( freqStr, dontSendNotification );
            mVecFreqLabels[i]->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
            mVecFreqLabels[i]->setFont(12);
            mVecFreqLabels[i]->setJustificationType(juce::Justification::centred);
            
            
            
        }
        
        
        
    }
    
    ~GUIStats()
    {
        for(int i=0; i<vecFreqRange.size(); i++)
        {
            delete mVecBars[i];
            delete mVecCountLabels[i];
            delete mVecFreqLabels[i];
        }
        
    }
    
    void paint(Graphics& g)override
    {
         g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
         g.fillAll(Colours::white);
        
        
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
                
                mVecCountLabels[i]->setText(static_cast<String>(count), dontSendNotification);
                
            }
            
            
        }
        
        
      
    
    }
    
    void resized() override
    {
        mTitle.setBounds(0.05*getWidth(), 0.1*getHeight(), 150, 30);
        
        mCountTitle.setBounds(0.2*getWidth(), 0.1*getHeight(), 70, 30);
        mPercentTitle.setBounds(0.2*getWidth(), 0.47*getHeight(), 70, 30);
        mFreqTitle.setBounds(0.2*getWidth(), 0.8*getHeight(), 70, 30);
        
       if(mVecBars.size() > 0)
       {
           for(int i=0; i<mVecBars.size(); i++)
           {
               mVecCountLabels[i]->setBounds( vecStartXPos[i]*getWidth(), 0.1*getHeight(),
                                               mBarSize, mBarSize );
               
               mVecBars[i]->setBounds( vecStartXPos[i]*getWidth(), 0.25*getHeight(),
                                       mBarSize, 0.6*getHeight() );
               
               mVecFreqLabels[i]->setBounds(vecStartXPos[i]*getWidth(),
                                           0.75*getHeight(),
                                           mBarSize*1.25, mBarSize*2);
               
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
    float mBarSize = 35; //0.05*getWidth(); //width
    
    std::vector<float> vecFreqRange; //current freq range
    
    Label mTitle;
    Label mCountTitle;
    Label mPercentTitle;
    Label mFreqTitle;
    
    std::vector<Label*> mVecFreqLabels;
    std::vector<Label*> mVecCountLabels;
    std::vector<StatsBar*> mVecBars;
    std::vector<float> vecStartXPos =
        {0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75};
};
