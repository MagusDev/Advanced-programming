#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../include/team.hpp"
#include "../include/player.hpp"

using namespace std;

class Game{
    private:
        vector <string> teams;
        vector <float> teamScores;
        vector <string> yellowCards;
        vector <string> redCards;
        vector <string> playersWithScroe;
        vector <float> playerScores;
    
    public:
        Game();

};

#endif