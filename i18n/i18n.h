#include <iostream>
#include <map>
using namespace std;
#include "translations.h"

class I18N {
    public:
        string gettext(string text, int amount=1);
        string getCurrency(int amount);
    private:
        static char locale[3];
};

string I18N::gettext(string text, int amount) {

}