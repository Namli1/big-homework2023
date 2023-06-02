#ifndef MENUS_H //making sure multiple definitions don't occur in our main source file, preventing double declarations of things like static variables, types and enums
#define MENUS_H

//由灏谛伦实现（除了i18nMenu()意外）

const int num_cols=100;

//All menu functions;

void displayLocationMenu();

void displayMainMenu();

void mainMenu();

void displayNearestMenu();

void displayLocationSelectionMenu();

void displayCanteens();

void displayFavouriteMenu();

//由栗思祺实现
void i18nMenu();

#endif
