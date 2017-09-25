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
    
    std::vector<int>& setGainFactors(Session& session);
    
    String getStrCurrentTime();
    
    String getStrFormatCurrentTime();
    
    String convertTimeStr(int timeInSeconds);
    
    String gainStr(Report& report);
    
    String reportTxtContent(Report& report);
    
};
