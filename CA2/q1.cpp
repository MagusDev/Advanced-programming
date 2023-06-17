#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


void printArray(const vector<int>& arr, int size, int index = 0, int minmax = 1, int prev = 0) {
    if (index >= size - 1) {
        return;
    }
    cout << arr[index] << " ";
    int next_index ;
    if (minmax) {
        next_index = max(arr[index], prev);
    } else {
        next_index = min(arr[index], prev);
    }
    printArray(arr, size, index + next_index, !minmax, arr[index]);
}


int main() {
    int size;
    vector<int> arr;

    // Read the size of the array
    cin >> size;

    // Read the elements of the array
    for (int i = 0; i < size; i++) {
        int element;
        cin >> element;
        arr.push_back(element);
    }

    printArray(arr,size);

    return 0;
}
