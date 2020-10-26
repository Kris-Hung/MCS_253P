#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

using namespace std;

#define STRMAX 100
#define SONGMAX 1024

struct Song {
    string title;
    string artist;
    int year_published;
};

struct Song music_library[SONGMAX];
int current_number_of_songs = 0;
string fileName;
fstream myfile;
bool song_is_in_library;

void determine_library_name(int argc, char * argv[]);
void load_MusicLibrary(string fileName);
void read_command();
bool evaluate_command(char command_input);
void add_song_to_MusicLibrary();
int find_index_of_song_with_name(string title);
string change_letter_case_to_upper_case(string input);
void crunch_down_from_index(int i);
void print_MusicLibrary(bool x, int index);
void remove_song_from_MusicLibrary_by_name();
void crunch_up_from_index(int i);
void store_MusicLibrary(string fileName);
string check_for_other_songs_with_same_name(string input_title, int i);
void look_up_song_by_name();


void determine_library_name(int argc, char * argv[]) {
    // determine the name of the music library file
    string libraryName;
    
    if (argc == 1)
        libraryName = "myMusic"; // defalt name of music library if no input name
    else  {
        for (int i=1; i<argc; i++) {
                libraryName += argv[i];
            if (i != argc-1 )
                libraryName += " ";
        }
    }
    cout << "Music Library Name: " << libraryName << endl;
    fileName += libraryName;
    fileName += ".txt";
}

void load_MusicLibrary(string fileName) {
    // load data from the file
    myfile.open (fileName, std::fstream::in | std::fstream::out);
    string line;
    int i=0;
    if (myfile.is_open()) { // if file exists
        while (getline(myfile, line)) {
            vector<string> result;
            stringstream ss(line);
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                result.push_back(substr);
            }
            music_library[i].title = result[0];
            music_library[i].artist = result[1];
            music_library[i].year_published = stoi(result[2]);
            i++;
            current_number_of_songs ++;
        }
        myfile.close();
    }
    else { // if file doesn't exist then create a new one
        myfile.open(fileName, fstream::in | fstream::out | fstream::trunc);
        myfile.close();
    }
}

void read_command() {
    char command_input;
    while (cin >> command_input) {
        if (!evaluate_command(command_input))
            break;
    }
}

bool evaluate_command(char command_input) {
    if (command_input == 'Q' || command_input == 'q') {
        return false;
    }
    else if (command_input == 'I' || command_input == 'i') {
        add_song_to_MusicLibrary();
        return true;
    }
    else if (command_input == 'P' || command_input == 'p') {
        print_MusicLibrary(true, 0);
        return true;
    }
    else if (command_input == 'D' || command_input == 'd') {
        remove_song_from_MusicLibrary_by_name();
        return true;
    }
    else if (command_input == 'L' || command_input == 'l') {
        look_up_song_by_name();
        return true;
    }
    else
        return true;
}

void add_song_to_MusicLibrary() {
    // check if the library is full.
    if (current_number_of_songs == SONGMAX) {
        cout << "You can't insert songs because this music library is full." << endl;
        return;
    }
    struct Song input_song;
    cin.ignore();
    cout << "Title: ";
    getline(cin, input_song.title);
    while (input_song.title.length() >= STRMAX) { // check if the input is valid
        cout << "Please enter a shorter title." << endl;
        cout << "Title: ";
        getline(cin, input_song.title);
    }
    cout << "Artist: ";
    getline(cin, input_song.artist);
    while (input_song.artist.length() >= STRMAX) { // check if the input is valid
        cout << "Please enter a shorter artist name." << endl;
        cout << "Artist: ";
        getline(cin, input_song.artist);
    }
    cout << "Year Published: ";
    cin >> input_song.year_published;
    int i;
    i = find_index_of_song_with_name(input_song.title);
    crunch_down_from_index(i);
    music_library[i] = input_song;
}

