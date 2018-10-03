/* 
 * File:   Cluster.h
 * Author: Nick Soetaert
 *
 * Created on November 30, 2017, 6:00 PM
 */

#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <queue>
#include <string>
#include "Job.h"
#include <iostream>
#include "CsvOutput.h"

using namespace std;

//Purpose: assigns Jobs to Cpus
class Cluster{
private:
    int _numAvailableCpus;
    bool _isFinished = false;
    priority_queue<Job, vector<Job>, greater<Job>> _jobQueue{}; //"waiting" jobs
    priority_queue<Job, vector<Job>, greater<Job>> _activeJobs{};
    CsvOutput output;
    
public:
    //to only be called once at start of program
    void setNumCpus(int numCpus){
        _numAvailableCpus = numCpus;
        output.initiateResultsCsv();
    }
    
    void addJobToQueue(Job newJob){
        _jobQueue.push(newJob);
    }
    
    void moveJobsFromQueueToActiveJobsIfPossible(int tick){
        Job toMove = _jobQueue.top();
        while((toMove.getRequiredCpus() <= _numAvailableCpus) && (_jobQueue.size() >= 1)){
            _numAvailableCpus -= toMove.getRequiredCpus();
            cout << "Moving " << toMove.getJobId() << " from jobQue to " 
                 << toMove.getRequiredCpus() << " unused Cpu(s)" << endl;
            cout << "Available CPUS: " << _numAvailableCpus << endl;
            _activeJobs.push(toMove); 
            _jobQueue.pop();
            toMove = _jobQueue.top();
        }
        cout<< "Did not move any jobs from jobQueue to activeJobs, " << endl
            << "    as jobQue is of length: " << _jobQueue.size() << endl
            << "    availableCpus: " << _numAvailableCpus << endl
            << "    CPUs needed for lowest CPU job: " << toMove.getRequiredCpus() << endl;
    }
    
    void doWork(){
        priority_queue<Job, vector<Job>, greater<Job>> tempQueue{};
        int numActiveJobs = _activeJobs.size(); //so we don't mess up the for loop
        int counter = 0;
        for(int i = 0; i < numActiveJobs; i++){ //only executes if there's >=1 job
            Job tempJob = _activeJobs.top(); //get the top job
            int newDuration = (tempJob.getTicksLeft() - 1); //decrement by 1
            tempJob.setDuration(newDuration);
            _activeJobs.pop(); //remove the job we just looked at
            tempQueue.push(tempJob); //add the job we just decremented
            counter++;
        }
        _activeJobs = tempQueue; //reassign to proper variable
        cout << "Did work on " << counter << " jobs." << endl;
        cout << "number of active jobs: " << _activeJobs.size() << endl;       
    }
    
    //when a job is removes, also output its info to results.csv
    void removeCompletedJobsFromActiveJobs(int tick){
        for(int i = 0; i < _activeJobs.size(); i++){
            Job topJob = _activeJobs.top();
            if(topJob.getTicksLeft() <= 0){ //if the job is complete
                int cpusToBeFreed = topJob.getRequiredCpus();
                topJob.setEndingTick(tick);
                output.writeJobToCsv(topJob);
                _activeJobs.pop(); //remove topJob
                _numAvailableCpus += cpusToBeFreed;
                cout << "Removed completed job: " <<
                        topJob.getJobId() << " (required CPUs: " <<
                        topJob.getRequiredCpus()<< " duration: " <<
                        topJob.getDuration() << ")" << endl;
                cout << "Available CPUS: " << _numAvailableCpus << endl;
            }
        }
    }
    
    bool getIsFinished(){
        return _isFinished;
    }
    void setIsFinishedIfPossible(){
        if((_jobQueue.size() == 0)&&(_activeJobs.size() == 0)){
            _isFinished = true;
        }
    }
};

#endif /* CLUSTER_H */

