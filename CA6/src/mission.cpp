#include "../include/mission.hpp"

using namespace std;

Mission::Mission(int missionID, int startTimestamp, int endTimestamp, int reward) {
    if(startTimestamp > endTimestamp || reward<0){
        throw INVALID_ARGS;
    }
    this->missionID = missionID;
    this->startTimestamp = startTimestamp;
    this->endTimestamp = endTimestamp;
    this->reward = reward;
}


int Mission::getMissionId() const {
    return missionID;
}



int Mission::getStartTimestamp() const {
    return startTimestamp;
}


int Mission::getEndTimestamp() const {
    return endTimestamp;
}


int Mission::getReward() const {
    return reward;
}

bool Mission::getCompleted(){
    return completed;
}

void Mission::printFull(){
    cout<< "mission " << getMissionId() << ":" << endl;
    cout<< "start timestamp: " << getStartTimestamp() << endl ;
    if(completed){
        cout<< "end timestamp: " << getEndTimestamp() << endl ;
        cout<< "reward: " << getReward() << endl;
        cout<< "status: "<< "completed"<<endl;
    }
    else{
        cout<< "end timestamp: " << -1 << endl ;
        cout<< "reward: " << getReward() << endl;
        cout<< "status: "<< "ongoing"<<endl;
    }
    
}

void Mission::printSummary(){
    cout<< "mission" << ": "  << getMissionId() << endl;
    cout<< "start timestamp: " << getStartTimestamp() << endl ;
    cout<< "end timestamp: " << getEndTimestamp() << endl ;
    cout<< "reward: " << getReward() << endl;
}




