#include <iostream>
#include <string>
#include "mission.hpp"

class DistanceMission : public Mission {
    private:
        int targetDistance;
    
    public:
        // Constructor
        DistanceMission(int missionID, int startTimestamp, int endTimestamp,  int _targetNumber, int reward);

        virtual bool isCompleted(const std::vector <Travel*> travels);
        virtual Mission* clone() const;
        
        int getTargetDistanceInMeters() const;
};