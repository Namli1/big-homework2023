struct Translation {
    string msgid; //Message ID (in English)
    map<string, string> translations;
    string msg_plural;
    map<string, string> plural_translations; //Translation for plural
    
    Translation(string msgid, map<string, string> translations)
        : msgid(msgid), translations(translations) {};
    Translation(string msgid, map<string, string> translations,
        string msg_plural, map<string, string> plural_translations)
        : msgid(msgid), translations(translations), msg_plural(msg_plural), plural_translations(plural_translations) {};
    Translation() {};
};

//All Translations
static const unsigned int translation_count = 4;
static const Translation allTranslations[translation_count] = {
    {
        "Hello, world!", {
            {"de", "Hallo, Welt!"},
            {"fr", "Bonjour le monde!"},
            {"es", "¡Hola mundo!"},
        }
    },
    {
        "Goodbye, world!", {
            {"de", "Auf Wiedersehen, Welt!"},
            {"fr", "Au revoir le monde!"},
            {"es", "¡Adiós mundo!"},
        }
    },
    {
        "person", {
            {"de", "Person"},
            {"zh", "人"},
        }, "people", {
            {"de", "Personen"},
            {"zh", "个人"},
        }
    },
    {
        "person %s in %s", {
            {"de", "Person %s in %s"},
            {"zh", "人 %s 在 %s"},
        }, "people %s in %s", {
            {"de", "Personen %s in %s"},
            {"zh", "个人 %s在%s"},
        }
    }
};