#include "../include/team.hpp"

Team::Team(string _name){
    name = _name;
}

Team::Team(string _name, vector<string> GoalKeepers, vector<string> defenders, vector<string> midFielders, vector<string> forwards){
    name = _name;
    for(auto gk : GoalKeepers){
        Player* p = new Player(gk, "gk");
        players.push_back(p);
    }
    for(auto gk : defenders){
        Player* p = new Player(gk, "df");
        players.push_back(p);
    }
    for(auto gk : midFielders){
        Player* p = new Player(gk, "md");
        players.push_back(p);
    }
    for(auto gk : forwards){
        Player* p = new Player(gk, "fw");
        players.push_back(p);
    }
}

string Team::getName(){
    return name;
}

void Team::printPlayers(string filter,bool ranked ){
    cout<<"list of players :"<<endl;
    int index = 1;
    for(auto p : players){
        if(filter != "all"){
            if(p->getRole() == filter){
                cout<< index << ". ";
                p->printInfo();
                index ++;
            }
        }
        else{
            cout<< index << ". ";
            p->printInfo();
            index ++;
        }
    }
}
