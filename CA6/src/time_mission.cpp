#include "../include/time_mission.hpp"

using namespace std;

TimeMission::TimeMission(int missionID, int startTimestamp, int endTimestamp, int _targetTime, int reward) : Mission(missionID, startTimestamp, endTimestamp, reward) {
    if(_targetTime <0){
        throw INVALID_ARGS;
    }
    this->targetTime = _targetTime;
}

bool TimeMission::isCompleted(const std::vector <Travel*> travels){
    if(completed) return true;
    int c = 0;
    for(auto t : travels){
        if((t->getStartTimestamp() >= getStartTimestamp()) && (t->getEndTimestamp() <= getEndTimestamp())){
            c += t->getEndTimestamp() - t->getStartTimestamp();
            if (c >= getTargetTime() * 60)
            {
                endTimestamp = t->getEndTimestamp();
                completed = true;
                return true;
            }
        }
    }
    
    return false;
}

Mission* TimeMission::clone() const{
    TimeMission* cm = new TimeMission(getMissionId(), getStartTimestamp(),getEndTimestamp(),targetTime,getReward());
    return cm;
}

int TimeMission::getTargetTime() const {
    return targetTime;
}