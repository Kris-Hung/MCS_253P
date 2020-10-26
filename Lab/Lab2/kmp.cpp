#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


vector<string> getPrefix(string pattern, int idx) {
	vector<string> res;
	for (int i = idx; i >= 0; i--) {
		res.push_back(pattern.substr(0, i));
	}
	return res;
}

vector<string> getSuffix(string pattern, int idx) {
	vector<string> res(1, "");
	for (int i = 0; i < idx; i++) {
		res.push_back(pattern.substr(idx - i, i + 1));
	}
	return res;
}

vector<int> getLps(string pattern) {
	vector<int> lps; 
	vector<string> prefix, suffix;
	for (int i = 0; i < (int) pattern.length(); i++) {
		prefix = getPrefix(pattern, i);
		suffix = getSuffix(pattern, i);
		for (string p: prefix) {
			if (find(suffix.begin(), suffix.end(), p) != suffix.end()) {
				lps.push_back(p.size());
				break;
			}
		}
	}
	return lps;
}

bool isSubStr(string needle, string haystack) {
	if (needle.length() == 0 
		|| haystack.length() == 0 
		|| needle.length() >= haystack.length()) { return false; }

	vector<int> lps = getLps(needle);
	int needleSize = (int) needle.length(), haystackSize = (int) haystack.length();

	int i = 0, j = 0;
	while (i < haystackSize) {
		if (haystack[i] == needle[j]) {
			i++;
			j++;
		} else {
			if (j > 0) { j = lps[j - 1]; }
			else { i++; }
		}

		if (j == needleSize) {
			return true;
			j = lps[j - 1];
		}
	}
	return false;
}



void contain(vector<string> & input) {
	int inputSize = input.size();
	cout << "----------------" << endl;
	for(int i =0; i < inputSize; i++) {
		cout << input.at(i) << ": ";
		for (int j = 0; j < inputSize; j++) {
			if (isSubStr(input.at(i), input[j])) {
				cout << input[j] << ", ";
			}
		}
		cout << endl;
	}
}


int main(int argc, char const *argv[]){
	if (argc != 2) {
		cout << "Need a input to represent the number of input strings." << endl;
		return 0;
	}
	vector<string> input;
	string str;
	cout << "Input your strings: " << endl;
	for (int i = 0; i < stoi(argv[1]); i++) {
		getline(cin, str);
		input.push_back(str);
	}
	contain(input);
	return 0;
}