int find_index_of_song_with_name(string title) {
    if (current_number_of_songs == 0)
        return 0;
    // binary search
    string s1, s2;
    s1 = change_letter_case_to_upper_case(title);
    int index=0, mid;
    int l = 0, r = current_number_of_songs-1;

    while (l <= r ) {
        mid = l + (r-l) / 2;
        // cout << "mid = " << mid  << " music_library = " << music_library[mid].title << endl;
        s2 = change_letter_case_to_upper_case(music_library[mid].title);
        int s = s1.compare(s2);
        if (s == 0) {
            s = title.compare(music_library[mid].title);
            if (s == 0) {
                index = mid;
                song_is_in_library = true;
                break;
            }
        }
        if (s > 0) {
            l = mid + 1;
            index = l;
        }
        else
            r = mid -1;
    }
    if (l > r)
        song_is_in_library = false;
    return index;
}

string change_letter_case_to_upper_case(string input) {
    string s;
    int input_length = input.length();
    for (int i=0; i<input_length; i++)
        s += toupper(input[i]);
    return s;
}

void crunch_down_from_index(int i) {
    current_number_of_songs += 1;
    for (int j=current_number_of_songs-1; j>i; j--)
        music_library[j] = music_library[j-1];
}

void print_MusicLibrary(bool x, int index) {
    if (x) { // print with numbers
        for (int i=0; i<current_number_of_songs; i++) {
        cout << i+1 << " Title: " << music_library[i].title << ", Artist: " << music_library[i].artist << ", Year Published: " << music_library[i].year_published << endl;
        }
    }
    else {
        // for look-up printing, print without numbers
        cout << "Title: " << music_library[index].title << ", Artist: " << music_library[index].artist << ", Year Published: " << music_library[index].year_published << endl;
    }
}

void remove_song_from_MusicLibrary_by_name() {
    string input_title;
    cin.ignore();
    cout << "Title: ";
    getline(cin, input_title);
    int i;
    i = find_index_of_song_with_name(input_title);
    if (!song_is_in_library)
        return;
    crunch_up_from_index(i);
    // check for other songs w/ the same name
    i = find_index_of_song_with_name(input_title);
    while (song_is_in_library) {
        crunch_up_from_index(i);
        i = find_index_of_song_with_name(input_title);
    }
}

void crunch_up_from_index(int i) {
    for (int j=i; j<current_number_of_songs-1; j++)
        music_library[j] = music_library[j+1];
    current_number_of_songs -= 1;
}

void look_up_song_by_name() {
    string input_title;
    cin.ignore();
    cout << "Title: ";
    getline(cin, input_title);
    int i;
    i = find_index_of_song_with_name(input_title);
    if (!song_is_in_library)
        cout << "The song is not in the library." << endl;
    else { // check for other songs w/ the same name
        string index;
        index += check_for_other_songs_with_same_name(input_title, i);
        string start, end;
        start += index[0];
        end += index[1];
        for (int j=stoi(start); j<=stoi(end); j++)
            print_MusicLibrary(false, j);
    }
}

string check_for_other_songs_with_same_name(string input_title, int i) {
    int left = i, right = i;
    string res;
    // find the right most index
    while (input_title == music_library[right+1].title && right < current_number_of_songs)
        right += 1;
    // find the left most index
    for (int j=i; j>=0; j--) {
        if (input_title == music_library[j].title)
            left = j;
    }
    res += to_string(left);
    res += to_string(right);
    return res;
}

void store_MusicLibrary(string fileName) {
    // save library back to the file
    myfile.open (fileName, fstream::in | fstream::out | fstream::trunc);
    for (int i=0; i<current_number_of_songs; i++) {
        myfile << music_library[i].title << "," << music_library[i].artist << "," << music_library[i].year_published << endl;
    }
    myfile.close();
}


int main(int argc, char * argv[]) {
    // determine the name of the music library file by command line input
    determine_library_name(argc, argv);

    // load file
    load_MusicLibrary(fileName);

    // read commands
    read_command();
    
    // save file
    store_MusicLibrary(fileName);

    return 0;
}