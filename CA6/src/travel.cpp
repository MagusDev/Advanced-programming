#include "../include/travel.hpp"



Travel::Travel(int driverID, int startTimestamp, int endTimestamp, int travelDistance) {
    if(startTimestamp > endTimestamp){
        throw INVALID_ARG;
    }
    this->driverID = driverID;
    this->startTimestamp = startTimestamp;
    this->endTimestamp = endTimestamp;
    this->travelDistance = travelDistance;
}


int Travel::getDriverId() const {
    return driverID;
}

int Travel::getStartTimestamp() const {
    return startTimestamp;
}

int Travel::getEndTimestamp() const {
    return endTimestamp;
}


int Travel::getTravelDistance() const {
    return travelDistance;
}