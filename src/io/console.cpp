#include "console.h"

#include <array>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

//Console libraries
#ifdef _WIN32
#include <cstdlib>
#endif

const int num_cols = 100;

void centrify_output(string str, int num_cols) //function for centring the text output
{
    int padding_left = (num_cols / 2) - (str.size() / 2); //calculating the distance from the left
    for(int i = 0; i < padding_left; ++i) cout << " "; //adding spaces
    cout << str;
}

void changeColor(string color) {
    #ifdef _WIN32
       system(color.c_str());
    #endif
}

void printspace(int n) //function to make adding new lines more convenient
{
    for(int i=0;i<n;i++)
    {
        cout<<"\n";
    }
}

void clearConsole() { //very useful function for cleaning up console, improving user experience by making the console blank after completed input
    #ifdef _WIN32
    // windows-code:
    system("cls");
    #elif defined(__APPLE__)
    // macos-code:
    cout << "\033[2J\033[1;1H";
    #else
    // Code for other platforms
    // ...
    #endif
}
