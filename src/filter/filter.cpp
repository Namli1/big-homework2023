#include <iostream>
#include <cstring>
#include <cmath>
#include <map>
#include <array>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>
#include <regex>
using namespace std;

#include "../models/classes.h"
#include "../data/canteens.h"
//#include "../i18n/i18n.h"
//#include "../global/global.h"
#include "../helpers/helpers.h"
#include "../proximity/proximity.h"
#include "../helpers/magic_enum.hpp"

string getOpeningTime(string message="Please enter the desired opening time (ex: >21:00, 17:00-15:00, 14:00): ") {
    cout << message;
    string opening_times_string;
    getline(cin, opening_times_string);
    return opening_times_string;
}

short parseDateFormat(string input) {
    // for (char ch : input) {
    //     //Check if is integer
    //     if(!isInteger(str(1, ch))) {
    //         //Start again
    //         cout << "Invalid date format, please input again:" << endl;
    //         getOpeningTime();
    //     } else {

    //     }
    // }
    istringstream iss(input);
    string hourStr, minuteStr;
    getline(iss, hourStr, ':');
    getline(iss, minuteStr);

    //Check if is integer -> not needed, have regex
    // if(!isInteger(hourStr, false) || !isInteger(minuteStr, false)) {
    //     //Start again
    //     cout << "Invalid date format, please input again:" << endl;
    //     getOpeningTime();
    //     return -1; //Invalid date
    // }

    short hours = std::stoi(hourStr);
    short minutes = std::stoi(minuteStr);

    return hours * 60 + minutes;
}

OpenTime parseOpenTime(string input) {
    //Validation regex, also checks if max value is 23:59
    regex moreless_regex("^(>|<)(([0-1]?[0-9]|2[0-3]):[0-5][0-9])$");
    regex one_time("^(([0-1]?[0-9]|2[0-3]):[0-5][0-9])$");
    regex range_time("^(([0-1]?[0-9]|2[0-3]):[0-5][0-9])(?:-(([0-1]?[0-9]|2[0-3]):[0-5][0-9]))?$");
    
    //Matching the regex with the input (this is for <hh:mm or >hh:mm)
    if(regex_match(input, moreless_regex)) {
        if(input[0] == '>') {
                //Set only start time
                short startMinutes = parseDateFormat(input.substr(1)); //Parse string after first character (which is '>')
                return OpenTime(startMinutes, startMinutes);
        } else if(input[0] == '<') {
            //Set only end time
            short endMinutes = parseDateFormat(input.substr(1)); //Parse string after first character (which is '<')
            return OpenTime(endMinutes, endMinutes);
        }
    } //This regex is for hh:mm
    else if (regex_match(input, one_time)) {
        istringstream iss(input);
        string hourStr, minuteStr;
        getline(iss, hourStr, ':');
        getline(iss, minuteStr);
        short hour = std::stoi(hourStr);
        short minute = std::stoi(minuteStr);
        short minutes_past_midnight = hour * 60 + minute;
        return OpenTime(minutes_past_midnight, minutes_past_midnight);
    }
    //This regex is for hh:mm-hh:mm
    else if (regex_match(input, range_time)) {
        istringstream iss(input);
        string hourStr1, minuteStr1, hourStr2, minuteStr2;
        getline(iss, hourStr1, ':');
        getline(iss, minuteStr1, '-');
        getline(iss, hourStr2, ':');
        getline(iss, minuteStr2);
        short hour1 = std::stoi(hourStr1);
        short hour2 = std::stoi(hourStr2);
        short minute1 = std::stoi(minuteStr1);
        short minute2 = std::stoi(minuteStr2);
        short minutes1 = hour1 * 60 + minute1;
        short minutes2 = hour2 * 60 + minute2;
        return OpenTime(minutes1, minutes2);
    } else {
        //Invalid value, start again
        string input_date = getOpeningTime("The date you entered is invalid, please re-enter: ");
        //Calling parser again:
        return parseOpenTime(input_date);
    }
}

