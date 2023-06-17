#include <iostream>
#include <string>
#include "mission.hpp"

class CountMission : public Mission {
    private:
        int targetNumber;
    
    public:

        CountMission(int missionID, int startTimestamp, int endTimestamp,  int _targetNumber, int reward);

        virtual bool isCompleted(const std::vector <Travel*> travels);
        virtual Mission* clone() const;
        
        int getTargetNumber() const;
};

