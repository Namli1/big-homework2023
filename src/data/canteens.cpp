#include "canteens.h"

#include <algorithm>
#include "../helpers/helpers.h"

using namespace std;

//Normal opening times: 6:30 - 9:00, 11:00 - 13:00, 17:00 - 19:00
OpenTime opentimes[3] = {OpenTime(390, 540), OpenTime(660, 780), OpenTime(1020, 1140)};
OpenTime special_opentimes[3] = {OpenTime(930, 540), OpenTime(660, 780), OpenTime(1020, 1410)};
set<Meal> qingfen_signature = {
    Meal("BiangBiangMian", {
        Optionality(false, Ingredient::BEEF),
        Optionality(false, Ingredient::EGG),
        Optionality(false, Ingredient::NOODLES),
        Optionality(false, Ingredient::TOMATOES),
    }
)};
set<Meal> guanchou_signature = {
    Meal("Hand-cut Noodles", {
        Optionality(true, Ingredient::BEEF),
        Optionality(true, Ingredient::GARLIC),
        Optionality(false, Ingredient::NOODLES),
        Optionality(false, Ingredient::VEGETABLES),
    }
)};
set<Meal> zijing_signature = {
    Meal("Hainan Chicken Rice", {
        Optionality(false, Ingredient::CHICKEN),
        Optionality(false, Ingredient::RICE),
        Optionality(false, Ingredient::VEGETABLES),
        Optionality(true, Ingredient::SOUP),
    }
)};
set<Meal> taoli_signature = {
    Meal("Korean Bibimbap", {
        Optionality(true, Ingredient::BEEF),
        Optionality(true, Ingredient::EGG),
        Optionality(false, Ingredient::RICE),
        Optionality(false, Ingredient::VEGETABLES),
    }
)};

set<Meal> qingfen_meals = {
    Meal("Peking Duck",
    {
        Optionality(false, Ingredient::DUCK),
        Optionality(false, Ingredient::RICE),
        Optionality(false, Ingredient::CABBAGE),
    })
};
set<Meal> guanchou_meals = {
    Meal("Dumplings",
    {
        Optionality(false, Ingredient::PORK),
        Optionality(false, Ingredient::VEGETABLES),
        Optionality(true, Ingredient::VINEGAR),
    })
};
set<Meal> zijing_meals = {
    Meal("Malatang",
    {
        Optionality(false, Ingredient::SAUCE),
        Optionality(false, Ingredient::NOODLES),
        Optionality(false, Ingredient::BEEF),
         Optionality(false, Ingredient::VEGETABLES),
         Optionality(false, Ingredient::EGG),
    })
};
set<Meal> taoli_meals = {
    Meal("Donburi",
    {
        Optionality(false, Ingredient::CHICKEN),
        Optionality(false, Ingredient::RICE),
        Optionality(false, Ingredient::CABBAGE),
        Optionality(true,Ingredient::SEASAME)
    })
};

set<Meal> demo_meals = {
    Meal("Fried Noodles",
        {
            Optionality(false, Ingredient::EGG),
            Optionality(false, Ingredient::TOMATOES),
            Optionality(true, Ingredient::PORK),
            Optionality(true, Ingredient::BEEF),
            Optionality(true, Ingredient::NOODLES),
        }),
    Meal("Fried Rice",
        {
            Optionality(false, Ingredient::EGG),
            Optionality(false, Ingredient::TOMATOES),
            Optionality(true, Ingredient::PORK),
            Optionality(true, Ingredient::BEEF),
            Optionality(true, Ingredient::RICE),
        })
};

const size_t canteen_count = 4;
Canteen canteens[canteen_count] = {
    Canteen("Qingfen", LatLng(40.00563834543003, 116.32985559225531), opentimes, qingfen_signature, qingfen_meals),
    Canteen("Guanchou", LatLng(40.00688482529249, 116.32177714507415), opentimes, guanchou_signature, guanchou_meals),
    Canteen("Zijing", LatLng(40.01211659204893, 116.32784164272837), opentimes, zijing_signature, zijing_meals),
    Canteen("Taoli", LatLng(40.01106416089835, 116.32614579635658), special_opentimes, taoli_signature, taoli_meals),
};

const size_t non_canteen_buildings_count = 1;
Building non_canteen_buildings[non_canteen_buildings_count] = {
    Building("Teaching Building 6", LatLng(40.00286861247089, 116.3298125318402)),
};

const size_t buildings_count = canteen_count + non_canteen_buildings_count;
Building* buildings = mergeArrays<Building>(canteens, canteen_count, non_canteen_buildings, non_canteen_buildings_count);
