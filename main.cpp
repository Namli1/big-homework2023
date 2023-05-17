#include <iostream>
#include <cstring>
#include <cmath>
#include <map>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;
#include "i18n/i18n.h"

int main() {
    // Create an instance of the I18N class with the "de" locale
    I18N i18n;

    // Call the gettext() method to translate a text string
    string translated_first = i18n.gettext("Hello, world!");
    cout << "Translated text: " << translated_first << endl;

    // Change the locale to "fr" and translate again
    //char locale[3] = "de";
    //i18n = I18N(locale);
    i18n.changeLocale("zh");
    vector<string> replacements = {"Alice", "Paris"};
    string translated = i18n.gettext("person %s in %s", 10, replacements);
    cout << "Translated text: " << 10 << translated << endl;

    //Date Format test
    unsigned short year = 2023;
    unsigned short month = 5;
    unsigned short day = 15;
    string defaultFormat = "default";
    i18n.changeLocale("zh");
    //TODO: This gives me an illegal hardware instruction error
    cout << i18n.getFormattedDate(year, month, day, defaultFormat) << endl;
    // cout << "Formatted default date: " << formattedDefaultDate << endl;

    // Call the getCurrency() method to format a currency amount
    string currency = i18n.getCurrency(1234, "EUR");
    cout << "Formatted currency: " << currency << endl;

    return 0;
}
