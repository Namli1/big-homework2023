#ifndef PROXIMITY_H
#define PROXIMITY_H

//整个模块由**灏谛伦**实现

#include "../models/classes.h"

float convertRadians(float a);

float Calculate_Distance(Building x,Building y);

Building getCurrentLocation();

bool isWithinRange(float distance, Building x, Building y);
float nearestCanteen(Building a);
string nearestCanteenName(Building a);
Canteen nearestCanteenObject(Building a);

#endif