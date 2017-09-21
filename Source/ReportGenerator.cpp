/*
  ==============================================================================

    ReportGenerator.cpp

  ==============================================================================
*/

#include "ReportGenerator.h"


ReportGenerator ReportGenerator::reportgenerator = ReportGenerator();



ReportGenerator& ReportGenerator::Instance()
{
    return reportgenerator;
    
}
