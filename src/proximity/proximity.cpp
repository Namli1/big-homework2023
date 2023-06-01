#include "proximity.h"
#include "../data/canteens.h"
#include "../helpers/helpers.h"

#include <cmath>


const float R=6371*pow(10,3); //using float instead of long double saves memory allocation and speeds up calculation time, but yields slightly less accurate result

float convertRadians(float a) //latitude and longitude values are given in degrees, however calculations need these values to be in radians
{
    a=a*M_PI/180;
    return a;
}

Building getCurrentLocation() {
    cout << "Please select your current location: " << endl;
    for(size_t i=0; i<buildings_count; i++) {
        cout << i+1 << " - " << buildings[i].getName() << endl;
    }
    cout << "Your choice: ";
    string choiceStr;
    int choice;
    cin >> choiceStr;
    choice = requestInteger(choiceStr);
    while(!verify(choice, 1, buildings_count)) {
        cout << "Number out of range, please input again: ";
        cin >> choice;
    }
    return buildings[choice-1];
}

float Calculate_Distance(Building x, Building y) //calculating distance between two canteens using Haversine formula, a mathematical formula commonly used for calculating distances between two points on a curved surface
    {
       float x1=convertRadians(x.getLocation().latitude);
       float x2=convertRadians(x.getLocation().longitude);
       float y1=convertRadians(y.getLocation().latitude);
       float y2=convertRadians(y.getLocation().longitude);
        float delta_lat=x1-y1;
        float delta_lon=x2-y2;
        float a=sin(delta_lat/2)*sin(delta_lat/2)+cos(y1)*cos(x1)*pow(sin(delta_lon/2),2);
        float  c=2*atan2(sqrt(a),sqrt(1-a));
        float  result=R*c;
        return result;
}

bool isWithinRange(float distance, Building x, Building y) {
    return Calculate_Distance(x, y) <= distance;
}

float nearestCanteen(Building a) //function to calculate the nearest canteen from current location. iterates through a list of canteens and uses the above defined calculate distance function to find the nearest one.
{
    //list<Canteen> mylist{Qingfen, Guanchou, Zijing, Taoli};
    float nearest=1000000;
    for (size_t i = 0; i < canteen_count; i++) {
        Canteen it = canteens[i];
        float distance2=Calculate_Distance(a, it);

        if(distance2<nearest&&distance2!=0)
        {
            nearest=distance2;
        }
    }
    return nearest;
}

string nearestCanteenName(Building a) //same as above but outputting the name rather than the distance, mainly important for user convenience.
{
    float nearest=1000000;
    string tempname;
    for (size_t i = 0; i < canteen_count; i++) {
        Canteen it = canteens[i];
        float distance2=Calculate_Distance(a, it);

        if(distance2<nearest&&distance2!=0)
        {
            nearest = distance2;
            tempname=it.getName();
        }

    }
    return tempname;
}


Canteen nearestCanteenObject(Building a) //similar to above, this returns the Canteen object closest to the user's current location, this function is used later to write information into text files
{
    float nearest=1000000;
    Canteen t;
    for (size_t i = 0; i < canteen_count; i++) {
        Canteen it = canteens[i];
        float distance2=Calculate_Distance(a, it);

        if(distance2<nearest&&distance2!=0)
        {
            nearest = distance2;
            t=it;
        }
    }
    return t;
}
