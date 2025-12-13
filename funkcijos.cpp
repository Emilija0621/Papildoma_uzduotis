#include <iostream>
#include <string>
#include <cwctype>
#include <locale>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>

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
using std::setw;
using std::left;
using std::ofstream;


string sutvarkyti_zodziai(const string& zodis) {
    string rezultatas;
    for (char c : zodis) {
        if (isalpha(c)) {
            rezultatas += tolower(c);
        }
    }
    return rezultatas;
}

vector<string> failo_skaitymas(const string& failo_pavadinimas){
    ifstream in(failo_pavadinimas);
    if (!in.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failo_pavadinimas << endl;
        return {};
    }
    
    vector<string> eilutes;
    string eilute;
    
    while (getline(in, eilute)) {
        if (!eilute.empty()) {
            eilutes.push_back(eilute);
        }
    }
    if (eilutes.empty()) {
        cout << "Failas " << failo_pavadinimas << " yra tuščias" << endl;
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


void cross_reference_terminalas(const map<string, Zodziai>& zodziai) {
    cout << "----- Cross reference lentele -----\n\n";

    cout << setw(15) << left << "Žodis " << "| " << setw (7) << left << "Kartai " << "| " << left << "Eilučių nr." << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    for (const auto& [zodis, duomenys] : zodziai) {
        if (duomenys.count > 1) {
            cout << setw(13) << left << zodis << " | " << setw(6) << left << duomenys.count << " | ";

            for (int nr : duomenys.eilutes_nr) {
                cout << nr << " ";
            }
            cout << endl;
        }
    }
}


void cross_reference_i_faila(const map<string, Zodziai>& zodziai, const string& failo_vardas) {

    ofstream out(failo_vardas);
    if (!out.is_open()) {
        cout << "Nepavyko sukurti failo" << endl;
        return;
    }

    out << "----- Cross reference lentele -----\n\n";

    out << setw(15) << left << "Žodis " << "| " << setw (7) << left << "Kartai " << "| " << left << "Eilučių nr." << endl;
    out << "-------------------------------------------------------------------------------------" << endl;
    
    for (const auto& [zodis, duomenys] : zodziai) {
        if (duomenys.count > 1) {
            out << setw(13) << left << zodis << " | " << setw(6) << left << duomenys.count << " | ";

            for (int nr : duomenys.eilutes_nr) {
                out << nr << " ";
            }
            out << endl;
        }
    }

    out.close();
}

