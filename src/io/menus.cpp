#include "menus.h"

#include <iostream>
#include <iomanip>
#include "console.h"
#include "../global/global.h"
#include "../models/classes.h"
#include "../helpers/helpers.h"
#include "../proximity/proximity.h"
#include "../data/canteens.h"
#include "../filter/filter.h"
#include "file.h"

using namespace std;

void listCanteens();
void listBuildings();

inline void displayMainMenu() { //initial main menu display, using the centrify function to format it
    centrify_output(i18n.gettext("**** Main Menu ****"),num_cols);
    printspace(3);
    centrify_output(i18n.gettext("1 - List Canteens"),num_cols);
    printspace(3);
    centrify_output(i18n.gettext("2 - Canteen Filter"),num_cols);
    printspace(3);
    centrify_output(i18n.gettext("3 - What is the Closest Canteen?"),num_cols);
    printspace(3);
    centrify_output(i18n.gettext("4 - Canteen Recommendation"),num_cols);
    printspace(3);
    centrify_output(i18n.gettext("5 - My Canteens"),num_cols);
    printspace(3);
    centrify_output(i18n.gettext("6 - Language/语言"),num_cols);
    printspace(3);
    centrify_output(i18n.gettext("7 - Clear Cache"),num_cols);
    printspace(4);
    centrify_output(i18n.gettext("Please choose: "),num_cols);
}

void displayLocationSelectionMenu() //Once you enter the location section of the menu, you can choose between the two different functions
{
    cout<<"To Find Nearest Canteen to you, Press 1"<<"\n";
    cout<<"To Find the Distance Between you and a Destination Canteen, Press 2"<<endl;
    int m;
    cin>>m;
    while(!verify(m, 1, 2)) {
        cin >> m;
    }
    switch(m){
        case 1:
            clearConsole();
            displayNearestMenu();
            break;
        case 2:
            clearConsole();
            displayLocationMenu();
            break;
    }
}

void displayNearestMenu() //a function to lead the user through the process of confirming their current location, and then outputting the nearest canteen based on the distance function
{
    cout<<"Please select your current location: "<<endl;
    listBuildings();
    int n;
    Building temp;
    Building temp2;
    cin>>n;
    while(!verify(n, 1, 5)) { //verifying input, this type of utilization appears a lot in our code as the user has to input confirmation commands frequently
        cin >> n;
    }
    temp = buildings[n-1]; //Getting the canteen from the buildings array defined in data/canteens.cpp //needs buildings[n-1] as array starts from [0]

    clearConsole();
    cout<<"Your Selected Current Location is: "<<temp.getName()<<"\n";
    while(!isThisCorrect()) //if the selection was incorrect, user has an option to re-select the location
    {
        clearConsole();
        cout<<"Please re-select your current location: "<<endl;
        listBuildings();
        cin>>n;
        while(!verify(n, 1, 5)) {
                cin >> n;
            }
        temp = buildings[n-1];

        clearConsole();
        cout<<"Your Selected Current Location is: "<<temp.getName()<<"\n";
    }
    clearConsole();
    cout<<"The Nearest Canteen to your current location ("<<temp.getName()<<") is "<<nearestCanteenName(temp)<<", "<<setprecision(3)<<nearestCanteen(temp)<<"m away"<<endl;
    cout<<"Would you like to save this Canteen to your favourites? Y/N"<<endl; //using file writing, the user can save their favourite canteens to a text file which can then be read using a different function in the menu
    char character;
    cin>>character;
    while(!verifyChar(character, 'Y', 'N')) {
            cin >> character;
        }
    if (character=='Y')
    {

    if(verifyFileInput(nearestCanteenObject(temp).getName(), "canteen_favourite.txt"))
    {
        clearConsole();
        nearestCanteenObject(temp).favourite(); //this utilizes the object return type nearest canteen function, allowing the user to save the nearest canteen to their favourites for future reference
        clearConsole();
        cout<<"Canteen has been successfully saved to favourites!"<<endl;

    }
     else
     {
         clearConsole();
         cout<<"Canteen already saved to favourites"<<endl;
    }
    }
    else
    {
        clearConsole();
    }
}


