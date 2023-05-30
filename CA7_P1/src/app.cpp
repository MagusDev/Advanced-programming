#include "../include/app.hpp"

App::App() {

}

void App::start(){
    cout<<"app started"<<endl;
    Admin* a = new Admin;
    users.push_back(a);

    initTeams();

    commandHandler();
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

string App::replaceSpacesWithUnderscores(string input) {
    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] == ' ') {
            input[i] = '_';
        }
    }
    return input;
}

void App::commandHandler(){
    string line;
	while (getline(cin, line))
	{
        try{
            vector<string> words = splitToWords(line);
            std::vector<string> command(words.begin() + 1, words.end());

            if (words[0] == "GET")
		    {
			    GETrequest(command);
		    }   
            else if (words[0] == "POST")
		    {
			    POSTrequest(command);
                cout<< SUCCESSFUL;
		    }   
            else if (words[0] == "PUT")
		    {
			    PUTrequest(command);
                cout<< SUCCESSFUL;
		    }   
            else if (words[0] == "DELETE")
		    {
			    DELETErequest(command);
                cout<< SUCCESSFUL;
		    }   
		    else
		    {
			    throw Bad_Request_Error();
		    }
        }
        catch (Permission_Error& p) {
			cout << p.what();
		}
		catch (Bad_Request_Error& b) {
			cout << b.what();
		}
		catch (Not_Found_Error& n) {
			cout << n.what();
		}

	}
}

void App::GETrequest(vector<string> command){
    if(command[0] == "players"){
        showTeamByName(command);
    }
}

void App::POSTrequest(vector<string> command){
    if(command[0] == "signup"){
        signUp(command[3], command[5]);
    }
    else if(command[0] == "login"){
        logIn(command[3], command[5]);
    }
    else if(command[0] == "register_admin"){
        registerAdmin(command[3], command[5]);
    }
    else if(command[0] == "logout"){
        logOut();
    }
    else if(command[0] == "close_transfer_window"){
        setTransferWindowOpen(false);
    }
    else if(command[0] == "open_transfer_window"){
        setTransferWindowOpen(true);
    }
}

void App::PUTrequest(vector<string> command){

}

void App::DELETErequest(vector<string> command){

}


vector<vector<string>> App::readCSV(string filename) {
	vector<vector<string>> data;
	ifstream file(filename);

	if (!file.is_open()) {
		cout << "Error opening file" << endl;
		return data;
	}

	string line;

	while (getline(file, line)) {
		stringstream ss(line);
		vector<string> row;

	    while (getline(ss, line, ',')) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            row.push_back(line);
        }

		data.push_back(row);
	}

	file.close();
	return data;
}

vector<string> App::parseString(string& input) {
    vector<string> result;
    stringstream ss(input);
    string item;
    while (getline(ss, item, ';')) {
        result.push_back(item);
    }
    return result;
}


void App::initTeams(){
    vector<vector<string>> data = readCSV(LEAGUE_ADRESS);
    for(int line = 1; line < data.size(); line++){

        Team* t = new Team(data[line][0],parseString(data[line][1]),parseString(data[line][2]),parseString(data[line][3]),parseString(data[line][4]));
        teams.push_back(t);

    }

}

void App::printTeams(){
    for(auto t : teams){
        cout << "Team Name: " << t->getName() << endl;;
        t->printPlayers();
        cout<<"=================================="<<endl;
    }
}

void App::signUp(std::string username, std::string password){
    for(auto u : users){
        if(u->getUserName() == username){
            throw Bad_Request_Error();
        }
    }
    RegularUser* u = new RegularUser(username, password);
    users.push_back(u);
    loggedUser = u;
}

void App::registerAdmin(std::string username, std::string password){
    try{
        User* a = getUser(username);
        if(a->getPassWord() == password && dynamic_cast<Admin*>(a)){
            loggedUser = a;
        }
    }
    catch(string exp){
        cout << exp << endl;
    }
    
}

void App::logIn(std::string username, std::string password){

    User* a = getUser(username);

    if(dynamic_cast<Admin*>(a)){
        throw Permission_Error();
    }

    if(a->getPassWord() == password){
        loggedUser = a;
    }
    else{
        throw Permission_Error();
    }

}

void App::logOut(){
    loggedUser = nullptr;
}

User* App::getUser(std::string username){
    for(auto u : users){
        if(u->getUserName() == username){
            return u;
        }
    }

    throw Not_Found_Error();
}

void App::setTransferWindowOpen(bool status){
    if(!dynamic_cast<Admin*>(loggedUser)){
        throw Permission_Error();
    }

    isTransferWindowOpen = status;
}

Team* App::getTeam(std::string teamName){
    for(auto t : teams){
        if(replaceSpacesWithUnderscores(t->getName())  == teamName){
            return t;
        }
    }
    throw Not_Found_Error();
}


void App::showTeamByName(std::vector<std::string> command){
    Team* t = getTeam(command[3]);
    string filter = "all";
    bool ranked = false;
    if(command.size() > 4){
        if(command[4] == "gk" || command[4] == "df" || command[4] == "md" || command[4] == "fw"){
            filter = command[4];
        }
        else{
            throw Bad_Request_Error();
        } 
    }
    if(command.size() > 5){
        ranked = true;
    }
    t->printPlayers(filter,ranked);

}
