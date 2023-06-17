#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../include/travel.hpp"
#include "../include/mission.hpp"

const std::string DUPLICATE_DRIVER_MISSION = "DUPLICATE_DRIVER_MISSION";

class Driver{
    private:
        int driverID;
        std::vector <Mission*> missions;
        std::vector <Travel*> travels;

        bool isMissionDuplicate(int id);

    
    public:

        Driver(int id);

        

        void AddTravel(int start, int end, int distance);
        void AddMission(Mission& mission);
        int getID();
        void PrintMissions();
        void printCompletedMissions();
        void sortMissionsByStartTime();
        int getCompletedMissionsCount();
};
