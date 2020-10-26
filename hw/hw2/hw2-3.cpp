#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define MAX 256

bool compare(char arr1[], char arr2[]) {
    for (int i=0; i<MAX; i++) {
        if (arr1[i] != arr2[i])
            return false;
    }
    return true;
}

void printArray(vector<int> arr) {
    if (arr.size() == 0)
        cout << "-1" << endl;
    else {
        for (int i=0; i<arr.size(); i++)
            cout << arr[i] << ", ";
        cout << endl;
    }
}

void anagram(string needle, string haystack) {
    int m = needle.size(), n = haystack.size();
    vector<int> result;
    char countNeedle [MAX] = {0}, countCurWindow [MAX] = {0};
    for (int i=0; i<m; i++) {
        countNeedle[needle[i]]++;
        countCurWindow[haystack[i]]++;
    }
    for (int i=0; i<n-m; i++) {
        if (compare(countNeedle, countCurWindow))
            result.push_back(i);
        countCurWindow[haystack[i+m]] ++;
        countCurWindow[haystack[i]] --;

    }
    if (compare(countNeedle, countCurWindow))
        result.push_back(n-m);
    printArray(result);
}

int main(int argc, char* argv[]) {
    string needle, haystack;
    cout << "needle: ";
    getline(cin, needle);
    cout << "haystack: ";
    getline(cin, haystack);
    anagram(needle, haystack);
}