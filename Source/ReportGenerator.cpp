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

std::vector<int> ReportGenerator::setGainFactors(Session& session)
{
    std::vector<int> gainVec;
    if(g_gainAmplification)
        gainVec.push_back(g_gainFactor);
    if(g_gainAttenuation)
        gainVec.push_back(-(g_gainFactor));
    
    return gainVec;
}


Report ReportGenerator::createReport(Session session, User& user)
{
    Report r;
    
    r.username = user.mUsername;
    r.date = getStrCurrentTime();
    r.timePractised = convertTimeStr(session.getDuration() );
    r.freqRange = session.getStrRange();
    r.gainFactor = setGainFactors(session);
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
                chosenDirectory.getFullPathName()+"/report_"+getStrFormatCurrentTime()+".txt";
            
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

String ReportGenerator::gainStr(Report& report)
{
    
    String s="";
    for(int i=0;i<(report.gainFactor).size();i++)
    {
        s += static_cast<String>(report.gainFactor[i])+" ";
        std::cout<<report.gainFactor[i]<<std::endl;
    }
    return s;
}

String ReportGenerator::linesPercent(float percent)
{
    String s = "";
    
    int nblines = static_cast<int>(percent*100)/2;
    
    for(int i=0;i<nblines;i++)
    {
        s +="-";
    }
    
    std::cout<<s<<std::endl;
    return s;
}

String ReportGenerator::freqRowStr(FreqStats& fs, float freq)
{
    String s ="Hz\t["+static_cast<String>(fs.count[freq])+"]\t\t|"+linesPercent(fs.getPercent(freq))+" "+
    static_cast<String>(fs.getPercent(freq)*100)+"% \n";
    
    return s;
}

String ReportGenerator::freqChartStr(Report& report)
{
    String range = report.freqRange;
    
    String s = "";

    if(range == "All" || range == "Low")
        s+=" 31.25"+freqRowStr(report.freqstats, 31.25);
    
    if(range == "All" || range == "Mid8" || range == "Low")
        s+=" 62.5 "+freqRowStr(report.freqstats, 62.5);

    if(range == "All" || range == "Mid8" || range == "Low")
        s+=" 125  "+freqRowStr(report.freqstats, 125);

    if(range == "All" || range == "Mid8" || range == "Mid" || range == "Low")
        s+=" 250  "+freqRowStr(report.freqstats, 250);

    if(range == "All" || range == "Mid8" || range == "Mid" || range == "Low")
        s+=" 500  "+freqRowStr(report.freqstats, 500);

    if(range == "All" || range == "Mid8" || range == "High" || range == "Mid")
        s+=" 1   k"+freqRowStr(report.freqstats, 1000);

    if(range == "All" || range == "Mid8" || range == "High" || range == "Mid")
        s+=" 2   k"+freqRowStr(report.freqstats, 2000);

    if(range == "All" || range == "Mid8" || range == "High" || range == "Mid")
        s+=" 4   k"+freqRowStr(report.freqstats, 4000);

    if(range == "All" || range == "Mid8" || range == "High")
        s+=" 8   k"+freqRowStr(report.freqstats, 8000);

    if(range == "All" || range == "High")
        s+="16   k"+freqRowStr(report.freqstats, 16000);


    return s;
}

String ReportGenerator::reportTxtContent(Report& report)
{

    
    String s = "\n";
    s+= "\t\t \n";
    s+="\t\t\tFILTER TRAINER\n";
    s+="\t\t\tREPORT\n";
    s+="\t\t*********************************************\n";
    s+="\n";
    s+="\t\t\tUser ["+report.username+"]\n";
    s+="\t\t\tDate: "+report.date+"\n";
    s+="\n";
    s+="\n";
    s+="\n";
    s+="\t***SESSION INFORMATION***\n";
    s+="\n";
    s+="\n";
    s+="Time practiced ["+report.timePractised+"]\n";
    s+="\n";
    s+="Exercise settings\n";
    s+="\tFrequency range ["+report.freqRange+"]\n";
    s+="\tAmplification or Attenuation (dB) ["+gainStr(report)+"]\n";
    s+="\n";
    s+="\n";
    s+="Name(s) of audo file(s) loaded\n";
    
    for(int i=0;i<(report.audioFiles).size();i++)
    {
         s+="\t["+report.audioFiles[i]+"]\n";
    }
    s+="\n";
    s+="\n";
    s+="Total number of questions asked ["+ static_cast<String>(report.nbQuestions) +"]\n";
    s+="\n";
    s+="\n";
    s+="\n";
    s+="\t***GRAPH***\n";
    s+="\n";
    s+="center\     #times  \n";
    s+="freq        involved         score (%)\n";
    s+="————————————————————————--------------\n";
    s+=freqChartStr(report);
    s+="\n";
    s+="\n";
    s+="\n";
    s+="\t***USER COMMENTS SECTION***\n";
    s+="\n";
    for(int i=0;i<(report.comments).size();i++)
    {
        s+="[["+(report.comments[i]).mDate+"\n";
        s+="\t["+(report.comments[i]).mText+"]\n";
        s+="\n";
        s+="\n";
    }
    s+="\n";
    
    return s;
}
