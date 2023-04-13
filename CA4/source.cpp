#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;

const char TIME_SEPARATOR = '-';
const char MEMBER_SEPARATOR = '$';
const string LINE_SEPARATOR = "---";






class SalaryConfig {
public:
	SalaryConfig(string _level, int _baseSalary, int _salaryPerHour, int _salaryPerExtraHour, int _officialWorkingHours, int _taxPercentage) {
		level = _level;
		baseSalary = _baseSalary;
		salaryPerHour = _salaryPerHour;
		salaryPerExtraHour = _salaryPerExtraHour;
		officialWorkingHours = _officialWorkingHours;
		taxPercentage = _taxPercentage;
	}

	string getLevel() {
		return level;
	}

	int calcSalary(int hours)
	{
		int salary = 0;
		if (hours < officialWorkingHours) {
			salary += hours * salaryPerHour;
		}
		else {
			salary += officialWorkingHours * salaryPerHour + (hours - officialWorkingHours) * salaryPerExtraHour;
		}

		return salary * (100 - taxPercentage) / 100;
	}

	void printInfo() {
		cout << "level: " << level << endl;
		cout << "baseSalary: " << baseSalary << endl;
		cout << "salaryPerHour: " << salaryPerHour << endl;
		cout << "salaryPerExtraHour: " << salaryPerExtraHour << endl;
		cout << "officialWorkingHours: " << officialWorkingHours << endl;
		cout << "taxPercentage: " << taxPercentage << endl;
	}

private:
	string level;
	int baseSalary;
	int salaryPerHour;
	int salaryPerExtraHour;
	int officialWorkingHours;
	int taxPercentage;
};

class WorkingHour {
public:
	WorkingHour(int _employee_id, int _day, string _working_interval) {
		day = _day;
		employee_id = _employee_id;
		extractInterval(_working_interval, startHour, endHour);
	}

	void printInfo() {
		cout << "employee_id: " << employee_id << endl;
		cout << "day: " << day << endl;
		cout << "working_interval: " << startHour << TIME_SEPARATOR << endHour << endl;
	}

	int getEployeeID() {
		return employee_id;
	}

	int getDay() {
		return day;
	}

	int getIntervalLength() {
		return endHour - startHour;
	}

private:
	int employee_id;
	int day;
	int startHour;
	int endHour;

	void extractInterval(string input_str, int& startHour, int& endHour) {
		stringstream ss(input_str);
		getline(ss, input_str, TIME_SEPARATOR);
		startHour = stoi(input_str);
		getline(ss, input_str);
		endHour = stoi(input_str);
	}
};

class Employee {
public:
	Employee(int _id, string _name, int _age, string _level) {
		id = _id;
		name = _name;
		age = _age;
		level = _level;
	}
	void printInfo() {
		cout << "id: " << id << endl;
		cout << "name: " << name << endl;
		cout << "age: " << age << endl;
		cout << "level: " << level << endl;
		calcTotalWorkingHours();
		for (auto workingHour : workingHours) {
			//workingHour->printInfo();
		}

		cout << "salary: " << getSalary() << endl;
		config->printInfo();
	}

	void assignWorkingHour(WorkingHour& _workingHour) {
		if (_workingHour.getEployeeID() == id) {
			workingHours.push_back(&_workingHour);
		}
	}

	int getID() {
		return id;
	}

	void assignTeamID(int _team_id) {
		team_id = _team_id;
	}

	int getSalary() {
		calcTotalWorkingHours();
		return config->calcSalary(totalWorkingHours);
	}

	void assignConfig(vector<SalaryConfig>& configs) {
		for (int c = 0; c < configs.size(); c++) {
			if (configs[c].getLevel() == level) {
				config = &configs[c];
			}
		}
	}

private:
	int id;
	string name;
	int age;
	string level;
	SalaryConfig* config;
	vector<WorkingHour*> workingHours;
	int totalWorkingHours;
	int team_id;

