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
        //If there is something saved in the file, set the locale
        memcpy(I18N::locale, saved_locale.c_str(), 3);
    } else {
        //Else set default to english
        memcpy(I18N::locale, "en", 3);
    }
    
}

I18N::I18N(char current[3]) {
    // The constructor with a char array argument copies the 3-letter locale code
    memcpy(I18N::locale, current, 3);
}

void I18N::changeLocale(char newLocale[3]) {
    //Change locale in object
    memcpy(I18N::locale, newLocale, 3);
    //Convert char* to string:
    string string_locale = newLocale;
    //Change locale in file, replacing all other file content
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
        //Replace the %s characters with the value of the vector
        output.replace(pos, 2, replacements[i]);
        //Move current position forward
        pos += replacements[i].length();
    }
    return output;
}

// Define the gettext() and getCurrency() methods for the I18N class
string I18N::gettext(string text, int amount, const vector<string>& vars) {
    bool hasVars = !(vars.empty()); //Check if any variables were given -> needs to use insertVariables
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
            } //If is not plural and not equal to defaultLocale
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
                    //Insert variables if any where given
                    return insertVariables(current.msg_plural, vars);
                }
                return current.msg_plural;
            } //If we need to use plural form and locale is not equal to defaultLocale
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
            //Get the last digit of the month
            unsigned short lastDigit = month % 10;
            month /= 10; //Remove last digit
            format[i] = to_string(lastDigit)[0];
        } else if (ch == 'd') {
            //Get last digit of the day
            unsigned short lastDigit = day % 10;
            day /= 10; //Remove last digit
            format[i] = to_string(lastDigit)[0];
        }
    }
    //Re-Reverse the string (so it's in original form again)
    reverse(format.rbegin(), format.rend());
    return format;
}

string I18N::getFormattedDate(unsigned short year, unsigned short month, unsigned short day, string format) {
    if(format.compare("default") == 0) {
        //Get default date format
        string default_format = default_date_formats.at(I18N::locale);
        return formatDate(year, month, day, default_format);
    } else {
        //Else use given format
        return formatDate(year, month, day, format);
    }
}

string I18N::getCurrency(int amount, string currency_code) {
    //Get the converion rate by the currency_code
    float conversion_rate = currency_conversions.at(currency_code);
    //Round to two decimal places
    float rounded = round(amount * conversion_rate * 100) / 100;
    return to_string(rounded);
}


//只用于测试，不是程序的一部分
// void testI18N() {
//     // Call the gettext() method to translate a text string
//     string translated_first = i18n.gettext("Hello, world!");
//     cout << "Translated text: " << translated_first << endl;

//     // Change the locale to "fr" and translate again
//     //char locale[3] = "de";
//     //i18n = I18N(locale);
//     i18n.changeLocale((char*)"zh");
//     vector<string> replacements = {"Ben", "Paris"};
//     string translated = i18n.gettext("person %s in %s", 10, replacements);
//     cout << "Translated text: " << 10 << translated << endl;

//     //Date Format test
//     unsigned short year = 2023;
//     unsigned short month = 5;
//     unsigned short day = 15;
//     string defaultFormat = "default";
//     i18n.changeLocale((char*)"zh");
//     //TODO: This gives me an illegal hardware instruction error
//     cout << i18n.getFormattedDate(year, month, day, defaultFormat) << endl;

//     // Call the getCurrency() method to format a currency amount
//     string currency = i18n.getCurrency(1234, "EUR");
//     cout << "Formatted currency: " << currency << endl;
// }