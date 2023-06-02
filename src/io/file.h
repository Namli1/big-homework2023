#ifndef FILE_H
#define FILE_H

#include <iostream>

using namespace std;

bool verifyFileInput(string s, string filename);
int displayFile(string filename, string empty_message="Sorry, there is no data stored.");
string readFile(string filename);
int writeFile(string input, string filename, bool replace=false);
void clearFile(string filename);

#endif