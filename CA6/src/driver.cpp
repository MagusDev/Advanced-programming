#include "../include/driver.hpp"

using namespace std;

Driver::Driver(int id) {
    driverID = id;
}

void Driver::AddTravel(int start, int end, int distance) {
    if(missions.empty()){
        return;
    }
    Travel* t = new Travel(driverID , start , end, distance);
    travels.push_back(t);
    printCompletedMissions();
}

void Driver::AddMission(Mission& mission) {
    if(isMissionDuplicate(mission.getMissionId())){
        throw DUPLICATE_DRIVER_MISSION;
    }
    Mission* m = mission.clone();
    missions.push_back(m);
    sortMissionsByStartTime();
}

int Driver::getID() {
    return driverID;
}

 void Driver::sortMissionsByStartTime() {
        std::sort(missions.begin(), missions.end(),
                [](Mission* a, Mission* b) {
                    return a->getStartTimestamp() < b->getStartTimestamp();
                }
        );
}

void Driver::PrintMissions() {
    cout<< "missions status for driver "<< driverID << ":" <<endl;
    for (size_t i = 0; i < missions.size(); i++) {
        missions[i]->printFull();
        if (i != missions.size() - 1) {
            cout << endl; 
        }
    }
}

void Driver::printCompletedMissions(){
    cout<< "completed missions for driver "<< driverID << ":" <<endl;
    int i = 0;
    for (auto m : missions) {
        if (m->isCompleted(travels)) {
            i++;
            m->printSummary();
            if (i != getCompletedMissionsCount() - 1) {
                cout << endl; 
            }
        }   
    }
}

bool Driver::isMissionDuplicate(int id){
    for (auto m : missions) {
        if(m->getMissionId() == id)
        return true;
    }
    return false;
}

int Driver::getCompletedMissionsCount(){
    int c = 0;
    for(auto m : missions){
        if(m->isCompleted(travels)) c++;
    }
    return c;
}