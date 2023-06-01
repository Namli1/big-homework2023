#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
#include "../models/classes.h"
#include "../global/global.h"

#include "helpers.h"


//Check if input is an integer
bool isInteger(string str, bool withFeedback) {
    for (int i = 0; i < str.length(); i++)
    //isDigit checks wether string is from '0' to '9'
    if (isdigit(str[i]) == false) {
        if(withFeedback) {
            cout << i18n.gettext("Please input a positive integer value: ");
        }
        return false;
    }
    return true;
}

//Request that input is an integer (if input is not an integer, it will prompt user to enter again)
int requestInteger(string& input) {
    while(!isInteger(input)) {
        getline(cin, input);
        //cin >> input;
    }
    return stoi(input);
}

//Verify that number is in a certain range
bool verify(int choice, int lowestOption, int highestOption) {
    //Check if in range:
    if (choice < lowestOption || choice > highestOption) {
        cout << "Number out of range! Please pick another option: ";
        return false;
    } else {
        return true;
    }
}

//same as above but using char inputs rather than int, allowing for Y/N answering, more convenient for users
bool verifyChar(char input, char a, char b, bool ignoreCaps) 
{
    if(ignoreCaps) {
        return (tolower(input)==a||tolower(input)==b||toupper(input)==a||toupper(input)==b);
    }
    if(input==a||input==b) return true;
    else return false;
}

//Asking user if what he entered is correct, feedback in form of y/n or Y/N
bool isThisCorrect(string message) {
    cout << message;
    char character;
    cin>>character;
    while(!verifyChar(character, 'Y', 'N')) {
        cin >> character;
    }
    if (character=='Y' || character=='y') {
        return true;
    } else {
        return false;
    }
}

//Formating minutes to a string
string formatMinutes(int minutes) {
    //If we only have 0-9, add another 0 in front (so it's 15:00 instead of 15:0)
    if(minutes < 10) {
        return "0" + to_string(minutes);
    } else {
        return to_string(minutes);
    }
}

//Removing whitespaces in string
string removeWhiteSpaces(string input) {
    // loop over every character and remove whitespaces
    std::string result;
    for (char ch : input) {
        if (!std::isspace(ch)) {
            result += ch;
        }
    }
    return result;
}

//Checking if file content is empty
bool file_is_empty(ifstream& pFile) {
    return pFile.peek() == ifstream::traits_type::eof();
}