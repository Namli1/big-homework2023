#include <iostream>
#include <cstring>
#include <cmath>
#include <map>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;
#include "i18n/i18n.h"

//Console libraries
#ifdef _WIN32
#include <cstdlib>
#endif


bool verify(int choice, int lowestOption, int highestOption) {
    if (choice < lowestOption || choice > highestOption) {
        cout << "Number out of range! Please pick another option: ";
        return false;
    } else {
        return true;
    }
}

void displayMainMenu() {
    cout << "Main Menu" << endl;
    cout << "1 - Search canteens" << endl;
    cout << "2 - Canteen Filter" << endl;
    cout << "3 - What is the closest canteen?" << endl;
    cout << "4 - Canteen recommendation" << endl;
    cout << "5 - My canteens" << endl;
    cout << "6 - Language/语言" << endl;
    cout << "Please choose: ";
}

void clearConsole() {
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

void mainMenu() {
    unsigned int choice1;
    unsigned int choice2;
    displayMainMenu();
    cin >> choice1;
    while(!verify(choice1, 1, 6)) {
        //User inputted number out of range
        cin >> choice1;
    }
    //Clear console:
    clearConsole();
    switch(choice1) {
            
    }
    cout << "Pick some other option now (test): " << endl;
    cin >> choice2;
}

int main() {
    cout << "Welcome to the Tsinghua Canteen Exploration Program" << endl;
    mainMenu();
    return 0;
}



void testI18N() {
    // Create an instance of the I18N class with the "de" locale
    I18N i18n;

    // Call the gettext() method to translate a text string
    string translated_first = i18n.gettext("Hello, world!");
    cout << "Translated text: " << translated_first << endl;

    // Change the locale to "fr" and translate again
    //char locale[3] = "de";
    //i18n = I18N(locale);
    i18n.changeLocale("zh");
    vector<string> replacements = {"Alice", "Paris"};
    string translated = i18n.gettext("person %s in %s", 10, replacements);
    cout << "Translated text: " << 10 << translated << endl;

    //Date Format test
    unsigned short year = 2023;
    unsigned short month = 5;
    unsigned short day = 15;
    string defaultFormat = "default";
    i18n.changeLocale("zh");
    //TODO: This gives me an illegal hardware instruction error
    cout << i18n.getFormattedDate(year, month, day, defaultFormat) << endl;
    // cout << "Formatted default date: " << formattedDefaultDate << endl;

    // Call the getCurrency() method to format a currency amount
    string currency = i18n.getCurrency(1234, "EUR");
    cout << "Formatted currency: " << currency << endl;
}