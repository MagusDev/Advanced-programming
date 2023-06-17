#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

const vector<string> START_TIMES = {"07:30","09:30","11:30"};
const vector<string> END_TIMES = {"09:00","11:00","13:00"};
const vector<string> DAYS_OF_WEEK = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
const int NUM_CLASSES = 2;




struct Teacher{
	string name;
	vector<string> availableDays;
	vector<string> courses;

};

struct AssignedTeacher{
	Teacher teacher;
	int timePeriodIndex;
	bool initialized = false;
};


struct Course{
	string name;
	vector<string> scheduledDays;
	vector<int> scheduledTimes; // this hold the index of time periods
	
	vector<AssignedTeacher> teachers = vector<AssignedTeacher>(NUM_CLASSES);

	
};



bool isWithinTimePeriod(const string& start_time1, const string& end_time1, 
                        const string& start_time2, const string& end_time2) {
							
    // Convert start time and end time strings to minutes since midnight
    int start1 = stoi(start_time1.substr(0, 2)) * 60 + stoi(start_time1.substr(3));
    int end1 = stoi(end_time1.substr(0, 2)) * 60 + stoi(end_time1.substr(3));
    int start2 = stoi(start_time2.substr(0, 2)) * 60 + stoi(start_time2.substr(3));
    int end2 = stoi(end_time2.substr(0, 2)) * 60 + stoi(end_time2.substr(3));
    
    // Check if first time period is completely within the second time period
    return start1 >= start2 && end1 <= end2;
}


vector<int> getAvailableTimes(string startTime, string endTime){
	vector<int> legitTimes;
	for(int i = 0; i < START_TIMES.size(); i++){
		if(isWithinTimePeriod(START_TIMES[i],END_TIMES[i],startTime,endTime)){
			legitTimes.push_back(i);
			
		}
	}
	return legitTimes;
}

bool isIntInVector(const vector<int>& vec, int item) {
    return find(vec.begin(), vec.end(), item) != vec.end();
}

bool isStringInVector(const vector<string>& vec, string item) {
    return find(vec.begin(), vec.end(), item) != vec.end();
}

bool isTeacherAvailable(Course course , vector<Course> setCourses, Teacher teacher, string day, int timePeriod){
		// if day is not in available days
		if(!isStringInVector(teacher.availableDays, day) ) return false;
		
		//if course is not in courses
		if(!isStringInVector(teacher.courses, course.name) )return false;
		
		//if teacher is busy in that time
		for(Course setCourse : setCourses){
			for(AssignedTeacher assignedTeacher : setCourse.teachers){
				if(assignedTeacher.teacher.name == teacher.name && assignedTeacher.timePeriodIndex == timePeriod) return false;
			}
		}
		//if cant teach on both days
		for(string courseDay : course.scheduledDays){
			if(find(teacher.availableDays.begin(), teacher.availableDays.end(), courseDay) == teacher.availableDays.end()) return false;
		}
		
		return true;
			
}

vector<Teacher> getAvailableTeachers(Course course , vector<Course> setCourses, vector<Teacher> teachers, string day, int timePeriod){
	vector<Teacher> availableTeachers;
	for(Teacher teacher : teachers){
		if(isTeacherAvailable(course,setCourses,teacher,day,timePeriod)){
			availableTeachers.push_back(teacher);
		}
	}
	return availableTeachers;
	
}

bool compareTeachers(const Teacher& t1, const Teacher& t2) {
    if (t1.availableDays.size() == t2.availableDays.size()) {
        return t1.name < t2.name;
    }
    return t1.availableDays.size() < t2.availableDays.size();
}

Teacher getTeacherWithLeastAvailableDays(const vector<Teacher>& teachers) {
    if (teachers.empty()) {
			cerr << "Error: empty vector of teachers\n";
        return {"", {},{}};
    }
    
    // Sort teachers by available days and name
    vector<Teacher> sortedTeachers = teachers;
    sort(sortedTeachers.begin(), sortedTeachers.end(), compareTeachers);
    
    // Return first teacher in sorted vector
    return sortedTeachers.front();
}

bool isCourseAvailable(Course course, vector<Course> setCourses, vector<Teacher> teachers, string day, int timePeriod){
	if(!isStringInVector(course.scheduledDays, day)) return false;
	
	if(!isIntInVector(course.scheduledTimes, timePeriod)) return false;
	
	if(getAvailableTeachers(course, setCourses, teachers, day, timePeriod).size() == 0) return false;
	
	return true;
}

