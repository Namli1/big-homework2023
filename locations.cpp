#include "latlng.h"

Location::Location()
{

}
Location::~Location()
{

}
Location::Location(float a,float b)
    {
        lat=a*M_PI/180; //converting lat and long into radians, as calculations all use radians, not degrees which these coordinates are usually displayed in.
        lon=b*M_PI/180;
    }
       float Location::Calculate_Distance(Location x)
    {
        float delta_lat=x.lat-lat;
        float delta_lon=x.lon-lon;
        float a=sin(delta_lat/2)*sin(delta_lat/2)+cos(lat)*cos(x.lat)*pow(sin(delta_lon/2),2);
        float  c=2*atan2(sqrt(a),sqrt(1-a));
        float  result=R*c;
        return result;

    }
void Location::display_info()
{
    cout<<"Coordinates: ("<<lat*180/M_PI<<","<<lon*180/M_PI<<")"<<endl;
}
Location Qingfen(40.00563834543003, 116.32985559225531);
Location Guanchou(40.00688482529249, 116.32177714507415);
Location Zijing(40.01211659204893, 116.32784164272837);
Location Taoli(40.01106416089835, 116.32614579635658);
Location Teaching_Building_Six(40.00286861247089, 116.3298125318402);
