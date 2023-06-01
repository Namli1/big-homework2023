#include <iostream>
#include <cstring>
#include <cmath>
#include <map>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;
#include "src/i18n/i18n.h"
#include "src/global/global.h"
#include "src/helpers/helpers.h"
#include "src/filter/filter.h"
#include "src/data/canteens.h"
#include "src/io/console.h"
#include "src/io/menus.h"

//Console libraries
#ifdef _WIN32
#include <cstdlib>
#endif

// bool isInteger(string str) {
//     for (int i = 0; i < str.length(); i++)
//     if (isdigit(str[i]) == false) {
//         cout << i18n.gettext("Please input a positive integer value") << endl;
//         return false;
//     }
//     return true;
// }

// bool verify(int choice, int lowestOption, int highestOption) {
//     //TODO: 
//     //Check if integer:
//     if (choice < lowestOption || choice > highestOption) {
//         cout << "Number out of range! Please pick another option: ";
//         return false;
//     } else {
//         return true;
//     }
// }

// inline void displayMainMenu() {
//     cout << "Main Menu" << endl;
//     cout << "1 - Search canteens" << endl;
//     cout << "2 - Canteen Filter" << endl;
//     cout << "3 - What is the closest canteen?" << endl;
//     cout << "4 - Canteen recommendation" << endl;
//     cout << "5 - My canteens" << endl;
//     cout << "6 - Language/语言" << endl;
//     cout << i18n.gettext("Please choose: ");
// }

// void mainMenu() {
//     string input;
//     displayMainMenu();
//     cin >> input;
//     //Make sure is integer:
//     while(!isInteger(input)) {
//         cin >> input;
//     }
//     unsigned int choice = stoi(input);
//     while(!verify(choice, 1, 6)) {
//         //User inputted number out of range
//         cin >> choice;
//     }
//     //Clear console:
//     clearConsole();
//     switch(choice) {
//         case 2:
//             filterMenu();
//         case 6:
//             i18nMenu();
//     }
//     // cout << "Pick some other option now (test): " << endl;
//     // cin >> choice2;
// }

void testI18N();

int main() {
    changeColor();
    cout << i18n.gettext("Welcome to the Tsinghua Canteen Exploration Program") << endl;
    //cout << canteens[0] << endl;
    mainMenu();
    //filterMenu();
    //testI18N();
    return 0;
}


void testI18N() {
    // Call the gettext() method to translate a text string
    string translated_first = i18n.gettext("Hello, world!");
    cout << "Translated text: " << translated_first << endl;

    // Change the locale to "fr" and translate again
    //char locale[3] = "de";
    //i18n = I18N(locale);
    i18n.changeLocale((char*)"zh");
    vector<string> replacements = {"Ben", "Paris"};
    string translated = i18n.gettext("person %s in %s", 10, replacements);
    cout << "Translated text: " << 10 << translated << endl;

    //Date Format test
    unsigned short year = 2023;
    unsigned short month = 5;
    unsigned short day = 15;
    string defaultFormat = "default";
    i18n.changeLocale((char*)"zh");
    //TODO: This gives me an illegal hardware instruction error
    cout << i18n.getFormattedDate(year, month, day, defaultFormat) << endl;

    // Call the getCurrency() method to format a currency amount
    string currency = i18n.getCurrency(1234, "EUR");
    cout << "Formatted currency: " << currency << endl;
}