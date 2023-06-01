#ifndef CANTEEN_H
#define CANTEEN_H

#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <array>
using namespace std;

struct LatLng {
    float latitude;
    float longitude;

    LatLng();
    LatLng(float latitude, float longitude);
    friend ostream & operator << (ostream &out, const LatLng &l);
};

struct OpenTime {
    unsigned short opening_time; //In minutes past midnight
    unsigned short closing_time; //In minutes past midnight

    OpenTime();
    OpenTime(unsigned short opening_time, unsigned short closing_time);
    void displayOpenTime();
};

enum Ingredient {
    DEFAULT,
    PORK,
    BEEF,
    LAMB,
    DUCK,
    NOODLES,
    RICE,
    TOMATOES,
    EGG,
    CABBAGE,
    CORIANDER,
    GARLIC,
    VEGETABLES,
    CHICKEN,
    SOUP,
    VINEGAR,
    SAUCE,
    SEASAME
};

struct Optionality {
    bool isOptional; //Wether ingredient is optional or always added
    Ingredient ingredient;

    Optionality(bool isOptional, Ingredient ingredient);
    //Need to define these because the <set> library needs to use these
    bool operator<(const Optionality& other) const;
    bool operator==(const Optionality& other) const;
};

class Meal  {
    private:
        string name;
        vector<Optionality> ingredients;
    public:
        Meal() {};
        Meal(string name, vector<Optionality> ingredients);
        set<Ingredient> getIngredients(bool includeOptional=true);
        string getName();
        //Need to define these because the <set> library needs to use these
        bool operator<(const Meal& other) const;
        bool operator==(const Meal& other) const;
};

class Building {
    private:
        string name;
        LatLng location;
    public:
        LatLng getLocation() const;
        string getName() const;
        Building() {};
        Building(string name, LatLng location);
};

class Canteen: public Building {
    private:
        //LatLng location;
        //Opening times -> array of opening times -> probably static
        OpenTime opening_times[3]; //No canteen has more than 4 opening times (I think)
        set<Meal> signature_meals;
        set<Meal> meals;
    public:
        Canteen() {};
        Canteen(string name, LatLng location, OpenTime opening_times[3], set<Meal> signature_meals, set<Meal> meals);
        int favourite();
        void display_information();
        OpenTime* getOpeningTimes();
        set<Meal> getSignatureMeals();
        string getSignatureMealsList();
        set<Meal> getMeals();
        set<Ingredient> getIngredients(bool includeOptional=true);
        set<Meal> containsIngredients(set<Ingredient> ingredients, bool includeOptional=true);
        //Need to define these because the <set> library needs to use these
        bool operator<(const Canteen& other) const;
        bool operator==(const Canteen& other) const;
};

#endif