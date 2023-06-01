#ifndef I18N_H
#define I18N_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <map>
#include <array>
#include <vector>
#include <algorithm>

#include "translations.h"

static vector<string> DEFAULT_VECTOR;

// struct TranslationPlural : public Translation {
//     string msg_plural;
//     map<string, string> translations_many; //Translation for plural
    
//     TranslationPlural(string msgid, map<string, string> translations,
//         string msg_plural, map<string, string> translations_many)
//         : Translation(msgid, translations), msg_plural(msg_plural),
//           translations_many(translations_many) {};
// };

//Default Date Formats
static const map<string, string> default_date_formats = {
    {"zh", "yyyy年mm月dd日"},
    {"de", "dd.mm.yyyy"},
    {"en", "mm/dd/yyyy"}
};

//Currency Conversions (to Renminbi) (from https://www.x-rates.com/table/?from=CNY&amount=1, 2023年5月17号)
static const map<string, float> currency_conversions = {
    {"RMB", 1},
    {"EUR", 0.131942},
    {"USD", 0.142941},
    {"YEN", 19.579240},
    {"RM", 0.647018}, //Malaysian Ringgit
    {"INR", 11.773304},
};

// Define the I18N class
class I18N {
    private:
        static char locale[3];
        static char default_locale[3];
        string insertVariables(string text, const vector<string>& replacements);
        string formatDate(unsigned short year, unsigned short month, unsigned short day, string format);
    public:
        string gettext(string text, int amount=1, const vector<string>& vars=DEFAULT_VECTOR);
        string getCurrency(int amount, string currency_code);
        string getFormattedDate(unsigned short year, unsigned short month, unsigned short day, string format="default");
        I18N();
        I18N(char current[3]);
        static void changeLocale(char newLocale[3]);
};


#endif