vector<Course> getAvailableCourses(vector<Course> courses , vector<Course> setCourses, vector<Teacher> teachers, string day, int timePeriod){
	vector<Course> availableCourses;
	for(Course course: courses){
		if(isCourseAvailable(course, setCourses, teachers, day, timePeriod)){
			availableCourses.push_back(course);
		}
	}
	return availableCourses;
}

bool compareCourses(const Course& c1, const Course& c2) {
    return c1.name < c2.name;
}



Course getBestCourse(vector<Course> courses){
	if (courses.empty()) {
		cerr << "Error: empty vector of teachers\n";
        return {"", {},{}};
    }
    

    vector<Course> sortedCourses = courses;
    sort(sortedCourses.begin(), sortedCourses.end(), compareCourses);
    

    return sortedCourses.front();
}

vector<Course> assignTeacher(vector<Course> setCourses, Course course, Teacher teacher,int timePeriod,int classNum){
	vector<Course> outCourses = setCourses;
	
	for(int i = 0 ; i< outCourses.size(); i++ ){
		if(outCourses[i].name == course.name){
			if(outCourses[i].teachers[classNum].initialized == false){
				AssignedTeacher t;
				t.teacher = teacher;
				
				t.timePeriodIndex = timePeriod;
				t.initialized = true;
				outCourses[i].teachers[classNum] = t;
				

			}
		}
	}
	return outCourses;
}



vector<Course>  setCourseSchedule(vector<Course> courses, vector<Teacher> teachers ) {
	vector<Course> setCourses =  courses;
	for(int classNum = 0; classNum <NUM_CLASSES; classNum ++){
		for(string day : DAYS_OF_WEEK){
			for(int timePeriod =0; timePeriod <3; timePeriod++){
				vector<Course> availableCourses = getAvailableCourses(courses,setCourses,teachers,day,timePeriod);
				if(availableCourses.size() == 0) continue;
				
				Course bestCourse = getBestCourse(availableCourses);
				Teacher bestTeacher = getTeacherWithLeastAvailableDays(getAvailableTeachers(bestCourse,setCourses,teachers,day,timePeriod));
				
				setCourses = assignTeacher(setCourses, bestCourse, bestTeacher, timePeriod, classNum);
			
			}
		}
	}
	return setCourses;
	
        
}


vector<string> slice(vector<string> const &vec, int const start, int const end) {
    auto first = vec.begin() + start;
    auto last = vec.begin() + end;

    vector<string> newVec(first, last);

    return newVec;
}

vector<string> getWordsFromString() {
    string input;
    getline(cin, input);

    vector<string> words;
    stringstream ss(input);

    string word;
    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}

vector<Teacher> getTeachers(){
	int n;
	cin >> n;
	vector<Teacher> teachers;
	for(int i = 0;i<=n; i ++){
		vector<string> words = getWordsFromString();
        if (!words.empty()) {
			Teacher t;
			t.name = words[0];
			t.availableDays = slice(words,2, stoi(words[1]) + 2);
			t.courses = slice(words,stoi(words[1]) + 3,words.size());
			teachers.push_back(t);
		}		
	}
	return teachers;
}

vector<Course> getCourses(){
	int k;
	cin >> k;
	vector<Course> courses;
	for(int i = 0;i<=k; i ++){
		vector<string> words = getWordsFromString();
        if (!words.empty()) {
			Course c;
			c.name = words[0];
			c.scheduledDays = slice(words,1,2);
			c.scheduledTimes = getAvailableTimes(words[3], words[4]);
			
			//c.startTime = words[3];
			//c.endTime = words[4];
			courses.push_back(c);
		}		
	}
	return courses;	
}



void printSchedule(vector<Course> schedule){
	vector<Course> sortedSchedule = schedule;
    sort(sortedSchedule.begin(), sortedSchedule.end(), compareCourses);
    
	for(Course course : sortedSchedule){
		cout<<course.name<<endl;
		for(int i = 0;  i< NUM_CLASSES; i++){
			if(course.teachers[i].initialized == true){
				cout<<course.teachers[i].teacher.name<<": "<<START_TIMES[course.teachers[i].timePeriodIndex]<<" "<< END_TIMES[course.teachers[i].timePeriodIndex]<<endl;
			}
			else{
				cout<<"Not Found"<<endl;
			}
		}
	}
}

int main() {
	vector<Teacher> teachers = getTeachers();
	vector<Course> courses = getCourses();    
	vector<Course> setCourses = setCourseSchedule(courses,teachers);
	printSchedule(setCourses);
    return 0;
}
