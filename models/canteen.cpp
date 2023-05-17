struct LatLng {
    float latitude;
    float longitude;
}

struct OpenTime {
    int opening_time; //In minutes past midnight
    int closing_time; //In minutes past midnight
}

class Canteen {
    private:
        string name;
        LatLng location;
        //Opening times -> array of opening times -> probably static
        OpenTime opening_times[4]; //No canteen has more than 4 opening times (I think)
    public:
        void display() {
            cout << "Name: " << name << endl;
        }
}
