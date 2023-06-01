#include "file.h"

#include <fstream>
#include <cstdio>
#include <iomanip>

using namespace std;

#include "../models/classes.h"
#include "../helpers/helpers.h"
#include "console.h"

bool verifyFileInput(string s, string filename) {
    ifstream file_obj2;
    file_obj2.open(filename, ios::in); //"canteen_favourite.txt"
    string tempname2;
    while(getline(file_obj2,tempname2))
    {
        if(tempname2==s) return false;
    }
        file_obj2.close();
        return true;
}

string readFile(string filename) {
    ifstream file_obj2;
    file_obj2.open(filename,ios::in);

    if(file_is_empty(file_obj2)) {
        return "";
    }

    string result;
    string tempname;
    while(getline(file_obj2,tempname)) {
        result.append(tempname);
    }
    file_obj2.close();
    return result;
}

int displayFile(string filename, string empty_message) {
    ifstream file_obj2;
    file_obj2.open(filename,ios::in);

    //Check if file is empty:
    if(file_is_empty(file_obj2)) {
        cout << empty_message << endl;
        return 1;
    }
    //Otherwise, just continue
    string tempname2;
    while(getline(file_obj2,tempname2))
    {
        if(tempname2.empty()) { //If the file is empty, output message
            cout << empty_message << endl;
        } else {
            cout<<tempname2<<endl;
        }
        
        printspace(1);
    }
    file_obj2.close();
    return 0;
}

int writeFile(string input, string filename, bool replace) {
    ofstream file_obj;
    if(replace) {
        file_obj.open(filename,ios::trunc); //Replacing file content
    } else {
        file_obj.open(filename,ios::app); //using ios::append mode allows new information to be appended to the end of the text file, allowing for new user input in the same file over time
    }
    if(verifyFileInput(input, filename)) {
        file_obj << input << endl;
    }
    file_obj.close();
   return 0;
}

void clearFile(string filename) //deletes file containing favourite canteens, equivalent to clearing the favourite canteen information
{
    remove(filename.c_str()); //Have to convert string to const char*, otherwise function doesnt work
    cout<<"Cache Cleared Successfully!"<<endl;
}
