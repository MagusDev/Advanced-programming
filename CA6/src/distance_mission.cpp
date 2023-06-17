#include "../include/distance_mission.hpp"


DistanceMission::DistanceMission(int missionID, int startTimestamp, int endTimestamp,  int _targetDistance, int reward) : Mission(missionID, startTimestamp, endTimestamp, reward)  {
    if(_targetDistance <0){
        throw INVALID_ARGS;
    }
    this->targetDistance = _targetDistance;
}

bool DistanceMission::isCompleted(const std::vector <Travel*> travels){
    if(completed) return true;
    int c = 0;
    for(auto t : travels){
        if((t->getStartTimestamp() >= getStartTimestamp()) && (t->getEndTimestamp() <= getEndTimestamp())){
            c += t->getTravelDistance();
            if (c >= getTargetDistanceInMeters())
            {
                endTimestamp = t->getEndTimestamp();
                completed = true;
                return true;
            }
        }
    }
    
    return false;
}

Mission* DistanceMission::clone() const{
    DistanceMission* cm = new DistanceMission(getMissionId(), getStartTimestamp(),getEndTimestamp(),targetDistance,getReward());
    return cm;
}

int DistanceMission::getTargetDistanceInMeters() const {
    return targetDistance;
}