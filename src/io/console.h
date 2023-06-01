#ifndef CONSOLE_H //making sure multiple definitions don't occur in our main source file, preventing double declarations of things like static variables, types and enums
#define CONSOLE_H
#include <iostream>
using namespace std;

//declarations of all the functions defined in the source file
void clearConsole();

void changeColor(string color="color 5E");

void centrify_output(string str, int num_cols);

void printspace(int n);

#endif
