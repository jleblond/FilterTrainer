/*
  ==============================================================================

    ReportGenerator.cpp

  ==============================================================================
*/

#include "ReportGenerator.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>


ReportGenerator ReportGenerator::reportgenerator = ReportGenerator();



ReportGenerator& ReportGenerator::Instance()
{
    return reportgenerator;
    
}

String ReportGenerator::getStrCurrentTime()
{
    // current date/time based on current system
    time_t now = time(0);
    // convert now to string form
    char* dt = ctime(&now);
    
    return dt;
}

String ReportGenerator::getStrFormatCurrentTime()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
    auto str = oss.str();
    
    return str;
}

String ReportGenerator::convertTimeStr(int timeInSeconds)
{
    String durationStr = "";
    
    int seconds, hours, minutes;
    minutes = timeInSeconds / 60;
    seconds = timeInSeconds % 60;
    hours = minutes / 60;
    minutes = minutes % 60;
    
    if(hours>=1)
    {
        durationStr += static_cast<String>(hours) + "h";
    }
    if(minutes>=1)
    {
        durationStr += static_cast<String>(minutes) + "m";
    }
    if(seconds>=1)
    {
        durationStr += static_cast<String>(seconds) + "s";
    }
    
    
    return durationStr;
}


Report ReportGenerator::createReport(Session session, User& user)
{
    Report r;
    
    r.username = user.mUsername;
    r.date = getStrCurrentTime();
    r.timePractised = convertTimeStr(session.getDuration() );
    r.freqRange = session.getStrRange();
    std::vector<int> gainFactor;            //**
    r.audioFiles = session.getAudioFileNames();
    r.nbQuestions = session.getQuestionsCount();
    r.comments = session.getComments();
    r.freqstats = session.mSessionStats;
    
    return r;
}


bool ReportGenerator::generateReportFile(Report& report)
{
    AlertWindow alert ("**Report Generator**",
                   "A report will be generated based on your session data. \n Please choose the directory where you want to save this report.",
                   AlertWindow::NoIcon);
    
    
    alert.addButton ("OK",     1, KeyPress (KeyPress::returnKey, 0, 0));
    
    if (alert.runModalLoop() != 0) // is they picked 'ok'
    {
        FileChooser fc ("Save the report in folder..",
                        File::getCurrentWorkingDirectory(),
                        "*",
                        true);
        
        if (fc.browseForDirectory())
        {
            File chosenDirectory = fc.getResult();
            String reportFilePath =
            chosenDirectory.getFullPathName()+"/reports/"+getStrFormatCurrentTime()+".txt";
            
            File reportFile(reportFilePath);
            reportFile.create();
            reportFile.appendText( reportTxtContent(report) );
            
            AlertWindow w ("**Report Generator**",
                           "File saved as...\n" + reportFilePath,
                           AlertWindow::NoIcon);
            
            
            w.addButton ("Open File",     1, KeyPress (KeyPress::returnKey, 0, 0));
            w.addButton ("Continue", 0, KeyPress (KeyPress::escapeKey, 0, 0));
            
            
            if (w.runModalLoop() != 0) // is they picked 'ok'
            {
                reportFile.revealToUser();
                
            }
            
            return true;
      
        }
    }

    return false;
  
   
}

String ReportGenerator::reportTxtContent(Report& report)
{
    String s = "\n";
    s+= "\t\t \n";
    s+="\t\t\tFILTER TRAINER\n";
    s+="\t\t\tREPORT\n";
    s+="\t\t*************************\n";
    s+="\n";
    s+="\t\t\tUser [Jasmine]\n";
    s+="\t\t\tDate [17/09/18]\n";
    s+="\t\t\tTime [10:24 PM]\n";
    s+="\n";
    s+="\n";
    s+="\n";
    s+="\t***SESSION INFORMATION***\n";
    s+="\n";
    s+="\n";
    s+="Time practiced [2h10m]\n";
    s+="\n";
    s+="Exercise settings\n";
    s+="\tFrequency range [Mid-8]\n";
    s+="\tAmplification/Attenuation (dB) [+12,-12]\n";
    s+="\n";
    s+="\n";
    s+="Name(s) of audo file(s) loaded\n";
    s+="[nameofaudiofile.mp3]\n";
    s+="[otherfile.wav]\n";
    s+="[blablabla.wav]\n";
    s+="\n";
    s+="\n";
    s+="Total number of questions asked [47]\n";
    s+="\n";
    s+="\n";
    s+="\n";
    s+="\t***GRAPH***\n";
    s+="\n";
    s+="center\n";
    s+="freq      score (%)\n";
    s+="————————————————————————-\n";
    s+=" 31  Hz  |——————————\n";
    s+=" 63  Hz  |——-\n";
    s+=" 125 Hz  |—————\n";
    s+=" 250 Hz\n";
    s+=" 500 Hz\n";
    s+=" 1  kHz\n";
    s+=" 2  kHz\n";
    s+=" 4  kHz\n";
    s+=" 8  kHz\n";
    s+="16  kHz\n";
    s+="\n";
    s+="\n";
    s+="\n";
    s+="\t***USER COMMENTS SECTION***\n";
    s+="\n";
    s+="[9:47PM]\n";
    s+="\t[lorem ipsum]\n";
    s+="\n";
    s+="\n";
    s+="[9:56PM]\n";
    s+="\t[test text blablablablalbalbal]\n";
    s+="\n";
    
    return s;
}
