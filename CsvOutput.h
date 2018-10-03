/* 
 * File:   CsvOutput.h
 * Author: Nick Soetaert
 *
 * Created on December 5, 2017, 5:20 PM
 */

#ifndef CSVOUTPUT_H
#define CSVOUTPUT_H
#include <iostream>
#include <fstream>
#include "Job.h"

class CsvOutput{
private:
    ofstream outputStream;
    
public:
    void initiateResultsCsv(){
    outputStream.open("results.csv");
    outputStream << "\"Job Name\",\"Starting Tick\",\"Ending Tick\",\"Duration\"" << endl;
    }
    
    void writeJobToCsv(Job job){
        outputStream << 
                "\"" << job.getJobId() << "\"," <<
                "\"" << job.getStartingTick() << "\"," <<
                "\"" << job.getEndingTick() << "\"," <<
                "\"" << (job.getEndingTick() - job.getStartingTick()) << "\"" << endl;
    }
};


#endif /* CSVOUTPUT_H */

