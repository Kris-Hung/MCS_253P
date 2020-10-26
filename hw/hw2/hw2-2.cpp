#include <iostream>
#include <string>

using namespace std;

int strstr(string needle, string haystack) {
    if (needle.size() == 0 || haystack.size() == 0 || haystack.size() < needle.size())
        return -1;
    for (int i=0; i<haystack.size() - needle.size()+1; i++) {
        int idx_needle = 0, j = i;
        while (haystack[j] == needle[idx_needle]) {
            if (idx_needle == needle.size() -1)
                return i;
            idx_needle++;
            j++;
        }
    }
    return -1;
}

string my_substr(string s, int pos, int len) {
    string result;
    int idx = 0;
    for (int i=pos; i<pos + len; i++) {
        result += s[i];
        idx++;
    }
    return result;
}

int numOccurrences(string needle, string haystack) {
    int result = 0;
    int found = strstr(needle, haystack);
    while (found != -1) {
        result ++;
        if (found + needle.size() == haystack.size())
            break;
        haystack = my_substr(haystack, found + needle.size(), haystack.size() - found - 1);
        found = strstr(needle, haystack);
    }
    return result;
}

int main(int argc, char* argv[]) {
    string needle, haystack;
    cout << "needle: ";
    getline(cin, needle);
    cout << "haystack: ";
    getline(cin, haystack);
    cout << numOccurrences(needle, haystack) << endl;
}