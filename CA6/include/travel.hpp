#ifndef TRAVEL_HPP
#define TRAVEL_HPP
#include <iostream>
#include <string>

const std::string INVALID_ARG = "INVALID_ARGUMENTS";

class Travel {
    private:
        int driverID;
        int startTimestamp;
        int endTimestamp;
        int travelDistance;
    
    public:
        Travel(int driverID, int startTimestamp, int endTimestamp, int travelDistance);
        
        int getDriverId() const;
        int getStartTimestamp() const;
        int getEndTimestamp() const;
        int getTravelDistance() const;
};

#endif