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

#include "../include/team.hpp"
#include "../include/user.hpp"
#include "Errors.hpp"

using namespace std;

const std::string SUCCESSFUL = "OK\n";

class App{
    private:
        const string LEAGUE_ADRESS = "data/premier_league.csv";

        vector<string> splitToWords(string line);
        vector<Team*> teams;
        vector<vector<string>> readCSV(string filename);
        vector<string> parseString(string& input);
        std::string replaceSpacesWithUnderscores(std::string input); 
        bool isTransferWindowOpen = false;


        void GETrequest(std::vector<std::string> words);
        void POSTrequest(std::vector<std::string> words);
        void PUTrequest(std::vector<std::string> words);
        void DELETErequest(std::vector<std::string> words);


        /////////////////////////////////////////////////////////////////////////
        std::vector <User*> users;
        User* loggedUser;

        void registerAdmin(std::string username, std::string password);
        void signUp(std::string username, std::string password);
        void logIn(std::string username, std::string password);
        User* getUser(std::string username);
        void logOut();

        void setTransferWindowOpen(bool status);
        //////////////////////////////////////////////////////////////////////////

        Team* getTeam(std::string teamName);
        void showTeamByName(std::vector<std::string> arguments);

        void initTeams();
        void printTeams();

    
    public:
        App();
        
        // Public methods
        void start();
        void commandHandler();

};