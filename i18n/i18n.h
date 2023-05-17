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
        const string gettext(string text, int amount=1, const vector<string>& vars=DEFAULT_VECTOR);
        string getCurrency(int amount, string currency_code);
        string getFormattedDate(unsigned short year, unsigned short month, unsigned short day, string format="default");
        I18N(char current[3]);
        I18N();
        static void changeLocale(char newLocale[3]) {
            memcpy(I18N::locale, newLocale, 3);
        }
};

// Define the static locale member variable
char I18N::default_locale[3] = "en";
char I18N::locale[3] = "en";

// Define the constructors for the I18N class
I18N::I18N() {
    // The default constructor sets the locale to "de"
    memcpy(I18N::locale, "en", 3);
}

I18N::I18N(char current[3]) {
    // The constructor with a char array argument copies the 3-letter locale code
    memcpy(I18N::locale, current, 3);
}

string I18N::insertVariables(string text, const vector<string>& replacements) {
    string& output = text;
    size_t pos = 0; //Current character position in string
    for (int i = 0; i < replacements.size(); i++) {
        pos = output.find("%s", pos); //Position of next %s sequence
        if (pos == string::npos) { //string::npos represents the maximum value for size_t and indicates an invalid or non-existent position in a string
            break; //Break if no %s is found
        }
        output.replace(pos, 2, replacements[i]);
        pos += replacements[i].length();
    }
    return output;
}

// Define the gettext() and getCurrency() methods for the I18N class
const string I18N::gettext(string text, int amount, const vector<string>& vars) {
    bool hasVars = !(vars.empty());
    cout << hasVars << endl;
    bool isDefaultLocale = strcmp(I18N::locale, I18N::default_locale) == 0;
    for(int i=0; i<translation_count; i++) { // loop over the translations
        Translation current = allTranslations[i];
        if(text.compare(current.msgid) == 0) {
            if(amount == 1 && isDefaultLocale) {
                if(hasVars) {
                    return insertVariables(current.msgid, vars);
                }
                return current.msgid;
            } else if (amount == 1) {
                if(hasVars) {
                    return insertVariables(current.translations[I18N::locale], vars);
                }
                return current.translations[I18N::locale];
            }
            //If amount != 1, use plural form 
            else if(isDefaultLocale) {
                if(hasVars) {
                    return insertVariables(current.msg_plural, vars);
                }
                return current.msg_plural;
            } else {
                if(hasVars) {
                    return insertVariables(current.plural_translations[I18N::locale], vars);
                }
                return current.plural_translations[I18N::locale];
            }
        }
    }
    return text; //Fallback if no translation found
}

string I18N::formatDate(unsigned short year, unsigned short month, unsigned short day, string format) {
    reverse(format.rbegin(), format.rend());
    for (int i = 0; i < format.length(); i++) {
        // Loop over every character in the reversed string
        char ch = format[i];
        if(ch == 'y') {
            unsigned short lastDigit = year % 10;
            year /= 10;
            // //Check that we're not at the last digit yet
            // if(year == 0) {
            //     //If we are at last digit, just return 00
            // } else {
            format[i] = to_string(lastDigit)[0];
            //}
        } else if (ch == 'm') {
            unsigned short lastDigit = month % 10;
            month /= 10;
            format[i] = to_string(lastDigit)[0];
        } else if (ch == 'd') {
            unsigned short lastDigit = day % 10;
            day /= 10;
            format[i] = to_string(lastDigit)[0];
        }
    }
    reverse(format.rbegin(), format.rend());
    return format;
}

string I18N::getFormattedDate(unsigned short year, unsigned short month, unsigned short day, string format) {
    //return "Hello";
    if(format.compare("default") == 0) {
        string default_format = default_date_formats.at(I18N::locale);
        return formatDate(year, month, day, default_format);
    } else {
        return formatDate(year, month, day, format);
    }
}

string I18N::getCurrency(int amount, string currency_code) {
    // not implemented in this example
    float conversion_rate = currency_conversions.at(currency_code);
    float rounded = round(amount * conversion_rate * 100) / 100;
    return to_string(rounded);
    //return "Unimplemented";
}