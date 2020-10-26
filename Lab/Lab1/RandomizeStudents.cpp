#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <list>

using namespace std;


int string_array_length(string* array)
{
    int i = 0;
    while (!array[i].empty())
        ++i;
    return i;
}

string* readFile(string fileName) {
    ifstream myfile;
    vector<string> studentsInFile;
    string line;
    myfile.open(fileName);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if(line.find("Student#") != string::npos) {
                break;
            }
        }
        while (getline(myfile, line)) {
            if(line.find("Total: ") != string::npos)
                break;
            else {  
                size_t firstTab = line.find('\t');
                size_t comma = line.find(',', firstTab + 1);
                size_t firstName_end_pos = line.find('\t', comma + 2);
                string lastName = line.substr(firstTab + 1, comma - (firstTab + 1));
                string firstName = line.substr(comma + 2, firstName_end_pos - (comma + 2));
                studentsInFile.push_back(firstName + " " + lastName);
            }
        }
    }
    myfile.close();
    string* result = new string[studentsInFile.size()];
    for (int i=0; i<studentsInFile.size()-1; i++) {
        result[i] = studentsInFile[i];
    }
    return result;
}

int getGroupSize() {
    int groupSize;
    cout << "group size: ";
    cin >> groupSize;
    return groupSize;
}

string* getAbsentStudents() {
    string absentees_input;
    cout << "absent students: ";
    cin.ignore();
    getline(cin, absentees_input);
    vector<string> result;
    stringstream ss(absentees_input);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        result.push_back(substr);
    }
    string* absentees = new string[result.size()];
    for (int i=0; i<result.size(); i++) {
        absentees[i] = result[i];
    }
    cout << endl;
    return absentees;
}

string* getPresentStudentNames(string* studentsInFile, string* absentStudents) {
    string* result = new string[string_array_length(studentsInFile) - string_array_length(absentStudents)];
    int count = 0;
    bool tmp ;
    for (int i=0; i<string_array_length(studentsInFile); i++) {
        tmp = true;
        for (int j=0; j<string_array_length(absentStudents); j++) {
            if (studentsInFile[i] == absentStudents[j])
                tmp = false;
        }
        if (tmp) {
            result[count] = studentsInFile[i];
            count ++;
        }
    }
    return result;
}

vector<int> generateShuffledGroupNumbers(int groupSize, int numberOfStudents) {
    vector<int> numbers;
    int size = numberOfStudents / groupSize;
    int groupNum = 1;
    int currentNum = 1;

    for (int i = 0; i < size * groupSize; i++){
        numbers.push_back(groupNum); 
        currentNum += 1;
        if (currentNum > size) {
            groupNum += 1;
            currentNum = 1; 
        }
    }
    for (int i = 1; i <= numberOfStudents - size * groupSize; i++) {
        numbers.push_back(i); 
    }
    random_shuffle (numbers.begin(), numbers.end());
    return numbers;
}

map< int, list <string> > getGroups(string* studentNames, vector<int> groupNumbers) { 
    // Map<Integer, List<String>> groups = new HashMap<>();
    map<int, list<string> > groups;
    for (int i = 0; i < groupNumbers.size(); i++) {
        int groupNum = groupNumbers[i];
        string studentName = studentNames[i];
        if(groups.find(groupNum) != groups.end()) {
            list<string> tmp = groups.find(groupNum)->second;
            tmp.push_back(studentName);
            groups[groupNum] = tmp;
        }
        else {
            list<string> tmp;
            tmp.push_back(studentName);
            groups[groupNum] = tmp;
        }
    }
    return groups;
}

void printGroups(int groupSize, map<int, list<string> > groups) {
    for (int i=1; i<=groupSize; i++) {
        list<string> tmp = groups.find(i)->second;
        cout << "Group" << i << ":" << endl;
        for (auto v : tmp)
            cout << v << "\n";
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    //string fileName = argv[1];
    string fileName = argv[1];

    // read file
    string* studentsInFile = readFile(fileName);

    // get group size and absent students names
    int groupSize = getGroupSize();
    string* absentStudents = getAbsentStudents();
    
    // process the .txt file, delete absent ones and get the students names.
    string* studentNames = getPresentStudentNames(studentsInFile, absentStudents);


    // shuffle group numbers
    vector<int> groupNumbers = generateShuffledGroupNumbers(groupSize, string_array_length(studentNames));

    // mapping
    map<int, list<string> > groups = getGroups(studentNames, groupNumbers);
    
    // print out the groups
    printGroups(groupSize, groups);

    return 0;
}