/*
  ==============================================================================

    ReportGenerator.h

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#include "Report.h"



class ReportGenerator : public Report
{
public:
    
    static ReportGenerator& Instance();
    
    
private:
    
    ReportGenerator(){}
    
    ~ReportGenerator(){}
    
    static ReportGenerator reportgenerator;
    
};
