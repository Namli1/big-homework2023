
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

const float R=6371*pow(10,3); //using float instead of long double saves memory allocation and speeds up calculation time, but yields slightly less accurate result
class Location
{
private:
    float lat, lon;
public:
   Location();
   Location(float a,float b);
    ~Location();
    float Calculate_Distance(Location x);
    void display_info();
};

extern Location Qingfen;
extern Location Guanchou;
extern Location Zijing;
extern Location Taoli;
extern Location Teaching_Building_Six;
