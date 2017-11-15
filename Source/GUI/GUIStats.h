/*
  ==============================================================================

    GUIStats.h
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
        
        
        addAndMakeVisible(mTitle);
        mTitle.setText("STATISTICS", dontSendNotification);
        mTitle.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        mTitle.setFont(18);
        
        addAndMakeVisible(mNbQuestions);
        mNbQuestions.setText("# of questions: 0", dontSendNotification);
        mNbQuestions.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        mNbQuestions.setFont(14);
        
        addAndMakeVisible(mScore);
        mScore.setText("Score: []", dontSendNotification);
        mScore.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        mScore.setFont(14);
        
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
        
        
        for(int i=0; i<g_AllRange.size(); i++)
        {
            float currFreq = g_AllRange[i];
            String freqStr = static_cast<String>( currFreq ) + "\nHz";
            String countStr = static_cast<String>( s->mSessionStats.count[currFreq] );
            
            
            //Bars
            mVecBars.push_back( new StatsBar(g_AllRange[i]) );
            addAndMakeVisible(mVecBars[i]);
            //mVecBars[i]->setVisible(false);
            
            //Count labels
            
            Label* countLabel = new Label(countStr, countStr);
            mVecCountLabels.push_back(countLabel);
            
            addAndMakeVisible(mVecCountLabels[i]);
            mVecCountLabels[i]->setText( countStr, dontSendNotification );
            mVecCountLabels[i]->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
            mVecCountLabels[i]->setFont(12);
            mVecCountLabels[i]->setJustificationType(juce::Justification::centred);
           // mVecCountLabels[i]->setVisible(false);
            
            
            //Frequency labels
            
            Label* freqLabel = new Label(freqStr, freqStr );
            mVecFreqLabels.push_back(freqLabel);
            
            addAndMakeVisible(mVecFreqLabels[i]);
            mVecFreqLabels[i]->setText( freqStr, dontSendNotification );
            mVecFreqLabels[i]->setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
            mVecFreqLabels[i]->setFont(12);
            mVecFreqLabels[i]->setJustificationType(juce::Justification::centred);
           // mVecFreqLabels[i]->setVisible(false);
            
            
        }
        
        
        
    }
    
    ~GUIStats()
    {
        for(int i=0; i<g_AllRange.size(); i++)
        {
            delete mVecBars[i];
            delete mVecCountLabels[i];
            delete mVecFreqLabels[i];
        }
        
    }
    
    void setSession(Session* sess)
    {
        for(int i=0; i<g_AllRange.size(); i++)
        {
            mVecCountLabels[i]->setVisible(false);
            mVecBars[i]->setVisible(false);
        }
        
        this->s = sess;
        
        visibleBarsRange();
        
    }
    
    Session * getSession()
    {
        return s;
    }
    
    void paint(Graphics& g)override
    {
         g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
         g.fillAll(Colours::white);
        
        
        if( mVecBars.size()>0 &&  s !=nullptr )
        {
            for(int i=0; i< g_AllRange.size() ; i++ )
            {
                float freq = g_AllRange[i];
                float percent = s->mSessionStats.getPercent(freq);
                float count = s->mSessionStats.count[freq];
                
                mVecBars[i]->updateValues(percent, count);
                mVecBars[i]->repaintBar();
                mVecCountLabels[i]->setText(static_cast<String>(count), dontSendNotification);
                
            }
            
            
        }
        
    
    }
    
    void resized() override
    {
        mTitle.setBounds(0.05*getWidth(), 0.1*getHeight(), 150, 30);
        mNbQuestions.setBounds(0.05*getWidth(), 0.25*getHeight(), 150, 50);
        mScore.setBounds(0.05*getWidth(), 0.4*getHeight(), 150, 50);
        
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
        std::cout<<"range ici: "<<range<<std::endl;
        
        switch(range)
        {
            case 2:
                return g_HighRange;
            case 3:
                return g_MidRange;
            case 4:
                return g_LowRange;
            case 5:
                return g_Mid8Range;
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
     
            
            if( s != nullptr )
            {
                s->updateStats(centerFreq, centerFreqAnswered, answerDistance);
                
                String nbQuestionsStr = static_cast<String>( s->getQuestionsCount() );
                mNbQuestions.setText("# of questions: " + nbQuestionsStr, dontSendNotification);
                
                String scoreStr = s->getScoreText();
                mScore.setText("Score: "+scoreStr, dontSendNotification);
                
                
                repaint();
                
                s->printStats(); //console print
            }
           
            
        }
        
        
    }
    
    void visibleBarsRange()
    {
        int range = s->getRange();
        
        
        int size = 0;
        int start = 0;
        
            switch(range)
            {
                case 1: //all
                    start = 0;
                    size = 10;
                    break;
                case 2: //high
                    start = 5;
                    size = 5;
                    break;
                case 3: //mid
                    start = 3;
                    size = 5;
                    break;
                case 4: //low
                    start = 0;
                    size = 5;
                    break;
                case 5: //mid8
                    start = 1;
                    size = 8;
                    break;
            }
        
        for(int i=start; i<(start+size) ;i++)
        {
            setVisibleComponents(i, true);
        }
        
    }
    
    void setVisibleComponents(int index, bool visibility)
    {
        mVecFreqLabels[index]->setVisible(visibility);
        mVecCountLabels[index]->setVisible(visibility);
        mVecBars[index]->setVisible(visibility);
    }
    
    
    void resetNbQuestionsLabelText()
    {
        mNbQuestions.setText("# of questions: 0", dontSendNotification);
    }
    
private:
    Session* s = new Session(0, 3, true, false);
    float mBarSize = 35; //0.05*getWidth(); //width
    
    
    Label mTitle;
    
    Label mScore;
    Label mNbQuestions;
    
    Label mCountTitle;
    Label mPercentTitle;
    Label mFreqTitle;
    
    std::vector<Label*> mVecFreqLabels;
    std::vector<Label*> mVecCountLabels;
    std::vector<StatsBar*> mVecBars;
    std::vector<double> vecStartXPos =
        {0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75};
};
