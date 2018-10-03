/* 
 * File:   Job.h
 *
 * Created on November 30, 2017, 3:08 PM
 */

#ifndef JOB_H
#define JOB_H

#include <string>

using namespace std;

class Job
{
private:
    string _jobId;
    int _requiredCpus;
    int _ticksLeft; //this decreases as we get complete the job. Consider removing from class.
    int _DURATION; //this does not change except when we first construct an instance of the class
    int _startingTick;
    int _endingTick;

public:  
    Job(string jobId, int requiredCpus, int duration, int startingTick){ //constructor
        _jobId = jobId;
        _requiredCpus = requiredCpus;
        _DURATION = duration;
        _ticksLeft = duration;
        _startingTick = startingTick;
    }
    
    string getJobId() const{
        return _jobId;
    }

    int getRequiredCpus() const{
        return _requiredCpus;
    }
    
    int getTicksLeft() const
    {
        return _ticksLeft; 
    }
    
    int getDuration() const
    {
        return _DURATION;
    }
    
    void setDuration(int value)
    {
        _ticksLeft = value;
    }
    int getStartingTick(){
        return _startingTick;
    }
    int setEndingTick(int tick){
        _endingTick = tick;
    }
    int getEndingTick(){
        return _endingTick;
    }
};

bool operator<(const Job &left, const Job &right)
{
        return left.getTicksLeft() < right.getTicksLeft();
}

bool operator>(const Job &left, const Job &right)
{
        return left.getTicksLeft() > right.getTicksLeft();
}

bool operator==(const Job &left, const Job &right)
{
        return left.getTicksLeft() == right.getTicksLeft();
}

#endif // JOB_H


