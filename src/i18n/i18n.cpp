#include "i18n.h"

#include "../io/file.h"

// Define the static locale member variable
char I18N::default_locale[3] = "en";
char I18N::locale[3] = "en";

// Define the constructors for the I18N class
I18N::I18N() {
    // The default constructor sets the locale to "de"
    string saved_locale = readFile("current_locale.txt");
    cout << "Read locale: " << saved_locale << endl;
    if(!saved_locale.empty()) {
        memcpy(I18N::locale, saved_locale.c_str(), 3);
    } else {
        //Set default to english
        memcpy(I18N::locale, "en", 3);
    }
    
}

I18N::I18N(char current[3]) {
    // The constructor with a char array argument copies the 3-letter locale code
    memcpy(I18N::locale, current, 3);
}

void I18N::changeLocale(char newLocale[3]) {
    memcpy(I18N::locale, newLocale, 3);
    string string_locale = newLocale;
    writeFile(string_locale, "current_locale.txt", true);
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
string I18N::gettext(string text, int amount, const vector<string>& vars) {
    bool hasVars = !(vars.empty());
    bool isDefaultLocale = strcmp(I18N::locale, I18N::default_locale) == 0;
    for(int i=0; i<translation_count; i++) { // loop over the translations
        Translation current = allTranslations[i];
        //If we found corresponding entry
        if(text.compare(current.msgid) == 0) {
            //If it has no plural and the locale is the defaultLocale
            if(amount == 1 && isDefaultLocale) {
                if(hasVars) {
                    //Insert variables if any where given
                    return insertVariables(current.msgid, vars);
                }
                //Else return the message directly
                return current.msgid;
            } //If is plural and not equal to defaultLocale
            else if (amount == 1) {
                if(hasVars) {
                    //Insert variables if any where given
                    return insertVariables(current.translations[I18N::locale], vars);
                }
                //Else return the translated message
                return current.translations[I18N::locale];
            }
            //If amount != 1, use plural form 
            else if(isDefaultLocale) {
                if(hasVars) {
                    return insertVariables(current.msg_plural, vars);
                }
                return current.msg_plural;
            } //If we need to use plural form and is not equal to defaultLocale
             else {
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
    //Reversing the format, so that if format contains only yy instead of yyyy,
    //the output will be 23 (for 2023), instead of 20 (output last digits, not first)
    reverse(format.rbegin(), format.rend());
    for (int i = 0; i < format.length(); i++) {
        // Loop over every character in the reversed string
        char ch = format[i];
        if(ch == 'y') {
            //Always get the last digit of the year
            unsigned short lastDigit = year % 10;
            year /= 10; //Remove last digit
            format[i] = to_string(lastDigit)[0];
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
        //Get default date format
        string default_format = default_date_formats.at(I18N::locale);
        return formatDate(year, month, day, default_format);
    } else {
        return formatDate(year, month, day, format);
    }
}

string I18N::getCurrency(int amount, string currency_code) {
    // not implemented in this example
    float conversion_rate = currency_conversions.at(currency_code);
    //Round to two decimal places
    float rounded = round(amount * conversion_rate * 100) / 100;
    return to_string(rounded);
}