#include <iostream>
#include <string>
#include <cwctype>
#include <locale>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

#include "funkcijos.h"

using std::cout;
using std::locale;
using std::iswalpha;
using std::towlower;
using std::ctype;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
using std::map;
using std::stringstream;

string sutvarkyti_zodziai(const string& zodis) {
    string rezultatas;
    for (char c : zodis) {
        if (isalpha(c)) {
            rezultatas += tolower(c);
        }
    }
    return rezultatas;
}

vector<string> txt_skaitymas(const string& failo_pavadinimas){
    ifstream in(failo_pavadinimas);
    if (!in.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failo_pavadinimas << endl;
    }
    
    vector<string> eilutes;
    string eilute;
    while (getline(in, eilute)) {
        eilutes.push_back(eilute);
    }

    in.close();
    return eilutes;
}

map<string, Zodziai> zodziu_skaiciavimas(const vector<string>& eilutes) {
    map<string, Zodziai> zodziu_duomenys;
    int eilute_nr = 0;

    for (const auto& eilute : eilutes) {
        eilute_nr++;
        stringstream ss(eilute);
        string zodis;

        while (ss >> zodis) {
            string sutvarkyta = sutvarkyti_zodziai(zodis);
            if (!sutvarkyta.empty()) {
                zodziu_duomenys[sutvarkyta].count++;
                zodziu_duomenys[sutvarkyta].eilutes_nr.insert(eilute_nr);
            }
        }
    }
    return zodziu_duomenys;
}

