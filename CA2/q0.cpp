#include <iostream>
#include <string>
using namespace std;

void to_upper(string& str, int index = 0) {
    if (index == str.length()) {
        return;
    }
    str[index] = toupper(str[index]);
    to_upper(str, index + 1);
}

int main() {
	string line;
	while (getline(cin, line)) {
		to_upper(line);
		cout << line << endl;
	}
	return 0;
}
