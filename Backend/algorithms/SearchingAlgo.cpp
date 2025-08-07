#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

void emitStep(const vector<int>& arr, const string& message, int left, int right, int mid) {
    stringstream ss;
    ss << R"({"array":[)";
    for (int i = 0; i < arr.size(); ++i) {
        ss << arr[i];
        if (i != arr.size() - 1) ss << ",";
    }
    ss << R"(],"message":")" << message << R"(","left":)" << left << R"(,"right":)" << right << R"(,"mid":)" << mid << "}";
    cout << ss.str() << endl;
    cout.flush();
}

int binarySearch(const vector<int>& arr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        emitStep(arr, "Checking middle element", left, right, mid);

        if (arr[mid] == target) {
            emitStep(arr, "Target found", left, right, mid);
            return mid;
        }
        else if (arr[mid] < target) {
            emitStep(arr, "Target is greater than middle element, searching right half", left, right, mid);
            left = mid + 1;
        }
        else {
            emitStep(arr, "Target is less than middle element, searching left half", left, right, mid);
            right = mid - 1;
        }
    }
    emitStep(arr, "Target not found", left, right, -1);
    return -1;
}

int main(int argc, char* argv[]) {
    int n, target;
    vector<int> arr;

    if (argc > 2) {
        n = stoi(argv[1]);
        target = stoi(argv[2]);
        arr.resize(n);
        for (int i = 0; i < n; ++i) arr[i] = i * 2;  // Example sorted array: even numbers
    } else {
        cin >> n >> target;
        arr.resize(n);
        for (int i = 0; i < n; ++i) cin >> arr[i];
    }

    if (n < 1) {
        cout << R"({"error":"Invalid array size"})" << endl;
        return 1;
    }

    emitStep(arr, "Starting binary search", 0, n - 1, -1);
    int index = binarySearch(arr, 0, n - 1, target);

    if (index != -1) {
        cout << R"({"result":"Target found at index )" << index << "\"}" << endl;
    } else {
        cout << R"({"result":"Target not found"})" << endl;
    }

    cout << R"({"action":"final"})" << endl;
    cout.flush();
    return 0;
}
