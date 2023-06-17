#include <iostream>
#include <vector>
using namespace std;

int countPaths(int x, int y, int n) {
    if (x == n-1 && y == n-1) { // base case: reached opposite corner
        return 1;
    } else if (x >= n || y >= n || x > y) { // invalid path (crossed diagonal)
        return 0;
    } else { // recursive case: go down or right
        return countPaths(x+1, y, n) + countPaths(x, y+1, n);
    }
}

int main() {
    int n; // size of the square
    cin >> n;
    int numPaths = countPaths(0, 0, n + 1);// this passes nubet of edges in each side
    cout << numPaths << endl;

    return 0;
}
