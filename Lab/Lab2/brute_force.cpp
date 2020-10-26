#include <iostream>
#include <vector>
#include <string>
using namespace std;


bool isSubStr(string s1, string s2) { 
	if (s1 == s2) { return false; }
	signed int size1 = s1.size(), size2 = s2.size();
	for (int i = 0; i < size2 - size1; i++) {
		if (s1 == s2.substr(i, s1.size())) {
			return true;
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