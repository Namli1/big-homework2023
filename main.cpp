#include <iostream>
using namespace std;
#include "src/global/global.h"
#include "src/io/console.h"

#include "src/io/menus.h"

int main() {
    changeColor();
    cout << i18n.gettext("Welcome to the Tsinghua Canteen Exploration Program") << endl;
    mainMenu();
    return 0;
}