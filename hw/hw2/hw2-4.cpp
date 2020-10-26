#include <iostream>
#include <string>

using namespace std;

void computeLPSArray(string needle, int M, int* lps); 
  
// Prints occurrences of txt[] in pat[] 
int strstrx(string needle, string haystack) 
{ 
    if (needle.size() == 0 || haystack.size() == 0 || haystack.size() < needle.size())
        return -1;
    
    int M = needle.size(); 
    int N = haystack.size(); 
    int lps[M]; 

    computeLPSArray(needle, M, lps); 
  
    int i = 0; // index for haystack 
    int j = 0; // index for needle 
    while (i < N) { 
        if (needle[j] == haystack[i]) { 
            j++; 
            i++; 
        }

        if (j == M) { 
            return (i-j);
        } 
        else if (i < N && needle[j] != haystack[i]) { 
            if (j != 0) j = lps[j - 1]; 
            else    i = i + 1; 
        } 
    } 
    return -1;
} 
  
// Fills lps[] for given patttern pat[0..M-1] 
void computeLPSArray(string needle, int M, int* lps) 
{ 
    int len = 0; 
    lps[0] = 0;
    int i = 1; 

    while (i < M) { 
        if (needle[i] == needle[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else { 
            if (len != 0)
                len = lps[len - 1]; 
            else {
                // if len == 0 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
} 


int main(int argc, char* argv[]) {
    string needle, haystack;
    cout << "needle: ";
    getline(cin, needle);
    cout << "haystack: ";
    getline(cin, haystack);
    cout << strstrx(needle, haystack) << endl;



}