#ifndef MISSION_HPP
#define MISSION_HPP

#include <iostream>
#include <string>
#include <vector>

#include "../include/travel.hpp"

const std::string INVALID_ARGS = "INVALID_ARGUMENTS";

class Mission {
    private:
        int missionID;
        int startTimestamp;
        int reward;

    protected:
        int endTimestamp;
        bool completed = false;
    
    public:

        Mission(int missionID, int startTimestamp, int endTimestamp, int reward);
        
        virtual Mission* clone() const = 0;

        int getMissionId() const;
        int getStartTimestamp() const;
        int getEndTimestamp() const;
        int getReward() const;
        void printSummary();
        void printFull();
        bool getCompleted();
        virtual bool isCompleted(const std::vector <Travel*> travels) = 0;
};

#endif
