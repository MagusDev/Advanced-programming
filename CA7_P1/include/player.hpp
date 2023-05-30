#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Player{
    private:
        string name;
        string role;
        float score = 0.0f;



    
    public:
        Player(string _name, string _role);
        void printInfo();
        string getName();
        string getRole();
        float getScore();

};

#endif