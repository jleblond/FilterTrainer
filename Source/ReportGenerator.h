/*
  ==============================================================================

    ReportGenerator.h

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#include "Report.h"
#include "global.h"

class ReportGenerator : public Report
{
public:
    
    static ReportGenerator& Instance();
    
    Report createReport(Session session, User& user);
    
    bool generateReportFile(Report& report);
    
    
private:
    
    ReportGenerator(){}
    
    ~ReportGenerator(){}
    
    static ReportGenerator reportgenerator;
    
    String getStrCurrentTime();
    
    String getStrFormatCurrentTime();
    
    String convertTimeStr(int timeInSeconds);
    
    String reportTxtContent(Report& report);
    
};