void displayLocationMenu() //similar to nearest canteen function, however this gives the distance between 2 user selected locations.
{
    cout<<"Please select your current location: "<<endl;
    listBuildings();
    int n;
    Building temp;
    Building temp2;
    cin>>n;
    while(!verify(n, 1, 5)) { //Verifying input is in range
        cin >> n;
    }
    temp = buildings[n-1];
    clearConsole();
    cout<<"Your Selected Current Location is: "<<temp.getName()<<"\n";
    while(!isThisCorrect())
    {
        clearConsole();
        cout<<"Please re-select your current location: "<<endl;
        listBuildings();
        cin>>n;
        while(!verify(n, 1, 5)) {
            cin >> n;
        }
        temp = buildings[n-1];
        clearConsole();
        cout<<"Your Selected Current Location is: "<<temp.getName()<<"\n";
        //Now it starts again to check if it is correct (goes back to beginning of while loop)
    }
    clearConsole();
    cout<<"Please Select Destination Canteen: "<<"\n";
    listCanteens();
    int j;
    cin>>j;
    while(!verify(j, 1, 4)) {
        cin >> j;
    }
    temp2 = buildings[j-1];
    clearConsole();
    cout<<"Your Selected Destination is: "<<temp2.getName()<<"\n";
    
    while(!isThisCorrect())
    {
        clearConsole();
        cout<<"Please re-select your destination: "<<endl;
        listCanteens();
        int n;
        cin>>n;
        while(!verify(n, 1, 4)) {
            cin >> n;
        }
        temp2 = buildings[n-1];
        clearConsole();
        cout<<"Your Selected Destination is: "<<temp2.getName()<<"\n";
        //Now it starts again to check if it is correct (goes back to beginning of while loop)
    }
    clearConsole();
    float distance1;
    distance1=Calculate_Distance(temp, temp2); //This also allows for customised input allowing for flexible distance calculation function
    cout<<"Distance between "<<temp.getName()<<" and "<<temp2.getName()<<": "<<setprecision(3)<<distance1<<"m"<<endl;
}

void displayFavouriteMenu() //reading text file with saved canteens, and then outputting the information into a list format
{
    cout<<"Your Favourite Canteens: "<<endl;
    printspace(1);
    displayFile("canteen_favourite.txt");
}

void listCanteens() //We have a function in our menu to view all canteens, this allows us to output the name values of a list of canteens.
{
    for (size_t i = 0; i < canteen_count; ++i) {
        Canteen it = canteens[i];
        cout<<" "<< i+1 << " - " << it.getName()<<"\n"<<"\n";
    }
    cout<<endl;
}

void listBuildings() //We have a function in our menu to view all canteens, this allows us to output the name values of a list of canteens.
{
    for (size_t i = 0; i < buildings_count; ++i) {
        Building it = buildings[i];
        cout<<" "<< i+1 << " - " << it.getName()<<"\n"<<"\n";
    }
    cout<<endl;
}

void displayCanteens() //Outputting a list of all canteens on our database
{
    cout<<"Please find below a list of all canteens available on campus: "<<endl;
    cout<<"\n";
    listCanteens();
    cout << "Enter number for detail view: ";
    string choiceStr;
    getline(cin, choiceStr);
    int choice = requestInteger(choiceStr);
    while(!verify(choice, 1, canteen_count)) {
        cout << "Number out of range! Please re-enter: " << endl;
        getline(cin, choiceStr);
        choice = requestInteger(choiceStr);
    }
    clearConsole();
    canteens[choice-1].display_information();
}

void mainMenu() { //acting as a intermediate between user input on the menu and the implemented function
    string choiceStr;
    unsigned int choice1;
    displayMainMenu();
    getline(cin >> ws, choiceStr); 
    choice1 = requestInteger(choiceStr);
    //cin >> choice1;
    while(!verify(choice1, 1, 6)) {
        cin >> choice1;
    }
    clearConsole();
    switch(choice1)
     {
    case 1:
        displayCanteens();
        break;
    case 2:
        filterMenu();
        break;
    case 3:
       displayLocationSelectionMenu();
       break;
    case 4:
        displayFavouriteMenu();
        break;
    case 5:
        i18nMenu();
        break;
    case 6:
        clearFile("canteen_favourite.txt");
        break;
    }
    cout << "Press 0 to return to main menu: " << endl;
    int b;
    cin>>b;
    if(b==0)
    {
        clearConsole();
        mainMenu();
    }
}

void i18nMenu() {
    cout << "Language Selection:" << endl;
    cout << "1 - English" << endl;
    cout << "2 - 中文" << endl;
    cout << "3 - Deutsch" << endl;
    cout << i18n.gettext("Please choose: ");
    string input;
    cin >> input;
    int choice = requestInteger(input);
    switch(choice) {
        case 1:
            i18n.changeLocale((char*)"en");
            break;
        case 2:
            i18n.changeLocale((char*)"zh");
            break;
        case 3:
            i18n.changeLocale((char*)"de");
            break;
    }
    clearConsole();
    cout << i18n.gettext("Success! Switched language.") << endl;
    mainMenu();
}


