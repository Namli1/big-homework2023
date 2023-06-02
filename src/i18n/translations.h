#ifndef TRANSLATIONS_H
#define TRANSLATIONS_H

//整个模块由**栗思祺**实现

using namespace std;

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
static const unsigned int translation_count = 15;
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
    },
    {
        "Success! Switched language.", {
            {"de", "Erfolg! Sprache geändert."},
            {"zh", "操作成功！切换语言了。"}
        }
    },
    {
        "Welcome to the Tsinghua Canteen Exploration Program", {
            {"de", "Wilkommen zum Tsinghua Kantinen Erkundungs Programm"},
        }
    },
    {
        "Please choose: ", {
            {"de", "Bitte wählen: "},
            {"zh", "请选择: "},
        }
    },
    {
        "**** Main Menu ****", {
            {"de", "**** Hauptmenü ****"},
            {"zh", "**** 主页 ****"},
        }
    },
    {
        "1 - List Canteens", {
            {"de", "1 - Kantinen auflisten"},
            {"zh", "1 - 食堂列表"},
        }
    },
    {
        "2 - Canteen Filter", {
            {"de", "2 - Kantinen Filter"},
            {"zh", "2 - 食堂过滤器"},
        }
    },
    {
        "3 - What is the Closest Canteen?", {
            {"de", "3 - Was ist die näheste Kantine?"},
            {"zh", "3 - 离我最近的食堂是哪个？"},
        }
    },
    {
        "4 - Canteen Recommendation", {
            {"de", "4 - Kantinen Empfehlung"},
            {"zh", "4 - 食堂推荐"},
        }
    },
    {
        "5 - My Canteens", {
            {"de", "5 - Meine Kantinen"},
            {"zh", "5 - 我的食堂"},
        }
    },
    {
        "6 - Language/语言", {
            {"de", "6 - Language/Sprache/语言"},
            {"zh", "6 - Language/语言"},
        }
    },
    {
        "7 - Clear Cache", {
            {"de", "7 - Cache löschen"},
            {"zh", "7 - 清洁缓存"},
        }
    },
};

#endif