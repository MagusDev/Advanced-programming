#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


#include "../include/player.hpp"

using namespace std;

class Team{
    private:
        string name;
        int score = 0.0f;
        vector <Player*> players;


    
    public:
        Team(string _name);
        Team(string _name, vector<string> GoalKeepers, vector<string> defenders, vector<string> midFielders, vector<string> forwards);
        string getName();
        void printPlayers(string filter = "all",bool ranked = false);


};

#endif