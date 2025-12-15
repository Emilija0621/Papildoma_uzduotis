#include <iostream>
#include <string>
#include <cwctype>
#include <locale>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>

using std::cout;
using std::locale;
using std::ctype;
using std::endl;
using std::vector;
using std::map;
using std::setw;
using std::left;
using std::wcout;
using std::wstring;
using std::wcout;
using std::wofstream;
using std::wifstream;
using std::wstringstream;

#include "funkcijos.h"


wstring sutvarkyti_zodziai(const wstring& zodis){
    wstring rezultatas;
    locale lt("lt_LT.UTF-8");
    const ctype<wchar_t>& facet = use_facet<ctype<wchar_t>>(lt);

       for (wchar_t c : zodis) {
           if (facet.is(std::ctype_base::alpha, c)) {
               rezultatas += facet.tolower(c);
           }
       }
       return rezultatas;
}


vector<wstring> failo_skaitymas(const string& failo_pavadinimas){
    wifstream in(failo_pavadinimas);
    in.imbue(locale("lt_LT.UTF-8"));

    if (!in.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failo_pavadinimas << endl;
        return {};
    }

    vector<wstring> eilutes;
    wstring eilute;

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


void cross_reference_terminalas(const map<wstring, int>& zodziu_skaicius, const map<wstring, vector<int>>& zodziu_eilutes) {
    wcout << L"----- Cross reference lentele -----\n\n";
    wcout << left << setw(15) << L"Žodis" << L"| " << setw(7) << L"Kartai" << L"| " << L"Eilučių nr." << endl;

    wcout << L"-------------------------------------------------------------------------------------\n";

    for (const auto& [zodis, kiekis] : zodziu_skaicius) {
        if (kiekis > 1) {
            wcout << left << setw(15) << zodis << L"| " << setw(7) << kiekis << L"| ";

            for (int nr : zodziu_eilutes.at(zodis)) {
                wcout << nr << L" ";
            }
            wcout << L"\n";
        }
    }
}


void cross_reference_i_faila(const map<wstring, int>& zodziu_skaicius, const map<wstring, vector<int>>& zodziu_eilutes, const string& failo_vardas) {
    wofstream out(failo_vardas);
    out.imbue(locale("lt_LT.UTF-8"));

    if (!out.is_open()) {
        cout << "Nepavyko sukurti failo" << endl;
        return;
    }

    out << L"----- Cross reference lentele -----\n\n";
    out << left << setw(15) << L"Žodis" << L"| " << setw(7) << L"Kartai" << L"| " << L"Eilučių nr." << endl;

    out << L"-------------------------------------------------------------------------------------\n";

    for (const auto& [zodis, kiekis] : zodziu_skaicius) {
        if (kiekis > 1) {
            out << left << setw(15) << zodis << L"| "
                << setw(7) << kiekis << L"| ";

            for (int nr : zodziu_eilutes.at(zodis)) {
                out << nr << L" ";
            }
            out << L"\n";
        }
    }

    out.close();
}

void analizuoti_teksta(const vector<wstring>& eilutes, map<wstring, int>& zodziu_skaicius, map<wstring, vector<int>>& zodziu_eilutes) {
    int eilutes_nr = 0;

    for (const auto& eilute : eilutes) {
        eilutes_nr++;
        wstringstream ss(eilute);
        wstring zodis;

        while (ss >> zodis) {
            wstring tvarkingas = sutvarkyti_zodziai(zodis);

            if (!tvarkingas.empty()) {
                zodziu_skaicius[tvarkingas]++;
                zodziu_eilutes[tvarkingas].push_back(eilutes_nr);
            }
        }
    }
}