	void calcTotalWorkingHours() {
		totalWorkingHours = 0;
		for (auto wh : workingHours) {
			totalWorkingHours += wh->getIntervalLength();
		}
	}

};

class Team {
public:
	Team(int _team_id, int _teamHeadID, string _memberIDs, int _bonus_min_working_hours = 0, float _bonus_working_hours_max_variance = 0) {
		team_id = _team_id;
		teamHeadID = _teamHeadID;
		memberIDs = extractMemberIDs(_memberIDs);
		bonus_min_working_hours = _bonus_min_working_hours;
		bonus_working_hours_max_variance = _bonus_working_hours_max_variance;
	}

	void printInfo() {
		cout << "Team ID: " << team_id << endl;
		cout << "Team Head: " << endl;
		teamHead->printInfo();
		cout << "Members: " << endl;
		for (auto m : members) {
			m->printInfo();
			cout << LINE_SEPARATOR << endl;
		}
		cout << "bonus min hours: " << bonus_min_working_hours << endl;
		cout << "bonus max variance: " << bonus_working_hours_max_variance << endl;
	}

	int getTeamID() {
		return team_id;
	}

	void assignMembers(vector<Employee>& _employees) {
		for (int e = 0; e < _employees.size(); e++) {
			if (find(memberIDs.begin(), memberIDs.end(), _employees[e].getID()) != memberIDs.end()) {
				members.push_back(&_employees[e]);
				_employees[e].assignTeamID(team_id);
			}
			if (teamHeadID == _employees[e].getID()) {
				teamHead = &_employees[e];
			}
		}
	}

private:
	int team_id;
	int teamHeadID;
	Employee* teamHead;
	vector<int> memberIDs;
	vector<Employee*> members;
	int bonus_min_working_hours;
	float bonus_working_hours_max_variance;

	vector<int> extractMemberIDs(string input_str) {
		vector<int> memberIDs;
		istringstream ss(input_str);
		string id;
		while (std::getline(ss, id, MEMBER_SEPARATOR)) {
			memberIDs.push_back(stoi(id));
		}
		return memberIDs;
	}

};

vector<vector<string>> readCSV(string filename) {
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
			row.push_back(line);
		}

		data.push_back(row);
	}

	file.close();
	return data;
}

vector<Employee> initEmployees(const vector<vector<string>>& data, vector<SalaryConfig>& salaryConfigs) {
	vector<Employee> employees;
	for (int line = 1; line < data.size(); line++)
	{
		Employee e(stoi(data[line][0]), data[line][1], stoi(data[line][2]), data[line][3]);
		e.assignConfig(salaryConfigs);
		employees.push_back(e);
	}
	return employees;
}

vector<WorkingHour> initWorkingHours(const vector<vector<string>>& data) {
	vector<WorkingHour> workingHours;
	for (int line = 1; line < data.size(); line++)
	{
		WorkingHour w(stoi(data[line][0]), stoi(data[line][1]), data[line][2]);
		workingHours.push_back(w);
	}
	return workingHours;
}

vector<SalaryConfig> initSalaryConfig(const vector<vector<string>>& data) {
	vector<SalaryConfig> salaryConfigs;
	for (int line = 1; line < data.size(); line++)
	{
		SalaryConfig s(data[line][0], stoi(data[line][1]), stoi(data[line][2]), stoi(data[line][3]), stoi(data[line][4]), stoi(data[line][5]));
		salaryConfigs.push_back(s);
	}
	return salaryConfigs;
}

void assignWorkingHoursToEmployees(vector<Employee>& employees, vector<WorkingHour>& workingHours) {
	for (int e = 0; e < employees.size(); e++) {
		for (int w = 0; w < workingHours.size(); w++) {
			employees[e].assignWorkingHour(workingHours[w]);
		}
	}
}

