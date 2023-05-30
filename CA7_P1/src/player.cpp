#include "../include/player.hpp"

Player::Player(string _name, string _role){
    name = _name;
    role = _role;
}

void Player::printInfo(){
    string info = "name: " + name + " | role: " + role + " | score: " + to_string(score);
    //cout << "name: " << name << " | role: " << role << " | score: " << score << endl;
    cout << info << endl;
}

string Player::getName(){
    return name;
}

string Player::getRole(){
    return role;
}

float Player::getScore(){
    return score;
}
