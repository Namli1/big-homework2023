using namespace std;

//Main classes
class Canteen;
class Meal;
struct Filter; //Struct or class???

//Helpers
enum Ingredient;
struct Optionality;
struct LatLng;

class Canteen {
    private:
        string name;
        LatLng location;
        //Opening times -> array of opening times -> probably static
        OpenTime opening_times[4]; //No canteen has more than 4 opening times (I think)
}

struct Optionality {
    bool is_optional; //Wether ingredient is optional or always added
    Ingredient ingredient;
}

enum Ingredient {
    Pork,
    Beef,
    Lamb,
    
}