Ingredient parseIngredient(string input){
    //Capitalizing the string (e.g. from pork to PORK)
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    //Finding the string in the enum using magic_enum library
    auto ing = magic_enum::enum_cast<Ingredient>(input);
    //If it exists, return it
    if (ing.has_value()) {
        return ing.value();
    } else { //Else return default value
        return Ingredient::DEFAULT;
    }
}

set<Ingredient> getIngredients() {
    string input;
    vector<string> singleStrings;
    getline(cin, input);

    //First remove all whitespaces of the string
    input = removeWhiteSpaces(input);

    std::istringstream ss(input);
    std::string substring;

    //Seperate the string at every comma
    while(getline(ss, substring, ',')) {
        singleStrings.push_back(substring);
    }
    //Turn every string ingredient into a ingredient enum
    set<Ingredient> ingredients;
    for (string element : singleStrings) {
        Ingredient parsed = parseIngredient(element);
        if (parsed == Ingredient::DEFAULT) {
            cout << "Ingredient \"" << element << "\" could not be found." << endl;
        }
        ingredients.insert(parsed);
    }
    return ingredients;
}

bool containsOpeningTime(Canteen canteen, OpenTime opening_time) {
    const OpenTime* opentimes = canteen.getOpeningTimes();
    //Loop over every opening time
    for(int i=0; i<3; i++) {
        OpenTime time = opentimes[i];
        //See if opening time is earlier than desired opening time and closing time later than desired closing time
        if (opening_time.opening_time >= time.opening_time) { //|| opening_time.closing_time <= time.closing_time) {
            return true;
        }
    }
    //If not contained, return false
    return false;
}

set<Canteen> filter(Building currentLocation, int max_distance, OpenTime opening_time, set<Ingredient> excl_ingredients, set<Ingredient> incl_ingredients) {
    set<Canteen> filtered;
    
    for (Canteen canteen : canteens) {
        //Filter for distance
        if(!isWithinRange(max_distance, currentLocation, canteen)) {
            continue;
        }
        //Filter for opening time
        else if(!containsOpeningTime(canteen, opening_time)) {
            continue;
        }
        //Filter for excluded ingredients: (if canteen contains the excluded elements, i.e. the included ingredients array is *not* empty)
        else if(!excl_ingredients.empty() && !(canteen.containsIngredients(excl_ingredients, false)).empty()) {
            continue;
        } 
        //Filter for included ingredients
        else if (!incl_ingredients.empty() && canteen.containsIngredients(incl_ingredients, true).empty()) {
            //If the ingredients do not exist
            continue;
        } else {
            //If canteen passed all tests before, add it to filtered list
            filtered.insert(canteen);
        }
    }
    return filtered;
}

void filterMenu() {
    cout << "Canteen Filter" << endl;

    //Variables
    unsigned short max_distance;
    set<Ingredient> ex_ingredients;
    set<Ingredient> in_ingredients;
    OpenTime opening_time;

    //Distance
    string max_distance_string;
    cout << "Please enter the maximal distance to the canteen (in meters, no decimal places): ";
    getline(cin, max_distance_string);
    //Check if is integer
    max_distance = requestInteger(max_distance_string); //stoi(max_distance_string);
    
    //Opening time
    string input_date = getOpeningTime();
    opening_time = parseOpenTime(input_date);

    //Excluded ingredients
    cout << "Please enter *excluded* ingredients (like this: pork, cabbage, ...): ";
    set<Ingredient> excl_ingredients = getIngredients();

    //Included ingredients
    cout << "Please enter *included* ingredients (like this: beef, coriander, ...): ";
    set<Ingredient> incl_ingredients = getIngredients();

    //Get current location:
    Building locationBuilding = getCurrentLocation();

    //Filter:
    set<Canteen> filteredCanteens = filter(locationBuilding, max_distance, opening_time, excl_ingredients, incl_ingredients);
    
    //Output:
    if(filteredCanteens.empty()) {
        cout << "No canteen matching your preferences found!" << endl;
    } else {
        cout << "The filtered canteens are: " << endl;
        for(Canteen result : filteredCanteens) {
            cout << result.getName() << endl;
        }
    }
}