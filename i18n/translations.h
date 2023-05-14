struct Translation {
    string msgid; //Message ID (in English)
    map<char[3], string> translations;
};

struct TranslationPlural : public Translation {
    string msg_plural;
    map<char[3], string> translations_many; //Translation for plural = 1
};

static const Translation allTranslations[10] = {
    Translation("Hello", {
        {"de", "Hallo"},
        {"zh", "你好"}
    }),
    TranslationPlural("%s person",
    {
        {"de", "Person"},
        {"zh", "人"}
    },
    
    "%s people",
    {
        {"de", "Personen"},
        {"zh", "人"}
    }),
};