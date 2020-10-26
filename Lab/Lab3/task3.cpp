#include<iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>

using namespace std;


void pop_string(map<int, vector<string> >& level_strings, string&  word, int level) {
	if (word != "") {
		level_strings[level].push_back(word);
		word = "";
	}
}

void print_result(map<int, vector<string> >& level_strings) {
	for (int i = 0; i < level_strings.size(); i++) {
		vector<string> tmp = level_strings[i];
		if (tmp.size() != 0) {
			cout << "|";
			for (int space_number=0; space_number<2*i; space_number++)
				cout << " ";
			for(int j=0; j<tmp.size(); j++)
				cout << tmp[j] << " ";
        	cout << endl;
		}
    }
}

void parse_string(string s) {
	stack<char> S;
	map<int, vector<string> > list;
	int level = 0;
	string word = "";
	
	for (auto c : s) {
		switch ( c ) {
			case '(': S.push(')'); pop_string(list, word, level); level++; break;
			case '[': S.push(']'); pop_string(list, word, level); level++; break;
			case '{': S.push('}'); pop_string(list, word, level); level++; break;
			case ')':case ']': case '}':
				if (S.empty() || S.top() != c ) {
					cout << "|mismatched groups!" << endl;
					return;
				}
				else pop_string(list, word, level); level--; S.pop(); break;
			case ' ': case '\t': break;	
			default: word += c;
		}
	}
	pop_string(list, word, level);
	if (S.empty()) print_result(list);
	else cout << "|mismatched groups!" << endl;
}

int main() {
	string s;
	cout << "Please input the text" << endl;
	cin >> s;
	parse_string(s);
}