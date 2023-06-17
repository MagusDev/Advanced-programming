#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <unordered_set>
#include <cmath>
#include <iomanip>
#include <algorithm>

#include "../include/driver.hpp"
#include "../include/time_mission.hpp"
#include "../include/distance_mission.hpp"
#include "../include/count_mission.hpp"



const std::string DUPLICATE_ID = "DUPLICATE_MISSION_ID";
const std::string DRIVER_NOT_FOUND = "DRIVER_NOT_FOUND";
const std::string MISSION_NOT_FOUND = "MISSION_NOT_FOUND";

class App{
    private:
        std::vector <Driver*> drivers;
        std::vector <Mission*> missions;

        std::vector<std::string> splitToWords(std::string line);

        bool isMissionDuplicate(int id);
        Driver* getDriver(int id);
        Mission* getMission(int id);


    
    public:

        App();
        
        // Public methods
        void start();
        void AddCountMission(int id, int start,int end,int target,int reward);
        void AddDistanceMission(int id, int start,int end,int target,int reward);
        void AddTimeMission(int id, int start,int end,int target,int reward);
        void PrintMissions();
};