vector<Team> initTeams(const vector<vector<string>>& data, vector<Employee>& employees) {
	vector<Team> teams;
	for (int line = 1; line < data.size(); line++)
	{
		Team t(stoi(data[line][0]), stoi(data[line][1]), data[line][2], stoi(data[line][3]), stof(data[line][4]));
		t.assignMembers(employees);
		teams.push_back(t);
	}
	return teams;
}

vector<string> splitToWords(string line)
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

void reportTotalHoursPerDay(vector<WorkingHour> workingHours,int startDay,int endDay) {
	for (int day = startDay; day <= endDay; day++) {
		int totalHours = 0;
		for (auto wh : workingHours) {
			if (wh.getDay() == day) {
				totalHours += wh.getIntervalLength();
			}
		}
		cout << "Day #" << day << ": " <<totalHours<< endl;
	}
}

void cammandHandler(vector<Employee>& employees, vector<Team>& teams,
	vector<WorkingHour>& workingHours, vector<SalaryConfig>& salaryConfigs) {
	string line;
	while (getline(cin, line))
	{
		vector<string> words = splitToWords(line);

		if (words[0] == "report_salaries")
		{
			//reportSalaries(employees);
		}
		else if (words[0] == "report_employee_salary")
		{
			//reportEmployeeSalary(employees, stoi(words[1]));
		}
		else if (words[0] == "report_team_salary")
		{
			//reportTeamSalary(teams, stoi(words[1]));
		}
		else if (words[0] == "report_total_hours_per_day")
		{
			reportTotalHoursPerDay(workingHours, stoi(words[1]), stoi(words[2]));
		}
		else if (words[0] == "report_employee_per_hour")
		{
			//reportEmployeePerHour(employees, stoi(words[1]), stoi(words[2]));
		}
		else if (words[0] == "show_salary_config")
		{
			//showSalaryConfig(salaryConfigs, words[1]);
		}
		else if (words[0] == "update_salary_config")
		{
			//updateSalaryConfig(salaryConfigs, words[1], stoi(words[2]),
			//					stoi(words[3]), stoi(words[4]), stoi(words[5]), stoi(words[6]));
		}
		else if (words[0] == "add_working_hours")
		{
			//addWorkingHours(employees, workingHours, stoi(words[1]), stoi(words[2]),
			//											stoi(words[3]), stoi(words[4]));
		}
		else if (words[0] == "delete_working_hours")
		{
			//deleteWorkingHours(employees, stoi(words[1]), stoi(words[2]));
		}
		else if (words[0] == "update_team_bonus")
		{
			//updateTeamBonus(teams, stoi(words[1]), stoi(words[2]));
		}
		else if (words[0] == "find_teams_for_bonus")
		{
			//find_teams_for_bonus(teams);
		}
		else
		{
			cerr << "Error: invalid command" << endl;
		}
	}
}

int main() {
	vector<SalaryConfig> salaryConfigs = initSalaryConfig(readCSV("salary_configs.csv"));
	vector<Employee> employees = initEmployees(readCSV("employees.csv"), salaryConfigs);
	vector<WorkingHour> workingHours = initWorkingHours(readCSV("working_hours.csv"));
	assignWorkingHoursToEmployees(employees, workingHours);
	vector<Team> teams = initTeams(readCSV("teams.csv"), employees);

	cammandHandler(employees, teams, workingHours, salaryConfigs);

	/*
	for (int i = 0; i < employees.size(); i++)
	{
		employees[i].printInfo();
		cout << endl;
	}
	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	for (int i = 0; i < workingHours.size(); i++)
	{
		workingHours[i].printInfo();
		cout << endl;
	}
	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	for (int i = 0; i < salaryConfigs.size(); i++)
	{
		salaryConfigs[i].printInfo();
		cout << endl;
	}
	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	for (int i = 0; i < teams.size(); i++)
	{
		teams[i].printInfo();
		cout << endl;
	}
	*/
	return 0;
}


