#include <iostream>
#include <string>
#include "mission.hpp"

class TimeMission : public Mission {
    private:
        int targetTime;
    
    public:
        TimeMission(int missionID, int startTimestamp, int endTimestamp,  int _targetTime, int reward);
        
        int getTargetTime() const;
        virtual bool isCompleted(const std::vector <Travel*> travels);
        virtual Mission* clone() const;
};

