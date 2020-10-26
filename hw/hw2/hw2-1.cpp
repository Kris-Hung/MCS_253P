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

int main(int argc, char* argv[]) {
    string needle, haystack;
    cout << "needle: ";
    getline(cin, needle);
    cout << "haystack: ";
    getline(cin, haystack);
    cout << strstr(needle, haystack) << endl;



}