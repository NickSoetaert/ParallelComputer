/* 
 * File:   main.cpp
 * Author: Nick Soetaert
 *
 * Created on November 30, 2017, 2:37 PM
 */

#include <istream>
#include "Job.h"
#include "Cluster.h"
#include "CsvOutput.h"
//g++ -std=c++14 Job.h Cluster.h CsvOutput.h main.cpp -o main

int main(){
    Cluster cluster;
    
    ifstream inputStream;
    inputStream.open("Jobs.txt"); //Jobs.txt
    int numCpus;
    inputStream >> numCpus;
    cluster.setNumCpus(numCpus);
    cout << "Set cluster to contain " << numCpus << " CPUs." << endl;

    string Id;
    int requiredCpus, duration;
    int tick = 1;

    while(cluster.getIsFinished() == false){
        cout << "~~~~TICK NUMBER: " << tick << "~~~~" << endl;    
        
        if(inputStream >> Id >> requiredCpus >> duration){ //if there are still jobs to read...
            Job newJob(Id, requiredCpus, duration, tick);  //create a new job
            if(newJob.getRequiredCpus() > numCpus){ //check that it doesn't require too many CPUs
                cout << "ERROR: Too many CPUs in " << newJob.getJobId() << endl;
                exit(1);
            }
            cluster.addJobToQueue(newJob);
            cout << "Read from file into jobQueue" << endl;
        } else {
            cout << "Did NOT read from file into jobQueue" << endl;
        }
        cluster.moveJobsFromQueueToActiveJobsIfPossible(tick);
        cluster.doWork();
        cluster.removeCompletedJobsFromActiveJobs(tick);
        cluster.setIsFinishedIfPossible();
        tick++;
    }
    cout << "Goodbye!" << endl;

    return 0;
}