

#include "../include/app.hpp"


using namespace std;

App::App() {

}

void App::start(){
    	string line;
	while (getline(cin, line))
	{
		vector<string> words = splitToWords(line);

		if (words[0] == "add_time_mission")
		{
            try{
                if(isMissionDuplicate(stoi(words[1]))) throw DUPLICATE_ID;
                AddTimeMission(stoi(words[1]), stoi(words[2]),stoi(words[3]) , stoi(words[4]),stoi(words[5]));
			    cout<<"OK"<<endl;     
            }
            catch(string error){
                    cout<< error <<endl;
            }
            
		}
		else if (words[0] == "add_distance_mission")
		{
			try{
                if(isMissionDuplicate(stoi(words[1]))) throw DUPLICATE_ID;
                AddDistanceMission(stoi(words[1]), stoi(words[2]),stoi(words[3]) , stoi(words[4]),stoi(words[5]));
			    cout<<"OK"<<endl;     
            }
            catch(string error){
                    cout<< error <<endl;
            }
		}
        else if (words[0] == "add_count_mission")
		{
			try{
                if(isMissionDuplicate(stoi(words[1]))) throw DUPLICATE_ID;
                AddCountMission(stoi(words[1]), stoi(words[2]),stoi(words[3]) , stoi(words[4]),stoi(words[5]));
			    cout<<"OK"<<endl;     
            }
            catch(string error){
                    cout<< error <<endl;
            }

		}
        else if (words[0] == "assign_mission")
		{
            try{
                Mission* mission = getMission(stoi(words[1]));
                Driver* driver = getDriver(stoi(words[2]));
                driver->AddMission(*mission);
                cout<< "OK" << endl;
            }
            catch (string error) {
                if (error == "DRIVER_NOT_FOUND") {
                    Mission* mission = getMission(stoi(words[1]));    
                    Driver* driver = new Driver(stoi(words[2]));
                    driver->AddMission(*mission);
                    drivers.push_back(driver);
                    cout<< "OK" << endl;
                }
                else {
                    cout <<  error << endl;
                }
}
        }

        else if (words[0] == "record_ride")
		{
            try
            {
                Driver* driver = getDriver(stoi(words[3]));
                driver->AddTravel(stoi(words[1]),stoi(words[2]),stoi(words[4]));
            }
            catch(string error)
            {
                if (error == "DRIVER_NOT_FOUND"){
                    
                }
                else{
                     cout<< error <<endl;
                }                
            }
        }

        else if (words[0] == "show_missions_status")
		{
            try{
                Driver* driver = getDriver(stoi(words[1]));
                driver->PrintMissions();
            }           
            catch(string error)
            {
                if (error == "DRIVER_NOT_FOUND"){
                    cout<<"DRIVER_MISSION_NOT_FOUND"<<endl;
                }
                else{
                     cout<< error <<endl;
                }                
            }

            
        }

        else if (words[0] == "print")
		{
			PrintMissions();
		}

        else if (words[0] == "close")
		{
			break;
		}

		else
		{
			cerr << "Error: invalid command" << endl;
		}
	}
}


void App::AddTimeMission(int id, int start,int end , int target,int reward){
    TimeMission* mission = new TimeMission(id,start,end, target,reward);
    missions.push_back(mission);
}


void App::AddDistanceMission(int id, int start,int end , int target,int reward){
    DistanceMission* mission = new DistanceMission(id,start,end, target,reward);
    missions.push_back(mission);
}


void App::AddCountMission(int id, int start,int end , int target,int reward){
    CountMission* mission = new CountMission(id,start,end, target,reward);
    missions.push_back(mission);
}

bool App::isMissionDuplicate(int id){
    for(auto m : missions){
        if(id == m->getMissionId()){
            return true;
        }

    }
    return false;
}

void App::PrintMissions(){
    for(auto m : missions){
        m->printSummary();
    }
}

vector<string> App::splitToWords(string line)
{
	vector<string> words;
	stringstream sLine(line);
	string word;
	while (sLine >> word)
	{
		words.push_back(word);
	}
	return words;
}

Driver* App::getDriver(int id){
    for(auto D : drivers){
        if(D->getID() == id) return D;
    }
    throw DRIVER_NOT_FOUND;
}


Mission* App::getMission(int id){
    for(auto M : missions){
        if(M->getMissionId() == id) return M;
    }
    throw MISSION_NOT_FOUND;
}