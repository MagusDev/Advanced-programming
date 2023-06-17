#include "../include/count_mission.hpp"


CountMission::CountMission(int missionID, int startTimestamp, int endTimestamp,  int _targetNumber, int reward) : Mission(missionID, startTimestamp, endTimestamp, reward) {
    if(_targetNumber <0){
        throw INVALID_ARGS;
    }
    this->targetNumber = _targetNumber;
}

bool CountMission::isCompleted(const std::vector <Travel*> travels){
    if(completed) return true;
    int c = 0;
    for(auto t : travels){
        if((t->getStartTimestamp() >= getStartTimestamp()) && (t->getEndTimestamp() <= getEndTimestamp())){
            c ++;
            if (c >= getTargetNumber())
            {
                endTimestamp = t->getEndTimestamp();
                completed = true;
                return true;
            }
        }
    }
    
    return false;
}

Mission* CountMission::clone() const{
    CountMission* cm = new CountMission(getMissionId(), getStartTimestamp(),getEndTimestamp(),targetNumber,getReward());
    return cm;
}


int CountMission::getTargetNumber() const {
    return targetNumber;
}