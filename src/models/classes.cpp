#include "classes.h"

#include "../io/file.h"
#include "../helpers/helpers.h"
#include "../io/console.h"
#include "../proximity/proximity.h"

//LatLng class
LatLng::LatLng() {};
LatLng::LatLng(float latitude, float longitude) : latitude(latitude), longitude(longitude) {};
ostream & operator << (ostream &out, const LatLng &l) {
    out << l.latitude;
    out << ", " << l.longitude << endl;
    return out;
}

//OpenTime class
OpenTime::OpenTime() {};
OpenTime::OpenTime(unsigned short opening_time, unsigned short closing_time) : opening_time(opening_time), closing_time(closing_time) {};
void OpenTime::displayOpenTime() {
    int opening_hour = opening_time / 60;
    int opening_minutes = opening_time % 60;
    int closing_hour = closing_time / 60;
    int closing_minutes = closing_time % 60;

    cout << opening_hour << ":";
    //If we only have 0-9, add another 0 in front 
    cout << formatMinutes(opening_minutes) << "-";
    cout << closing_hour << ":";
    cout << formatMinutes(closing_minutes);
    cout<<"  ";
}

//Building class
Building::Building(string name, LatLng location) : location(location), name(name) {};

LatLng Building::getLocation() const {
    return location;
}

string Building::getName() const {
    return name;
}

//Optionality struct
Optionality::Optionality(bool isOptional, Ingredient ingredient) : isOptional(isOptional), ingredient(ingredient) {};

bool Optionality::operator<(const Optionality& other) const {
    return isOptional < other.isOptional;
}

bool Optionality::operator==(const Optionality& other) const {
    return isOptional == other.isOptional && ingredient == other.ingredient;
}

//Meal Class
Meal::Meal(string name, vector<Optionality> ingredients) : name(name), ingredients(ingredients) {}

string Meal::getName() {
    return name;
}

set<Ingredient> Meal::getIngredients(bool includeOptional) {
    set<Ingredient> ingredients;
    //Loop over all (optional) ingredients of the meal
    for (size_t i = 0; i < this->ingredients.size(); ++i) {
        Optionality optionalityIngredient = this->ingredients[i];
        //If is optional and we should not include optional, just continue loop
        if(!includeOptional && optionalityIngredient.isOptional) {
            continue;
        } else {
            ingredients.insert(optionalityIngredient.ingredient);
        }
    }
    return ingredients;
}

bool Meal::operator<(const Meal& other) const {
    return name < other.name;
}

bool Meal::operator==(const Meal& other) const {
    return name == other.name && ingredients == other.ingredients;
}

//Canteen class
Canteen::Canteen(string name, LatLng location, OpenTime opening_times[3], set<Meal> signature_meals, set<Meal> meals) 
: Building(name, location), signature_meals(signature_meals), meals(meals) {
    //Assign opening times array:
    for (int i = 0; i < 3; i++) {
        this->opening_times[i] = opening_times[i];
    }
   //copy(opening_times, opening_times + 3, this->opening_times);
}

string Canteen::getSignatureMealsList() {
    string result;
    for(Meal meal : signature_meals) {
        result.append(meal.getName());
        result.append(", ");
    }
    //Remove last comma
    result.resize(result.size() - 2);
    return result;
}

void Canteen::display_information()
{
    cout<<"Canteen Name: "<<getName()<<endl;
    printspace(1);
    cout<<"Opening Times: ";
    for(int i=0;i<3;i++) {
        opening_times[i].displayOpenTime();
    }
    printspace(2);
    cout<<"Speciality Dishes: ";
    cout << getSignatureMealsList() << endl;
    printspace(1);
    cout<<"Location: ";
    cout<<getLocation();
    printspace(1);
    cout<<"Nearest Canteen: ";
    cout<<nearestCanteenName(*this) << endl;
}

int Canteen::favourite() {
    return writeFile(getName(), "canteen_favourite.txt");
}

set<Meal> Canteen::getSignatureMeals() {
    return this->signature_meals;
}

set<Meal> Canteen::getMeals() {
    set<Meal> meals = signature_meals;
    meals.insert(this->meals.begin(), this->meals.end());
    return meals;
}

set<Ingredient> Canteen::getIngredients(bool includeOptional) {
    //TODO
    set<Ingredient> ingredients;
    //Loop over all meals
    for(Meal meal : meals) {
        ingredients.insert(meal.getIngredients(includeOptional).begin(), meal.getIngredients(includeOptional).end());
    }
    return ingredients;
}

OpenTime* Canteen::getOpeningTimes() {
    return this->opening_times;
}

set<Meal> Canteen::containsIngredients(set<Ingredient> ingredients, bool includeOptional) {
    set<Meal> matchingMeals;
    //Loop over all meals
    for(Meal meal : meals) {
        //See if the current meals contains any of the specified ingredients:
        bool containsIngredients = setContains(meal.getIngredients(includeOptional), ingredients);
        if(containsIngredients) {
            matchingMeals.insert(meal);
        }
    }
    return matchingMeals;
}

bool Canteen::operator<(const Canteen& other) const {
    return this->getName() < other.getName();
}

bool Canteen::operator==(const Canteen& other) const {
    return this->getName() == other.getName();
}